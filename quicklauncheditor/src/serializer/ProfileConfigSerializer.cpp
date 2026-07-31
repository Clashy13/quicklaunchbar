#include "ProfileConfigSerializer.hpp"

#include "ProfileSerializer.hpp"
#include "shared/serializer/JsonSerializer.hpp"
#include "shared/serializer/PropertySerializer.hpp"

namespace Editor::Serializer {

    QList<Models::Profile> ProfileConfigSerializer::load() {
        const auto obj = Shared::Serializer::JsonSerializer::loadJsonObject(
            ProfileConfigSerializer::filePath() );

        if ( obj.isEmpty() ) {
            return {};
        }

        if ( const auto array = Shared::Serializer::PropertySerializer::serializedArrayProperty(
                 obj,
                 ProfileConfigSerializer::profilesStr ) ) {
            QList<Models::Profile> profiles;
            for ( const auto element : *array ) {
                if ( !element.isObject() ) {
                    qWarning().noquote() << "Property list element is not an object";
                    continue;
                }

                if ( const auto& profile = ProfileSerializer::serialized( element.toObject() ) ) {
                    profiles.push_back( *profile );
                }
            }
            return profiles;
        }
        return {};
    }

    void ProfileConfigSerializer::save( const QList<Models::Profile>& profiles ) {
        if ( profiles.empty() ) {
            return;
        }

        QJsonArray arr;
        for ( const auto& profile : profiles ) {
            arr.push_back( ProfileSerializer::deserialized( profile ) );
        }

        QJsonObject obj;
        obj[ ProfileConfigSerializer::profilesStr ] = arr;

        const auto success = Shared::Serializer::JsonSerializer::saveJsonObject(
            obj,
            ProfileConfigSerializer::filePath() );

        if ( !success ) {
            qWarning().noquote() << "Could not save profiles to JSON file";
        }
    }
} // namespace Editor::Serializer