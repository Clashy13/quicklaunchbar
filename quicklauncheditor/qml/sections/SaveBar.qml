import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import QuickLaunchEditor 1.0

import "qrc:/components"

RowLayout {
    id: root
    spacing: 6

    Button {
        id: discardButton
        Layout.fillHeight: true
        text: "Discard Changes"
        enabled: ProfileManager.edited
        style: Colors.Secondary
        onClicked: {
            discardWindow.showCentered(root.Window.window);
        }

        ToolWindow {
            id: discardWindow
            minimumWidth: 200
            minimumHeight: 100
            maximumWidth: 200
            maximumHeight: 100
            onButtonPressed: (index) =>  {
                if(index == 1) {
                    ProfileManager.discardEdited();
                }
            }

            buttonModel: [ { name: "Cancel" }, { name: "Discard" } ]

            Text {
                anchors.fill: parent
                anchors.margins: 6
                text: "Do you really want to discard all changes?"
                wrapMode: Text.WordWrap
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
        }
    }

    Button {
        Layout.fillHeight: true
        Layout.preferredWidth: 60
        text: "Save"
        enabled: ProfileManager.edited
        backgroundColorStyle: Button.Green
        style: Colors.Secondary
        onClicked: {
            ProfileManager.save();
        }
    }
}