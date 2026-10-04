#include "ExecutionTargetManager.hpp"

#include "../models/CommandExecutionTarget.hpp"
#include "../models/ExecutableFileExecutionTarget.hpp"
#include "../models/GroupExecutionTarget.hpp"
#include "../models/OpenFileExecutionTarget.hpp"
#include "../models/OpenUrlExecutionTarget.hpp"
#include "../serializer/ExecutionTargetSerializer.hpp"
#include "shared/models/ExecutionTargetType.hpp"
#include "shared/serializer/PropertySerializer.hpp"

#include <QApplication>
#include <QClipboard>
#include <QJsonDocument>
#include <QJsonObject>
#include <optional>
#include <qurl.h>
#include <quuid.h>

namespace Editor::Manager {

    ExecutionTargetManager::ExecutionTargetManager( QObject* parent ) : QObject( parent ) {}

    ExecutionTargetManager* ExecutionTargetManager::instance() {
        static ExecutionTargetManager executionTargetManager;
        return &executionTargetManager;
    }

    QString ExecutionTargetManager::contentSource( const Type type ) {
        switch ( type ) {
            case Type::DesktopApplication:
                return "qrc:/executiontargets/DesktopApplicationContent.qml";
            case Type::ExecutableFile:
                return "qrc:/executiontargets/ExecutableFileContent.qml";
            case Type::Command:
                return "qrc:/executiontargets/CommandContent.qml";
            case Type::OpenFile:
                return "qrc:/executiontargets/OpenFileContent.qml";
            case Type::OpenUrl:
                return "qrc:/executiontargets/OpenUrlContent.qml";
            case Type::Group:
                return "qrc:/executiontargets/GroupContent.qml";
            default:
                return "";
        }
    }

    QString ExecutionTargetManager::typeToString( const Type type ) {
        return this->_executionTargetNames[ static_cast<qsizetype>( type ) ];
    }

    Models::ExecutionTarget* ExecutionTargetManager::newExecutionTarget( const Type type ) {
        switch ( type ) {
            case Type::ExecutableFile:
                return new Models::ExecutableFileExecutionTarget( QUuid::createUuid(),
                                                                  "",
                                                                  type,
                                                                  "",
                                                                  "",
                                                                  "" );
            case Type::Command:
                return new Models::CommandExecutionTarget( QUuid::createUuid(), "", type, "", "" );
            case Type::OpenFile:
                return new Models::OpenFileExecutionTarget( QUuid::createUuid(), "", type, "", "" );
            case Type::OpenUrl:
                return new Models::OpenUrlExecutionTarget( QUuid::createUuid(),
                                                           "",
                                                           type,
                                                           QUrl( "" ),
                                                           "" );
            case Type::Group:
                return new Models::GroupExecutionTarget( QUuid::createUuid(), "", type, {} );
            default:
                return nullptr;
        }
    }

    Models::DesktopApplicationExecutionTarget*
    ExecutionTargetManager::newDesktopApplication( Models::DesktopApplication* application ) {
        return new Models::DesktopApplicationExecutionTarget( QUuid::createUuid(),
                                                              application->name(),
                                                              Type::DesktopApplication,
                                                              application->iconSource(),
                                                              application->command() );
    }

    void
    ExecutionTargetManager::renewExecutionTargetUuid( Models::ExecutionTarget* executionTarget ) {
        executionTarget->setUuid( QUuid::createUuid() );
        if ( executionTarget->type() == Shared::Models::ExecutionTarget::Type::Group ) {
            for ( auto singleExecutionTarget :
                  dynamic_cast<Models::GroupExecutionTarget*>( executionTarget )
                      ->executionTargets()
                      ->list() ) {
                singleExecutionTarget->setUuid( QUuid::createUuid() );
            }
        }
    }

    void
    ExecutionTargetManager::executionTargetToClipboard( Models::ExecutionTarget* executionTarget ) {
        auto deserializedExecutionTarget =
            Serializer::ExecutionTargetSerializer::deserialized( executionTarget );
        QJsonObject clipboardContent = { { "type", "quicklauncheditor/clipboard" },
                                         { "execution_target", deserializedExecutionTarget } };

        QString clipboardContentStr =
            QJsonDocument( clipboardContent ).toJson( QJsonDocument::Indented );
        QApplication::clipboard()->setText( clipboardContentStr );
    }

    std::optional<Models::ExecutionTarget*> ExecutionTargetManager::executionTargetFromClipboard() {
        QString text = QGuiApplication::clipboard()->text();

        QJsonParseError error;
        QJsonDocument doc = QJsonDocument::fromJson( text.toUtf8(), &error );

        if ( error.error != QJsonParseError::NoError ) {
            return std::nullopt;
        }

        if ( !doc.isObject() ) {
            return std::nullopt;
        }

        QJsonObject clipboardContent = doc.object();

        if ( const auto type =
                 Shared::Serializer::PropertySerializer::serializedStringProperty( clipboardContent,
                                                                                   "type" ) ) {
            if ( *type != "quicklauncheditor/clipboard" ) {
                return std::nullopt;
            }
        }

        if ( const auto executionTargetObj =
                 Shared::Serializer::PropertySerializer::serializedObjectProperty(
                     clipboardContent,
                     "execution_target" ) ) {
            if ( const auto executionTarget =
                     Serializer::ExecutionTargetSerializer::serialized( *executionTargetObj ) ) {
                return executionTarget;
            } else {
                return std::nullopt;
            }
        } else {
            return std::nullopt;
        }
    }
} // namespace Editor::Manager