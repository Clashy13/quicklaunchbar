#pragma once

#include <QString>
#include <QStringList>

namespace Shared::Models::ExecutionTarget {

    class IconSource {
      public:
        enum class Type { Theme, FromFile, Image, Resource };

        explicit IconSource( const IconSource::Type type, const QString& value )
            : type( type ), value( value ) {}

        bool operator==( const IconSource& other ) {
            return this->type == other.type && this->value == other.value;
        }

        IconSource::Type type;
        QString value;
    };
} // namespace Shared::Models::ExecutionTarget
