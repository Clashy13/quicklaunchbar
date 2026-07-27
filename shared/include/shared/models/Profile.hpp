#pragma once

#include "ExecutionTarget.hpp"
#include "ProfileView.hpp"

#include <memory>
#include <vector>

namespace Models::Profile {
    class Profile {
      public:
        explicit Profile(
            const QUuid& uuid,
            const QString& name,
            const QString& shortcut,
            const ProfileView& view,
            std::vector<std::unique_ptr<ExecutionTarget::ExecutionTarget>> executionTargets )
            : uuid( uuid ), name( name ), shortcut( shortcut ), view( view ),
              executionTargets( std::move( executionTargets ) ) {}

        QUuid uuid;
        QString name;
        QString shortcut;
        ProfileView view;
        std::vector<std::unique_ptr<ExecutionTarget::ExecutionTarget>> executionTargets;
    };
} // namespace Models::Profile
