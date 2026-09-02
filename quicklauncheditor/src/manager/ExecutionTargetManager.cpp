#include "ExecutionTargetManager.hpp"

#include "../models/CommandExecutionTarget.hpp"
#include "../models/ExecutableFileExecutionTarget.hpp"
#include "../models/GroupExecutionTarget.hpp"
#include "../models/OpenFileExecutionTarget.hpp"
#include "../models/OpenUrlExecutionTarget.hpp"

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
} // namespace Editor::Manager