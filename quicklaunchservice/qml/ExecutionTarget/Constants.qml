pragma Singleton
import QtQuick

import QuickLaunchService 1.0

QtObject {
    readonly property int executionTargetListItemHeight: 38
    readonly property int executionTargetListItemMaxWidth: 300
    readonly property int executionTargetIconItemWidth: 120
    readonly property int executionTargetIconItemHeight: 134
    readonly property var groupIconLayouts: ({
        1: [
            {x:0, y:0, w:1, h:1}
        ],
        2: [
            {x:0,   y:0.25, w:0.5, h:0.5},
            {x:0.5, y:0.25, w:0.5, h:0.5}
        ],
        3: [
            {x:0.25, y:0,   w:0.5, h:0.5},
            {x:0,    y:0.5, w:0.5, h:0.5},
            {x:0.5,  y:0.5, w:0.5, h:0.5}
        ],
        4: [
            {x:0,   y:0,   w:0.5, h:0.5},
            {x:0.5, y:0,   w:0.5, h:0.5},
            {x:0,   y:0.5, w:0.5, h:0.5},
            {x:0.5, y:0.5, w:0.5, h:0.5}
        ]
    })
}
