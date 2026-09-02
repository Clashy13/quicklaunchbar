import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import QuickLaunchEditor 1.0

import "qrc:/components"

Button {
    id: root

    property alias rectangle: rec

    enum Style {
        Default,
        Green
    }
    
    palette.buttonText: {
        if(root.selected || root.pressed) {
            return Qt.darker(Colors.text, 1.4);
        } else if(!root.enabled) {
            return Colors.textDisabled;
        } else if(root.hovered) {
            return Qt.lighter(Colors.text, 1.4);
        } else {
            return Colors.text;
        }
    }
    property bool selected: false
    enabled: !selected
    property int style: Colors.Primary
    property int backgroundColorStyle: Button.Default
    icon.color: palette.buttonText
    font.pixelSize: 14
    padding: 6
    background: Rectangle {
        id: rec
        color: {
            if(root.selected || root.pressed) {
                if(root.backgroundColorStyle == Button.Green) {
                    return Qt.darker(Colors.markedGreen, 1.4);
                } else {
                    return root.style == Colors.Secondary ? Colors.secondary.buttonSelected : Colors.primary.buttonSelected;
                }
            } else if(!root.enabled) {
                return root.style == Colors.Secondary ? Colors.secondary.button : Colors.primary.button;
            } else if(root.hovered) {
                if(root.backgroundColorStyle == Button.Green) {
                    return Qt.lighter(Colors.markedGreen, 1.4);
                } else {
                    return root.style == Colors.Secondary ? Colors.secondary.buttonHovered : Colors.primary.buttonHovered;
                }
            } else {
                if(root.backgroundColorStyle == Button.Green) {
                    return Colors.markedGreen;
                } else {
                    return root.style == Colors.Secondary ? Colors.secondary.button : Colors.primary.button;
                }
            }
        }
        radius: 4
        border.width: 1
        border.color: {
            if(root.selected || root.pressed) {
                return Colors.secondary.border;
            } else {
                return Colors.primary.border;
            }
        }

    }
}