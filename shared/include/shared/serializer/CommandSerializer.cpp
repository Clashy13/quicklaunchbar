#include "CommandSerializer.hpp"

#include "PropertySerializer.hpp"

namespace Shared::Serializer {

    std::optional<CommandSerializer::Command>
    CommandSerializer::serialized( const QJsonObject& obj ) {
        const auto program = CommandSerializer::serializedProgram( obj );
        const auto arguments = CommandSerializer::serializedArguments( obj );

        if ( program && arguments ) {
            Command command( *program, *arguments );
            return command;
        } else {
            return std::nullopt;
        }
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

    std::optional<QString> CommandSerializer::serializedProgram( const QJsonObject& obj ) {
        if ( const auto programOpt =
                 PropertySerializer::serializedStringProperty( obj,
                                                               CommandSerializer::programStr ) ) {
            return *programOpt;
        } else {
            return std::nullopt;
        }
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

} // namespace Shared::Serializer