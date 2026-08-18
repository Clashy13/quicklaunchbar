#include "ExecutionTargetSerializer.hpp"

#include "../models/ExecutableFileExecutionTarget.hpp"
#include "../models/OpenFileExecutionTarget.hpp"
#include "../models/OpenUrlExecutionTarget.hpp"
#include "../models/ProgramExecutionTarget.hpp"
#include "shared/serializer/IconSourceSerializer.hpp"
#include "shared/serializer/PropertySerializer.hpp"

#include <QProcess>

namespace Editor::Serializer {

    std::optional<Models::ExecutionTarget*>
    ExecutionTargetSerializer::serialized( const QJsonObject& obj ) {
        if ( const auto type = ExecutionTargetSerializer::serializedType( obj ) ) {
            using Type = Shared::Models::ExecutionTarget::Type;
            if ( *type == Type::Group ) {
                return ExecutionTargetSerializer::serializedGroup( obj );
            } else {
                return ExecutionTargetSerializer::serializedSingleExecutionTarget( obj );
            }
        } else {
            return std::nullopt;
        }
    }

    QJsonObject
    ExecutionTargetSerializer::deserialized( Models::ExecutionTarget* executionTarget ) {

        QJsonObject obj;
        obj[ ExecutionTargetSerializer::uuidStr ] =
            executionTarget->uuid().toString( QUuid::WithoutBraces );
        obj[ ExecutionTargetSerializer::nameStr ] = executionTarget->name();
        obj[ ExecutionTargetSerializer::typeStr ] =
            ExecutionTargetSerializer::typeToString( executionTarget->type() );

        using Type = Shared::Models::ExecutionTarget::Type;
        switch ( executionTarget->type() ) {
            case Type::DesktopApplication: {
                const auto programExecutionTarget =
                    dynamic_cast<Models::ProgramExecutionTarget*>( executionTarget );
                obj[ ExecutionTargetSerializer::iconSourceStr ] =
                    Shared::Serializer::IconSourceSerializer::deserialized(
                        programExecutionTarget->iconSource() );
                obj[ ExecutionTargetSerializer::commandStr ] = programExecutionTarget->command();
                return obj;
            }
            case Type::ExecutableFile: {
                const auto executableFileExecutionTarget =
                    dynamic_cast<Models::ExecutableFileExecutionTarget*>( executionTarget );
                obj[ ExecutionTargetSerializer::iconSourceStr ] =
                    Shared::Serializer::IconSourceSerializer::deserialized(
                        executableFileExecutionTarget->iconSource() );
                obj[ ExecutionTargetSerializer::commandStr ] =
                    executableFileExecutionTarget->filePath() + " " +
                    executableFileExecutionTarget->arguments();
                return obj;
            }
            case Type::Command: {
                const auto programExecutionTarget =
                    dynamic_cast<Models::ProgramExecutionTarget*>( executionTarget );
                obj[ ExecutionTargetSerializer::iconSourceStr ] =
                    Shared::Serializer::IconSourceSerializer::deserialized(
                        programExecutionTarget->iconSource() );
                obj[ ExecutionTargetSerializer::commandStr ] = programExecutionTarget->command();
                return obj;
            }
            case Type::OpenFile: {
                const auto fileExecutionTarget =
                    dynamic_cast<Models::OpenFileExecutionTarget*>( executionTarget );
                obj[ ExecutionTargetSerializer::iconSourceStr ] =
                    Shared::Serializer::IconSourceSerializer::deserialized(
                        fileExecutionTarget->iconSource() );
                obj[ ExecutionTargetSerializer::filePathStr ] = fileExecutionTarget->filePath();
                return obj;
            }
            case Type::OpenUrl: {
                const auto urlExecutionTarget =
                    dynamic_cast<Models::OpenUrlExecutionTarget*>( executionTarget );
                obj[ ExecutionTargetSerializer::iconSourceStr ] =
                    Shared::Serializer::IconSourceSerializer::deserialized(
                        urlExecutionTarget->iconSource() );
                obj[ ExecutionTargetSerializer::urlStr ] = urlExecutionTarget->url().toString();
                return obj;
            }
            case Type::Group: {
                const auto groupExecutionTarget =
                    dynamic_cast<Models::GroupExecutionTarget*>( executionTarget );
                obj[ ExecutionTargetSerializer::executionTargetsStr ] =
                    ExecutionTargetSerializer::deserializedSingleExecutionTargets(
                        groupExecutionTarget->executionTargets() );
                return obj;
            }
            default:
                return {};
        }
    }

    std::optional<QString> ExecutionTargetSerializer::serializedCommand( const QJsonObject& obj ) {
        if ( const auto commandOpt =
                 Shared::Serializer::PropertySerializer::serializedStringProperty(
                     obj,
                     ExecutionTargetSerializer::commandStr ) ) {
            return *commandOpt;
        } else {
            return std::nullopt;
        }
    }

