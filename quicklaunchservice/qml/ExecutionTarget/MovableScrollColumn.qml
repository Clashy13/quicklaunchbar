import QtQuick
import QtQuick.Controls

ScrollView {
    id: root

    required property var model
    property alias delegate: repeater.delegate
    required property int maxWidth
    required property int maxHeight
    property alias scrollAnimRunning: scrollAnim.running

    width: Math.min(column.implicitWidth + (ScrollBar.vertical.visible ? ScrollBar.vertical.width : 0),root.maxWidth)
    height: Math.min(column.implicitHeight,root.maxHeight)

    ScrollBar.vertical.policy: root.contentHeight > root.height ? ScrollBar.AlwaysOn : ScrollBar.AlwaysOff
    ScrollBar.horizontal.policy: ScrollBar.AlwaysOff

    Component.onCompleted: {
        contentItem.boundsBehavior = Flickable.StopAtBounds;
    }

    Column {
        id: column

        width: Math.min(maxChildImplicitWidth, root.maxWidth)
        readonly property real maxChildImplicitWidth: {
            let w = 0;
            for (let i = 0; i < children.length; ++i)
                w = Math.max(w, children[i].implicitWidth);
            return w;
        }

        Repeater {
            id: repeater
            model: root.model
        }
    }

    NumberAnimation {
        id: scrollAnim
        target: root.contentItem
        property: "contentY"
        duration: 120
        easing.type: Easing.OutCubic
    }

    function moveTo(index) {
        const item = repeater.itemAt(index);
        const top = item.y;
        const bottom = top + item.height;

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
