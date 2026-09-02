import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import QuickLaunchEditor 1.0

import "qrc:/components"

Item {
    id: root

    required property var executionTarget

    implicitHeight: row.implicitHeight + row.anchors.margins*2

    RowLayout {
        id: row
        anchors.fill: parent
        anchors.margins: 6
        spacing: 18

        Image {
            source: executionTarget.iconUrl
            Layout.preferredWidth: 40
            Layout.preferredHeight: 40
            sourceSize: Qt.size(Layout.preferredWidth, Layout.preferredHeight)
        }

        Text {
            Layout.alignment: Qt.AlignVCenter
            Layout.fillWidth: true
            text: executionTarget.name
            font.pixelSize: 16
            elide: Text.ElideRight
        }
    }
}
