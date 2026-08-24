#include "ProfileSerializer.hpp"

#include "ExecutionTargetSerializer.hpp"
#include "shared/models/ProfileView.hpp"
#include "shared/serializer/ProfileViewSerializer.hpp"
#include "shared/serializer/PropertySerializer.hpp"

#include <optional>

namespace Editor::Serializer {

    std::optional<Models::Profile*> ProfileSerializer::serialized( const QJsonObject& obj ) {
        const auto uuid = ProfileSerializer::serializedUuid( obj );
        const auto name = ProfileSerializer::serializedName( obj );
        const auto enabled = ProfileSerializer::serializedEnabled( obj );
        const auto shortcut = ProfileSerializer::serializedShortcut( obj );
        const auto view = ProfileSerializer::serializedView( obj );
        const auto executionTargets = ProfileSerializer::serializedExecutionTargets( obj );

        if ( uuid && name && enabled && shortcut && view && executionTargets ) {
            return new Models::Profile( *uuid,
                                        *name,
                                        *enabled,
                                        *shortcut,
                                        *view,
                                        *executionTargets );
        } else {
            return std::nullopt;
        }
    }

    QJsonObject ProfileSerializer::deserialized( Models::Profile* profile ) {
        const auto view = static_cast<Shared::Models::Profile::ProfileView>( *profile->view() );
        return { { ProfileSerializer::uuidStr, profile->uuid().toString( QUuid::WithoutBraces ) },
                 { ProfileSerializer::nameStr, profile->name() },
                 { ProfileSerializer::enabledStr, profile->enabled() },
                 { ProfileSerializer::shortcutStr, profile->shortcut() },
                 { ProfileSerializer::viewStr,
                   Shared::Serializer::ProfileViewSerializer::deserialized( view ) },
                 { ProfileSerializer::executionTargetsStr,
                   ProfileSerializer::deserializedExecutionTargets(
                       profile->executionTargets()->list() ) } };
    }

    std::optional<Models::ProfileView*>
    ProfileSerializer::serializedView( const QJsonObject& obj ) {
        if ( const auto viewOpt = Shared::Serializer::ProfileSerializer::serializedView( obj ) ) {
            const auto view = *viewOpt;
            return new Models::ProfileView( view.mode,
                                            view.position,
                                            view.offset,
                                            view.wrapMode,
                                            view.flowDirection );
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

    QJsonArray ProfileSerializer::deserializedExecutionTargets(
        const QList<Models::ExecutionTarget*>& executionTargets ) {
        QJsonArray jsonExecutionTargets;
        for ( auto executionTarget : executionTargets ) {
            jsonExecutionTargets.push_back(
                ExecutionTargetSerializer::deserialized( executionTarget ) );
        }
        return jsonExecutionTargets;
    }
} // namespace Editor::Serializer