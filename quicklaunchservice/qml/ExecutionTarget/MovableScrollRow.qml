import QtQuick
import QtQuick.Controls

ScrollView {
    id: root

    required property var model
    property alias delegate: repeater.delegate
    required property int maxWidth
    required property int maxHeight
    property alias scrollAnimRunning: keyScrollAnim.running

    width: Math.min(row.implicitWidth, root.maxWidth)
    height: Math.min(row.implicitHeight + (ScrollBar.horizontal.visible ? ScrollBar.horizontal.height : 0),root.maxHeight)

    ScrollBar.horizontal.policy: root.contentWidth > root.width ? ScrollBar.AlwaysOn : ScrollBar.AlwaysOff
    ScrollBar.vertical.policy: ScrollBar.AlwaysOff

    Component.onCompleted: {
        contentItem.boundsBehavior = Flickable.StopAtBounds;
    }

    Row {
        id: row

        Repeater {
            id: repeater
            model: root.model
        }
    }

    NumberAnimation {
        id: mouseScrollAnim
        target: root.contentItem
        property: "contentX"
        duration: 120
        easing.type: Easing.OutCubic
    }

    NumberAnimation {
        id: keyScrollAnim
        target: root.contentItem
        property: "contentX"
        duration: 120
        easing.type: Easing.OutCubic
    }

    WheelHandler {
        onWheel: function(event) {
            let newContentX = 0;
            if (event.angleDelta.y > 0) {
                newContentX = root.contentItem.contentX - event.angleDelta.y;
                if (newContentX < 0) {
                    newContentX = 0;
                }
            } else {
                newContentX = root.contentItem.contentX - event.angleDelta.y;
                if (newContentX + root.contentItem.width > root.contentItem.contentWidth) {
                    newContentX = root.contentItem.contentWidth -  root.contentItem.width;
                }
            }

            if(newContentX != root.contentItem.contentX) {
                mouseScrollAnim.stop();
                mouseScrollAnim.from = root.contentItem.contentX;
                mouseScrollAnim.to = newContentX;
                mouseScrollAnim.start();
            }

            event.accepted = true;
        }
    }

    function moveTo(index) {
        const item = repeater.itemAt(index);
        const left = item.x;
        const right = left + item.width;

        let newContentX = -1;
        if (left < root.contentItem.contentX) {
            newContentX = left;
        } else if (right > root.contentItem.contentX + root.contentItem.width) {
            newContentX = right - root.contentItem.width;
        }

        if(newContentX != -1 && newContentX != root.contentItem.contentX) {
            keyScrollAnim.stop();
            keyScrollAnim.from = root.contentItem.contentX;
            keyScrollAnim.to = newContentX;
            keyScrollAnim.start();
        }
    }
}
