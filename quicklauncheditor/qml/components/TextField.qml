import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import QuickLaunchEditor 1.0

TextField {
    id: root

    font.pixelSize: 14
    color: Colors.text
    padding: 6

    background: Rectangle {
        color: Colors.primary.textInput
        border.width: 1
        border.color: root.activeFocus ? Colors.markedBlue : Colors.primary.border
    }
}