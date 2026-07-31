#include "PropertySerializer.hpp"

namespace Shared::Serializer {

    std::optional<QString> PropertySerializer::serializedStringProperty( const QJsonObject& obj,
                                                                         const QString& key ) {
        if ( !PropertySerializer::containsKey( obj, key ) ) {
            return std::nullopt;
        }

        const auto value = obj[ key ];

        if ( !value.isString() ) {
            qWarning().noquote() << "Property is not a string:" << key;
            return std::nullopt;
        }

        return value.toString();
    }

    std::optional<bool> PropertySerializer::serializedBoolProperty( const QJsonObject& obj,
                                                                    const QString& key ) {
        if ( !PropertySerializer::containsKey( obj, key ) ) {
            return std::nullopt;
        }

        const auto value = obj[ key ];

        if ( !value.isBool() ) {
            qWarning().noquote() << "Property is not a bool:" << key;
            return std::nullopt;
        }

        return value.toBool();
    }

    std::optional<int> PropertySerializer::serializedIntProperty( const QJsonObject& obj,
                                                                  const QString& key ) {
        if ( !PropertySerializer::containsKey( obj, key ) ) {
            return std::nullopt;
        }

        const auto value = obj[ key ];

        if ( !value.isDouble() ) {
            qWarning().noquote() << "Property is not a number:" << key;
            return std::nullopt;
        }

        return value.toInt();
    }

    std::optional<QJsonObject> PropertySerializer::serializedObjectProperty( const QJsonObject& obj,
                                                                             const QString& key ) {
        if ( !PropertySerializer::containsKey( obj, key ) ) {
            return std::nullopt;
        }

        const auto value = obj[ key ];

        if ( !value.isObject() ) {
            qWarning().noquote() << "Property is not an object:" << key;
            return std::nullopt;
        }

        return value.toObject();
    }

    std::optional<QJsonArray> PropertySerializer::serializedArrayProperty( const QJsonObject& obj,
                                                                           const QString& key ) {
        if ( !PropertySerializer::containsKey( obj, key ) ) {
            return std::nullopt;
        }

        const auto value = obj[ key ];

        if ( !value.isArray() ) {
            qWarning().noquote() << "Property is not a list:" << key;
            return std::nullopt;
        }

        return value.toArray();
    }

    bool PropertySerializer::containsKey( const QJsonObject& obj, const QString& key ) {
        if ( obj.contains( key ) ) {
            return true;
        }
        qWarning().noquote() << "Missing required property:" << key;
        return false;
    }

} // namespace Shared::Serializer