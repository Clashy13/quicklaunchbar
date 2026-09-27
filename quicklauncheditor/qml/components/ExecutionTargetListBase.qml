import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import QuickLaunchEditor 1.0

import "qrc:/components"
import "qrc:/executiontargets"

Item {
    id: root

    required property var executionTargets
    property alias delegate: repeater.delegate
    property alias repeater: repeater
    implicitHeight: column.height
    property int spacing: 0
    signal itemAdded(top: int, bottom: int)

    Column {
        id: column
        width: parent.width
        spacing: root.spacing
        Repeater {
            id: repeater
            model: root.executionTargets
            onItemAdded: (index, item) => {
                let top = 0;
                for(let i = 0; i < index; i++) {
                    top += repeater.itemAt(i).height + root.spacing;
                }
                root.itemAdded(top,top + item.height);
            }
        }
    }

    function showDeleteWindow(index) {
        deleteWindow.index = index;
        deleteWindow.showCentered(root.Window.window);
    }

    ToolWindow {
        id: deleteWindow
        minimumWidth: 200
        minimumHeight: 100
        maximumWidth: 200
        maximumHeight: 100

        property int index: -1
        onButtonPressed: (index) =>  {
            if(index == 1 && deleteWindow.index != -1) {
                if(ProfileManager.currentProfile) {
                    root.executionTargets.removeItem(deleteWindow.index);
                }
                deleteWindow.index = -1;
            }
        }

        buttonModel: [ { name: "Cancel" }, { name: "Delete" } ]

        Text {
            anchors.fill: parent
            anchors.margins: 6
            text: "Do you really want to delete this execution target?"
            wrapMode: Text.WordWrap
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }
    }
}
