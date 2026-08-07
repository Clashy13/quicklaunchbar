#include "ProfileViewSerializer.hpp"

#include "PropertySerializer.hpp"

namespace Shared::Serializer {

    std::optional<ProfileViewSerializer::ProfileView>
    ProfileViewSerializer::serialized( const QJsonObject& obj ) {
        const auto mode = ProfileViewSerializer::serializedMode( obj );
        const auto position = ProfileViewSerializer::serializedPosition( obj );
        const auto offset = ProfileViewSerializer::serializedOffset( obj );
        const auto wrapMode = ProfileViewSerializer::serializedWrapMode( obj );

        if ( mode && position && offset && wrapMode ) {
            ProfileView::FlowDirection flowDirection;
            if ( *mode == ProfileView::Mode::Icon ) {
                if ( const auto flowDirectionOpt =
                         ProfileViewSerializer::serializedFlowDirection( obj ) ) {
                    flowDirection = *flowDirectionOpt;
                } else {
                    return std::nullopt;
                }
            } else {
                flowDirection = ProfileView::FlowDirection::Vertical;
            }
            ProfileView view( *mode, *position, *offset, *wrapMode, flowDirection );
            return view;
        } else {
            return std::nullopt;
        }
    }

    QJsonObject ProfileViewSerializer::deserialized( const ProfileView& view ) {
        QJsonObject obj;
        obj[ ProfileViewSerializer::modeStr ] = ProfileViewSerializer::modeToString( view.mode );
        obj[ ProfileViewSerializer::positionStr ] =
            ProfileViewSerializer::positionToString( view.position );
        obj[ ProfileViewSerializer::offsetStr ] = view.offset;
        obj[ ProfileViewSerializer::wrapModeStr ] =
            ProfileViewSerializer::wrapModeToString( view.wrapMode );

        if ( view.mode == ProfileView::Mode::Icon ) {
            obj[ ProfileViewSerializer::flowDirectionStr ] =
                ProfileViewSerializer::flowDirectionToString( view.flowDirection );
        }

        return obj;
    }

    std::optional<ProfileViewSerializer::ProfileView::Mode>
    ProfileViewSerializer::serializedMode( const QJsonObject& obj ) {
        if ( const auto modeStrOpt =
                 PropertySerializer::serializedStringProperty( obj,
                                                               ProfileViewSerializer::modeStr ) ) {
            if ( const auto modeOpt = ProfileViewSerializer::modeFromString( *modeStrOpt ) ) {
                return *modeOpt;
            } else {
                return std::nullopt;
            }
        } else {
            return std::nullopt;
        }
    }

    std::optional<ProfileViewSerializer::ProfileView::Position>
    ProfileViewSerializer::serializedPosition( const QJsonObject& obj ) {
        if ( const auto positionStrOpt = PropertySerializer::serializedStringProperty(
                 obj,
                 ProfileViewSerializer::positionStr ) ) {
            if ( const auto positionOpt =
                     ProfileViewSerializer::positionFromString( *positionStrOpt ) ) {
                return *positionOpt;
            } else {
                return std::nullopt;
            }
        } else {
            return std::nullopt;
        }
    }

    std::optional<qsizetype> ProfileViewSerializer::serializedOffset( const QJsonObject& obj ) {
        if ( const auto marginOpt =
                 PropertySerializer::serializedIntProperty( obj,
                                                            ProfileViewSerializer::offsetStr ) ) {
            if ( *marginOpt < 0 ) {
                qWarning().noquote()
                    << "Property is not a size type:" << ProfileViewSerializer::offsetStr;
                return std::nullopt;
            }
            return *marginOpt;
        } else {
            return std::nullopt;
        }
    }

