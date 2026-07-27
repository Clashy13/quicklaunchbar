#include "ProfileManager.hpp"

#include "QmlExecutionTarget.hpp"
#include "QmlProfile.hpp"
#include "shared/models/ExecutionTarget.hpp"
#include "shared/models/GroupExecutionTarget.hpp"
#include "shared/models/SingleExecutionTarget.hpp"
#include "shared/models/Uri.hpp"
#include "shared/models/UriExecutionTarget.hpp"
#include "shared/serializer/ProfileConfigSerializer.hpp"

#include <QDesktopServices>
#include <QHotkey>
#include <QProcess>
#include <QUrl>
#include <qtypes.h>
#include <vector>

ProfileManager::ProfileManager( QObject* parent )
    : QObject( parent ), _profiles( std::move( Serializer::ProfileConfigSerializer::load() ) ) {
    this->setQmlProfiles();
    this->connectShortcutsToProfiles();
}

void ProfileManager::launchExecutionTargetByIndex( const qsizetype index ) {
    if ( this->hasCurrentProfile() ) {
        this->startExecutionTargetProcess( index );
        this->currentProfileIndex = -1;
    }
}

void ProfileManager::connectShortcutsToProfiles() {
    for ( qsizetype i = 0; i < this->_profiles.size(); ++i ) {
        if ( this->_profiles.at( i ).enabled ) {
            auto* hotkey =
                new QHotkey( QKeySequence( this->_profiles.at( i ).shortcut ), true, this );
            connect( hotkey, &QHotkey::activated, this, [ this, i ]() {
                emit this->toggleProfile( i );
            } );
        }
    }
}

void ProfileManager::setQmlProfiles() {
    for ( const auto& profile : this->_profiles ) {
        const auto viewSource = ProfileManager::executionTargetViewSource( profile.view );
        QList<QmlExecutionTarget*> qmlExecutionTargets;
        for ( const auto& executionTarget : profile.executionTargets ) {
            const auto executionTargetName = executionTarget->name;
            QList<QUrl> iconUrls;
            for ( const auto& iconSource : executionTarget->iconSources ) {
                iconUrls.push_back( ProfileManager::iconSourceUrl( iconSource ) );
            }
            qmlExecutionTargets.push_back(
                new QmlExecutionTarget( executionTarget->name, iconUrls ) );
        }
        this->_qmlProfiles.push_back(
            new QmlProfile( profile.name, viewSource, qmlExecutionTargets ) );
    }
}

QUrl ProfileManager::iconSourceUrl( const Models::ExecutionTarget::IconSource& iconSource ) {
    using Type = Models::ExecutionTarget::IconSource::Type;
    switch ( iconSource.type ) {
        case Type::Theme:
            return QUrl( "image://themeicons/" + iconSource.value );
        case Type::FromFile:
            return QUrl( "image://fileicons" + iconSource.value );
        case Type::Image:
            return QUrl( "image:/" + iconSource.value );
        case Type::Resource:
            return QUrl( "qrc:/icons/" + iconSource.value + ".svg" );
    }
}

QString
ProfileManager::executionTargetViewSource( const Models::Profile::ProfileView& profileView ) {
    using ProfileView = Models::Profile::ProfileView;
    if ( profileView.mode == ProfileView::Mode::List ) {
        if ( profileView.wrapMode == ProfileView::WrapMode::Grid ) {
            return "qml/ExecutionTarget/ListGridView.qml";
        } else {
            return "qml/ExecutionTarget/ListScrollView.qml";
        }
    } else {
        if ( profileView.wrapMode == ProfileView::WrapMode::Grid ) {
            if ( profileView.flowDirection == ProfileView::FlowDirection::Vertical ) {
                return "qml/ExecutionTarget/VerticalIconGridView.qml";
            } else {
                return "qml/ExecutionTarget/HorizontalIconGridView.qml";
            }
        } else {
            if ( profileView.flowDirection == ProfileView::FlowDirection::Vertical ) {
                return "qml/ExecutionTarget/VerticalIconScrollView.qml";
            } else {
                return "qml/ExecutionTarget/HorizontalIconScrollView.qml";
            }
        }
    }
}

void ProfileManager::startExecutionTargetProcess( qsizetype index ) {
    if ( !this->hasCurrentProfile() ) {
        return;
    }

    using Type = Models::ExecutionTarget::ExecutionTarget::Type;

    const auto& executionTarget =
        this->_profiles.at( this->currentProfileIndex ).executionTargets.at( index );
    switch ( executionTarget->type ) {
        case Type::DesktopApplication:
        case Type::ExecutableFile:
        case Type::Command: {
            const auto& singleExecutionTarget =
                static_cast<Models::ExecutionTarget::SingleExecutionTarget*>(
                    executionTarget.get() );
            ProfileManager::startSingleProcess( singleExecutionTarget->command );
            break;
        }
        case Type::OpenFile: {
            const auto& uriExecutionTarget =
                static_cast<Models::ExecutionTarget::UriExecutionTarget*>( executionTarget.get() );
            QDesktopServices::openUrl( QUrl::fromLocalFile( uriExecutionTarget->uri ) );
            break;
        }
        case Type::OpenUrl: {
            const auto& uriExecutionTarget =
                static_cast<Models::ExecutionTarget::UriExecutionTarget*>( executionTarget.get() );
            QDesktopServices::openUrl( QUrl( uriExecutionTarget->uri ) );
            break;
        }
        case Type::Group: {
            const auto& groupExecutionTarget =
                static_cast<Models::ExecutionTarget::GroupExecutionTarget*>(
                    executionTarget.get() );
            for ( const auto& command : groupExecutionTarget->commands ) {
                ProfileManager::startSingleProcess( command );
            }
            for ( const auto& uri : groupExecutionTarget->uriList ) {
                using UriType = Models::ExecutionTarget::Uri::Type;
                switch ( uri.type ) {
                    case UriType::File:
                        QDesktopServices::openUrl( QUrl::fromLocalFile( uri.value ) );
                        break;
                    case UriType::Url:
                        QDesktopServices::openUrl( QUrl( uri.value ) );
                        break;
                }
            }
            break;
        }
    }
}

void ProfileManager::startSingleProcess( const Models::ExecutionTarget::Command& command ) {
    const bool success = QProcess::startDetached( command.program, command.arguments );
    if ( !success ) {
        qWarning().noquote() << "Process failed:" << command.program
                             << command.arguments.join( " " );
    }
}