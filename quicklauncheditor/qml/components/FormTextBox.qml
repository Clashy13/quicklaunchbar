import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import QuickLaunchEditor 1.0

import "qrc:/components"

TextField {
    id: root

    property bool wrongText: false
    property string errorText
    property color borderColor
    property bool errorVisible: false

    onErrorVisibleChanged: {
        if(!errorVisible) {
            root.errorText = "";
            root.wrongText = false;
        }
    }

    background: Rectangle {
        color: Colors.primary.textInput
        border.width: 1
        border.color: root.borderColor
    }

    Text {
        visible: root.errorVisible
        anchors.top: parent.bottom
        anchors.left: parent.left
        anchors.topMargin: 2
        anchors.leftMargin: 6
        font.pixelSize: 12
        color: Colors.markedRed
        text: errorText
    }
}
