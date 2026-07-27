#include "ExecutionTargetSerializer.hpp"

#include "CommandSerializer.hpp"
#include "IconSourceSerializer.hpp"
#include "PropertySerializer.hpp"
#include "UriSerializer.hpp"

#include <memory>
#include <optional>

namespace Serializer {

    namespace ExecutionTarget = Models::ExecutionTarget;

    std::optional<std::unique_ptr<ExecutionTarget::ExecutionTarget>>
    ExecutionTargetSerializer::serialized( const QJsonObject& obj ) {
        QUuid uuid;
        if ( const auto uuidOpt = PropertySerializer::serializedStringProperty(
                 obj,
                 ExecutionTargetSerializer::uuidStr ) ) {
            uuid = QUuid( *uuidOpt );
        } else {
            return std::nullopt;
        }
        QString name;
        if ( const auto nameOpt = PropertySerializer::serializedStringProperty(
                 obj,
                 ExecutionTargetSerializer::nameStr ) ) {
            name = *nameOpt;
        } else {
            return std::nullopt;
        }
        QList<IconSource> iconSources;
        if ( const auto iconSourcesOpt = ExecutionTargetSerializer::serializedIconSources( obj ) ) {
            iconSources = *iconSourcesOpt;
        } else {
            return std::nullopt;
        }

        using Type = ExecutionTarget::ExecutionTarget::Type;

        QString typeStr;
        Type type;
        if ( const auto typeStrOpt = PropertySerializer::serializedStringProperty(
                 obj,
                 ExecutionTargetSerializer::typeStr ) ) {
            typeStr = *typeStrOpt;
            if ( const auto typeOpt = ExecutionTargetSerializer::typeFromString( *typeStrOpt ) ) {
                type = *typeOpt;
            } else {
                return std::nullopt;
            }
        } else {
            return std::nullopt;
        }

        switch ( type ) {
            case Type::DesktopApplication:
            case Type::ExecutableFile:
            case Type::Command:
                return ExecutionTargetSerializer::serializedSingle( uuid,
                                                                    name,
                                                                    type,
                                                                    iconSources,
                                                                    obj );
            case Type::OpenFile:
            case Type::OpenUrl:
                return ExecutionTargetSerializer::serializedUri( uuid,
                                                                 name,
                                                                 type,
                                                                 iconSources,
                                                                 obj );
            case Type::Group:
                return ExecutionTargetSerializer::serializedGroup( uuid,
                                                                   name,
                                                                   type,
                                                                   iconSources,
                                                                   obj );
            default:
                qWarning().noquote() << "Unknown execution target type:" << typeStr;
                return std::nullopt;
        }
    }

    QJsonObject ExecutionTargetSerializer::deserialized(
        const std::unique_ptr<ExecutionTarget::ExecutionTarget>& executionTarget ) {
        QJsonObject obj;
        obj[ ExecutionTargetSerializer::uuidStr ] =
            executionTarget->uuid.toString( QUuid::WithoutBraces );
        obj[ ExecutionTargetSerializer::nameStr ] = executionTarget->name;
        obj[ ExecutionTargetSerializer::iconSourcesStr ] =
            ExecutionTargetSerializer::deserializedIconSources( executionTarget->iconSources );
        obj[ ExecutionTargetSerializer::typeStr ] =
            ExecutionTargetSerializer::typeToString( executionTarget->type );
        using Type = ExecutionTarget::ExecutionTarget::Type;
        switch ( executionTarget->type ) {
            case Type::DesktopApplication:
            case Type::ExecutableFile:
            case Type::Command:
                ExecutionTargetSerializer::deserializedSingle(
                    obj,
                    static_cast<ExecutionTarget::SingleExecutionTarget*>( executionTarget.get() ) );
                break;
            case Type::OpenFile:
            case Type::OpenUrl:
                ExecutionTargetSerializer::deserializedUri(
                    obj,
                    static_cast<ExecutionTarget::UriExecutionTarget*>( executionTarget.get() ) );
                break;
            case Type::Group:
                ExecutionTargetSerializer::deserializedGroup(
                    obj,
                    static_cast<ExecutionTarget::GroupExecutionTarget*>( executionTarget.get() ) );
                break;
        }
        return obj;
    }

    std::optional<std::unique_ptr<ExecutionTarget::GroupExecutionTarget>>
    ExecutionTargetSerializer::serializedGroup(
        const QUuid& uuid,
        const QString& name,
        ExecutionTarget::ExecutionTarget::Type type,
        const QList<ExecutionTarget::IconSource>& iconSources,
        const QJsonObject& obj ) {
        if ( const auto array = PropertySerializer::serializedArrayProperty(
                 obj,
                 ExecutionTargetSerializer::commandsStr ) ) {
            QList<ExecutionTarget::Command> commands;
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

            if ( const auto array = PropertySerializer::serializedArrayProperty(
                     obj,
                     ExecutionTargetSerializer::uriListStr ) ) {
                QList<ExecutionTarget::Uri> uriList;
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

                return std::make_unique<ExecutionTarget::GroupExecutionTarget>( uuid,
                                                                                name,
                                                                                type,
                                                                                iconSources,
                                                                                commands,
                                                                                uriList );

            } else {
                return std::nullopt;
            }

        } else {
            return std::nullopt;
        }
    }

