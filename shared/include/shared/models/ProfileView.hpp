#pragma once

#include <qtypes.h>

namespace Models::Profile {
    class ProfileView {
      public:
        enum class Mode { Icon, List };
        enum class HorizontalAnchor { Left, Center, Right };
        enum class VerticalAnchor { Top, Center, Bottom };
        enum class WrapMode { Scroll, Grid };
        enum class FlowDirection { Horizontal, Vertical };

        explicit ProfileView( Mode mode,
                              HorizontalAnchor horizontalAnchor,
                              VerticalAnchor verticalAnchor,
                              qsizetype margin,
                              WrapMode wrapMode,
                              FlowDirection flowDirection )
            : mode( mode ), horizontalAnchor( horizontalAnchor ), verticalAnchor( verticalAnchor ),
              margin( margin ), wrapMode( wrapMode ), flowDirection( flowDirection ) {}

        Mode mode;
        HorizontalAnchor horizontalAnchor;
        VerticalAnchor verticalAnchor;
        qsizetype margin;
        WrapMode wrapMode;
        FlowDirection flowDirection;
    };
} // namespace Models::Profile
