#include "ExecutionTargetSerializer.hpp"

#include "IconSourceSerializer.hpp"
#include "PropertySerializer.hpp"

#include <QProcess>
#include <optional>

namespace Shared::Serializer {

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

    std::optional<ExecutionTargetSerializer::Type>
    ExecutionTargetSerializer::serializedType( const QJsonObject& obj ) {
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

    std::optional<Models::ExecutionTarget::IconSource>
    ExecutionTargetSerializer::serializedIconSource( const QJsonObject& obj ) {
        if ( const auto iconSourceObjOpt = PropertySerializer::serializedObjectProperty(
                 obj,
                 ExecutionTargetSerializer::iconSourceStr ) ) {
            if ( const auto iconSourceOpt =
                     IconSourceSerializer::serialized( *iconSourceObjOpt ) ) {
                return *iconSourceOpt;
            }
        }
        return std::nullopt;
    }

    std::optional<Models::ExecutionTarget::Command>
    ExecutionTargetSerializer::serializedCommand( const QJsonObject& obj ) {
        if ( const auto commandOpt = PropertySerializer::serializedStringProperty(
                 obj,
                 ExecutionTargetSerializer::commandStr ) ) {
            auto arguments = QProcess::splitCommand( *commandOpt );
            const auto program = arguments.takeFirst();
            Command cmd( program, arguments );
            return cmd;
        }
        return std::nullopt;
    }

    std::optional<QString> ExecutionTargetSerializer::serializedFilePath( const QJsonObject& obj ) {
        if ( const auto filePathOpt = PropertySerializer::serializedStringProperty(
                 obj,
                 ExecutionTargetSerializer::filePathStr ) ) {
            return *filePathOpt;
        } else {
            return std::nullopt;
        }
    }

    std::optional<QUrl> ExecutionTargetSerializer::serializedUrl( const QJsonObject& obj ) {
        if ( const auto urlOpt = PropertySerializer::serializedStringProperty(
                 obj,
                 ExecutionTargetSerializer::urlStr ) ) {
            return QUrl( *urlOpt );
        } else {
            return std::nullopt;
        }
    }

    QString ExecutionTargetSerializer::typeToString( const Type type ) {
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

    std::optional<ExecutionTargetSerializer::Type>
    ExecutionTargetSerializer::typeFromString( const QString& type ) {
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

} // namespace Shared::Serializer