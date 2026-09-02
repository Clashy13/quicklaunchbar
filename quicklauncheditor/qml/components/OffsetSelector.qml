import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import QuickLaunchEditor 1.0

import "qrc:/components"

RowLayout {
    id: root
    spacing: -1

    required property int value
    signal valueEdited(value: int)

    onValueChanged: {
        input.text = root.value
    }

    Button {
        id: minus100
        text: "-100"
        Layout.preferredHeight: 30
        rectangle.radius: 0
        rectangle.topLeftRadius: 4
        rectangle.bottomLeftRadius: 4
        onClicked: {
            root.valueEdited(Math.max(0,root.value-100));
        }
    }

    Button {
        id: minus10
        text: "-10"
        Layout.preferredHeight: 30
        rectangle.radius: 0
        onClicked: {
            root.valueEdited(Math.max(0,root.value-10));
        }
    }

    TextField {
        id: input
        Layout.preferredWidth: 50
        Layout.preferredHeight: 30
        horizontalAlignment: TextInput.AlignHCenter
        verticalAlignment: TextInput.AlignVCenter
        text: root.value
        validator: IntValidator {
            bottom: 0
            top: 99999
        }
        inputMethodHints: Qt.ImhDigitsOnly

        onTextEdited: {
            if(text == "") {
                root.valueEdited(0);
            } else {
                root.valueEdited(text);
            }
        }

        onActiveFocusChanged: {
            if(!activeFocus) {
                text = root.value;
            }
        }
    }

    Button {
        id: plus10
        text: "+10"
        Layout.preferredHeight: 30
        rectangle.radius: 0
        onClicked: {
            root.valueEdited(root.value + 10);
        }
    }

    Button {
        id: plus100
        text: "+100"
        Layout.preferredHeight: 30
        rectangle.radius: 0
        rectangle.topRightRadius: 4
        rectangle.bottomRightRadius: 4
        onClicked: {
            root.valueEdited(root.value + 100);
        }
    }
}