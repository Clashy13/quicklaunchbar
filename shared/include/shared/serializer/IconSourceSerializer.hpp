#pragma once

#include "../models/IconSource.hpp"

#include <QJsonObject>
#include <optional>

namespace Shared::Serializer {

    class IconSourceSerializer {

      protected:
        using IconSource = Models::ExecutionTarget::IconSource;

      public:
        static std::optional<IconSource> serialized( const QJsonObject& obj );

        static QJsonObject deserialized( const IconSource& iconSource );

        static QUrl iconSourceToUrl( const IconSource& iconSource );

      private:
        static std::optional<IconSource::Type> serializedType( const QJsonObject& obj );

        static std::optional<QString> serializedValue( const QJsonObject& obj );

        static QString typeToString( const IconSource::Type type );

        static std::optional<IconSource::Type> typeFromString( const QString& type );

        static constexpr auto typeStr = "type";
        static constexpr auto valueStr = "value";

        static constexpr auto themeTypeStr = "theme";
        static constexpr auto fromFileTypeStr = "from_file";
        static constexpr auto imageTypeStr = "image";
        static constexpr auto resourceTypeStr = "resource";
    };

} // namespace Shared::Serializer