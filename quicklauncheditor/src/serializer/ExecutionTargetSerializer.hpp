#pragma once

#include "../models/CommandExecutionTarget.hpp"
#include "../models/DesktopApplicationExecutionTarget.hpp"
#include "../models/ExecutableFileExecutionTarget.hpp"
#include "../models/ExecutionTarget.hpp"
#include "../models/GroupExecutionTarget.hpp"
#include "../models/OpenFileExecutionTarget.hpp"
#include "../models/OpenUrlExecutionTarget.hpp"
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
        static std::optional<bool> serializedUseDefaultName( const QJsonObject& obj );

        static std::optional<bool> serializedUseDefaultIconSource( const QJsonObject& obj );

        static std::optional<QString> serializedCommand( const QJsonObject& obj );

        static std::optional<Models::SingleExecutionTarget*>
        serializedSingleExecutionTarget( const QJsonObject& obj );

        static std::optional<QList<Models::SingleExecutionTarget*>>
        serializedSingleExecutionTargets( const QJsonObject& obj );

        static QJsonArray deserializedSingleExecutionTargets(
            const QList<Models::SingleExecutionTarget*>& executionTargets );

        static std::optional<Models::DesktopApplicationExecutionTarget*>
        serializedDesktopApplication( const QJsonObject& obj );

        static std::optional<Models::ExecutableFileExecutionTarget*>
        serializedExecutableFile( const QJsonObject& obj );

        static std::optional<Models::CommandExecutionTarget*>
        serializedCommandExecutionTarget( const QJsonObject& obj );

        static std::optional<Models::OpenFileExecutionTarget*>
        serializedOpenFile( const QJsonObject& obj );

        static std::optional<Models::OpenUrlExecutionTarget*>
        serializedOpenUrl( const QJsonObject& obj );

        static std::optional<Models::GroupExecutionTarget*>
        serializedGroup( const QJsonObject& obj );

        static QJsonObject deserializedDesktopApplication(
            Models::DesktopApplicationExecutionTarget* executionTarget );

        static QJsonObject
        deserializedExecutableFile( Models::ExecutableFileExecutionTarget* executionTarget );

        static QJsonObject
        deserializedCommandExecutionTarget( Models::CommandExecutionTarget* executionTarget );

        static QJsonObject deserializedOpenFile( Models::OpenFileExecutionTarget* executionTarget );

        static QJsonObject deserializedOpenUrl( Models::OpenUrlExecutionTarget* executionTarget );

        static QJsonObject deserializedGroup( Models::GroupExecutionTarget* executionTarget );

        static constexpr auto useDefaultNameStr = "use_default_name";
        static constexpr auto useDefaultIconSourceStr = "use_default_icon_source";
    };
} // namespace Editor::Serializer