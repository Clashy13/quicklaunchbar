import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import QuickLaunchEditor 1.0

import "qrc:/components"

Rectangle {
    id: root
    color: "transparent"
    border.width: 1
    border.color: Colors.secondary.border  

    signal removed()
    signal removedItem(model: var, index: int)

    required property var executionTarget
    property var sourceContentComponent: {
        switch(root.executionTarget.type) {
            case 0:
                return desktopApplicationContent;
            case 1:
                return executableFileContent;
            case 2:
                return commandContent;
            case 3:
                return openFileContent;
            case 4:
                return openUrlContent;
        }
    }
    height: column.height + 2

    ColumnLayout {
        id: column
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.margins: 1
        spacing: 0

        Rectangle {
            Layout.preferredHeight: 30
            Layout.fillWidth: true
            color: Colors.secondary.background

            RowLayout {
                anchors.fill: parent
                anchors.leftMargin: 6
                anchors.rightMargin: 2
                anchors.topMargin: 2
                anchors.bottomMargin: 2

                Text {
                    text: ExecutionTargetManager.typeToString(root.executionTarget.type)
                }

                Item {
                    Layout.fillWidth: true
                }

                Button {
                    icon.source: Icons.trashCan
                    Layout.fillHeight: true
                    Layout.preferredWidth: height
                    style: Colors.Secondary
                    onClicked: {
                        root.removed();
                    }
                }

                Button {
                    Layout.fillHeight: true
                    Layout.preferredWidth: height
                    style: Colors.Secondary
                    text: root.executionTarget.collapsed ? '▼' : '▲'
                    onPressed: {
                        root.executionTarget.collapsed = !root.executionTarget.collapsed
                    }
                }
            }
        }

        Loader {
            id: contentLoader
            visible: !root.executionTarget.collapsed
            Layout.fillWidth: true
            Layout.preferredHeight: item ? item.implicitHeight : 0
            sourceComponent: root.sourceContentComponent
        }
    }

    function desktopApplicationContent() {
        return desktopApplicationContent;
    }

    Component {
        id: desktopApplicationContent
        DesktopApplicationContent {
            executionTarget: root.executionTarget
        }
    }

    function executableFileContent() {
        return executableFileContent;
    }

    Component {
        id: executableFileContent
        ExecutableFileContent {
            executionTarget: root.executionTarget
        }
    }

    function commandContent() {
        return commandContent;
    }

    Component {
        id: commandContent
        CommandContent {
            executionTarget: root.executionTarget
        }
    }

    function openFileContent() {
        return openFileContent;
    }

    Component {
        id: openFileContent
        OpenFileContent {
            executionTarget: root.executionTarget
        }
    }

    function openUrlContent() {
        return openUrlContent;
    }

    Component {
        id: openUrlContent
        OpenUrlContent {
            executionTarget: root.executionTarget
        }
    }
}