#include "ProfileViewSerializer.hpp"

#include "PropertySerializer.hpp"

#include <qdebug.h>
#include <qjsonobject.h>
#include <qtypes.h>

namespace Serializer {

    std::optional<ProfileView> ProfileViewSerializer::serialized( const QJsonObject& obj ) {
        ProfileView::Mode mode;
        if ( const auto modeStrOpt =
                 PropertySerializer::serializedStringProperty( obj,
                                                               ProfileViewSerializer::modeStr ) ) {
            if ( const auto modeOpt = ProfileViewSerializer::modeFromString( *modeStrOpt ) ) {
                mode = *modeOpt;
            } else {
                return std::nullopt;
            }
        } else {
            return std::nullopt;
        }
        ProfileView::HorizontalAnchor horizontalAnchor;
        if ( const auto horizontalAnchorStrOpt = PropertySerializer::serializedStringProperty(
                 obj,
                 ProfileViewSerializer::horizontalAnchorStr ) ) {
            if ( const auto horizontalAnchorOpt = ProfileViewSerializer::horizontalAnchorFromString(
                     *horizontalAnchorStrOpt ) ) {
                horizontalAnchor = *horizontalAnchorOpt;
            } else {
                return std::nullopt;
            }
        } else {
            return std::nullopt;
        }
        ProfileView::VerticalAnchor verticalAnchor;
        if ( const auto verticalAnchorStrOpt = PropertySerializer::serializedStringProperty(
                 obj,
                 ProfileViewSerializer::verticalAnchorStr ) ) {
            if ( const auto verticalAnchorOpt =
                     ProfileViewSerializer::verticalAnchorFromString( *verticalAnchorStrOpt ) ) {
                verticalAnchor = *verticalAnchorOpt;
            } else {
                return std::nullopt;
            }
        } else {
            return std::nullopt;
        }
        qsizetype margin;
        if ( const auto marginOpt =
                 PropertySerializer::serializedIntProperty( obj,
                                                            ProfileViewSerializer::marginStr ) ) {
            if ( *marginOpt < 0 ) {
                qWarning().noquote()
                    << "Property is not a size type:" << ProfileViewSerializer::marginStr;
                return std::nullopt;
            }
            margin = *marginOpt;
        } else {
            return std::nullopt;
        }
        ProfileView::WrapMode wrapMode;
        if ( const auto wrapModeStrOpt = PropertySerializer::serializedStringProperty(
                 obj,
                 ProfileViewSerializer::wrapModeStr ) ) {
            if ( const auto wrapModeOpt =
                     ProfileViewSerializer::wrapModeFromString( *wrapModeStrOpt ) ) {
                wrapMode = *wrapModeOpt;
            } else {
                return std::nullopt;
            }
        } else {
            return std::nullopt;
        }
        if ( mode == ProfileView::Mode::Icon ) {
            ProfileView::FlowDirection flowDirection;
            if ( const auto flowDirectionStrOpt = PropertySerializer::serializedStringProperty(
                     obj,
                     ProfileViewSerializer::flowDirectionStr ) ) {
                if ( const auto flowDirectionOpt =
                         ProfileViewSerializer::flowDirectionFromString( *flowDirectionStrOpt ) ) {
                    flowDirection = *flowDirectionOpt;
                } else {
                    return std::nullopt;
                }
            } else {
                return std::nullopt;
            }
            ProfileView view( mode,
                              horizontalAnchor,
                              verticalAnchor,
                              margin,
                              wrapMode,
                              flowDirection );
            return view;
        } else {
            ProfileView view( mode,
                              horizontalAnchor,
                              verticalAnchor,
                              margin,
                              wrapMode,
                              ProfileView::FlowDirection::Vertical );
            return view;
        }
    }

    QJsonObject ProfileViewSerializer::deserialized( const ProfileView& view ) {
        QJsonObject obj;
        obj[ ProfileViewSerializer::modeStr ] = ProfileViewSerializer::modeToString( view.mode );
        obj[ ProfileViewSerializer::horizontalAnchorStr ] =
            ProfileViewSerializer::horizontalAnchorToString( view.horizontalAnchor );
        obj[ ProfileViewSerializer::verticalAnchorStr ] =
            ProfileViewSerializer::verticalAnchorToString( view.verticalAnchor );
        obj[ ProfileViewSerializer::marginStr ] = view.margin;
        obj[ ProfileViewSerializer::wrapModeStr ] =
            ProfileViewSerializer::wrapModeToString( view.wrapMode );

        if ( view.mode == ProfileView::Mode::Icon ) {
            obj[ ProfileViewSerializer::flowDirectionStr ] =
                ProfileViewSerializer::flowDirectionToString( view.flowDirection );
        }

        return obj;
    }

    QString ProfileViewSerializer::modeToString( const ProfileView::Mode mode ) {
        switch ( mode ) {
            case ProfileView::Mode::Icon:
                return ProfileViewSerializer::iconModeStr;
            case ProfileView::Mode::List:
                return ProfileViewSerializer::listModeStr;
            default:
                return "";
        }
    }

