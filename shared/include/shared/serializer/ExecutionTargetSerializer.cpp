#include "ExecutionTargetSerializer.hpp"

#include "CommandSerializer.hpp"
#include "IconSourceSerializer.hpp"
#include "PropertySerializer.hpp"
#include "UriSerializer.hpp"

namespace Shared::Serializer {

    std::optional<ExecutionTargetSerializer::ExecutionTarget>
    ExecutionTargetSerializer::serialized( const QJsonObject& obj ) {
        const auto uuid = ExecutionTargetSerializer::serializedUuid( obj );
        const auto name = ExecutionTargetSerializer::serializedName( obj );
        const auto type = ExecutionTargetSerializer::serializedType( obj );
        const auto iconSources = ExecutionTargetSerializer::serializedIconSources( obj );
        const auto commands = ExecutionTargetSerializer::serializedCommands( obj );
        const auto uriList = ExecutionTargetSerializer::serializedUriLists( obj );

        if ( uuid && name && type && iconSources && commands && uriList ) {
            ExecutionTarget executionTarget( *uuid,
                                             *name,
                                             *type,
                                             *iconSources,
                                             *commands,
                                             *uriList );
            return executionTarget;
        } else {
            return std::nullopt;
        }
    }

    QJsonObject ExecutionTargetSerializer::deserialized( const ExecutionTarget& executionTarget ) {
        return {
            { ExecutionTargetSerializer::uuidStr,
              executionTarget.uuid.toString( QUuid::WithoutBraces ) },
            { ExecutionTargetSerializer::nameStr, executionTarget.name },
            { ExecutionTargetSerializer::typeStr,
              ExecutionTargetSerializer::typeToString( executionTarget.type ) },
            { ExecutionTargetSerializer::iconSourcesStr,
              ExecutionTargetSerializer::deserializedIconSources( executionTarget.iconSources ) },
            { ExecutionTargetSerializer::commandsStr,
              ExecutionTargetSerializer::deserializedCommands( executionTarget.commands ) },
            { ExecutionTargetSerializer::uriListStr,
              ExecutionTargetSerializer::deserializedUriList( executionTarget.uriList ) } };
    }

    std::optional<QUuid> ExecutionTargetSerializer::serializedUuid( const QJsonObject& obj ) {
        if ( const auto uuidOpt = PropertySerializer::serializedStringProperty(
                 obj,
                 ExecutionTargetSerializer::uuidStr ) ) {
            return QUuid( *uuidOpt );
        } else {
            return std::nullopt;
        }
    }

    std::optional<QString> ExecutionTargetSerializer::serializedName( const QJsonObject& obj ) {
        if ( const auto nameOpt = PropertySerializer::serializedStringProperty(
                 obj,
                 ExecutionTargetSerializer::nameStr ) ) {
            return *nameOpt;
        } else {
            return std::nullopt;
        }
    }

    std::optional<ExecutionTargetSerializer::ExecutionTarget::Type>
    ExecutionTargetSerializer::serializedType( const QJsonObject& obj ) {
        ExecutionTarget::Type type;
        if ( const auto typeStrOpt = PropertySerializer::serializedStringProperty(
                 obj,
                 ExecutionTargetSerializer::typeStr ) ) {
            if ( const auto typeOpt = ExecutionTargetSerializer::typeFromString( *typeStrOpt ) ) {
                return *typeOpt;
            } else {
                return std::nullopt;
            }
        } else {
            return std::nullopt;
        }
    }

    std::optional<QList<ExecutionTargetSerializer::IconSource>>
    ExecutionTargetSerializer::serializedIconSources( const QJsonObject& obj ) {
        if ( const auto array = PropertySerializer::serializedArrayProperty(
                 obj,
                 ExecutionTargetSerializer::iconSourcesStr ) ) {
            QList<IconSource> iconSources;
            for ( const auto element : *array ) {
                if ( !element.isObject() ) {
                    qWarning().noquote() << "Property list element is not an object";
                    return std::nullopt;
                }

                if ( const auto iconSource =
                         IconSourceSerializer::serialized( element.toObject() ) ) {
                    iconSources.push_back( *iconSource );
                } else {
                    return std::nullopt;
                }
            }
            return iconSources;
        } else {
            return std::nullopt;
        }
    }

