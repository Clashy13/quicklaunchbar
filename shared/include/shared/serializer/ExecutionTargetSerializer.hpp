#pragma once

#include "../models/ExecutionTarget.hpp"
#include "../models/GroupExecutionTarget.hpp"
#include "../models/SingleExecutionTarget.hpp"
#include "../models/UriExecutionTarget.hpp"

#include <QJsonObject>
#include <optional>

namespace Serializer {

    class ExecutionTargetSerializer {
      public:
        static std::optional<std::unique_ptr<Models::ExecutionTarget::ExecutionTarget>>
        serialized( const QJsonObject& obj );

        static QJsonObject deserialized(
            const std::unique_ptr<Models::ExecutionTarget::ExecutionTarget>& executionTarget );

      private:
        static std::optional<std::unique_ptr<Models::ExecutionTarget::GroupExecutionTarget>>
        serializedGroup( const QUuid& uuid,
                         const QString& name,
                         Models::ExecutionTarget::ExecutionTarget::Type type,
                         const QList<Models::ExecutionTarget::IconSource>& iconSources,
                         const QJsonObject& obj );

        static std::optional<std::unique_ptr<Models::ExecutionTarget::SingleExecutionTarget>>
        serializedSingle( const QUuid& uuid,
                          const QString& name,
                          Models::ExecutionTarget::ExecutionTarget::Type type,
                          const QList<Models::ExecutionTarget::IconSource>& iconSources,
                          const QJsonObject& obj );

        static std::optional<std::unique_ptr<Models::ExecutionTarget::UriExecutionTarget>>
        serializedUri( const QUuid& uuid,
                       const QString& name,
                       Models::ExecutionTarget::ExecutionTarget::Type type,
                       const QList<Models::ExecutionTarget::IconSource>& iconSources,
                       const QJsonObject& obj );

        static std::optional<QList<Models::ExecutionTarget::IconSource>>
        serializedIconSources( const QJsonObject& obj );

        static QJsonArray
        deserializedIconSources( const QList<Models::ExecutionTarget::IconSource>& iconSources );

        static void
        deserializedGroup( QJsonObject& obj,
                           Models::ExecutionTarget::GroupExecutionTarget* executionTarget );

        static void
        deserializedSingle( QJsonObject& obj,
                            Models::ExecutionTarget::SingleExecutionTarget* executionTarget );

        static void deserializedUri( QJsonObject& obj,
                                     Models::ExecutionTarget::UriExecutionTarget* executionTarget );

        static std::optional<Models::ExecutionTarget::ExecutionTarget::Type>
        typeFromString( const QString& type );

        static QString typeToString( const Models::ExecutionTarget::ExecutionTarget::Type type );

        static constexpr auto uuidStr = "uuid";
        static constexpr auto nameStr = "name";
        static constexpr auto typeStr = "type";
        static constexpr auto iconSourcesStr = "icon_sources";

        static constexpr auto commandsStr = "commands";
        static constexpr auto commandStr = "command";
        static constexpr auto uriStr = "uri";
        static constexpr auto uriListStr = "uri_list";

        static constexpr auto desktopApplicationTypeStr = "desktop_application";
        static constexpr auto executableFileTypeStr = "executable_file";
        static constexpr auto commandTypeStr = "command";
        static constexpr auto openFileTypeStr = "open_file";
        static constexpr auto openUrlTypeStr = "open_url";
        static constexpr auto groupTypeStr = "group";
    };
} // namespace Serializer