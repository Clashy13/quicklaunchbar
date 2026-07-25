import QtQuick

import QuickLaunchService 1.0

Rectangle {
    id: root
    
    required property var executionTarget
    required property bool isSelected
    required property int iconSize
    required property int margin
    required property bool supressMouseHover

    signal launched()
    signal selected()

    color: root.isSelected ? Colors.secondary : "transparent"

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        onClicked: root.launched()
        hoverEnabled: true
        onEntered: {
            if(!root.supressMouseHover) {
                root.selected();
            }
        }
    }
}
