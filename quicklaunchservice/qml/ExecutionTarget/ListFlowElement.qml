import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import QuickLaunchService 1.0

FlowElement {
    id: root
    
    iconSize: 30
    margin: 4
    radius: 6
    anchors.left: parent.left
    anchors.right: parent.right
    implicitWidth: executionTargetDisplay.implicitWidth + root.margin * 2
    implicitHeight: executionTargetDisplay.implicitHeight + root.margin * 2
    height: Constants.executionTargetListItemHeight
    

    RowLayout {
        id: executionTargetDisplay
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.leftMargin: root.margin
        anchors.rightMargin: root.margin
        anchors.verticalCenter: parent.verticalCenter
        spacing: 8
        clip: true

        GroupIcon {
            id: iconImage
            width: root.iconSize
            height: root.iconSize
            sources: root.executionTarget.iconSources
        }

        Label {
            id: executionTargetTitle
            Layout.fillWidth: true
            text: executionTarget.name
            elide: Text.ElideRight
            font.pixelSize: 14
        }
    }
}
