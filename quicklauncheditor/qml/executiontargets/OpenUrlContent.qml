import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

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
            text: "Url"
        }

        TextField {
            Layout.fillWidth: true
            text: executionTarget.url

            onTextEdited: {
                executionTarget.url = text;
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
