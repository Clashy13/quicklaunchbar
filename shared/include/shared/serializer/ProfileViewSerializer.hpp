#pragma once

#include "../models/ProfileView.hpp"

#include <QJsonObject>
#include <optional>

namespace Shared::Serializer {

    class ProfileViewSerializer {

        using ProfileView = Models::Profile::ProfileView;

      public:
        static std::optional<ProfileView> serialized( const QJsonObject& obj );

        static QJsonObject deserialized( const ProfileView& view );

      private:
        static std::optional<ProfileView::Mode> serializedMode( const QJsonObject& obj );

        static std::optional<ProfileView::Position> serializedPosition( const QJsonObject& obj );

        static std::optional<qsizetype> serializedMargin( const QJsonObject& obj );

        static std::optional<ProfileView::WrapMode> serializedWrapMode( const QJsonObject& obj );

        static std::optional<ProfileView::FlowDirection>
        serializedFlowDirection( const QJsonObject& obj );

        static QString modeToString( const ProfileView::Mode mode );

        static std::optional<ProfileView::Mode> modeFromString( const QString& mode );

        static QString positionToString( const ProfileView::Position position );

        static std::optional<ProfileView::Position> positionFromString( const QString& position );

        static QString wrapModeToString( const ProfileView::WrapMode wrapMode );

        static std::optional<ProfileView::WrapMode> wrapModeFromString( const QString& wrapMode );

        static QString flowDirectionToString( const ProfileView::FlowDirection flowDirection );

        static std::optional<ProfileView::FlowDirection>
        flowDirectionFromString( const QString& flowDirection );

        static constexpr auto modeStr = "mode";
        static constexpr auto positionStr = "position";
        static constexpr auto marginStr = "margin";
        static constexpr auto wrapModeStr = "wrap_mode";
        static constexpr auto flowDirectionStr = "flow_direction";

        static constexpr auto iconModeStr = "icon";
        static constexpr auto listModeStr = "list";

        static constexpr auto topLeftPositionStr = "top_left";
        static constexpr auto topPositionStr = "top";
        static constexpr auto topRightPositionStr = "top_right";
        static constexpr auto leftPositionStr = "left";
        static constexpr auto centerPositionStr = "center";
        static constexpr auto rightPositionStr = "right";
        static constexpr auto bottomLeftPositionStr = "bottom_left";
        static constexpr auto bottomPositionStr = "bottom";
        static constexpr auto bottomRightPositionStr = "bottom_right";

        static constexpr auto scrollWrapModeStr = "scroll";
        static constexpr auto gridWrapModeStr = "grid";

        static constexpr auto horizontalFlowDirectionStr = "horizontal";
        static constexpr auto verticalFlowDirectionStr = "vertical";
    };

} // namespace Shared::Serializer