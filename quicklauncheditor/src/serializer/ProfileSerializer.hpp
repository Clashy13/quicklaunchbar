#pragma once

#include "../models/Profile.hpp"
#include "shared/serializer/ProfileSerializer.hpp"

namespace Editor::Serializer {

    class ProfileSerializer : public Shared::Serializer::ProfileSerializer {

        using ExecutionTarget = Shared::Models::ExecutionTarget::ExecutionTarget;

      public:
        static std::optional<Models::Profile> serialized( const QJsonObject& obj );

        static QJsonObject deserialized( const Models::Profile& profile );

      private:
        static std::optional<QList<ExecutionTarget>>
        serializedExecutionTargets( const QJsonObject& obj );

        static QJsonArray
        deserializedExecutionTargets( const QList<ExecutionTarget>& executionTargets );
    };
} // namespace Editor::Serializer