#pragma once

#include "../models/Uri.hpp"

#include <QJsonObject>
#include <optional>

namespace Shared::Serializer {

    class UriSerializer {

      protected:
        using Uri = Models::ExecutionTarget::Uri;

      public:
        static std::optional<Uri> serialized( const QJsonObject& obj );

        static QJsonObject deserialized( const Uri& command );

      private:
        static std::optional<Uri::Type> serializedType( const QJsonObject& obj );

        static std::optional<QString> serializedValue( const QJsonObject& obj );

        static std::optional<Uri::Type> typeFromString( const QString& type );

        static QString typeToString( const Uri::Type type );

        static constexpr auto typeStr = "type";
        static constexpr auto valueStr = "value";

        static constexpr auto fileTypeStr = "file";
        static constexpr auto urlTypeStr = "url";
    };

} // namespace Shared::Serializer