#pragma once

#include "../models/Command.hpp"

#include <QJsonArray>
#include <QJsonObject>
#include <optional>

namespace Serializer {

    using Command = Models::ExecutionTarget::Command;

    class CommandSerializer {
      public:
        static std::optional<Command> serialized( const QJsonObject& obj );

        static QJsonObject deserialized( const Command& command );

      private:
        static QJsonArray deserializedArguments( const QStringList& arguments );

        static std::optional<QStringList> serializedArguments( const QJsonObject& obj );

        static constexpr auto programStr = "program";
        static constexpr auto argumentsStr = "arguments";
    };

} // namespace Serializer