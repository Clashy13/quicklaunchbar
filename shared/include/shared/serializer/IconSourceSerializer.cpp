#include "IconSourceSerializer.hpp"

#include "PropertySerializer.hpp"

namespace Serializer {

    std::optional<IconSource> IconSourceSerializer::serialized( const QJsonObject& obj ) {
        IconSource::Type type;
        if ( const auto typeStrOpt =
                 PropertySerializer::serializedStringProperty( obj,
                                                               IconSourceSerializer::typeStr ) ) {
            if ( const auto typeOpt = IconSourceSerializer::typeFromString( *typeStrOpt ) ) {
                type = *typeOpt;
            } else {
                return std::nullopt;
            }
        } else {
            return std::nullopt;
        }
        QString value;
        if ( const auto valueOpt =
                 PropertySerializer::serializedStringProperty( obj,
                                                               IconSourceSerializer::valueStr ) ) {
            value = *valueOpt;
        } else {
            return std::nullopt;
        }
        IconSource iconSource( type, value );
        return iconSource;
    }

    QJsonObject IconSourceSerializer::deserialized( const IconSource& iconSource ) {
        return { { IconSourceSerializer::typeStr,
                   IconSourceSerializer::typeToString( iconSource.type ) },
                 { IconSourceSerializer::valueStr, iconSource.value } };
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

    std::optional<IconSource::Type> IconSourceSerializer::typeFromString( const QString& type ) {
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

} // namespace Serializer