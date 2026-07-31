#include "UriSerializer.hpp"

#include "PropertySerializer.hpp"

namespace Shared::Serializer {

    std::optional<UriSerializer::Uri> UriSerializer::serialized( const QJsonObject& obj ) {
        const auto type = UriSerializer::serializedType( obj );
        const auto value = UriSerializer::serializedValue( obj );

        if ( type && value ) {
            Uri uri( *type, *value );
            return uri;
        } else {
            return std::nullopt;
        }
    }

    QJsonObject UriSerializer::deserialized( const Uri& uri ) {
        return { { UriSerializer::typeStr, UriSerializer::typeToString( uri.type ) },
                 { UriSerializer::valueStr, uri.value } };
    }

    std::optional<UriSerializer::Uri::Type>
    UriSerializer::serializedType( const QJsonObject& obj ) {
        if ( const auto typeStrOpt =
                 PropertySerializer::serializedStringProperty( obj, UriSerializer::typeStr ) ) {
            if ( const auto typeOpt = UriSerializer::typeFromString( *typeStrOpt ) ) {
                return *typeOpt;
            } else {
                return std::nullopt;
            }
        } else {
            return std::nullopt;
        }
    }

    std::optional<QString> UriSerializer::serializedValue( const QJsonObject& obj ) {
        if ( const auto valueOpt =
                 PropertySerializer::serializedStringProperty( obj, UriSerializer::valueStr ) ) {
            return *valueOpt;
        } else {
            return std::nullopt;
        }
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

    std::optional<UriSerializer::Uri::Type> UriSerializer::typeFromString( const QString& type ) {
        if ( type == UriSerializer::fileTypeStr ) {
            return Uri::Type::File;
        } else if ( type == UriSerializer::urlTypeStr ) {
            return Uri::Type::Url;
        } else {
            qWarning().noquote() << "Unknown icon source type:" << type;
            return std::nullopt;
        }
    }

} // namespace Shared::Serializer