#include "ExecutionTargetSerializer.hpp"

#include "shared/serializer/IconSourceSerializer.hpp"
#include "shared/serializer/PropertySerializer.hpp"

#include <QFileInfo>
#include <QProcess>
#include <optional>

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
        using Type = Shared::Models::ExecutionTarget::Type;
        switch ( executionTarget->type() ) {
            case Type::DesktopApplication:
                return ExecutionTargetSerializer::deserializedDesktopApplication(
                    dynamic_cast<Models::DesktopApplicationExecutionTarget*>( executionTarget ) );
            case Type::ExecutableFile:
                return ExecutionTargetSerializer::deserializedExecutableFile(
                    dynamic_cast<Models::ExecutableFileExecutionTarget*>( executionTarget ) );
            case Type::Command:
                return ExecutionTargetSerializer::deserializedCommandExecutionTarget(
                    dynamic_cast<Models::CommandExecutionTarget*>( executionTarget ) );
            case Type::OpenFile:
                return ExecutionTargetSerializer::deserializedOpenFile(
                    dynamic_cast<Models::OpenFileExecutionTarget*>( executionTarget ) );
            case Type::OpenUrl:
                return ExecutionTargetSerializer::deserializedOpenUrl(
                    dynamic_cast<Models::OpenUrlExecutionTarget*>( executionTarget ) );
            case Type::Group:
                return ExecutionTargetSerializer::deserializedGroup(
                    dynamic_cast<Models::GroupExecutionTarget*>( executionTarget ) );
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

    std::optional<bool>
    ExecutionTargetSerializer::serializedUseDefaultIconSource( const QJsonObject& obj ) {
        if ( const auto useDefaultIconSourceOpt =
                 Shared::Serializer::PropertySerializer::serializedBoolProperty(
                     obj,
                     ExecutionTargetSerializer::useDefaultIconSourceStr ) ) {
            return *useDefaultIconSourceOpt;
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
        if ( const auto type = ExecutionTargetSerializer::serializedType( obj ) ) {
            using Type = Shared::Models::ExecutionTarget::Type;
            switch ( *type ) {
                case Type::DesktopApplication:
                    return ExecutionTargetSerializer::serializedDesktopApplication( obj );
                case Type::ExecutableFile:
                    return ExecutionTargetSerializer::serializedExecutableFile( obj );
                case Type::Command:
                    return ExecutionTargetSerializer::serializedCommandExecutionTarget( obj );
                case Type::OpenFile:
                    return ExecutionTargetSerializer::serializedOpenFile( obj );
                case Type::OpenUrl:
                    return ExecutionTargetSerializer::serializedOpenUrl( obj );
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

    std::optional<Models::DesktopApplicationExecutionTarget*>
    ExecutionTargetSerializer::serializedDesktopApplication( const QJsonObject& obj ) {
        const auto uuid = ExecutionTargetSerializer::serializedUuid( obj );
        const auto name = ExecutionTargetSerializer::serializedName( obj );
        const auto iconSource = ExecutionTargetSerializer::serializedIconSource( obj );
        const auto command = ExecutionTargetSerializer::serializedCommand( obj );

        if ( uuid && name && iconSource && command ) {
            return new Models::DesktopApplicationExecutionTarget(
                *uuid,
                *name,
                Shared::Models::ExecutionTarget::Type::DesktopApplication,
                *iconSource,
                *command );
        } else {
            return std::nullopt;
        }
    }

    std::optional<Models::ExecutableFileExecutionTarget*>
    ExecutionTargetSerializer::serializedExecutableFile( const QJsonObject& obj ) {
        const auto uuid = ExecutionTargetSerializer::serializedUuid( obj );
        const auto name = ExecutionTargetSerializer::serializedName( obj );
        const auto iconSource = ExecutionTargetSerializer::serializedIconSource( obj );
        const auto command = ExecutionTargetSerializer::serializedCommand( obj );
        const auto useDefaultName = ExecutionTargetSerializer::serializedUseDefaultName( obj );
        const auto useDefaultIconSource =
            ExecutionTargetSerializer::serializedUseDefaultIconSource( obj );

        if ( uuid && name && iconSource && command && useDefaultName && useDefaultIconSource ) {
            auto arguments = QProcess::splitCommand( *command );
            const auto filePath = arguments.takeFirst();

            return new Models::ExecutableFileExecutionTarget(
                *uuid,
                *useDefaultName ? "" : *name,
                Shared::Models::ExecutionTarget::Type::ExecutableFile,
                filePath,
                arguments.join( " " ),
                *useDefaultIconSource ? "" : iconSource->value );
        } else {
            return std::nullopt;
        }
    }

    std::optional<Models::CommandExecutionTarget*>
    ExecutionTargetSerializer::serializedCommandExecutionTarget( const QJsonObject& obj ) {
        const auto uuid = ExecutionTargetSerializer::serializedUuid( obj );
        const auto name = ExecutionTargetSerializer::serializedName( obj );
        const auto iconSource = ExecutionTargetSerializer::serializedIconSource( obj );
        const auto command = ExecutionTargetSerializer::serializedCommand( obj );
        const auto useDefaultName = ExecutionTargetSerializer::serializedUseDefaultName( obj );
        const auto useDefaultIconSource =
            ExecutionTargetSerializer::serializedUseDefaultIconSource( obj );

        if ( uuid && name && iconSource && command && useDefaultName && useDefaultIconSource ) {
            return new Models::CommandExecutionTarget(
                *uuid,
                *useDefaultName ? "" : *name,
                Shared::Models::ExecutionTarget::Type::Command,
                *command,
                *useDefaultIconSource ? "" : iconSource->value );
        } else {
            return std::nullopt;
        }
    }

    std::optional<Models::OpenFileExecutionTarget*>
    ExecutionTargetSerializer::serializedOpenFile( const QJsonObject& obj ) {
        const auto uuid = ExecutionTargetSerializer::serializedUuid( obj );
        const auto name = ExecutionTargetSerializer::serializedName( obj );
        const auto iconSource = ExecutionTargetSerializer::serializedIconSource( obj );
        const auto filePath = ExecutionTargetSerializer::serializedFilePath( obj );
        const auto useDefaultName = ExecutionTargetSerializer::serializedUseDefaultName( obj );
        const auto useDefaultIconSource =
            ExecutionTargetSerializer::serializedUseDefaultIconSource( obj );

        if ( uuid && name && iconSource && filePath && useDefaultName && useDefaultIconSource ) {
            return new Models::OpenFileExecutionTarget(
                *uuid,
                *useDefaultName ? "" : *name,
                Shared::Models::ExecutionTarget::Type::OpenFile,
                *filePath,
                *useDefaultIconSource ? "" : iconSource->value );
        } else {
            return std::nullopt;
        }
    }

    std::optional<Models::OpenUrlExecutionTarget*>
    ExecutionTargetSerializer::serializedOpenUrl( const QJsonObject& obj ) {
        const auto uuid = ExecutionTargetSerializer::serializedUuid( obj );
        const auto name = ExecutionTargetSerializer::serializedName( obj );
        const auto iconSource = ExecutionTargetSerializer::serializedIconSource( obj );
        const auto url = ExecutionTargetSerializer::serializedUrl( obj );
        const auto useDefaultName = ExecutionTargetSerializer::serializedUseDefaultName( obj );
        const auto useDefaultIconSource =
            ExecutionTargetSerializer::serializedUseDefaultIconSource( obj );

        if ( uuid && name && iconSource && url && useDefaultName && useDefaultIconSource ) {
            return new Models::OpenUrlExecutionTarget(
                *uuid,
                *useDefaultName ? "" : *name,
                Shared::Models::ExecutionTarget::Type::OpenUrl,
                *url,
                *useDefaultIconSource ? "" : iconSource->value );
        } else {
            return std::nullopt;
        }
    }

    std::optional<Models::GroupExecutionTarget*>
    ExecutionTargetSerializer::serializedGroup( const QJsonObject& obj ) {
        const auto uuid = ExecutionTargetSerializer::serializedUuid( obj );
        const auto name = ExecutionTargetSerializer::serializedName( obj );
        const auto executionTargets =
            ExecutionTargetSerializer::serializedSingleExecutionTargets( obj );

        if ( uuid && name && executionTargets ) {
            return new Models::GroupExecutionTarget( *uuid,
                                                     *name,
                                                     Shared::Models::ExecutionTarget::Type::Group,
                                                     *executionTargets );
        } else {
            return std::nullopt;
        }
    }

    QJsonObject ExecutionTargetSerializer::deserializedDesktopApplication(
        Models::DesktopApplicationExecutionTarget* executionTarget ) {
        return { { ExecutionTargetSerializer::uuidStr,
                   executionTarget->uuid().toString( QUuid::WithoutBraces ) },
                 { ExecutionTargetSerializer::typeStr,
                   ExecutionTargetSerializer::typeToString( executionTarget->type() ) },
                 { ExecutionTargetSerializer::nameStr, executionTarget->name() },
                 { ExecutionTargetSerializer::commandStr, executionTarget->command() },
                 { ExecutionTargetSerializer::iconSourceStr,
                   Shared::Serializer::IconSourceSerializer::deserialized(
                       executionTarget->iconSource() ) } };
    }

    QJsonObject ExecutionTargetSerializer::deserializedExecutableFile(
        Models::ExecutableFileExecutionTarget* executionTarget ) {
        QJsonObject obj;
        obj[ ExecutionTargetSerializer::uuidStr ] =
            executionTarget->uuid().toString( QUuid::WithoutBraces );
        obj[ ExecutionTargetSerializer::typeStr ] =
            ExecutionTargetSerializer::typeToString( executionTarget->type() );

        obj[ ExecutionTargetSerializer::commandStr ] =
            executionTarget->filePath() + " " + executionTarget->arguments();

        const auto useDefaultIconSource = executionTarget->iconFilePath().isEmpty();
        obj[ ExecutionTargetSerializer::useDefaultIconSourceStr ] = useDefaultIconSource;

        using IconSource = Shared::Models::ExecutionTarget::IconSource;
        if ( useDefaultIconSource ) {
            IconSource iconSource( IconSource::Type::FromFile, executionTarget->filePath() );
            obj[ ExecutionTargetSerializer::iconSourceStr ] =
                Shared::Serializer::IconSourceSerializer::deserialized( iconSource );
        } else {
            IconSource iconSource( IconSource::Type::Image, executionTarget->iconFilePath() );
            obj[ ExecutionTargetSerializer::iconSourceStr ] =
                Shared::Serializer::IconSourceSerializer::deserialized( iconSource );
        }

        const auto useDefaultName = executionTarget->name().isEmpty();
        obj[ ExecutionTargetSerializer::useDefaultNameStr ] = useDefaultName;

        auto name = executionTarget->name();
        if ( useDefaultName ) {
            name = QFileInfo( executionTarget->filePath() ).fileName();
        }
        obj[ ExecutionTargetSerializer::nameStr ] = name;
        return obj;
    }

    QJsonObject ExecutionTargetSerializer::deserializedCommandExecutionTarget(
        Models::CommandExecutionTarget* executionTarget ) {
        QJsonObject obj;
        obj[ ExecutionTargetSerializer::uuidStr ] =
            executionTarget->uuid().toString( QUuid::WithoutBraces );
        obj[ ExecutionTargetSerializer::typeStr ] =
            ExecutionTargetSerializer::typeToString( executionTarget->type() );

        obj[ ExecutionTargetSerializer::commandStr ] = executionTarget->command();

        const auto useDefaultIconSource = executionTarget->iconFilePath().isEmpty();
        obj[ ExecutionTargetSerializer::useDefaultIconSourceStr ] = useDefaultIconSource;

        using IconSource = Shared::Models::ExecutionTarget::IconSource;
        if ( useDefaultIconSource ) {
            IconSource iconSource( IconSource::Type::Resource, "command_icon" );
            obj[ ExecutionTargetSerializer::iconSourceStr ] =
                Shared::Serializer::IconSourceSerializer::deserialized( iconSource );
        } else {
            IconSource iconSource( IconSource::Type::Image, executionTarget->iconFilePath() );
            obj[ ExecutionTargetSerializer::iconSourceStr ] =
                Shared::Serializer::IconSourceSerializer::deserialized( iconSource );
        }

        const auto useDefaultName = executionTarget->name().isEmpty();
        obj[ ExecutionTargetSerializer::useDefaultNameStr ] = useDefaultName;

        auto name = executionTarget->name();
        if ( useDefaultName ) {
            name = executionTarget->command();
        }
        obj[ ExecutionTargetSerializer::nameStr ] = name;
        return obj;
    }

    QJsonObject ExecutionTargetSerializer::deserializedOpenFile(
        Models::OpenFileExecutionTarget* executionTarget ) {
        QJsonObject obj;
        obj[ ExecutionTargetSerializer::uuidStr ] =
            executionTarget->uuid().toString( QUuid::WithoutBraces );
        obj[ ExecutionTargetSerializer::typeStr ] =
            ExecutionTargetSerializer::typeToString( executionTarget->type() );

        obj[ ExecutionTargetSerializer::filePathStr ] = executionTarget->filePath();

        const auto useDefaultIconSource = executionTarget->iconFilePath().isEmpty();
        obj[ ExecutionTargetSerializer::useDefaultIconSourceStr ] = useDefaultIconSource;

        using IconSource = Shared::Models::ExecutionTarget::IconSource;
        if ( useDefaultIconSource ) {
            IconSource iconSource( IconSource::Type::FromFile, executionTarget->filePath() );
            obj[ ExecutionTargetSerializer::iconSourceStr ] =
                Shared::Serializer::IconSourceSerializer::deserialized( iconSource );
        } else {
            IconSource iconSource( IconSource::Type::Image, executionTarget->iconFilePath() );
            obj[ ExecutionTargetSerializer::iconSourceStr ] =
                Shared::Serializer::IconSourceSerializer::deserialized( iconSource );
        }

        const auto useDefaultName = executionTarget->name().isEmpty();
        obj[ ExecutionTargetSerializer::useDefaultNameStr ] = useDefaultName;

        auto name = executionTarget->name();
        if ( useDefaultName ) {
            name = QFileInfo( executionTarget->filePath() ).fileName();
        }
        obj[ ExecutionTargetSerializer::nameStr ] = name;
        return obj;
    }

    QJsonObject ExecutionTargetSerializer::deserializedOpenUrl(
        Models::OpenUrlExecutionTarget* executionTarget ) {
        QJsonObject obj;
        obj[ ExecutionTargetSerializer::uuidStr ] =
            executionTarget->uuid().toString( QUuid::WithoutBraces );
        obj[ ExecutionTargetSerializer::typeStr ] =
            ExecutionTargetSerializer::typeToString( executionTarget->type() );

        obj[ ExecutionTargetSerializer::urlStr ] = executionTarget->url().toString();

        const auto useDefaultIconSource = executionTarget->iconFilePath().isEmpty();
        obj[ ExecutionTargetSerializer::useDefaultIconSourceStr ] = useDefaultIconSource;

        using IconSource = Shared::Models::ExecutionTarget::IconSource;
        if ( useDefaultIconSource ) {
            // temp placeholder for browser icon
            // TODO
            IconSource iconSource( IconSource::Type::Theme, "firefox" );
            obj[ ExecutionTargetSerializer::iconSourceStr ] =
                Shared::Serializer::IconSourceSerializer::deserialized( iconSource );
        } else {
            IconSource iconSource( IconSource::Type::Image, executionTarget->iconFilePath() );
            obj[ ExecutionTargetSerializer::iconSourceStr ] =
                Shared::Serializer::IconSourceSerializer::deserialized( iconSource );
        }

        const auto useDefaultName = executionTarget->name().isEmpty();
        obj[ ExecutionTargetSerializer::useDefaultNameStr ] = useDefaultName;

        auto name = executionTarget->name();
        if ( useDefaultName ) {
            name = executionTarget->url().toString();
        }
        obj[ ExecutionTargetSerializer::nameStr ] = name;
        return obj;
    }

    QJsonObject
    ExecutionTargetSerializer::deserializedGroup( Models::GroupExecutionTarget* executionTarget ) {
        return { { ExecutionTargetSerializer::uuidStr,
                   executionTarget->uuid().toString( QUuid::WithoutBraces ) },
                 { ExecutionTargetSerializer::typeStr,
                   ExecutionTargetSerializer::typeToString( executionTarget->type() ) },
                 { ExecutionTargetSerializer::nameStr, executionTarget->name() },
                 { ExecutionTargetSerializer::executionTargetsStr,
                   ExecutionTargetSerializer::deserializedSingleExecutionTargets(
                       executionTarget->executionTargets() ) } };
    }
} // namespace Editor::Serializer