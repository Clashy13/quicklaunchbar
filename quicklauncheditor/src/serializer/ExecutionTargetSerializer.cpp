#include "ExecutionTargetSerializer.hpp"

#include "../models/ExecutableFileExecutionTarget.hpp"
#include "../models/OpenFileExecutionTarget.hpp"
#include "../models/OpenUrlExecutionTarget.hpp"
#include "../models/ProgramExecutionTarget.hpp"
#include "shared/serializer/IconSourceSerializer.hpp"
#include "shared/serializer/PropertySerializer.hpp"

#include <QFileInfo>
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
                obj[ ExecutionTargetSerializer::nameStr ] = programExecutionTarget->name();
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

                const auto useDefaultName = executableFileExecutionTarget->name().isEmpty();
                obj[ ExecutionTargetSerializer::useDefaultNameStr ] = useDefaultName;

                auto name = executableFileExecutionTarget->name();
                if ( useDefaultName ) {
                    name = QFileInfo( executableFileExecutionTarget->filePath() ).fileName();
                }
                obj[ ExecutionTargetSerializer::nameStr ] = name;
                return obj;
            }
            case Type::Command: {
                const auto programExecutionTarget =
                    dynamic_cast<Models::ProgramExecutionTarget*>( executionTarget );
                obj[ ExecutionTargetSerializer::iconSourceStr ] =
                    Shared::Serializer::IconSourceSerializer::deserialized(
                        programExecutionTarget->iconSource() );
                obj[ ExecutionTargetSerializer::commandStr ] = programExecutionTarget->command();

                const auto useDefaultName = programExecutionTarget->name().isEmpty();
                obj[ ExecutionTargetSerializer::useDefaultNameStr ] = useDefaultName;

                auto name = programExecutionTarget->name();
                if ( useDefaultName ) {
                    name = programExecutionTarget->command();
                }
                obj[ ExecutionTargetSerializer::nameStr ] = name;
                return obj;
            }
            case Type::OpenFile: {
                const auto fileExecutionTarget =
                    dynamic_cast<Models::OpenFileExecutionTarget*>( executionTarget );
                obj[ ExecutionTargetSerializer::iconSourceStr ] =
                    Shared::Serializer::IconSourceSerializer::deserialized(
                        fileExecutionTarget->iconSource() );

                obj[ ExecutionTargetSerializer::filePathStr ] = fileExecutionTarget->filePath();

                const auto useDefaultName = fileExecutionTarget->name().isEmpty();
                obj[ ExecutionTargetSerializer::useDefaultNameStr ] = useDefaultName;

                auto name = fileExecutionTarget->name();
                if ( useDefaultName ) {
                    name = QFileInfo( fileExecutionTarget->filePath() ).fileName();
                }
                obj[ ExecutionTargetSerializer::nameStr ] = name;
                return obj;
            }
            case Type::OpenUrl: {
                const auto urlExecutionTarget =
                    dynamic_cast<Models::OpenUrlExecutionTarget*>( executionTarget );
                obj[ ExecutionTargetSerializer::iconSourceStr ] =
                    Shared::Serializer::IconSourceSerializer::deserialized(
                        urlExecutionTarget->iconSource() );
                obj[ ExecutionTargetSerializer::urlStr ] = urlExecutionTarget->url().toString();

                const auto useDefaultName = urlExecutionTarget->name().isEmpty();
                obj[ ExecutionTargetSerializer::useDefaultNameStr ] = useDefaultName;

                auto name = urlExecutionTarget->name();
                if ( useDefaultName ) {
                    name = urlExecutionTarget->url().toString();
                }
                obj[ ExecutionTargetSerializer::nameStr ] = name;
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

    std::optional<bool>
    ExecutionTargetSerializer::serializedUseDefaultName( const QJsonObject& obj ) {
        if ( const auto useDefaultNameOpt =
                 Shared::Serializer::PropertySerializer::serializedBoolProperty(
                     obj,
                     ExecutionTargetSerializer::useDefaultNameStr ) ) {
            return *useDefaultNameOpt;
        } else {
            return std::nullopt;
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
                    const auto useDefaultName =
                        ExecutionTargetSerializer::serializedUseDefaultName( obj );

                    if ( iconSource && command && useDefaultName ) {
                        auto arguments = QProcess::splitCommand( *command );
                        const auto filePath = arguments.takeFirst();

                        return new Models::ExecutableFileExecutionTarget( *uuid,
                                                                          *useDefaultName ? ""
                                                                                          : *name,
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
                    const auto useDefaultName =
                        ExecutionTargetSerializer::serializedUseDefaultName( obj );

                    if ( iconSource && command && useDefaultName ) {
                        return new Models::ProgramExecutionTarget( *uuid,
                                                                   *useDefaultName ? "" : *name,
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
                    const auto useDefaultName =
                        ExecutionTargetSerializer::serializedUseDefaultName( obj );

                    if ( iconSource && filePath && useDefaultName ) {
                        return new Models::OpenFileExecutionTarget( *uuid,
                                                                    *useDefaultName ? "" : *name,
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
                    const auto useDefaultName =
                        ExecutionTargetSerializer::serializedUseDefaultName( obj );

                    if ( iconSource && url && useDefaultName ) {
                        return new Models::OpenUrlExecutionTarget( *uuid,
                                                                   *useDefaultName ? "" : *name,
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