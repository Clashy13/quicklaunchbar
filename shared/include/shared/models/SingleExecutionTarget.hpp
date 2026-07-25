#pragma once

#include "Command.hpp"
#include "ExecutionTarget.hpp"

namespace Models::ExecutionTarget {

    class SingleExecutionTarget : public ExecutionTarget {
      public:
        explicit SingleExecutionTarget( const QUuid& uuid,
                                        const QString& name,
                                        ExecutionTarget::Type type,
                                        const QList<IconSource>& iconSources,
                                        const Command& command )
            : ExecutionTarget( uuid, name, type, iconSources ), command( command ) {}

        Command command;
    };
} // namespace Models::ExecutionTarget
