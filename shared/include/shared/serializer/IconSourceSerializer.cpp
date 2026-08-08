#include "IconSourceSerializer.hpp"

#include "PropertySerializer.hpp"

namespace Shared::Serializer {

    std::optional<IconSourceSerializer::IconSource>
    IconSourceSerializer::serialized( const QJsonObject& obj ) {
        const auto type = IconSourceSerializer::serializedType( obj );
        const auto value = IconSourceSerializer::serializedValue( obj );

        if ( type && value ) {
            IconSource iconSource( *type, *value );
            return iconSource;
        } else {
            return std::nullopt;
        }
    }

    QJsonObject IconSourceSerializer::deserialized( const IconSource& iconSource ) {
        return { { IconSourceSerializer::typeStr,
                   IconSourceSerializer::typeToString( iconSource.type ) },
                 { IconSourceSerializer::valueStr, iconSource.value } };
    }

    QUrl IconSourceSerializer::iconSourceToUrl( const IconSource& iconSource ) {
        switch ( iconSource.type ) {
            case IconSource::Type::Theme:
                return QUrl( "image://themeicons/" + iconSource.value );
            case IconSource::Type::FromFile:
                return QUrl( "image://fileicons" + iconSource.value );
            case IconSource::Type::Image:
                return QUrl( "image:/" + iconSource.value );
            case IconSource::Type::Resource:
                return QUrl( "qrc:/icons/" + iconSource.value + ".svg" );
        }
    }

    std::optional<IconSourceSerializer::IconSource::Type>
    IconSourceSerializer::serializedType( const QJsonObject& obj ) {
        if ( const auto typeStrOpt =
                 PropertySerializer::serializedStringProperty( obj,
                                                               IconSourceSerializer::typeStr ) ) {
            if ( const auto typeOpt = IconSourceSerializer::typeFromString( *typeStrOpt ) ) {
                return *typeOpt;
            } else {
                return std::nullopt;
            }
        } else {
            return std::nullopt;
        }
    }

    std::optional<QString> IconSourceSerializer::serializedValue( const QJsonObject& obj ) {
        if ( const auto valueOpt =
                 PropertySerializer::serializedStringProperty( obj,
                                                               IconSourceSerializer::valueStr ) ) {
            return *valueOpt;
        } else {
            return std::nullopt;
        }
    }

    QString IconSourceSerializer::typeToString( const IconSource::Type type ) {
        switch ( type ) {
            case IconSource::Type::Theme:
                return IconSourceSerializer::themeTypeStr;
            case IconSource::Type::FromFile:
                return IconSourceSerializer::fromFileTypeStr;
            case IconSource::Type::Image:
                return IconSourceSerializer::imageTypeStr;
            case IconSource::Type::Resource:
                return IconSourceSerializer::resourceTypeStr;
            default:
                return "";
        }
    }

    std::optional<IconSourceSerializer::IconSource::Type>
    IconSourceSerializer::typeFromString( const QString& type ) {
        if ( type == IconSourceSerializer::themeTypeStr ) {
            return IconSource::Type::Theme;
        } else if ( type == IconSourceSerializer::fromFileTypeStr ) {
            return IconSource::Type::FromFile;
        } else if ( type == IconSourceSerializer::imageTypeStr ) {
            return IconSource::Type::Image;
        } else if ( type == IconSourceSerializer::resourceTypeStr ) {
            return IconSource::Type::Resource;
        } else {
            qWarning().noquote() << "Unknown icon source type:" << type;
            return std::nullopt;
        }
    }

} // namespace Shared::Serializer