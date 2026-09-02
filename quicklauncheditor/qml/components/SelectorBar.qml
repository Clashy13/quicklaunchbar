import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import QuickLaunchEditor 1.0

import "qrc:/components"

Row {
    id: root

    required property var model
    spacing: -1

    required property int checkedIndex

    signal checked(index: int)

    Repeater {
        model: root.model
        delegate: Button {
            id: button
            required property int index
            required property string name
            required property url iconSource
            text: name

            icon.source: iconSource
            selected: root.checkedIndex == index

            rectangle.topLeftRadius: index == 0 ? 4 : 0
            rectangle.bottomLeftRadius: index == 0 ? 4 : 0
            rectangle.topRightRadius: index == root.model.length - 1 ? 4 : 0
            rectangle.bottomRightRadius: index == root.model.length - 1 ? 4 : 0

            topPadding: 6
            bottomPadding: 6
            rightPadding: 10
            leftPadding: 10
            onPressed: {
                if(root.checkedIndex != index) {
                    root.checked(index);
                }
            }
        }
    }
}