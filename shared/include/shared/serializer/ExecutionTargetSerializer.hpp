#pragma once

#include "../models/Command.hpp"
#include "../models/ExecutionTarget.hpp"
#include "../models/IconSource.hpp"
#include "../models/Uri.hpp"

#include <QJsonObject>
#include <optional>

namespace Shared::Serializer {

    class ExecutionTargetSerializer {

        using ExecutionTarget = Models::ExecutionTarget::ExecutionTarget;
        using IconSource = Models::ExecutionTarget::IconSource;
        using Command = Models::ExecutionTarget::Command;
        using Uri = Models::ExecutionTarget::Uri;

      public:
        static std::optional<ExecutionTarget> serialized( const QJsonObject& obj );

        static QJsonObject deserialized( const ExecutionTarget& executionTarget );

      protected:
        static std::optional<QUuid> serializedUuid( const QJsonObject& obj );

        static std::optional<QString> serializedName( const QJsonObject& obj );

        static std::optional<ExecutionTarget::Type> serializedType( const QJsonObject& obj );

        static std::optional<QList<IconSource>> serializedIconSources( const QJsonObject& obj );

        static std::optional<QList<Command>> serializedCommands( const QJsonObject& obj );

        static std::optional<QList<Uri>> serializedUriLists( const QJsonObject& obj );

        static QJsonArray deserializedIconSources( const QList<IconSource>& iconSources );

        static QJsonArray deserializedCommands( const QList<Command>& commands );

        static QJsonArray deserializedUriList( const QList<Uri>& uriList );

        static std::optional<ExecutionTarget::Type> typeFromString( const QString& type );

        static QString typeToString( const ExecutionTarget::Type type );

        static constexpr auto uuidStr = "uuid";
        static constexpr auto nameStr = "name";
        static constexpr auto typeStr = "type";
        static constexpr auto iconSourcesStr = "icon_sources";
        static constexpr auto commandsStr = "commands";
        static constexpr auto uriListStr = "uri_list";

        static constexpr auto desktopApplicationTypeStr = "desktop_application";
        static constexpr auto executableFileTypeStr = "executable_file";
        static constexpr auto commandTypeStr = "command";
        static constexpr auto openFileTypeStr = "open_file";
        static constexpr auto openUrlTypeStr = "open_url";
        static constexpr auto groupTypeStr = "group";
    };
} // namespace Shared::Serializer