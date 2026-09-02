import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Dialogs

import QuickLaunchEditor 1.0

import "qrc:/components"

RowLayout {
    id: root

    required property string iconFilePath

    TextField {
        id: iconFilePathEdit
        Layout.fillWidth: true
        text: root.iconFilePath

        onTextEdited: {
            root.iconFilePath = text;
        }
    }

    Button {
        Layout.preferredWidth: height
        Layout.fillHeight: true
        icon.source: Icons.folder
        icon.color: Colors.text
        onClicked: {
            imageDialog.open();
        }
    }

    FileDialog {
        id: imageDialog

        title: "Select an image"
        nameFilters: [
            "Image files (*.png *.jpg *.jpeg *.bmp *.gif *.webp *.tif *.tiff *.svg)"
        ]

        onAccepted: {
            root.iconFilePath = new URL(selectedFile).pathname;;
        }
    }
}
