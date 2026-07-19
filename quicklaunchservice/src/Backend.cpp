#include "Backend.hpp"

#include "ProfileSerializer.hpp"
#include "shared/ProfileConfigNames.hpp"
#include "shared/ProfileConfigPath.hpp"

#include <QCursor>
#include <QDebug>
#include <QGuiApplication>
#include <QHotkey>
#include <QRegion>
#include <boost/property_tree/json_parser.hpp>
#include <filesystem>

Backend::Backend( QObject* parent ) : QObject( parent ) {
    this->setProfilesFromConfigFile();
    this->connectShortcutsToProfiles();
    connect( this, &Backend::hideWindow, this, [ this ]() { this->_currentProfile = nullptr; } );
}

void Backend::setProfilesFromConfigFile() {
    const auto profileConfigPath = ProfileConfig::filePath().toStdString();
    if ( !std::filesystem::exists( profileConfigPath ) ) {
        qWarning().noquote() << "Could not find file:"
                             << QString::fromStdString( profileConfigPath );
        return;
    }

    ptree tree;
    boost::property_tree::read_json( profileConfigPath, tree );

    this->_profiles.clear();

    if ( const auto profiles = tree.get_child_optional( ProfileConfig::Key::Profile::Key ) ) {
        for ( const auto profile : *profiles ) {
            if ( const auto serializedProfile =
                     ProfileSerializer::serializedProfile( profile.second ) ) {
                this->_profiles.push_back( *serializedProfile );
            }
        }
    } else {
        qWarning().noquote() << "Could not find property '" +
                                    QString( ProfileConfig::Key::Profile::Key ) + "'";
    }
}

void Backend::connectShortcutsToProfiles() {
    for ( auto profile : this->_profiles ) {
        auto* hotkey = new QHotkey( QKeySequence( profile->shortcut() ), true, this );

        connect( hotkey, &QHotkey::activated, this, [ this, profile ]() {
            this->toggleProfile( profile );
        } );
    }
}

void Backend::launchExecutionTargetByIndex( const qsizetype index ) {
    if ( this->_currentProfile ) {
        if ( auto executionTarget = this->_currentProfile->executionTargetAt( index ) ) {
            executionTarget->startProcess();
        } else {
            qWarning().noquote() << "Could not find execution target of profile '" +
                                        this->_currentProfile->name() + "': index out of range";
        }
        this->_currentProfile = nullptr;
    }

    emit this->hideWindow();
}

void Backend::toggleProfile( Profile* profile ) {
    const auto newCurrentScreen = this->newCurrentScreen();
    if ( profile == this->_currentProfile ) {
        if ( newCurrentScreen == this->_currentProfileScreen ) {
            emit this->hideWindow();
            this->_currentProfile = nullptr;
        } else {
            this->_currentProfileScreen = newCurrentScreen;
            emit this->showProfile( profile );
        }
    } else {
        this->_currentProfile = profile;
        if ( newCurrentScreen != this->_currentProfileScreen ) {
            this->_currentProfileScreen = newCurrentScreen;
        }
        emit this->showProfile( profile );
    }
}

QPoint Backend::contentPosition( const qsizetype width, const qsizetype height ) const {
    if ( this->_currentProfile == nullptr || this->_currentProfileScreen == nullptr ) {
        return QPoint( 0, 0 );
    }

    const auto geo = this->_currentProfileScreen->geometry();
    const auto margin = this->_currentProfile->view()->margin();

    qsizetype x = 0;
    if ( this->_currentProfile->view()->horizontalAnchor() ==
         ProfileConfig::Value::Profile::View::HorizontalAnchor::Left ) {
        x = margin;
    } else if ( this->_currentProfile->view()->horizontalAnchor() ==
                ProfileConfig::Value::Profile::View::HorizontalAnchor::Center ) {
        x = geo.width() / 2 - width / 2;
    } else if ( this->_currentProfile->view()->horizontalAnchor() ==
                ProfileConfig::Value::Profile::View::HorizontalAnchor::Right ) {
        x = geo.width() - width - margin;
    }

    qsizetype y = 0;
    if ( this->_currentProfile->view()->verticalAnchor() ==
         ProfileConfig::Value::Profile::View::VerticalAnchor::Top ) {
        y = margin;
    } else if ( this->_currentProfile->view()->verticalAnchor() ==
                ProfileConfig::Value::Profile::View::VerticalAnchor::Center ) {
        y = geo.height() / 2 - height / 2;
    } else if ( this->_currentProfile->view()->verticalAnchor() ==
                ProfileConfig::Value::Profile::View::VerticalAnchor::Bottom ) {
        y = geo.height() - height - margin;
    }

    return QPoint( x, y );
}

qsizetype Backend::availableContentWidth() {
    const auto screenWidth = this->_currentProfileScreen
                                 ? this->_currentProfileScreen->geometry().width()
                                 : this->newCurrentScreen()->geometry().width();
    const auto margin = this->_currentProfile ? this->_currentProfile->view()->margin() : 0;
    return screenWidth - margin * 2;
}

qsizetype Backend::availableContentHeight() {
    const auto screenHeight = this->_currentProfileScreen
                                  ? this->_currentProfileScreen->geometry().height()
                                  : this->newCurrentScreen()->geometry().height();
    const auto margin = this->_currentProfile ? this->_currentProfile->view()->margin() : 0;
    return screenHeight - margin * 2;
}

void Backend::maskWindow( QQuickWindow* window, QRect contentRect ) {
    window->setMask( QRegion( contentRect ) );
}

QRect Backend::currentScreenRect() const {
    if ( this->_currentProfileScreen ) {
        return this->_currentProfileScreen->geometry();
    }
    return this->newCurrentScreen()->geometry();
}

QScreen* Backend::newCurrentScreen() const {
    QScreen* screen = QGuiApplication::screenAt( QCursor::pos() );
    if ( !screen ) {
        return QGuiApplication::primaryScreen();
    }
    return screen;
}

QString Backend::executionTargetViewSource( ProfileView* profileView ) {
    namespace ViewValue = ProfileConfig::Value::Profile::View;
    if ( profileView->mode() == ViewValue::Mode::List ) {
        if ( profileView->wrapMode() == ViewValue::WrapMode::Grid ) {
            return "qml/ExecutionTarget/ListGridView.qml";
        } else {
            return "qml/ExecutionTarget/ListScrollView.qml";
        }
    } else {
        if ( profileView->wrapMode() == ViewValue::WrapMode::Grid ) {
            if ( profileView->flowDirection() == ViewValue::FlowDirection::Vertical ) {
                return "qml/ExecutionTarget/VerticalIconGridView.qml";
            } else {
                return "qml/ExecutionTarget/HorizontalIconGridView.qml";
            }
        } else {
            if ( profileView->flowDirection() == ViewValue::FlowDirection::Vertical ) {
                return "qml/ExecutionTarget/VerticalIconScrollView.qml";
            } else {
                return "qml/ExecutionTarget/HorizontalIconScrollView.qml";
            }
        }
    }
}
