import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Window

import QuickLaunchEditor 1.0

import "qrc:/components"

Item {
    id: root

    required property var executionTargets
    property var executionTargetNames: ExecutionTargetManager.executionTargetNames

    implicitHeight: row.implicitHeight

    RowLayout {
        id: row
        anchors.fill: parent
        anchors.leftMargin: 6
        spacing: 6

        Text {
            text: "Execution Targets"
        }

        Item {
            Layout.fillWidth: true
        }

        Button {
            id: addButton
            text: "Add"
            onPressed: {
                if(menu.visible) {
                    menu.close()
                } else {
                    menu.open()
                }
            }

            contentItem: Row {
                spacing: 8

                Text {
                    text: addButton.text
                    verticalAlignment: Text.AlignVCenter
                }

                Text {
                    text: menu.opened ? "▴" : "▾"
                    verticalAlignment: Text.AlignVCenter
                }
            }

            Menu {
                id: menu
                y: addButton.height
                closePolicy: Popup.CloseOnPressOutsideParent
                background: Rectangle {
                    color: Colors.primary.background
                    border.width: 1
                    border.color: Colors.secondary.border
                }
                implicitWidth: Math.max(children.map(child => child.implicitWidth))
                Repeater {
                    model: root.executionTargetNames
                    delegate: MenuItem {
                        id: mennuItem
                        required property int index
                        required property var modelData
                        contentItem: Text {
                            text: modelData
                        }
                        background: Rectangle {
                            color: mennuItem.hovered ? Colors.listItemSelected : "transparent"
                        }
                        onTriggered: {
                            if(index == 0) {
                                desktopApplicationSelector.showCentered(root.Window.window);
                            } else {
                                const e = ExecutionTargetManager.newExecutionTarget(index);
                                root.executionTargets.addItem(e);
                            }
                        }
                    }
                }
            }
        }
    }

    DesktopApplicationSelectionWindow {
        id: desktopApplicationSelector
        onApplicationSelected: (application) => {
            const e = ExecutionTargetManager.newDesktopApplication(application);
            root.executionTargets.addItem(e);
        }
    }
}