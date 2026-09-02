import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import QuickLaunchEditor 1.0

import "qrc:/components"

Item {
    id: root

    RowLayout {
        anchors.fill: parent
        spacing: 6

        FormTextBox {
            id: nameField
            placeholderText: "Profile Name"
            Layout.alignment: Qt.AlignVCenter
            Layout.fillWidth: true
            Layout.fillHeight: true
            padding: 6
            onAccepted: {
                root.evaluateName();
            }
            errorVisible: nameField.focus || addButton.focus
            borderColor: {
                if(nameField.wrongText && (nameField.focus || addButton.focus)) {
                    return Colors.markedRed;
                } else if(nameField.focus) {
                    return Colors.markedBlue;
                } else {
                    return Colors.primary.border;
                }
            }
        }

        Button {
            id: addButton
            text: "Add"
            Layout.fillHeight: true
            leftPadding: 10
            rightPadding: 10
            onClicked: {
                nameField.accepted();
            }
        }
    }

    function nameExists(name) {
        const profiles = ProfileManager.profiles;
        for (var i = 0; i < profiles.rowCount(); i++) {
            if (profiles.itemAt(i).name === name) {
                return true;
            }
        }
        return false;
    }

    function evaluateName() {
        const name = nameField.text.trim();
                
        if(name.length > 0) {
            if(root.nameExists(name)) {
                nameField.wrongText = true;
                nameField.errorText = "Name already exists";
            } else {
                ProfileManager.addProfile(name);
                nameField.clear();
                nameField.wrongText = false;
                nameField.errorText = "";
            }
        } else {
            nameField.wrongText = true;
            nameField.errorText = "Name cannot be empty";
        }
    }
}

