#pragma once

#include "Command.hpp"
#include "IconSource.hpp"
#include "Uri.hpp"

#include <QList>
#include <QUuid>

namespace Shared::Models::ExecutionTarget {

    class ExecutionTarget {

      public:
        enum class Type { DesktopApplication, ExecutableFile, Command, OpenFile, OpenUrl, Group };

        explicit ExecutionTarget( const QUuid& uuid,
                                  const QString& name,
                                  const Type type,
                                  const QList<IconSource>& iconSources,
                                  const QList<Command>& commands,
                                  const QList<Uri>& uriList )
            : uuid( uuid ), name( name ), type( type ), iconSources( iconSources ),
              commands( commands ), uriList( uriList ) {}

        QUuid uuid;
        QString name;
        Type type;
        QList<IconSource> iconSources;
        QList<Command> commands;
        QList<Uri> uriList;
    };

} // namespace Shared::Models::ExecutionTarget
