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

            SingleExecutionTargetList {
                id: executionTargetList
                anchors.fill: parent
                anchors.topMargin: 6
                anchors.leftMargin: 6
                anchors.bottomMargin: 6
                anchors.rightMargin: -1
                spacing: -2
                executionTargets: root.executionTarget.executionTargets
                onItemAdded: (top,bottom) => {
                    const localY = executionTargetList.mapToItem(root, 0, 0).y;
                    root.itemAdded(localY+top,localY+bottom)
                }
            }
        }
    }
}
