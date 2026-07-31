#pragma once

#include "../models/ProfileView.hpp"

#include <QJsonArray>
#include <QJsonObject>
#include <optional>

namespace Shared::Serializer {

    class ProfileSerializer {

        using ProfileView = Models::Profile::ProfileView;

      protected:
        static std::optional<QUuid> serializedUuid( const QJsonObject& obj );

        static std::optional<QString> serializedName( const QJsonObject& obj );

        static std::optional<bool> serializedEnabled( const QJsonObject& obj );

        static std::optional<QString> serializedShortcut( const QJsonObject& obj );

        static std::optional<ProfileView> serializedView( const QJsonObject& obj );

        static constexpr auto uuidStr = "uuid";
        static constexpr auto nameStr = "name";
        static constexpr auto enabledStr = "enabled";
        static constexpr auto shortcutStr = "shortcut";
        static constexpr auto viewStr = "view";
        static constexpr auto executionTargetsStr = "execution_targets";
    };

} // namespace Shared::Serializer