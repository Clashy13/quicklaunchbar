#pragma once

#include "../models/ExecutionTarget.hpp"
#include "../models/Profile.hpp"

#include <QJsonArray>
#include <QJsonObject>
#include <memory>
#include <optional>

namespace Serializer {

    using Profile = Models::Profile::Profile;
    using ExecutionTarget = Models::ExecutionTarget::ExecutionTarget;

    class ProfileSerializer {
      public:
        static std::optional<Profile> serialized( const QJsonObject& obj );

        static QJsonObject deserialized( const Profile& profile );

      private:
        static std::optional<std::vector<std::unique_ptr<ExecutionTarget>>>
        serializedExecutionTargets( const QJsonObject& obj );

        static QJsonArray deserializedExecutionTargets(
            const std::vector<std::unique_ptr<ExecutionTarget>>& executionTargets );

        static constexpr auto uuidStr = "uuid";
        static constexpr auto nameStr = "name";
        static constexpr auto enabledStr = "enabled";
        static constexpr auto shortcutStr = "shortcut";
        static constexpr auto viewStr = "view";
        static constexpr auto executionTargetsStr = "execution_targets";
    };

} // namespace Serializer