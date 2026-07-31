#pragma once

#include <QString>

namespace Shared::Models::ExecutionTarget {

    class Uri {
      public:
        enum class Type { File, Url };

        Uri( const Type type, const QString& value ) : type( type ), value( value ) {}

        Uri::Type type;
        QString value;
    };
} // namespace Shared::Models::ExecutionTarget