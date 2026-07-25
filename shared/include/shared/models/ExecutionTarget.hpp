#pragma once

#include "IconSource.hpp"

#include <QList>
#include <QUuid>

namespace Models::ExecutionTarget {

    class ExecutionTarget {
      public:
        enum class Type { DesktopApplication, ExecutableFile, Command, OpenFile, OpenUrl, Group };

        explicit ExecutionTarget( const QUuid& uuid,
                                  const QString& name,
                                  ExecutionTarget::Type type,
                                  const QList<IconSource>& iconSources )
            : uuid( uuid ), name( name ), type( type ), iconSources( iconSources ) {}

        virtual ~ExecutionTarget() = 0;

        QUuid uuid;
        QString name;
        ExecutionTarget::Type type;
        QList<IconSource> iconSources;
    };

    inline ExecutionTarget::~ExecutionTarget() = default;
} // namespace Models::ExecutionTarget
