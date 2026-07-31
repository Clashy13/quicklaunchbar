#include "ProfileConfigSerializer.hpp"

#include "ProfileSerializer.hpp"
#include "shared/serializer/JsonSerializer.hpp"
#include "shared/serializer/PropertySerializer.hpp"

namespace Service::Serializer {

    QList<Models::Profile*> ProfileConfigSerializer::load() {
        const auto obj = Shared::Serializer::JsonSerializer::loadJsonObject(
            ProfileConfigSerializer::filePath() );

        if ( obj.isEmpty() ) {
            return {};
        }

        if ( const auto array = Shared::Serializer::PropertySerializer::serializedArrayProperty(
                 obj,
                 ProfileConfigSerializer::profilesStr ) ) {
            QList<Models::Profile*> profiles;
            for ( const auto element : *array ) {
                if ( !element.isObject() ) {
                    qWarning().noquote() << "Property list element is not an object";
                    continue;
                }

                if ( auto profile = ProfileSerializer::serialized( element.toObject() ) ) {
                    profiles.push_back( *profile );
                }
            }
            return profiles;
        }
        return {};
    }
} // namespace Service::Serializer