import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import QuickLaunchEditor 1.0

import "qrc:/components"

Rectangle {
    id: root
    color: Colors.primary.background
    border.width: 1
    border.color: Colors.secondary.border

    Drag.active: dragMouseArea.drag.active
    Drag.hotSpot: dragMouseArea.mapToItem(root, dragMouseArea.mouseX, dragMouseArea.mouseY)
    required property var dragParent
    property real dragItemIndex
    property int trueIndex
    required property var dragTargetList
    property bool collapsed: root.executionTarget.collapsed
    property int topbarHeight: 30
    
    property bool isGroup: false

    signal dragStarted()
    signal dragFinished()
    signal removed()
    signal removedWithWindow()
    signal removedItem(model: var, index: int)
    signal duplicated()

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
            Layout.preferredHeight: root.topbarHeight
            Layout.fillWidth: true
            color: Colors.secondary.background

            Button {
                icon.source: Icons.drag
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                width: height*1.625
                anchors.margins: 3
                anchors.horizontalCenter: parent.horizontalCenter
                background: null
                visible: (dragMouseArea.containsMouse || dragMouseArea.drag.active) && typeName.contentWidth + 8 < (root.width / 2 - width / 2)
                enabled: dragMouseArea.drag.active
            }

            RowLayout {
                anchors.fill: parent

                Item {
                    Layout.fillWidth: true
                    Layout.fillHeight: true

                    Text {
                        id: typeName
                        anchors.fill: parent
                        anchors.leftMargin: 6
                        anchors.rightMargin: 2
                        verticalAlignment: Text.AlignVCenter
                        text: ExecutionTargetManager.typeToString(root.executionTarget.type)
                        elide: Text.ElideRight
                    }

                    MouseArea {
                        id: dragMouseArea
                        anchors.fill: parent
                        drag.target: root
                        cursorShape: containsPress ? Qt.ClosedHandCursor : containsMouse ? Qt.OpenHandCursor : Qt.ArrowCursor
                        hoverEnabled: true

                        drag.onActiveChanged: {
                            if (drag.active) {
                                root.dragStarted();
                            } else {
                                root.dragFinished();
                            }
                        }
                    }
                }

                Row {
                    Layout.fillHeight: true
                    Layout.margins: 2
                    Layout.preferredWidth: implicitWidth
                    spacing: 4

                    Button {
                        height: parent.height
                        width: height
                        style: Colors.Secondary
                        text: root.executionTarget.collapsed ? '▼' : '▲'
                        onPressed: {
                            root.executionTarget.collapsed = !root.executionTarget.collapsed
                        }
                    }

                    Button {
                        id: menuButton
                        icon.source: Icons.menu
                        height: parent.height
                        width: height
                        style: Colors.Secondary
                        onPressed: {
                            if(menu.visible) {
                                menu.close()
                            } else {
                                menu.open()
                            }
                        }

                        Menu {
                            id: menu
                            y: menuButton.height
                            width: 140
                            closePolicy: Popup.CloseOnPressOutsideParent
                            background: Rectangle {
                                color: Colors.primary.background
                                border.width: 1
                                border.color: Colors.secondary.border
                            }

                            MenuItem {
                                id: removeButton
                                contentItem: Text {
                                    text: "Delete"
                                }
                                background:  Rectangle {
                                    color: removeButton.hovered ? Colors.listItemSelected : "transparent"
                                }
                                onTriggered: {
                                    root.removedWithWindow();
                                }
                            }

                            MenuItem {
                                id: copyButton
                                contentItem: Text {
                                    text: "Copy"
                                }
                                background:  Rectangle {
                                    color: copyButton.hovered ? Colors.listItemSelected : "transparent"
                                }
                                onTriggered: {
                                    ExecutionTargetManager.executionTargetToClipboard(root.executionTarget);
                                }
                            }

                            MenuItem {
                                id: cutButton
                                contentItem: Text {
                                    text: "Cut"
                                }
                                background:  Rectangle {
                                    color: cutButton.hovered ? Colors.listItemSelected : "transparent"
                                }
                                onTriggered: {
                                    ExecutionTargetManager.executionTargetToClipboard(root.executionTarget);
                                    root.removed();
                                }
                            }

                            MenuItem {
                                id: duplicateButton
                                contentItem: Text {
                                    text: "Duplicate"
                                }
                                background:  Rectangle {
                                    color: duplicateButton.hovered ? Colors.listItemSelected : "transparent"
                                }
                                onTriggered: {
                                    root.duplicated();
                                }
                            }
                        }
                    }
                }
            }
        }

        Loader {
            id: contentLoader
            visible: !root.collapsed
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