import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import QuickLaunchEditor 1.0

import "qrc:/components"

Item {
    id: root

    Item {
        id: content
        anchors.fill: parent

        Rectangle {
            anchors.fill: parent
            color: "transparent"
            border.width: 2
            border.color: Colors.primary.border

            ScrollList {
                id: scrollview
                anchors.fill: parent
                anchors.margins: 2
                model: ProfileManager.profiles
                delegate: Button {
                    id: button
                    required property int index
                    required property var item
                    width: scrollview.width
                    checkable: true

                    contentItem: Text {
                        text: item.name
                        font.pixelSize: 14
                        anchors.left: parent.left
                        anchors.leftMargin: 6
                        color: Colors.text
                        elide: Text.ElideRight
                    }

                    onPressed: {
                        ProfileManager.currentProfileIndex = index;
                        ProfileManager.currentProfileIndexChanged();
                    }

                    background: Rectangle {
                        color: index == ProfileManager.currentProfileIndex ? Colors.listItemSelected : button.hovered ? Colors.listItemHovered : "transparent"
                        anchors.left: parent.left
                        anchors.right: parent.right
                    }
                }
            }    
        }
    }
}
