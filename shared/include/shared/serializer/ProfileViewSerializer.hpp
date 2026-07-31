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

        static std::optional<ProfileView::HorizontalAnchor>
        serializedHorizontalAnchor( const QJsonObject& obj );

        static std::optional<ProfileView::VerticalAnchor>
        serializedVerticalAnchor( const QJsonObject& obj );

        static std::optional<qsizetype> serializedMargin( const QJsonObject& obj );

        static std::optional<ProfileView::WrapMode> serializedWrapMode( const QJsonObject& obj );

        static std::optional<ProfileView::FlowDirection>
        serializedFlowDirection( const QJsonObject& obj );

        static QString modeToString( const ProfileView::Mode mode );

        static std::optional<ProfileView::Mode> modeFromString( const QString& mode );

        static QString
        horizontalAnchorToString( const ProfileView::HorizontalAnchor horizontalAnchor );

        static std::optional<ProfileView::HorizontalAnchor>
        horizontalAnchorFromString( const QString& horizontalAnchor );

        static QString verticalAnchorToString( const ProfileView::VerticalAnchor verticalAnchor );

        static std::optional<ProfileView::VerticalAnchor>
        verticalAnchorFromString( const QString& verticalAnchor );

        static QString wrapModeToString( const ProfileView::WrapMode wrapMode );

        static std::optional<ProfileView::WrapMode> wrapModeFromString( const QString& wrapMode );

        static QString flowDirectionToString( const ProfileView::FlowDirection flowDirection );

        static std::optional<ProfileView::FlowDirection>
        flowDirectionFromString( const QString& flowDirection );

        static constexpr auto modeStr = "mode";
        static constexpr auto horizontalAnchorStr = "horizontal_anchor";
        static constexpr auto verticalAnchorStr = "vertical_anchor";
        static constexpr auto marginStr = "margin";
        static constexpr auto wrapModeStr = "wrap_mode";
        static constexpr auto flowDirectionStr = "flow_direction";

        static constexpr auto iconModeStr = "icon";
        static constexpr auto listModeStr = "list";

        static constexpr auto leftHorizontalAnchorStr = "left";
        static constexpr auto centerHorizontalAnchorStr = "center";
        static constexpr auto rightHorizontalAnchorStr = "right";

        static constexpr auto topVerticalAnchorStr = "top";
        static constexpr auto centerVerticalAnchorStr = "center";
        static constexpr auto bottomVerticalAnchorStr = "bottom";

        static constexpr auto scrollWrapModeStr = "scroll";
        static constexpr auto gridWrapModeStr = "grid";

        static constexpr auto horizontalFlowDirectionStr = "horizontal";
        static constexpr auto verticalFlowDirectionStr = "vertical";
    };

} // namespace Shared::Serializer