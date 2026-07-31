#include "ProfileViewSerializer.hpp"

namespace Service::Serializer {

    QString ProfileViewSerializer::viewToSource( const ProfileView& view ) {
        if ( view.mode == ProfileView::Mode::List ) {
            if ( view.wrapMode == ProfileView::WrapMode::Grid ) {
                return "qml/ExecutionTarget/ListGridView.qml";
            } else {
                return "qml/ExecutionTarget/ListScrollView.qml";
            }
        } else {
            if ( view.wrapMode == ProfileView::WrapMode::Grid ) {
                if ( view.flowDirection == ProfileView::FlowDirection::Vertical ) {
                    return "qml/ExecutionTarget/VerticalIconGridView.qml";
                } else {
                    return "qml/ExecutionTarget/HorizontalIconGridView.qml";
                }
            } else {
                if ( view.flowDirection == ProfileView::FlowDirection::Vertical ) {
                    return "qml/ExecutionTarget/VerticalIconScrollView.qml";
                } else {
                    return "qml/ExecutionTarget/HorizontalIconScrollView.qml";
                }
            }
        }
    }
} // namespace Service::Serializer