    std::optional<ProfileView::Mode> ProfileViewSerializer::modeFromString( const QString& mode ) {
        if ( mode == ProfileViewSerializer::iconModeStr ) {
            return ProfileView::Mode::Icon;
        } else if ( mode == ProfileViewSerializer::listModeStr ) {
            return ProfileView::Mode::List;
        } else {
            qWarning().noquote() << "Unknown profile view mode:" << mode;
            return std::nullopt;
        }
    }

    QString ProfileViewSerializer::horizontalAnchorToString(
        const ProfileView::HorizontalAnchor horizontalAnchor ) {
        switch ( horizontalAnchor ) {
            case ProfileView::HorizontalAnchor::Left:
                return ProfileViewSerializer::leftHorizontalAnchorStr;
            case ProfileView::HorizontalAnchor::Center:
                return ProfileViewSerializer::centerHorizontalAnchorStr;
            case ProfileView::HorizontalAnchor::Right:
                return ProfileViewSerializer::rightHorizontalAnchorStr;
            default:
                return "";
        }
    }

    std::optional<ProfileView::HorizontalAnchor>
    ProfileViewSerializer::horizontalAnchorFromString( const QString& horizontalAnchor ) {
        if ( horizontalAnchor == ProfileViewSerializer::leftHorizontalAnchorStr ) {
            return ProfileView::HorizontalAnchor::Left;
        } else if ( horizontalAnchor == ProfileViewSerializer::centerHorizontalAnchorStr ) {
            return ProfileView::HorizontalAnchor::Center;
        } else if ( horizontalAnchor == ProfileViewSerializer::rightHorizontalAnchorStr ) {
            return ProfileView::HorizontalAnchor::Right;
        } else {
            qWarning().noquote() << "Unknown profile view horizontal anchor:" << horizontalAnchor;
            return std::nullopt;
        }
    }

    QString ProfileViewSerializer::verticalAnchorToString(
        const ProfileView::VerticalAnchor verticalAnchor ) {
        switch ( verticalAnchor ) {
            case ProfileView::VerticalAnchor::Top:
                return ProfileViewSerializer::topVerticalAnchorStr;
            case ProfileView::VerticalAnchor::Center:
                return ProfileViewSerializer::centerVerticalAnchorStr;
            case ProfileView::VerticalAnchor::Bottom:
                return ProfileViewSerializer::bottomVerticalAnchorStr;
            default:
                return "";
        }
    }

    std::optional<ProfileView::VerticalAnchor>
    ProfileViewSerializer::verticalAnchorFromString( const QString& verticalAnchor ) {
        if ( verticalAnchor == ProfileViewSerializer::topVerticalAnchorStr ) {
            return ProfileView::VerticalAnchor::Top;
        } else if ( verticalAnchor == ProfileViewSerializer::centerVerticalAnchorStr ) {
            return ProfileView::VerticalAnchor::Center;
        } else if ( verticalAnchor == ProfileViewSerializer::bottomVerticalAnchorStr ) {
            return ProfileView::VerticalAnchor::Bottom;
        } else {
            qWarning().noquote() << "Unknown profile view vertical anchor:" << verticalAnchor;
            return std::nullopt;
        }
    }

    QString ProfileViewSerializer::wrapModeToString( const ProfileView::WrapMode wrapMode ) {
        switch ( wrapMode ) {
            case ProfileView::WrapMode::Scroll:
                return ProfileViewSerializer::scrollWrapModeStr;
            case ProfileView::WrapMode::Grid:
                return ProfileViewSerializer::gridWrapModeStr;
            default:
                return "";
        }
    }

    std::optional<ProfileView::WrapMode>
    ProfileViewSerializer::wrapModeFromString( const QString& wrapMode ) {
        if ( wrapMode == ProfileViewSerializer::scrollWrapModeStr ) {
            return ProfileView::WrapMode::Scroll;
        } else if ( wrapMode == ProfileViewSerializer::gridWrapModeStr ) {
            return ProfileView::WrapMode::Grid;
        } else {
            qWarning().noquote() << "Unknown profile view wrap mode:" << wrapMode;
            return std::nullopt;
        }
    }

    QString
    ProfileViewSerializer::flowDirectionToString( const ProfileView::FlowDirection flowDirection ) {
        switch ( flowDirection ) {
            case ProfileView::FlowDirection::Horizontal:
                return ProfileViewSerializer::horizontalFlowDirectionStr;
            case ProfileView::FlowDirection::Vertical:
                return ProfileViewSerializer::verticalFlowDirectionStr;
            default:
                return "";
        }
    }

    std::optional<ProfileView::FlowDirection>
    ProfileViewSerializer::flowDirectionFromString( const QString& flowDirection ) {
        if ( flowDirection == ProfileViewSerializer::horizontalFlowDirectionStr ) {
            return ProfileView::FlowDirection::Horizontal;
        } else if ( flowDirection == ProfileViewSerializer::verticalFlowDirectionStr ) {
            return ProfileView::FlowDirection::Vertical;
        } else {
            qWarning().noquote() << "Unknown profile view flow direction:" << flowDirection;
            return std::nullopt;
        }
    }

} // namespace Serializer