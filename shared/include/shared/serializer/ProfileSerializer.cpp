#include "ProfileSerializer.hpp"

#include "ExecutionTargetSerializer.hpp"
#include "ProfileViewSerializer.hpp"
#include "PropertySerializer.hpp"

namespace Serializer {

    std::optional<Profile> ProfileSerializer::serialized( const QJsonObject& obj ) {
        QUuid uuid;
        if ( const auto uuidOpt =
                 PropertySerializer::serializedStringProperty( obj, ProfileSerializer::uuidStr ) ) {
            uuid = QUuid( *uuidOpt );
        } else {
            return std::nullopt;
        }
        QString name;
        if ( const auto nameOpt =
                 PropertySerializer::serializedStringProperty( obj, ProfileSerializer::nameStr ) ) {
            name = *nameOpt;
        } else {
            return std::nullopt;
        }
        bool enabled;
        if ( const auto enabledOpt =
                 PropertySerializer::serializedBoolProperty( obj,
                                                             ProfileSerializer::enabledStr ) ) {
            enabled = *enabledOpt;
        } else {
            return std::nullopt;
        }
        QString shortcut;
        if ( const auto shortcutOpt =
                 PropertySerializer::serializedStringProperty( obj,
                                                               ProfileSerializer::shortcutStr ) ) {
            shortcut = *shortcutOpt;
        } else {
            return std::nullopt;
        }

        if ( const auto viewObj =
                 PropertySerializer::serializedObjectProperty( obj, ProfileSerializer::viewStr ) ) {
            if ( const auto view = ProfileViewSerializer::serialized( *viewObj ) ) {
                if ( auto executionTargets =
                         ProfileSerializer::serializedExecutionTargets( obj ) ) {
                    Profile profile( uuid,
                                     name,
                                     enabled,
                                     shortcut,
                                     *view,
                                     std::move( *executionTargets ) );
                    return profile;
                } else {
                    return std::nullopt;
                }
            } else {
                return std::nullopt;
            }
        } else {
            return std::nullopt;
        }
    }

    QJsonObject ProfileSerializer::deserialized( const Profile& profile ) {
        return {
            { ProfileSerializer::uuidStr, profile.uuid.toString( QUuid::WithoutBraces ) },
            { ProfileSerializer::nameStr, profile.name },
            { ProfileSerializer::enabledStr, profile.enabled },
            { ProfileSerializer::shortcutStr, profile.shortcut },
            { ProfileSerializer::viewStr, ProfileViewSerializer::deserialized( profile.view ) },
            { ProfileSerializer::executionTargetsStr,
              ProfileSerializer::deserializedExecutionTargets( profile.executionTargets ) } };
    }

    std::optional<std::vector<std::unique_ptr<ExecutionTarget>>>
    ProfileSerializer::serializedExecutionTargets( const QJsonObject& obj ) {
        if ( const auto array = PropertySerializer::serializedArrayProperty(
                 obj,
                 ProfileSerializer::executionTargetsStr ) ) {
            std::vector<std::unique_ptr<ExecutionTarget>> executionTargets;
            for ( const auto element : *array ) {
                if ( !element.isObject() ) {
                    qWarning().noquote() << "Property list element is not an object";
                    return std::nullopt;
                }

                if ( auto executionTarget =
                         ExecutionTargetSerializer::serialized( element.toObject() ) ) {
                    executionTargets.push_back( std::move( *executionTarget ) );
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
        const std::vector<std::unique_ptr<ExecutionTarget>>& executionTargets ) {
        QJsonArray jsonExecutionTargets;
        for ( const auto& executionTarget : executionTargets ) {
            if ( executionTarget ) {
                jsonExecutionTargets.push_back(
                    ExecutionTargetSerializer::deserialized( executionTarget ) );
            }
        }
        return jsonExecutionTargets;
    }

} // namespace Serializer