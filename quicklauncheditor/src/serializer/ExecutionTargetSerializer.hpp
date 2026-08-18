#pragma once

#include "../models/ExecutionTarget.hpp"
#include "../models/GroupExecutionTarget.hpp"
#include "../models/SingleExecutionTarget.hpp"
#include "shared/serializer/ExecutionTargetSerializer.hpp"

#include <QJsonArray>
#include <optional>

namespace Editor::Serializer {

    class ExecutionTargetSerializer : public Shared::Serializer::ExecutionTargetSerializer {

      public:
        static std::optional<Models::ExecutionTarget*> serialized( const QJsonObject& obj );

        static QJsonObject deserialized( Models::ExecutionTarget* executionTarget );

      private:
        static std::optional<QString> serializedCommand( const QJsonObject& obj );

        static std::optional<Models::SingleExecutionTarget*>
        serializedSingleExecutionTarget( const QJsonObject& obj );

        static std::optional<QList<Models::SingleExecutionTarget*>>
        serializedSingleExecutionTargets( const QJsonObject& obj );

        static QJsonArray deserializedSingleExecutionTargets(
            const QList<Models::SingleExecutionTarget*>& executionTargets );

        static std::optional<Models::GroupExecutionTarget*>
        serializedGroup( const QJsonObject& obj );
    };
} // namespace Editor::Serializer