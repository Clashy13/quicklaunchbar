#pragma once

#include <QString>

namespace Models::ExecutionTarget {

    class Uri {
      public:
        enum Type { File, Url };

        Uri( Type type, const QString& value ) : type( type ), value( value ) {}

        Type type;
        QString value;
    };
} // namespace Models::ExecutionTarget