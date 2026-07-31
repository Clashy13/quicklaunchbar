#pragma once

#include "../models/Command.hpp"

#include <QJsonArray>
#include <QJsonObject>
#include <optional>

namespace Shared::Serializer {

    class CommandSerializer {

        using Command = Models::ExecutionTarget::Command;

      public:
        static std::optional<Command> serialized( const QJsonObject& obj );

        static QJsonObject deserialized( const Command& command );

      private:
        static std::optional<QString> serializedProgram( const QJsonObject& obj );

        static std::optional<QStringList> serializedArguments( const QJsonObject& obj );

        static QJsonArray deserializedArguments( const QStringList& arguments );

        static constexpr auto programStr = "program";
        static constexpr auto argumentsStr = "arguments";
    };

} // namespace Shared::Serializer