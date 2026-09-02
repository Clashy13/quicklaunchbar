import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import QuickLaunchEditor 1.0

import "qrc:/components"

ColumnLayout {
    id: root
    spacing: 12

    required property var executionTarget
    signal itemAdded(top: int, bottom: int)

    RowLayout {
        Layout.fillWidth: true
        Layout.margins: 6
        spacing: 12

        Text {
            text: "Name"
        }

        TextField {
            Layout.fillWidth: true
            text: executionTarget.name

            onTextEdited: {
                executionTarget.name = text;
            }
        }
    }

    AddExecutionTargetOption {
        Layout.fillWidth: true
        executionTargets: root.executionTarget.executionTargets
        executionTargetNames: ExecutionTargetManager.singleExecutionTargetNames
    }

    Rectangle {
        Layout.fillWidth: true
        color: Colors.secondary.background
        Layout.preferredHeight: rec.implicitHeight + rec.anchors.topMargin + rec.anchors.bottomMargin

        Rectangle {
            id: rec
            anchors.fill: parent
            anchors.topMargin: 10
            anchors.leftMargin: 10
            anchors.bottomMargin: 10
            color: Colors.primary.background
            implicitHeight: executionTargetList.implicitHeight + executionTargetList.anchors.topMargin + executionTargetList.anchors.bottomMargin
            
            Column {
                id: executionTargetList
                anchors.fill: parent
                anchors.topMargin: 6
                anchors.leftMargin: 6
                anchors.bottomMargin: 6
                spacing: -2

                Repeater {
                    id: repeater
                    model: root.executionTarget.executionTargets

                    delegate: SingleExecutionTargetBox {
                        anchors.left: parent.left
                        anchors.right: parent.right
                        anchors.rightMargin: -1
                        required property var item
                        required property int index 
                        executionTarget: item
                        onRemoved: {
                            deleteWindow.index = index;
                            deleteWindow.showCentered(root.Window.window);
                        }
                    }
                    onItemAdded: (index, item) => {
                        let top = repeater.mapToItem(root, 0, 0).y;
                        for(let i = 0; i < index; i++) {
                            top += repeater.itemAt(i).height + root.spacing;
                        }
                        root.itemAdded(top,top + item.height);
                    }
                }
            }
        }
    }

    ToolWindow {
        id: deleteWindow
        minimumWidth: 200
        minimumHeight: 100
        maximumWidth: 200
        maximumHeight: 100

        property int index: -1
        onButtonPressed: (index) => {
            if(index == 1 && deleteWindow.index != -1) {
                root.executionTarget.executionTargets.removeItem(deleteWindow.index);
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
