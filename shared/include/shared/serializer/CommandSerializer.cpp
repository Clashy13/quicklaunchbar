#include "CommandSerializer.hpp"

#include "PropertySerializer.hpp"

namespace Serializer {

    std::optional<Command> CommandSerializer::serialized( const QJsonObject& obj ) {
        QString program;
        if ( const auto programOpt =
                 PropertySerializer::serializedStringProperty( obj,
                                                               CommandSerializer::programStr ) ) {
            program = *programOpt;
        } else {
            return std::nullopt;
        }
        QStringList arguments;
        if ( const auto argumentsOpt = CommandSerializer::serializedArguments( obj ) ) {
            arguments = *argumentsOpt;
        } else {
            return std::nullopt;
        }

        Command command( program, arguments );
        return command;
    }

    QJsonObject CommandSerializer::deserialized( const Command& command ) {
        return { { CommandSerializer::programStr, command.program },
                 { CommandSerializer::argumentsStr,
                   CommandSerializer::deserializedArguments( command.arguments ) } };
    }

    QJsonArray CommandSerializer::deserializedArguments( const QStringList& arguments ) {
        QJsonArray deserializedArguments;
        for ( const auto& argument : arguments ) {
            deserializedArguments.push_back( QJsonValue( argument ) );
        }
        return deserializedArguments;
    }

    std::optional<QStringList> CommandSerializer::serializedArguments( const QJsonObject& obj ) {
        if ( const auto argumentsOpt =
                 PropertySerializer::serializedArrayProperty( obj,
                                                              CommandSerializer::argumentsStr ) ) {

            QStringList serializedArguments;
            for ( const auto& argument : *argumentsOpt ) {
                if ( !argument.isString() ) {
                    qWarning().noquote() << "Property list element is not a string";
                    return std::nullopt;
                }
                serializedArguments.push_back( argument.toString() );
            }
            return serializedArguments;
        } else {
            return std::nullopt;
        }
    }

} // namespace Serializer