    std::optional<Models::SingleExecutionTarget*>
    ExecutionTargetSerializer::serializedSingleExecutionTarget( const QJsonObject& obj ) {
        const auto uuid = ExecutionTargetSerializer::serializedUuid( obj );
        const auto name = ExecutionTargetSerializer::serializedName( obj );
        const auto type = ExecutionTargetSerializer::serializedType( obj );

        using Type = Shared::Models::ExecutionTarget::Type;
        if ( uuid && name && type ) {
            switch ( *type ) {
                case Type::DesktopApplication: {
                    const auto iconSource = ExecutionTargetSerializer::serializedIconSource( obj );
                    const auto command = ExecutionTargetSerializer::serializedCommand( obj );

                    if ( iconSource && command ) {
                        return new Models::ProgramExecutionTarget( *uuid,
                                                                   *name,
                                                                   *type,
                                                                   *iconSource,
                                                                   *command );
                    } else {
                        return std::nullopt;
                    }
                }
                case Type::ExecutableFile: {
                    const auto iconSource = ExecutionTargetSerializer::serializedIconSource( obj );
                    const auto command = ExecutionTargetSerializer::serializedCommand( obj );

                    if ( iconSource && command ) {
                        auto arguments = QProcess::splitCommand( *command );
                        const auto filePath = arguments.takeFirst();
                        return new Models::ExecutableFileExecutionTarget( *uuid,
                                                                          *name,
                                                                          *type,
                                                                          *iconSource,
                                                                          filePath,
                                                                          arguments.join( " " ) );
                    } else {
                        return std::nullopt;
                    }
                }
                case Type::Command: {
                    const auto iconSource = ExecutionTargetSerializer::serializedIconSource( obj );
                    const auto command = ExecutionTargetSerializer::serializedCommand( obj );

                    if ( iconSource && command ) {
                        return new Models::ProgramExecutionTarget( *uuid,
                                                                   *name,
                                                                   *type,
                                                                   *iconSource,
                                                                   *command );
                    } else {
                        return std::nullopt;
                    }
                }
                case Type::OpenFile: {
                    const auto iconSource = ExecutionTargetSerializer::serializedIconSource( obj );
                    const auto filePath = ExecutionTargetSerializer::serializedFilePath( obj );

                    if ( iconSource && filePath ) {
                        return new Models::OpenFileExecutionTarget( *uuid,
                                                                    *name,
                                                                    *type,
                                                                    *iconSource,
                                                                    *filePath );
                    } else {
                        return std::nullopt;
                    }
                }
                case Type::OpenUrl: {
                    const auto iconSource = ExecutionTargetSerializer::serializedIconSource( obj );
                    const auto url = ExecutionTargetSerializer::serializedUrl( obj );

                    if ( iconSource && url ) {
                        return new Models::OpenUrlExecutionTarget( *uuid,
                                                                   *name,
                                                                   *type,
                                                                   *iconSource,
                                                                   *url );
                    } else {
                        return std::nullopt;
                    }
                }
                default:
                    return std::nullopt;
            }
        } else {
            return std::nullopt;
        }
    } // namespace Editor::Serializer

    std::optional<QList<Models::SingleExecutionTarget*>>
    ExecutionTargetSerializer::serializedSingleExecutionTargets( const QJsonObject& obj ) {
        if ( const auto array = Shared::Serializer::PropertySerializer::serializedArrayProperty(
                 obj,
                 ExecutionTargetSerializer::executionTargetsStr ) ) {
            QList<Models::SingleExecutionTarget*> executionTargets;
            for ( const auto element : *array ) {
                if ( !element.isObject() ) {
                    qWarning().noquote() << "Property list element is not an object";
                    return std::nullopt;
                }

                if ( const auto executionTarget =
                         ExecutionTargetSerializer::serializedSingleExecutionTarget(
                             element.toObject() ) ) {
                    executionTargets.push_back( *executionTarget );
                } else {
                    return std::nullopt;
                }
            }
            return executionTargets;
        } else {
            return std::nullopt;
        }
    }

    QJsonArray ExecutionTargetSerializer::deserializedSingleExecutionTargets(
        const QList<Models::SingleExecutionTarget*>& executionTargets ) {
        QJsonArray jsonExecutionTargets;
        for ( const auto executionTarget : executionTargets ) {
            jsonExecutionTargets.push_back(
                ExecutionTargetSerializer::deserialized( executionTarget ) );
        }
        return jsonExecutionTargets;
    }

    std::optional<Models::GroupExecutionTarget*>
    ExecutionTargetSerializer::serializedGroup( const QJsonObject& obj ) {
        const auto uuid = ExecutionTargetSerializer::serializedUuid( obj );
        const auto name = ExecutionTargetSerializer::serializedName( obj );
        const auto type = ExecutionTargetSerializer::serializedType( obj );
        const auto executionTargets =
            ExecutionTargetSerializer::serializedSingleExecutionTargets( obj );

        if ( uuid && name && type && executionTargets ) {
            return new Models::GroupExecutionTarget( *uuid, *name, *type, *executionTargets );
        } else {
            return std::nullopt;
        }
    }
} // namespace Editor::Serializer