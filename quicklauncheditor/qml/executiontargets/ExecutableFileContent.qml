import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Dialogs

import QuickLaunchEditor 1.0

import "qrc:/components"

Item {
    id: root

    required property var executionTarget

    implicitHeight: grid.implicitHeight + grid.anchors.margins*2

    GridLayout {
        id: grid
        anchors.fill: parent
        anchors.margins: 6
        columns: 2
        columnSpacing: 12
        rowSpacing: 12

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

        Text {
            text: "File Path"
        }

        RowLayout {
            Layout.fillWidth: true

            TextField {
                Layout.fillWidth: true
                text: executionTarget.filePath

                onTextEdited: {
                    executionTarget.filePath = text;
                }
            }

            Button {
                Layout.preferredWidth: height
                Layout.fillHeight: true
                icon.source: Icons.folder
                onClicked: {
                    fileDialog.open();
                }
            }

            FileDialog {
                id: fileDialog

                title: "Select a file"
                nameFilters: [
                    "All files (*)"
                ]

                onAccepted: {
                    executionTarget.filePath = new URL(selectedFile).pathname;;
                }
            }
        }

        Text {
            text: "Arguments"
        }

        TextField {
            Layout.fillWidth: true
            text: executionTarget.arguments

            onTextEdited: {
                executionTarget.arguments = text;
            }
        }

        Text {
            text: "Icon File"
        }

        IconImageSelector {
            Layout.fillWidth: true
            iconFilePath: executionTarget.iconFilePath
            onIconFilePathChanged: {
                executionTarget.iconFilePath = iconFilePath;
            }
        }
    }
}