#pragma once

#include "Command.hpp"
#include "ExecutionTarget.hpp"

namespace Models::ExecutionTarget {

    class UriExecutionTarget : public ExecutionTarget {
      public:
        explicit UriExecutionTarget( const QUuid& uuid,
                                     const QString& name,
                                     ExecutionTarget::Type type,
                                     const QList<IconSource>& iconSources,
                                     const QString& uri )
            : ExecutionTarget( uuid, name, type, iconSources ), uri( uri ) {}

        QString uri;
    };
} // namespace Models::ExecutionTarget
