import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Effects

import QuickLaunchEditor 1.0

import "qrc:/components"

ToolWindow {
    id: root

    property int selectedApplicationIndex: -1
    buttonModel: [
        {
            name: "Cancel"
        },
        {
            name: "Select",
            backgroundColorStyle: Button.Green,
            enabled: root.selectedApplicationIndex != -1
        }
    ]

    signal applicationSelected(application: var)

    onVisibleChanged: {
        if(visible) {
            nameFilterEdit.text = "";
            selectedApplicationIndex = -1;
            nameFilterEdit.forceActiveFocus();
        }
    }

    onButtonPressed: (index) => {
        if(index == 1) {
            root.applicationSelected(scrollview.model[root.selectedApplicationIndex]);
        }
    }
    
    width: 300
    height: 400
    minimumWidth: 200
    minimumHeight: 200

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 6
        spacing: 6

        TextField {
            id: nameFilterEdit
            Layout.fillWidth: true
            placeholderText: "Enter name"
            onTextChanged: {
                root.selectedApplicationIndex = -1;
            }
            topPadding: 6
            bottomPadding: 6
            leftPadding: searchIcon.width

            Button {
                id: searchIcon
                anchors.left: parent.left
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                width: height
                icon.source: Icons.search
                icon.color: Colors.text
                enabled: false
                background: Item {}
            }
        }

        Item {
            id: content
            Layout.fillWidth: true
            Layout.fillHeight: true        

            Rectangle {
                anchors.fill: parent
                color: "transparent"
                border.width: 2
                border.color: Colors.primary.border

                ScrollList {
                    id: scrollview
                    anchors.fill: parent
                    anchors.margins: 2
                    model: {
                        const nameFilter = nameFilterEdit.text.trim().toLowerCase();
                        if(nameFilter == "") {
                            return DesktopApplicationProvider.applications;
                        } else {
                            const normalizedFilter = root.normalized(nameFilter);
                            return DesktopApplicationProvider.applications.filter((application) => {
                                return application && root.normalized(application.name).includes(normalizedFilter);
                            } );
                        }
                    }
                    onModelChanged: {
                        scrollview.reload();
                        scrollview.moveTo(0,0);
                    }
                    delegate: Button {
                        id: button
                        required property int index
                        required property string name
                        required property url iconUrl
                        width: scrollview.width
                        height: 50
                        checkable: true

                        contentItem: RowLayout {
                            anchors.fill: parent
                            anchors.margins: 6
                            spacing: 12

                            Image {
                                source: button.iconUrl
                                Layout.preferredWidth: height
                                Layout.fillHeight: true
                            }

                            Text {
                                Layout.fillWidth: true
                                Layout.fillHeight: true
                                verticalAlignment: Text.AlignVCenter
                                text: button.name
                                elide: Text.ElideRight
                                font.pixelSize: 14
                            }
                        }

                        background: Rectangle {
                            anchors.fill: parent
                            color: index == root.selectedApplicationIndex ? Colors.listItemSelected : button.hovered ? Colors.listItemHovered : "transparent"
                        }

                        onPressed: {
                            selectedApplicationIndex = button.index
                        }
                    }
                }    
            }
        }
    }

    function normalized(string) {
        return string
            .toLowerCase()
            .trim()
            .normalize("NFD")
            .replace(/[\u0300-\u036f]/g, "");
    }
}
