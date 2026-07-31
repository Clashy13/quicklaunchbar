#include "ProfileSerializer.hpp"

#include "shared/serializer/ExecutionTargetSerializer.hpp"
#include "shared/serializer/ProfileViewSerializer.hpp"
#include "shared/serializer/PropertySerializer.hpp"

namespace Editor::Serializer {

    std::optional<Models::Profile> ProfileSerializer::serialized( const QJsonObject& obj ) {
        const auto uuid = ProfileSerializer::serializedUuid( obj );
        const auto name = ProfileSerializer::serializedName( obj );
        const auto enabled = ProfileSerializer::serializedEnabled( obj );
        const auto shortcut = ProfileSerializer::serializedShortcut( obj );
        const auto view = ProfileSerializer::serializedView( obj );
        const auto executionTargets = ProfileSerializer::serializedExecutionTargets( obj );

        if ( uuid && name && enabled && shortcut && view && executionTargets ) {
            Models::Profile profile( *uuid, *name, *enabled, *shortcut, *view, *executionTargets );
            return profile;
        } else {
            return std::nullopt;
        }
    }

    QJsonObject ProfileSerializer::deserialized( const Models::Profile& profile ) {
        return { { ProfileSerializer::uuidStr, profile.uuid.toString( QUuid::WithoutBraces ) },
                 { ProfileSerializer::nameStr, profile.name },
                 { ProfileSerializer::enabledStr, profile.enabled },
                 { ProfileSerializer::shortcutStr, profile.shortcut },
                 { ProfileSerializer::viewStr,
                   Shared::Serializer::ProfileViewSerializer::deserialized( profile.view ) },
                 { ProfileSerializer::executionTargetsStr,
                   ProfileSerializer::deserializedExecutionTargets( profile.executionTargets ) } };
    }

    std::optional<QList<ProfileSerializer::ExecutionTarget>>
    ProfileSerializer::serializedExecutionTargets( const QJsonObject& obj ) {
        if ( const auto array = Shared::Serializer::PropertySerializer::serializedArrayProperty(
                 obj,
                 ProfileSerializer::executionTargetsStr ) ) {
            QList<ExecutionTarget> executionTargets;
            for ( const auto element : *array ) {
                if ( !element.isObject() ) {
                    qWarning().noquote() << "Property list element is not an object";
                    return std::nullopt;
                }

                if ( auto executionTarget =
                         Shared::Serializer::ExecutionTargetSerializer::serialized(
                             element.toObject() ) ) {
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
        const QList<ExecutionTarget>& executionTargets ) {
        QJsonArray jsonExecutionTargets;
        for ( const auto& executionTarget : executionTargets ) {
            jsonExecutionTargets.push_back(
                Shared::Serializer::ExecutionTargetSerializer::deserialized( executionTarget ) );
        }
        return jsonExecutionTargets;
    }
} // namespace Editor::Serializer