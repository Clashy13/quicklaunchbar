import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import QuickLaunchEditor 1.0

import "qrc:/components"

Item {
    id: root

    property string name: {
        if(ProfileManager.currentProfile) {
            return ProfileManager.currentProfile.name;
        } else {
            return "";
        }
    }

    onNameChanged: {
        nameField.text = root.name;
    }

    RowLayout {
        id: content
        anchors.fill: parent
        spacing: 6

        Row {
            Layout.fillWidth: true
            spacing: 6

            StackLayout {
                id: nameTitle
                property bool editing: false
                currentIndex: nameTitle.editing ? 1 : 0
                property int minimumWidth: 80
                property int preferredWidth: Math.max(implicitWidth, 100)
                property int maximumWidth: parent.width - parent.spacing - editButton.width
                width: Math.min(maximumWidth,Math.max(minimumWidth,preferredWidth))

                Item {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    
                    Text {
                        id: title
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.left: parent.left
                        anchors.right: parent.right
                        anchors.leftMargin: 6
                        text: root.name
                        elide: Text.ElideRight
                    }
                }

                FormTextBox {
                    id: nameField
                    Layout.fillWidth: true
                    Layout.fillHeight: true

                    text: root.name
                    width: 140
                    padding: 6
                    onAccepted: {
                        root.evaluateName();
                    }
                    errorVisible: nameField.focus || editButton.focus
                    borderColor: {
                        if(nameField.wrongText && (nameField.focus || editButton.focus)) {
                            return Colors.markedRed;
                        } else if(nameField.focus) {
                            return Colors.markedBlue;
                        } else {
                            return Colors.primary.border;
                        }
                    }

                    onActiveFocusChanged: {
                        if(!activeFocus && !editButton.focus) {
                            text = root.name;
                            nameTitle.editing = false;
                            errorVisible = false;
                        }
                    }
                }
            }


            Button {
                id: editButton
                icon.source: Icons.edit
                Layout.fillHeight: true
                Layout.preferredWidth: height
                onClicked: {
                    if(nameTitle.editing) {
                        nameField.accepted();
                    } else {
                        nameTitle.editing = true
                        nameField.errorVisible = true;
                        nameField.forceActiveFocus();
                        nameField.selectAll();
                    }
                }
            }
        }

        Item {
            Layout.fillWidth: true
        }

        Button {
            icon.source: Icons.trashCan
            icon.color: Colors.text
            Layout.fillHeight: true
            Layout.preferredWidth: height
            onClicked: {
                deleteProfileWindow.showCentered(root.Window.window);
            }
        }
    }

    ToolWindow {
        id: deleteProfileWindow
        minimumWidth: 200
        minimumHeight: 100
        maximumWidth: 200
        maximumHeight: 100
        onButtonPressed: (index) =>  {
            if(index == 1) {
                ProfileManager.removeCurrentProfile();
            }
        }

        buttonModel: [ { name: "Cancel" }, { name: "Delete" } ]

        Text {
            anchors.fill: parent
            anchors.margins: 6
            text: "Do you really want to delete this profile?"
            wrapMode: Text.WordWrap
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }
    }

    function nameExists(name) {
        const profiles = ProfileManager.profiles;
        const currentProfileIndex = ProfileManager.currentProfileIndex;
        for (var i = 0; i < profiles.rowCount(); i++) {
            if (i != currentProfileIndex && profiles.itemAt(i).name === name) {
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
                if(root.name != name) {
                    if(ProfileManager.currentProfile) {
                        ProfileManager.currentProfile.name = name;
                    }
                }
                nameField.wrongText = false;
                nameField.errorText = "";
                nameTitle.editing = false;
                nameField.errorVisible = false;
            }
        } else {
            nameField.wrongText = true;
            nameField.errorText = "Name cannot be empty";
        }
    }
}