    std::optional<QList<ExecutionTargetSerializer::Command>>
    ExecutionTargetSerializer::serializedCommands( const QJsonObject& obj ) {
        if ( const auto array = PropertySerializer::serializedArrayProperty(
                 obj,
                 ExecutionTargetSerializer::commandsStr ) ) {
            QList<Command> commands;
            for ( const auto element : *array ) {
                if ( !element.isObject() ) {
                    qWarning().noquote() << "Property list element is not an object";
                    return std::nullopt;
                }

                if ( const auto command = CommandSerializer::serialized( element.toObject() ) ) {
                    commands.push_back( *command );
                } else {
                    return std::nullopt;
                }
            }
            return commands;
        } else {
            return std::nullopt;
        }
    }

    std::optional<QList<ExecutionTargetSerializer::Uri>>
    ExecutionTargetSerializer::serializedUriLists( const QJsonObject& obj ) {
        if ( const auto array = PropertySerializer::serializedArrayProperty(
                 obj,
                 ExecutionTargetSerializer::uriListStr ) ) {
            QList<Uri> uriList;
            for ( const auto element : *array ) {
                if ( !element.isObject() ) {
                    qWarning().noquote() << "Property list element is not an object";
                    return std::nullopt;
                }

                if ( const auto uri = UriSerializer::serialized( element.toObject() ) ) {
                    uriList.push_back( *uri );
                } else {
                    return std::nullopt;
                }
            }
            return uriList;
        } else {
            return std::nullopt;
        }
    }

    QJsonArray
    ExecutionTargetSerializer::deserializedIconSources( const QList<IconSource>& iconSources ) {
        QJsonArray jsonIconSources;
        for ( const auto iconSource : iconSources ) {
            jsonIconSources.push_back(
                Shared::Serializer::IconSourceSerializer::deserialized( iconSource ) );
        }
        return jsonIconSources;
    }

    QJsonArray ExecutionTargetSerializer::deserializedCommands( const QList<Command>& commands ) {
        QJsonArray jsonCommands;
        for ( const auto& command : commands ) {
            jsonCommands.push_back(
                Shared::Serializer::CommandSerializer::deserialized( command ) );
        }
        return jsonCommands;
    }

    QJsonArray ExecutionTargetSerializer::deserializedUriList( const QList<Uri>& uriList ) {
        QJsonArray jsonUriList;
        for ( const auto& uri : uriList ) {
            jsonUriList.push_back( Shared::Serializer::UriSerializer::deserialized( uri ) );
        }
        return jsonUriList;
    }

    QString ExecutionTargetSerializer::typeToString( const ExecutionTarget::Type type ) {
        switch ( type ) {
            case ExecutionTarget::Type::DesktopApplication:
                return ExecutionTargetSerializer::desktopApplicationTypeStr;
            case ExecutionTarget::Type::ExecutableFile:
                return ExecutionTargetSerializer::executableFileTypeStr;
            case ExecutionTarget::Type::Command:
                return ExecutionTargetSerializer::commandTypeStr;
            case ExecutionTarget::Type::OpenFile:
                return ExecutionTargetSerializer::openFileTypeStr;
            case ExecutionTarget::Type::OpenUrl:
                return ExecutionTargetSerializer::openUrlTypeStr;
            case ExecutionTarget::Type::Group:
                return ExecutionTargetSerializer::groupTypeStr;
            default:
                return "";
        }
    }

    std::optional<ExecutionTargetSerializer::ExecutionTarget::Type>
    ExecutionTargetSerializer::typeFromString( const QString& type ) {
        if ( type == ExecutionTargetSerializer::desktopApplicationTypeStr ) {
            return ExecutionTarget::Type::DesktopApplication;
        } else if ( type == ExecutionTargetSerializer::executableFileTypeStr ) {
            return ExecutionTarget::Type::ExecutableFile;
        } else if ( type == ExecutionTargetSerializer::commandTypeStr ) {
            return ExecutionTarget::Type::Command;
        } else if ( type == ExecutionTargetSerializer::openFileTypeStr ) {
            return ExecutionTarget::Type::OpenFile;
        } else if ( type == ExecutionTargetSerializer::openUrlTypeStr ) {
            return ExecutionTarget::Type::OpenUrl;
        } else if ( type == ExecutionTargetSerializer::groupTypeStr ) {
            return ExecutionTarget::Type::Group;
        } else {
            qWarning().noquote() << "Unknown execution target type:" << type;
            return std::nullopt;
        }
    }

} // namespace Shared::Serializer