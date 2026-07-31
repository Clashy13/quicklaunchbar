#pragma once

#include "shared/models/ExecutionTarget.hpp"
#include "shared/models/ProfileView.hpp"

namespace Editor::Models {
    class Profile {

        using ExecutionTarget = Shared::Models::ExecutionTarget::ExecutionTarget;
        using ProfileView = Shared::Models::Profile::ProfileView;

      public:
        explicit Profile( const QUuid& uuid,
                          const QString& name,
                          const bool enabled,
                          const QString& shortcut,
                          const ProfileView& view,
                          const QList<ExecutionTarget>& executionTargets )
            : uuid( uuid ), name( name ), enabled( enabled ), shortcut( shortcut ), view( view ),
              executionTargets( executionTargets ) {}

        QUuid uuid;
        QString name;
        bool enabled;
        QString shortcut;
        ProfileView view;
        QList<ExecutionTarget> executionTargets;
    };
} // namespace Editor::Models
