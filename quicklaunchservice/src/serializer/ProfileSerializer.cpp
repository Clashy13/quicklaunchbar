#include "ProfileSerializer.hpp"

#include "ExecutionTargetSerializer.hpp"
#include "serializer/ProfileViewSerializer.hpp"
#include "shared/serializer/PropertySerializer.hpp"

namespace Service::Serializer {
    std::optional<Models::Profile*> ProfileSerializer::serialized( const QJsonObject& obj ) {
        const auto enabled = ProfileSerializer::serializedEnabled( obj );
        if ( enabled && !( *enabled ) ) {
            return std::nullopt;
        }
        const auto uuid = ProfileSerializer::serializedUuid( obj );
        const auto name = ProfileSerializer::serializedName( obj );
        const auto shortcut = ProfileSerializer::serializedShortcut( obj );
        const auto view = ProfileSerializer::serializedView( obj );
        const auto executionTargets = ProfileSerializer::serializedExecutionTargets( obj );

        if ( uuid && name && enabled && shortcut && view && executionTargets ) {
            const auto viewSource = ProfileViewSerializer::viewToSource( *view );
            return new Models::Profile( *uuid,
                                        *name,
                                        *shortcut,
                                        *view,
                                        viewSource,
                                        *executionTargets );
        } else {
            return std::nullopt;
        }
    }

    std::optional<QList<Models::ExecutionTarget*>>
    ProfileSerializer::serializedExecutionTargets( const QJsonObject& obj ) {
        if ( const auto array = Shared::Serializer::PropertySerializer::serializedArrayProperty(
                 obj,
                 ProfileSerializer::executionTargetsStr ) ) {
            QList<Models::ExecutionTarget*> executionTargets;
            for ( const auto element : *array ) {
                if ( !element.isObject() ) {
                    qWarning().noquote() << "Property list element is not an object";
                    return std::nullopt;
                }

                if ( auto executionTarget =
                         ExecutionTargetSerializer::serialized( element.toObject() ) ) {
                    executionTargets.push_back( *executionTarget );
                } else {
                    return std::nullopt;
                }
            }
            return executionTargets;
        } else {
            return std::nullopt;
        }
    }

} // namespace Service::Serializer