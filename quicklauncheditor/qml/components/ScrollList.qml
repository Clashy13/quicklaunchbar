import QtQuick
import QtQuick.Controls

import QuickLaunchEditor 1.0

ScrollView {
    id: root

    required property var model
    property alias delegate: repeater.delegate
    spacing: 0

    ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
    ScrollBar.vertical: ScrollBar {
        id: scrollbar
        policy: root.contentHeight > root.height ? ScrollBar.AlwaysOn : ScrollBar.AlwaysOff
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        contentItem: Rectangle {
            implicitHeight: root.height
            implicitWidth: 6
            radius: implicitWidth / 2
            color: scrollbar.pressed ? Colors.scrollBarPressed : scrollbar.hovered ? Colors.scrollBarHovered : Colors.scrollBar
        }
    }

    Component.onCompleted: {
        contentItem.boundsBehavior = Flickable.StopAtBounds;
    }

    Column {
        id: column
        anchors.left: parent.left
        anchors.right: parent.right
        spacing: root.spacing

        Repeater {
            id: repeater
            model: root.model
            Component.onCompleted: {
                addToMoveItemConnection.enabled = true;
            }
        }
    }

    Connections {
        id: addToMoveItemConnection
        target: repeater
        enabled: false

        function onItemAdded(index, item) {
            root.moveToItem(index, item)
        }
    }

    function reload() {
        addToMoveItemConnection.enabled = false;
        Qt.callLater(()=> {addToMoveItemConnection.enabled = true;})
    }

    NumberAnimation {
        id: scrollAnim
        target: root.contentItem
        property: "contentY"
        duration: 120
        easing.type: Easing.OutCubic
    }

    function moveToItem(index, item) {
        let top = 0;
        for(let i = 0; i < index; i++) {
            top += repeater.itemAt(i).height + root.spacing;
        }
        root.moveTo(top,top + item.height);
    }

    function moveToSubItem(index, subItemTop, subItemBottom) {
        let top = 0;
        for(let i = 0; i < index; i++) {
            top += repeater.itemAt(i).height + root.spacing;
        }
        const bottom = top + subItemBottom;
        top += subItemBottom;

        root.moveTo(top,bottom);
    }

    function moveTo(top, bottom) {
        let newContentY = -1;
        if (top < root.contentItem.contentY) {
            newContentY = top;
        } else if (bottom > root.contentItem.contentY + root.contentItem.height) {
            newContentY = bottom - root.contentItem.height;
        }

        if(newContentY != -1 && newContentY != root.contentItem.contentY) {
            scrollAnim.stop();
            scrollAnim.from = root.contentItem.contentY;
            scrollAnim.to = newContentY;
            scrollAnim.start();
        }
    }
}
