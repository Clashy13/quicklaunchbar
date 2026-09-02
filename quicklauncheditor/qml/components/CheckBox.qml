import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Effects

import QuickLaunchEditor 1.0

CheckBox {
    id: checkbox
    width: 36
    height: 18
    indicator: Item {
        width: 36
        height: 18
        Image {
            id: sourceImage
            source: checkbox.checked
                ? Icons.checkBoxChecked
                : Icons.checkBoxUnchecked
            visible: false
        }

        MultiEffect {
            id: multiEffect
            source: sourceImage
            width: 36
            height: 18
            brightness: 1
            colorization: 1
            colorizationColor: checkbox.checked ? Colors.checkboxChecked : Colors.checkboxUnchecked
        }
    }
}