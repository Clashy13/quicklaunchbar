#pragma once

#include "../models/DesktopApplication.hpp"
#include "../models/DesktopApplicationExecutionTarget.hpp"
#include "../models/ExecutionTarget.hpp"
#include "shared/models/ExecutionTargetType.hpp"

#include <QObject>

namespace Editor::Manager {

    class ExecutionTargetManager : public QObject {
        Q_OBJECT

        Q_PROPERTY( QStringList executionTargetNames READ executionTargetNames CONSTANT )
        Q_PROPERTY(
            QStringList singleExecutionTargetNames READ singleExecutionTargetNames CONSTANT )

        using Type = Shared::Models::ExecutionTarget::Type;

      public:
        static ExecutionTargetManager* instance();

        Q_INVOKABLE QString contentSource( const Type type );

        Q_INVOKABLE QString typeToString( const Type type );

        Q_INVOKABLE Models::ExecutionTarget* newExecutionTarget( const Type type );

        Q_INVOKABLE Models::DesktopApplicationExecutionTarget*
        newDesktopApplication( Models::DesktopApplication* application );

        const QStringList& executionTargetNames() {
            return this->_executionTargetNames;
        }

        const QStringList singleExecutionTargetNames() {
            return this->_executionTargetNames.mid( 0, this->_executionTargetNames.size() - 1 );
        }

      private:
        explicit ExecutionTargetManager( QObject* parent = nullptr );

        const QStringList _executionTargetNames = { "Desktop Application",
                                                    "Executable File",
                                                    "Command",
                                                    "Open File",
                                                    "Open Url",
                                                    "Group" };
    };
} // namespace Editor::Manager
