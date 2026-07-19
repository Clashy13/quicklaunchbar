import QtQuick

import QuickLaunchService 1.0

Item {
    id: root

    required property var sources
    readonly property var layouts: Constants.groupIconLayouts

    Repeater {
        model: Math.min(root.sources.length, 4)

        Image {
            required property int index
            readonly property int count: Math.min(root.sources.length, 4)
            readonly property var rect: root.layouts[count][index]

            source: root.sources[index]

            x: rect.x * root.width
            y: rect.y * root.height
            width: rect.w * root.width
            height: rect.h * root.height
            sourceSize: Qt.size(width, height)
        }
    }
}
