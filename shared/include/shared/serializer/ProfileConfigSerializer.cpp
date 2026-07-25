#include "ProfileConfigSerializer.hpp"

#include "../serializer/ProfileSerializer.hpp"
#include "../serializer/PropertySerializer.hpp"
#include "JsonSerializer.hpp"

#include <QDir>
#include <QJsonArray>
#include <QStandardPaths>

namespace Serializer {
    std::vector<Profile> ProfileConfigSerializer::load() {
        const auto obj = JsonSerializer::loadJsonObject( ProfileConfigSerializer::filePath() );

        if ( obj.isEmpty() ) {
            return {};
        }

        if ( const auto array = PropertySerializer::serializedArrayProperty(
                 obj,
                 ProfileConfigSerializer::profilesStr ) ) {
            std::vector<Profile> profiles;
            for ( const auto element : *array ) {
                if ( !element.isObject() ) {
                    qWarning().noquote() << "Property list element is not an object";
                    continue;
                }

                if ( auto profile = ProfileSerializer::serialized( element.toObject() ) ) {
                    profiles.push_back( std::move( *profile ) );
                }
            }
            return profiles;
        }
        return {};
    }

    void ProfileConfigSerializer::save( const std::vector<Models::Profile::Profile>& profiles ) {
        if ( profiles.empty() ) {
            return;
        }

        QJsonArray arr;
        for ( const auto& profile : profiles ) {
            arr.push_back( ProfileSerializer::deserialized( profile ) );
        }

        QJsonObject obj;
        obj[ ProfileConfigSerializer::profilesStr ] = arr;

        const auto success =
            JsonSerializer::saveJsonObject( obj, ProfileConfigSerializer::filePath() );

        if ( !success ) {
            qWarning().noquote() << "Could not save profiles to JSON file";
        }
    }

    QString ProfileConfigSerializer::filePath() {
        return QDir( QStandardPaths::writableLocation( QStandardPaths::GenericConfigLocation ) )
            .filePath( "quicklaunchbar/profiles.json" );
    }

} // namespace Serializer