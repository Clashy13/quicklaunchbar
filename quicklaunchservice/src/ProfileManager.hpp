#pragma once

#include "models/Profile.hpp"
#include "shared/models/Command.hpp"

#include <QObject>

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
        void connectShortcutsToProfiles();

        static void startProcesses( const QList<Command>& commands, const QList<QUrl>& uriList );

        const QList<Models::Profile*> _profiles;
    };
} // namespace Service
