#include "ExecutionTargetSerializer.hpp"

#include "../models/ExecutionTarget.hpp"
#include "shared/serializer/IconSourceSerializer.hpp"
#include "shared/serializer/PropertySerializer.hpp"

namespace Service::Serializer {

    std::optional<Models::ExecutionTarget*>
    ExecutionTargetSerializer::serialized( const QJsonObject& obj ) {
        const auto uuid = ExecutionTargetSerializer::serializedUuid( obj );
        const auto name = ExecutionTargetSerializer::serializedName( obj );
        const auto type = ExecutionTargetSerializer::serializedType( obj );
        QList<QUrl> iconSources;
        QList<Command> commands;
        QList<QUrl> uriList;

        if ( uuid && name && type ) {
            if ( *type == Type::Group ) {
                if ( const auto array =
                         Shared::Serializer::PropertySerializer::serializedArrayProperty(
                             obj,
                             ExecutionTargetSerializer::executionTargetsStr ) ) {
                    for ( const auto element : *array ) {
                        if ( !element.isObject() ) {
                            qWarning().noquote() << "Property list element is not an object";
                            return std::nullopt;
                        }

                        const auto executionTargetObj = element.toObject();
                        const auto elementType =
                            ExecutionTargetSerializer::serializedType( executionTargetObj );
                        if ( elementType ) {
                            const auto success =
                                ExecutionTargetSerializer::serializeSingleProperties(
                                    iconSources,
                                    commands,
                                    uriList,
                                    *elementType,
                                    executionTargetObj );
                        }
                    }
                }
            } else {
                const auto success =
                    ExecutionTargetSerializer::serializeSingleProperties( iconSources,
                                                                          commands,
                                                                          uriList,
                                                                          *type,
                                                                          obj );
                if ( !success ) {
                    return std::nullopt;
                }
            }
            return new Models::ExecutionTarget( *uuid,
                                                *name,
                                                *type,
                                                iconSources,
                                                commands,
                                                uriList );
        } else {
            return std::nullopt;
        }
    }

    bool ExecutionTargetSerializer::serializeSingleProperties( QList<QUrl>& iconSources,
                                                               QList<Command>& commands,
                                                               QList<QUrl>& uriList,
                                                               const Type type,
                                                               const QJsonObject& obj ) {
        if ( type != Type::Group ) {
            if ( const auto iconSource = ExecutionTargetSerializer::serializedIconSource( obj ) ) {
                iconSources.push_back(
                    Shared::Serializer::IconSourceSerializer::iconSourceToUrl( *iconSource ) );
            } else {
                return false;
            }
        }
        switch ( type ) {
            case Type::DesktopApplication:
            case Type::ExecutableFile:
            case Type::Command: {
                if ( const auto command = ExecutionTargetSerializer::serializedCommand( obj ) ) {
                    commands.push_back( *command );
                    break;
                } else {
                    return false;
                }
            }
            case Type::OpenFile: {
                if ( const auto filePath = ExecutionTargetSerializer::serializedFilePath( obj ) ) {
                    uriList.push_back( QUrl::fromLocalFile( *filePath ) );
                    break;
                } else {
                    return false;
                }
            }
            case Type::OpenUrl: {
                if ( const auto url = ExecutionTargetSerializer::serializedUrl( obj ) ) {
                    uriList.push_back( QUrl( *url ) );
                    break;
                } else {
                    return false;
                }
            }
            default:
                return false;
        }
        return true;
    }

} // namespace Service::Serializer