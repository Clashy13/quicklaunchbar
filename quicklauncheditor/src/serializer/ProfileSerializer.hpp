#pragma once

#include "../models/Profile.hpp"
#include "shared/serializer/ProfileSerializer.hpp"

namespace Editor::Serializer {

    class ProfileSerializer : public Shared::Serializer::ProfileSerializer {

      public:
        static std::optional<Models::Profile*> serialized( const QJsonObject& obj );

        static QJsonObject deserialized( Models::Profile* profile );

      private:
        static std::optional<Models::ProfileView*> serializedView( const QJsonObject& obj );

        static std::optional<QList<Models::ExecutionTarget*>>
        serializedExecutionTargets( const QJsonObject& obj );

        static QJsonArray
        deserializedExecutionTargets( const QList<Models::ExecutionTarget*>& executionTargets );
    };
} // namespace Editor::Serializer