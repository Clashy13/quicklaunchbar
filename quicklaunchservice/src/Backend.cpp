#include "Backend.hpp"

#include "ProfileManager.hpp"
#include "shared/models/ProfileView.hpp"

#include <QCursor>
#include <QDebug>
#include <QGuiApplication>
#include <QRegion>

namespace Service {

    Backend::Backend( QObject* parent ) : QObject( parent ) {
        connect( this, &Backend::hideWindow, this, [ this ]() {
            this->_profileManager.currentProfile = nullptr;
        } );
        connect( &this->_profileManager,
                 &ProfileManager::toggleProfile,
                 this,
                 &Backend::toggleProfile );
    }

    void Backend::launchExecutionTargetByIndex( const qsizetype index ) {
        this->_profileManager.launchExecutionTargetByIndex( index );
        emit this->hideWindow();
    }

    void Backend::toggleProfile( Models::Profile* profile ) {
        const auto newCurrentScreen = this->newCurrentScreen();
        if ( profile == this->_profileManager.currentProfile ) {
            if ( newCurrentScreen == this->_currentProfileScreen ) {
                emit this->hideWindow();
                this->_profileManager.currentProfile = nullptr;
            } else {
                this->_currentProfileScreen = newCurrentScreen;
                emit this->showProfile( this->_profileManager.currentProfile );
            }
        } else {
            this->_profileManager.currentProfile = profile;
            if ( newCurrentScreen != this->_currentProfileScreen ) {
                this->_currentProfileScreen = newCurrentScreen;
            }
            emit this->showProfile( this->_profileManager.currentProfile );
        }
    }

    QPoint Backend::contentPosition( const qsizetype width, const qsizetype height ) const {
        if ( this->_profileManager.currentProfile == nullptr ||
             this->_currentProfileScreen == nullptr ) {
            return QPoint( 0, 0 );
        }

        const auto view = this->_profileManager.currentProfile->view();
        const auto geo = this->_currentProfileScreen->geometry();
        const auto margin = view.margin;

        using ProfileView = Shared::Models::Profile::ProfileView;

        qsizetype x = 0;
        switch ( view.position ) {
            case ProfileView::Position::TopLeft:
            case ProfileView::Position::Left:
            case ProfileView::Position::BottomLeft:
                x = x = margin;
                break;
            case ProfileView::Position::Top:
            case ProfileView::Position::Center:
            case ProfileView::Position::Bottom:
                x = geo.width() / 2 - width / 2;
                break;
            case ProfileView::Position::TopRight:
            case ProfileView::Position::Right:
            case ProfileView::Position::BottomRight:
                x = geo.width() - width - margin;
                break;
        }

        qsizetype y = 0;
        switch ( view.position ) {
            case ProfileView::Position::TopLeft:
            case ProfileView::Position::Top:
            case ProfileView::Position::TopRight:
                y = margin;
                break;
            case ProfileView::Position::Left:
            case ProfileView::Position::Center:
            case ProfileView::Position::Right:
                y = geo.height() / 2 - height / 2;
                break;
            case ProfileView::Position::BottomLeft:
            case ProfileView::Position::Bottom:
            case ProfileView::Position::BottomRight:
                y = geo.height() - height - margin;
                break;
        }

        return QPoint( x, y );
    }

    qsizetype Backend::availableContentWidth() {
        const auto screenWidth = this->_currentProfileScreen
                                     ? this->_currentProfileScreen->geometry().width()
                                     : this->newCurrentScreen()->geometry().width();
        const auto margin = this->_profileManager.currentProfile != nullptr
                                ? this->_profileManager.currentProfile->view().margin
                                : 0;
        return screenWidth - margin * 2;
    }

    qsizetype Backend::availableContentHeight() {
        const auto screenHeight = this->_currentProfileScreen
                                      ? this->_currentProfileScreen->geometry().height()
                                      : this->newCurrentScreen()->geometry().height();
        const auto margin = this->_profileManager.currentProfile != nullptr
                                ? this->_profileManager.currentProfile->view().margin
                                : 0;
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
} // namespace Service