    std::optional<ProfileViewSerializer::ProfileView::WrapMode>
    ProfileViewSerializer::serializedWrapMode( const QJsonObject& obj ) {
        if ( const auto wrapModeStrOpt = PropertySerializer::serializedStringProperty(
                 obj,
                 ProfileViewSerializer::wrapModeStr ) ) {
            if ( const auto wrapModeOpt =
                     ProfileViewSerializer::wrapModeFromString( *wrapModeStrOpt ) ) {
                return *wrapModeOpt;
            } else {
                return std::nullopt;
            }
        } else {
            return std::nullopt;
        }
    }

    std::optional<ProfileViewSerializer::ProfileView::FlowDirection>
    ProfileViewSerializer::serializedFlowDirection( const QJsonObject& obj ) {
        if ( const auto flowDirectionStrOpt = PropertySerializer::serializedStringProperty(
                 obj,
                 ProfileViewSerializer::flowDirectionStr ) ) {
            if ( const auto flowDirectionOpt =
                     ProfileViewSerializer::flowDirectionFromString( *flowDirectionStrOpt ) ) {
                return *flowDirectionOpt;
            } else {
                return std::nullopt;
            }
        } else {
            return std::nullopt;
        }
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

    std::optional<ProfileViewSerializer::ProfileView::Mode>
    ProfileViewSerializer::modeFromString( const QString& mode ) {
        if ( mode == ProfileViewSerializer::iconModeStr ) {
            return ProfileView::Mode::Icon;
        } else if ( mode == ProfileViewSerializer::listModeStr ) {
            return ProfileView::Mode::List;
        } else {
            qWarning().noquote() << "Unknown profile view mode:" << mode;
            return std::nullopt;
        }
    }

    QString ProfileViewSerializer::positionToString( const ProfileView::Position position ) {
        switch ( position ) {
            case ProfileView::Position::TopLeft:
                return ProfileViewSerializer::topLeftPositionStr;
            case ProfileView::Position::Top:
                return ProfileViewSerializer::topPositionStr;
            case ProfileView::Position::TopRight:
                return ProfileViewSerializer::topRightPositionStr;
            case ProfileView::Position::Left:
                return ProfileViewSerializer::leftPositionStr;
            case ProfileView::Position::Center:
                return ProfileViewSerializer::centerPositionStr;
            case ProfileView::Position::Right:
                return ProfileViewSerializer::rightPositionStr;
            case ProfileView::Position::BottomLeft:
                return ProfileViewSerializer::bottomLeftPositionStr;
            case ProfileView::Position::Bottom:
                return ProfileViewSerializer::bottomPositionStr;
            case ProfileView::Position::BottomRight:
                return ProfileViewSerializer::bottomRightPositionStr;
            default:
                return "";
        }
    }

    std::optional<ProfileViewSerializer::ProfileView::Position>
    ProfileViewSerializer::positionFromString( const QString& position ) {
        if ( position == ProfileViewSerializer::topLeftPositionStr ) {
            return ProfileView::Position::TopLeft;
        } else if ( position == ProfileViewSerializer::topPositionStr ) {
            return ProfileView::Position::Top;
        } else if ( position == ProfileViewSerializer::topRightPositionStr ) {
            return ProfileView::Position::TopRight;
        } else if ( position == ProfileViewSerializer::leftPositionStr ) {
            return ProfileView::Position::Left;
        } else if ( position == ProfileViewSerializer::centerPositionStr ) {
            return ProfileView::Position::Center;
        } else if ( position == ProfileViewSerializer::rightPositionStr ) {
            return ProfileView::Position::Right;
        } else if ( position == ProfileViewSerializer::bottomLeftPositionStr ) {
            return ProfileView::Position::BottomLeft;
        } else if ( position == ProfileViewSerializer::bottomPositionStr ) {
            return ProfileView::Position::Bottom;
        } else if ( position == ProfileViewSerializer::bottomRightPositionStr ) {
            return ProfileView::Position::BottomRight;
        } else {
            qWarning().noquote() << "Unknown profile view horizontal anchor:" << position;
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

    std::optional<ProfileViewSerializer::ProfileView::WrapMode>
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

    std::optional<ProfileViewSerializer::ProfileView::FlowDirection>
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

} // namespace Shared::Serializer