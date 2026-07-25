#pragma once

#include "Command.hpp"
#include "ExecutionTarget.hpp"
#include "Uri.hpp"

namespace Models::ExecutionTarget {

    class GroupExecutionTarget : public ExecutionTarget {
      public:
        explicit GroupExecutionTarget( const QUuid& uuid,
                                       const QString& name,
                                       ExecutionTarget::Type type,
                                       const QList<IconSource>& iconSources,
                                       const QList<Command>& commands,
                                       const QList<Uri>& uriList )
            : ExecutionTarget( uuid, name, type, iconSources ), commands( commands ),
              uriList( uriList ) {}

        QList<Command> commands;
        QList<Uri> uriList;
    };
} // namespace Models::ExecutionTarget
