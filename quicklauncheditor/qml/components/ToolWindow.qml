import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import QuickLaunchEditor 1.0

import "qrc:/components"

ApplicationWindow {
    id: root
    
    flags: Qt.Tool | Qt.Window

    visible: false

    required property var buttonModel

    signal buttonPressed(index: int)

    color: Colors.primary.background

    function showCentered(parentWindow) {
        root.x = parentWindow.x +
                        (parentWindow.width - root.width) / 2

        root.y = parentWindow.y +
                        (parentWindow.height - root.height) / 2

        root.show();
        root.requestActivate();
    }

    property real buttonWidth: {
        var w = 0
        for (var i = 0; i < repeater.count; ++i) {
            var item = repeater.itemAt(i)
            if (item)
                w = Math.max(w, item.implicitWidth)
        }
        return w
    }

    footer: Item {
        width: parent.width
        height: 42
        RowLayout {
            anchors.fill: parent
            anchors.margins: 6
            spacing: 6

            Repeater {
                id: repeater
                model: root.buttonModel
                delegate: Button {
                    required property int index
                    required property var modelData
                    Layout.fillWidth: true
                    Layout.preferredWidth: root.buttonWidth
                    Layout.fillHeight: true
                    text: modelData.name
                    Component.onCompleted: {
                        if(modelData.enabled != null) {
                            enabled = Qt.binding(() => {
                                return modelData.enabled;
                            });
                        }
                        if(modelData.backgroundColorStyle != null) {
                            backgroundColorStyle = Qt.binding(() => {
                                return modelData.backgroundColorStyle;
                            });
                        }
                    }
                    onClicked: {
                        root.buttonPressed(index);
                        root.close();
                    }
                }
            }
        }
    }
    
}

// import QtQuick
// import QtQuick.Controls
// import QtQuick.Layouts

// import QuickLaunchEditor 1.0

// import "qrc:/components"

// ApplicationWindow {
//     id: root

//     flags: Qt.Tool | Qt.Window

//     visible: false

//     required property string acceptButtonText
//     property bool acceptButtonEnabled: true

//     signal canceled()
//     signal accepted()

//     background: Rectangle {
//         color: Colors.background
//     }

//     function showCentered(parentWindow) {
//         root.x = parentWindow.x +
//                         (parentWindow.width - root.width) / 2

//         root.y = parentWindow.y +
//                         (parentWindow.height - root.height) / 2

//         root.show();
//         root.requestActivate();
//     }

//     footer: Item {
//         width: parent.width
//         height: 42
//         RowLayout {
//             anchors.fill: parent
//             anchors.margins: 6
//             spacing: 6

//             Button {
//                 Layout.fillWidth: true
//                 Layout.fillHeight: true
//                 text: "Cancel"
//                 onClicked: {
//                     root.canceled();
//                     root.close();
//                 }
//             }

//             Button {
//                 Layout.fillWidth: true
//                 Layout.fillHeight: true
//                 text: root.acceptButtonText
//                 color: Colors.markedGreen
//                 enabled: root.acceptButtonEnabled
//                 onClicked: {
//                     root.accepted();
//                     root.close();
//                 }
//             }
//         }
//     }
    
// }