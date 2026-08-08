#pragma once

#include "../models/Command.hpp"
#include "../models/ExecutionTargetType.hpp"
#include "../models/IconSource.hpp"

#include <QJsonObject>
#include <optional>

namespace Shared::Serializer {

    class ExecutionTargetSerializer {

        using Type = Models::ExecutionTarget::Type;
        using IconSource = Models::ExecutionTarget::IconSource;
        using Command = Models::ExecutionTarget::Command;

      protected:
        static std::optional<QUuid> serializedUuid( const QJsonObject& obj );

        static std::optional<QString> serializedName( const QJsonObject& obj );

        static std::optional<Type> serializedType( const QJsonObject& obj );

        static std::optional<IconSource> serializedIconSource( const QJsonObject& obj );

        static std::optional<Command> serializedCommand( const QJsonObject& obj );

        static std::optional<QString> serializedFilePath( const QJsonObject& obj );

        static std::optional<QUrl> serializedUrl( const QJsonObject& obj );

        static std::optional<Type> typeFromString( const QString& type );

        static QString typeToString( const Type type );

        static constexpr auto uuidStr = "uuid";
        static constexpr auto nameStr = "name";
        static constexpr auto typeStr = "type";

        static constexpr auto iconSourceStr = "icon_source";
        static constexpr auto commandStr = "command";
        static constexpr auto filePathStr = "file_path";
        static constexpr auto urlStr = "url";
        static constexpr auto executionTargetsStr = "execution_targets";

        static constexpr auto desktopApplicationTypeStr = "desktop_application";
        static constexpr auto executableFileTypeStr = "executable_file";
        static constexpr auto commandTypeStr = "command";
        static constexpr auto openFileTypeStr = "open_file";
        static constexpr auto openUrlTypeStr = "open_url";
        static constexpr auto groupTypeStr = "group";
    };
} // namespace Shared::Serializer