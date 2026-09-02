import QtQuick 
import QtQuick.Controls

import QuickLaunchEditor 1.0

import "qrc:/components"

Item {
    id: root
    required property string shortcut
    property bool wrongText: false

    signal editingFinished(shortcut: string)

    onShortcutChanged: {
        shortcutText.text = root.shortcut;
    }

    implicitHeight: column.implicitHeight


    ShortcutEditor { 
        id: editor 
        onEditingFinished: {
            root.evaluateShorcut(editor.sequence.toString());
        }
    }

    Column {
        id: column
        anchors.fill: parent
        spacing: 2

        Rectangle {
            id: textBox
            anchors.left: parent.left
            anchors.right: parent.right
            height: 30
            color: Colors.primary.textInput
            border.color: {
                if(root.wrongText) {
                    return Colors.markedRed;
                } else if(editor.capturing) {
                    return Colors.markedBlue;
                } else {
                    return Colors.primary.border;
                }
            }
            
            Text {
                id: shortcutText
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.leftMargin: 6
                text: root.shortcut
                elide: Text.ElideRight
            }
            
            MouseArea { 
                anchors.fill: parent 
                onClicked: { 
                    editor.capturing = true
                    textBox.forceActiveFocus() 
                } 
            }

            onActiveFocusChanged: {
                if (!activeFocus) {
                    editor.capturing = false;
                    root.wrongText = false;
                    shortcutText.text = root.shortcut;
                }
            }
            
            Keys.onPressed: function(event) { 
                if (editor.capturing) {
                    editor.keyPressed( event.key, event.modifiers ) 
                    event.accepted = true 
                }
            } 
        }

        Text {
            id: errorText
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.leftMargin: 6
            font.pixelSize: 12
            color: Colors.markedRed
            text: root.wrongText ? "Shortcut already exists" : " "
        }

    }

    function shortcutExists(shortcut) {
        const profiles = ProfileManager.profiles;
        const currentProfileIndex = ProfileManager.currentProfileIndex;
        for (var i = 0; i < profiles.length; i++) {
            if (i != currentProfileIndex && profiles[i].shortcut === shortcut) {
                return true;
            }
        }
        return false;
    }

    function evaluateShorcut(shortcut) {
        if(root.shortcutExists(shortcut)) {
            root.wrongText = true;
            shortcutText.text = shortcut;
        } else {
            if(root.shortcut != shortcut) {
                root.editingFinished(shortcut);
            }
            root.wrongText = false;
        }
    }
}
