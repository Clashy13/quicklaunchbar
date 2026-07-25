import QtQuick
import QtQuick.Controls

import QuickLaunchService 1.0

FlowElement {
    id: root
    
    iconSize: 100
    margin: 10
    radius: 10
    implicitWidth: executionTargetDisplay.implicitWidth + root.margin * 2
    implicitHeight: executionTargetDisplay.implicitHeight + root.margin * 2
    width: Constants.executionTargetIconItemWidth
    height: Constants.executionTargetIconItemHeight

    Column {
        id: executionTargetDisplay
        anchors.centerIn: parent
        spacing: 0
        clip: true

        GroupIcon {
            id: iconImage
            width: root.iconSize
            height: root.iconSize
            sources: root.executionTarget.iconSources
        }

        Label {
            id: executionTargetTitle
            anchors.left: parent.left
            anchors.right: parent.right
            horizontalAlignment: Text.AlignHCenter
            text: executionTarget.name
            elide: Text.ElideRight
            font.pixelSize: 12
        }
    }
}
