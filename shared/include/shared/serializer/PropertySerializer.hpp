#pragma once

#include <QJsonArray>
#include <QJsonObject>
#include <optional>

namespace Serializer {

    class PropertySerializer {
      public:
        static std::optional<QString> serializedStringProperty( const QJsonObject& obj,
                                                                const QString& key );

        static std::optional<int> serializedIntProperty( const QJsonObject& obj,
                                                         const QString& key );

        static std::optional<QJsonObject> serializedObjectProperty( const QJsonObject& obj,
                                                                    const QString& key );

        static std::optional<QJsonArray> serializedArrayProperty( const QJsonObject& obj,
                                                                  const QString& key );

      private:
        static bool containsKey( const QJsonObject& obj, const QString& key );
    };

} // namespace Serializer