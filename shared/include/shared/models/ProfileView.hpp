#pragma once

#include <qtypes.h>

namespace Shared::Models::Profile {

    class ProfileView {
      public:
        enum class Mode { Icon, List };
        enum class Position {
            TopLeft,
            Top,
            TopRight,
            Left,
            Center,
            Right,
            BottomLeft,
            Bottom,
            BottomRight
        };
        enum class WrapMode { Scroll, Grid };
        enum class FlowDirection { Right, Down };

        explicit ProfileView( const Mode mode,
                              const Position position,
                              const qsizetype offset,
                              const WrapMode wrapMode,
                              const FlowDirection flowDirection )
            : mode( mode ), position( position ), offset( offset ), wrapMode( wrapMode ),
              flowDirection( flowDirection ) {}

        Mode mode;
        Position position;
        qsizetype offset;
        WrapMode wrapMode;
        FlowDirection flowDirection;
    };
} // namespace Shared::Models::Profile
