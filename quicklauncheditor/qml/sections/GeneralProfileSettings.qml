import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import QuickLaunchEditor 1.0

import "qrc:/components"

Item {
    id: root

    property var profile: ProfileManager.currentProfile

    implicitHeight: grid.implicitHeight + grid.anchors.margins*2
    implicitWidth: grid.implicitWidth + grid.anchors.margins*2

    GridLayout {
        id: grid
        anchors.fill: parent
        anchors.margins: 6

        columns: 2
        columnSpacing: 12
        rowSpacing: 12

        Text {
            text: "Enabled"
        }

        Item {
            CheckBox {
                id: enabledCheckBox
                anchors.verticalCenter: parent.verticalCenter
                checked: {
                    if(root.profile) {
                        return root.profile.enabled
                    } else {
                        return true;
                    }
                }
                onToggled: {
                    root.profile.enabled = checked;
                }
            }
        }

        Text {
            text: "Shortcut"
            Layout.topMargin: 6
            Layout.alignment: Qt.AlignTop
        }

        ShortcutEdit {
            Layout.fillWidth: true
            shortcut: {
                if(root.profile) {
                    return root.profile.shortcut
                } else {
                    return "";
                }
            }
            onEditingFinished: (shortcut) => {
                root.profile.shortcut = shortcut;
            }
        }

        Text {
            text: "View Mode"
        }

        SelectorBar {
            model: [
                {
                    name: "Icon",
                    iconSource: Icons.iconViewMode
                },
                {
                    name: "List",
                    iconSource: Icons.listViewMode
                }
            ]
            checkedIndex: {
                if(root.profile) {
                    return root.profile.view.mode
                } else {
                    return 0;
                }
            }
            onChecked: (index) => {
                root.profile.view.mode = index;
            }
        }

        Text {
            text: "Position"
            Layout.topMargin: 6
            Layout.alignment: Qt.AlignTop
        }

        PositionSelectionField {
            checkedIndex: {
                if(root.profile) {
                    return root.profile.view.position
                } else {
                    return 0;
                }
            }
            onChecked: (index) => {
                root.profile.view.position = index;
            }
        }

        Text {
            text: "Offset"
        }

        OffsetSelector {
            value: {
                if(root.profile) {
                    return root.profile.view.offset
                } else {
                    return 0;
                }
            }
            onValueEdited: (value) => {
                root.profile.view.offset = value;
            }
        }

        Text {
            text: "Wrap Mode"
        }

        SelectorBar {
            model: [
                {
                    name: "Scroll",
                    iconSource: Icons.scrollWrapMode
                },
                {
                    name: "Grid",
                    iconSource: Icons.gridWrapMode
                }
            ]
            checkedIndex: {
                if(root.profile) {
                    return root.profile.view.wrapMode
                } else {
                    return 0;
                }
            }
            onChecked: (index) => {
                root.profile.view.wrapMode = index;
            }
        } 

        StackLayout {
            currentIndex: {
                if(root.profile) {
                    return root.profile.view.mode
                } else {
                    return 0;
                }
            }
            Layout.topMargin: 6
            Text {
                text: "Flow Direction"
                Layout.alignment: Qt.AlignTop
            }

            Item {}
        }

        StackLayout {
            currentIndex: {
                if(root.profile) {
                    return root.profile.view.mode
                } else {
                    return 0;
                }
            }
            SelectorBar {
                model: [
                    {
                        name: "",
                        iconSource: Icons.flowRight
                    },
                    {
                        name: "",
                        iconSource: Icons.flowDown
                    }
                ]
                checkedIndex: {
                    if(root.profile) {
                        return root.profile.view.flowDirection
                    } else {
                        return 0;
                    }
                }
                onChecked: (index) => {
                    root.profile.view.flowDirection = index;
                }
            }

            Item {}
        }
    }
}
