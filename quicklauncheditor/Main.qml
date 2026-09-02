import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import QuickLaunchEditor 1.0

import "qrc:/sections"
import "qrc:/components"

Window {
    id: root

    visible: true
    width: column.implicitWidth
    height: column.implicitHeight
    minimumWidth: column.Layout.minimumWidth + column.anchors.margins*2
    minimumHeight: column.Layout.minimumHeight + column.anchors.margins*2

    onClosing: (close) => {
        if(ProfileManager.edited) {
            close.accepted = false;
            closeWindow.showCentered(root);
        }
    }

    Rectangle {
        id: background
        anchors.fill: parent
        color: Colors.primary.background
    }

    ColumnLayout {
        id: column
        anchors.fill: parent
        spacing: 0

        Rectangle {
            Layout.fillWidth: true
            Layout.preferredHeight: 42
            Layout.minimumHeight: 42
            color: Colors.secondary.background

            SaveBar {
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.margins: 6
            }
        }

        Rectangle {
            Layout.fillWidth: true
            Layout.preferredHeight: 1
            color: Colors.secondary.border
        }

        RowLayout {
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.margins: 6
            spacing: 12

            ColumnLayout {
                Layout.fillHeight: true
                Layout.preferredWidth: 190
                Layout.maximumWidth: 190
                Layout.minimumWidth: 120
                spacing: 20

                AddProfileOption {
                    Layout.fillWidth: true
                    Layout.minimumHeight: 30
                    Layout.maximumHeight: 30
                }

                ProfileList {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    Layout.preferredHeight: 160
                    Layout.minimumHeight: 60
                }
            }

            StackLayout {
                currentIndex: ProfileManager.currentProfile == null

                RowLayout {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    spacing: 12

                    ColumnLayout {
                        Layout.fillWidth: false
                        Layout.preferredWidth: generalProfileSettings.implicitWidth
                        Layout.alignment: Qt.AlignTop
                        spacing: 20

                        ProfileTitleBar {
                            Layout.fillWidth: true
                            Layout.minimumHeight: 30
                            Layout.maximumHeight: 30
                        }

                        GeneralProfileSettings {
                            id: generalProfileSettings
                            Layout.alignment: Qt.AlignTop
                            Layout.fillWidth: false
                            Layout.fillHeight: false
                            Layout.preferredWidth: implicitWidth
                            Layout.minimumWidth: implicitWidth
                            Layout.minimumHeight: implicitHeight
                        }
                    }

                    ColumnLayout {
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        spacing: 20

                        AddExecutionTargetOption {
                            Layout.fillWidth: true
                            Layout.minimumHeight: 30
                            Layout.maximumHeight: 30
                            executionTargets: {
                                if(ProfileManager.currentProfile) {
                                    return ProfileManager.currentProfile.executionTargets
                                } else {
                                    return []
                                }
                            }
                        }

                        ExecutionTargetList {
                            Layout.fillHeight: true
                            Layout.fillWidth: true
                            Layout.preferredHeight: 160
                            Layout.minimumHeight: 60
                            Layout.preferredWidth: 400
                            Layout.minimumWidth: 300
                        }
                    }
                }

                Item {
                    Text {
                        anchors.centerIn: parent
                        text: "No profiles created."
                        font.pixelSize: 16
                    }
                }
            }
        }
    }

    ToolWindow {
        id: closeWindow

        minimumWidth: 400
        minimumHeight: 100
        maximumWidth: 400
        maximumHeight: 100

        buttonModel: [
            {
                name: "Cancel"
            },
            {
                name: "Discard and Close"
            },
            {
                name: "Save and Close",
                backgroundColorStyle: Button.Green
            }
        ]

        onButtonPressed: (index) => {
            if(index == 1) {
                ProfileManager.discardEdited();
                Qt.quit();
            } else if(index == 2) {
                ProfileManager.save();
                Qt.quit();
            }
        }

        Text {
            anchors.fill: parent
            text: "Do you want to save before closing?"
            wrapMode: Text.WordWrap
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.pixelSize: 16
        }
    }
}
