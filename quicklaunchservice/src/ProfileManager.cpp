#include "ProfileManager.hpp"

#include "serializer/ProfileConfigSerializer.hpp"

#include <QDesktopServices>
#include <QProcess>
#include <QUrl>
#include <memory>

namespace Service {

    ProfileManager::ProfileManager( QObject* parent ) : QObject( parent ) {
        this->reloadProfiles();
    }

    void ProfileManager::launchExecutionTargetByIndex( const qsizetype index ) {
        if ( this->currentProfile ) {
            if ( auto executionTarget = this->currentProfile->executionTargetAt( index ) ) {
                this->startProcesses( executionTarget->commands(), executionTarget->uriList() );
                this->currentProfile = nullptr;
            }
        }
    }

    void ProfileManager::reloadProfiles() {
        for ( const auto connection : this->_shortcutConnections ) {
            this->disconnect( connection );
        }
        this->_shortcutConnections.clear();

        this->_hotkeys.clear();

        this->_profiles = Serializer::ProfileConfigSerializer::load();
        for ( auto profile : this->_profiles ) {
            profile->setParent( this );
        }
        this->connectShortcutsToProfiles();
    }

    void ProfileManager::connectShortcutsToProfiles() {
        for ( const auto profile : this->_profiles ) {
            this->_hotkeys.push_back(
                std::make_unique<QHotkey>( QKeySequence( profile->shortcut() ), true, this ) );

            this->_shortcutConnections.push_back(
                connect( this->_hotkeys.back().get(),
                         &QHotkey::activated,
                         this,
                         [ this, profile ]() { emit this->toggleProfile( profile ); } ) );
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