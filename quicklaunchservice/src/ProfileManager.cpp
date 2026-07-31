#include "ProfileManager.hpp"

#include "serializer/ProfileConfigSerializer.hpp"

#include <QDesktopServices>
#include <QHotkey>
#include <QProcess>
#include <QUrl>

namespace Service {

    ProfileManager::ProfileManager( QObject* parent )
        : QObject( parent ), _profiles( Serializer::ProfileConfigSerializer::load() ) {
        for ( auto profile : this->_profiles ) {
            profile->setParent( this );
        }
        this->connectShortcutsToProfiles();
    }

    void ProfileManager::launchExecutionTargetByIndex( const qsizetype index ) {
        if ( this->currentProfile ) {
            if ( auto executionTarget = this->currentProfile->executionTargetAt( index ) ) {
                this->startProcesses( executionTarget->commands(), executionTarget->uriList() );
                this->currentProfile = nullptr;
            }
        }
    }

    void ProfileManager::connectShortcutsToProfiles() {
        for ( const auto profile : this->_profiles ) {
            auto* hotkey = new QHotkey( QKeySequence( profile->shortcut() ), true, this );
            connect( hotkey, &QHotkey::activated, this, [ this, profile ]() {
                emit this->toggleProfile( profile );
            } );
        }
    }

    void ProfileManager::startProcesses( const QList<Command>& commands,
                                         const QList<QUrl>& uriList ) {
        for ( const auto& command : commands ) {
            const bool success = QProcess::startDetached( command.program, command.arguments );
            if ( !success ) {
                qWarning().noquote()
                    << "Process failed:" << command.program << command.arguments.join( " " );
            }
        }
        for ( const auto& uri : uriList ) {
            QDesktopServices::openUrl( QUrl( uri ) );
        }
    }

} // namespace Service