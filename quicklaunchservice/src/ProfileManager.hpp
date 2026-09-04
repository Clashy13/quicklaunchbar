#pragma once

#include "models/Profile.hpp"
#include "shared/models/Command.hpp"

#include <QHotkey>
#include <QObject>
#include <memory>

namespace Service {

    class ProfileManager : public QObject {
        Q_OBJECT

        using Command = Shared::Models::ExecutionTarget::Command;

      public:
        ProfileManager( QObject* parent = nullptr );

        void launchExecutionTargetByIndex( const qsizetype index );

        Models::Profile* currentProfile;

      signals:
        void toggleProfile( Models::Profile* profile );

      private:
        void reloadProfiles();

        void connectShortcutsToProfiles();

        static void startProcesses( const QList<Command>& commands, const QList<QUrl>& uriList );

        QList<Models::Profile*> _profiles;
        std::vector<std::unique_ptr<QHotkey>> _hotkeys;
        QList<QMetaObject::Connection> _shortcutConnections;
    };
} // namespace Service
