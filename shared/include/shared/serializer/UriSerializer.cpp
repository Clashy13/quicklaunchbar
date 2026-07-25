#include "UriSerializer.hpp"

#include "PropertySerializer.hpp"

namespace Serializer {

    std::optional<Uri> UriSerializer::serialized( const QJsonObject& obj ) {
        Uri::Type type;
        if ( const auto typeStrOpt =
                 PropertySerializer::serializedStringProperty( obj, UriSerializer::typeStr ) ) {
            if ( const auto typeOpt = UriSerializer::typeFromString( *typeStrOpt ) ) {
                type = *typeOpt;
            } else {
                return std::nullopt;
            }
        } else {
            return std::nullopt;
        }
        QString value;
        if ( const auto valueOpt =
                 PropertySerializer::serializedStringProperty( obj, UriSerializer::valueStr ) ) {
            value = *valueOpt;
        } else {
            return std::nullopt;
        }
        Uri iconSource( type, value );
        return iconSource;
    }

    QJsonObject UriSerializer::deserialized( const Uri& iconSource ) {
        return { { UriSerializer::typeStr, UriSerializer::typeToString( iconSource.type ) },
                 { UriSerializer::valueStr, iconSource.value } };
    }

    QString UriSerializer::typeToString( const Uri::Type type ) {
        switch ( type ) {
            case Uri::Type::File:
                return UriSerializer::fileTypeStr;
            case Uri::Type::Url:
                return UriSerializer::urlTypeStr;
            default:
                return "";
        }
    }

    std::optional<Uri::Type> UriSerializer::typeFromString( const QString& type ) {
        if ( type == UriSerializer::fileTypeStr ) {
            return Uri::Type::File;
        } else if ( type == UriSerializer::urlTypeStr ) {
            return Uri::Type::Url;
        } else {
            qWarning().noquote() << "Unknown icon source type:" << type;
            return std::nullopt;
        }
    }

} // namespace Serializer