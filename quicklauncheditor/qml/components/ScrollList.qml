import QtQuick
import QtQuick.Controls

import QuickLaunchEditor 1.0

ScrollListBase {
    id: root

    required property var model
    property alias delegate: repeater.delegate
    repeater: repeater

    Column {
        id: column
        anchors.left: parent.left
        anchors.right: parent.right
        spacing: root.spacing

        Repeater {
            id: repeater
            model: root.model
        }
    }
}
