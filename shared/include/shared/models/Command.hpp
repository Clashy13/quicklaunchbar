#pragma once

#include <QString>
#include <QStringList>

namespace Shared::Models::ExecutionTarget {

    class Command {
      public:
        explicit Command( const QString& program, const QStringList& arguments )
            : program( program ), arguments( arguments ) {}

        QString program;
        QStringList arguments;
    };
} // namespace Shared::Models::ExecutionTarget