    std::optional<std::unique_ptr<ExecutionTarget::SingleExecutionTarget>>
    ExecutionTargetSerializer::serializedSingle(
        const QUuid& uuid,
        const QString& name,
        ExecutionTarget::ExecutionTarget::Type type,
        const QList<ExecutionTarget::IconSource>& iconSources,
        const QJsonObject& obj ) {
        if ( const auto commandObj = PropertySerializer::serializedObjectProperty(
                 obj,
                 ExecutionTargetSerializer::commandStr ) ) {
            if ( const auto command = CommandSerializer::serialized( *commandObj ) ) {
                return std::make_unique<ExecutionTarget::SingleExecutionTarget>( uuid,
                                                                                 name,
                                                                                 type,
                                                                                 iconSources,
                                                                                 *command );
            } else {
                return std::nullopt;
            }
        } else {
            return std::nullopt;
        }
    }

    std::optional<std::unique_ptr<ExecutionTarget::UriExecutionTarget>>
    ExecutionTargetSerializer::serializedUri( const QUuid& uuid,
                                              const QString& name,
                                              ExecutionTarget::ExecutionTarget::Type type,
                                              const QList<ExecutionTarget::IconSource>& iconSources,
                                              const QJsonObject& obj ) {
        QString uri;
        if ( const auto uriOpt = PropertySerializer::serializedStringProperty(
                 obj,
                 ExecutionTargetSerializer::uriStr ) ) {
            uri = *uriOpt;
        } else {
            return std::nullopt;
        }
        return std::make_unique<ExecutionTarget::UriExecutionTarget>( uuid,
                                                                      name,
                                                                      type,
                                                                      iconSources,
                                                                      uri );
    }

    std::optional<QList<IconSource>>
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

    QJsonArray
    ExecutionTargetSerializer::deserializedIconSources( const QList<IconSource>& iconSources ) {
        QJsonArray jsonIconSources;
        for ( const auto& iconSource : iconSources ) {
            jsonIconSources.push_back( IconSourceSerializer::deserialized( iconSource ) );
        }
        return jsonIconSources;
    }

    void ExecutionTargetSerializer::deserializedGroup(
        QJsonObject& obj,
        ExecutionTarget::GroupExecutionTarget* executionTarget ) {
        QJsonArray commands;
        for ( const auto& command : executionTarget->commands ) {
            commands.push_back( CommandSerializer::deserialized( command ) );
        }
        obj[ ExecutionTargetSerializer::commandsStr ] = commands;
        QJsonArray uriList;
        for ( const auto& uri : executionTarget->uriList ) {
            uriList.push_back( UriSerializer::deserialized( uri ) );
        }
        obj[ ExecutionTargetSerializer::uriListStr ] = uriList;
    }

    void ExecutionTargetSerializer::deserializedSingle(
        QJsonObject& obj,
        ExecutionTarget::SingleExecutionTarget* executionTarget ) {
        obj[ ExecutionTargetSerializer::commandStr ] =
            CommandSerializer::deserialized( executionTarget->command );
    }

    void ExecutionTargetSerializer::deserializedUri(
        QJsonObject& obj,
        ExecutionTarget::UriExecutionTarget* executionTarget ) {
        obj[ ExecutionTargetSerializer::uriStr ] = executionTarget->uri;
    }

    QString
    ExecutionTargetSerializer::typeToString( const ExecutionTarget::ExecutionTarget::Type type ) {
        using Type = ExecutionTarget::ExecutionTarget::Type;
        switch ( type ) {
            case Type::DesktopApplication:
                return ExecutionTargetSerializer::desktopApplicationTypeStr;
            case Type::ExecutableFile:
                return ExecutionTargetSerializer::executableFileTypeStr;
            case Type::Command:
                return ExecutionTargetSerializer::commandTypeStr;
            case Type::OpenFile:
                return ExecutionTargetSerializer::openFileTypeStr;
            case Type::OpenUrl:
                return ExecutionTargetSerializer::openUrlTypeStr;
            case Type::Group:
                return ExecutionTargetSerializer::groupTypeStr;
            default:
                return "";
        }
    }

    std::optional<ExecutionTarget::ExecutionTarget::Type>
    ExecutionTargetSerializer::typeFromString( const QString& type ) {
        using Type = ExecutionTarget::ExecutionTarget::Type;
        if ( type == ExecutionTargetSerializer::desktopApplicationTypeStr ) {
            return Type::DesktopApplication;
        } else if ( type == ExecutionTargetSerializer::executableFileTypeStr ) {
            return Type::ExecutableFile;
        } else if ( type == ExecutionTargetSerializer::commandTypeStr ) {
            return Type::Command;
        } else if ( type == ExecutionTargetSerializer::openFileTypeStr ) {
            return Type::OpenFile;
        } else if ( type == ExecutionTargetSerializer::openUrlTypeStr ) {
            return Type::OpenUrl;
        } else if ( type == ExecutionTargetSerializer::groupTypeStr ) {
            return Type::Group;
        } else {
            qWarning().noquote() << "Unknown execution target type:" << type;
            return std::nullopt;
        }
    }

} // namespace Serializer