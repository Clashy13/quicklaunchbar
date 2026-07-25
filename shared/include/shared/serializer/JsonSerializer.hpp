#pragma once

#include <QJsonObject>
#include <QString>

namespace Serializer {

    class JsonSerializer {
      public:
        static QJsonObject loadJsonObject( const QString& filePath );

        static bool saveJsonObject( const QJsonObject& json, const QString& filePath );
    };
} // namespace Serializer