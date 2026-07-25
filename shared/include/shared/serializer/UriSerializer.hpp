#pragma once

#include "../models/Uri.hpp"

#include <QJsonObject>
#include <optional>

namespace Serializer {

    using Uri = Models::ExecutionTarget::Uri;

    class UriSerializer {
      public:
        static std::optional<Uri> serialized( const QJsonObject& obj );

        static QJsonObject deserialized( const Uri& command );

      private:
        static QString typeToString( const Uri::Type type );

        static std::optional<Uri::Type> typeFromString( const QString& type );

        static constexpr auto typeStr = "type";
        static constexpr auto valueStr = "value";

        static constexpr auto fileTypeStr = "file";
        static constexpr auto urlTypeStr = "url";
    };

} // namespace Serializer