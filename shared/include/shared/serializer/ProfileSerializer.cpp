#include "ProfileSerializer.hpp"

#include "ProfileViewSerializer.hpp"
#include "PropertySerializer.hpp"

namespace Shared::Serializer {

    std::optional<QUuid> ProfileSerializer::serializedUuid( const QJsonObject& obj ) {
        if ( const auto uuidOpt =
                 PropertySerializer::serializedStringProperty( obj, ProfileSerializer::uuidStr ) ) {
            return QUuid( *uuidOpt );
        } else {
            return std::nullopt;
        }
    }

    std::optional<QString> ProfileSerializer::serializedName( const QJsonObject& obj ) {
        if ( const auto nameOpt =
                 PropertySerializer::serializedStringProperty( obj, ProfileSerializer::nameStr ) ) {
            return *nameOpt;
        } else {
            return std::nullopt;
        }
    }

    std::optional<bool> ProfileSerializer::serializedEnabled( const QJsonObject& obj ) {
        if ( const auto enabledOpt =
                 PropertySerializer::serializedBoolProperty( obj,
                                                             ProfileSerializer::enabledStr ) ) {
            return *enabledOpt;
        } else {
            return std::nullopt;
        }
    }

    std::optional<QString> ProfileSerializer::serializedShortcut( const QJsonObject& obj ) {
        if ( const auto shortcutOpt =
                 PropertySerializer::serializedStringProperty( obj,
                                                               ProfileSerializer::shortcutStr ) ) {
            return *shortcutOpt;
        } else {
            return std::nullopt;
        }
    }

    std::optional<ProfileSerializer::ProfileView>
    ProfileSerializer::serializedView( const QJsonObject& obj ) {
        if ( const auto viewObj =
                 PropertySerializer::serializedObjectProperty( obj, ProfileSerializer::viewStr ) ) {
            if ( const auto view = ProfileViewSerializer::serialized( *viewObj ) ) {
                return *view;
            } else {
                return std::nullopt;
            }
        } else {
            return std::nullopt;
        }
    }

} // namespace Shared::Serializer