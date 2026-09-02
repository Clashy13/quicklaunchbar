import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import QuickLaunchEditor 1.0

import "qrc:/components"

Item {
    id: root

    required property int checkedIndex

    signal checked(index: int)

    width: 160
    height: 90

    GridLayout {
        anchors.fill: parent
        columns: 3
        rows: 3
        rowSpacing: 0
        columnSpacing: 0

        Repeater {
            id: repeater
            model: [
                    {iconSource: Icons.topLeftPosition},
                    {iconSource: Icons.topPosition},
                    {iconSource: Icons.topRightPosition},
                    {iconSource: Icons.leftPosition},
                    {iconSource: Icons.centerPosition},
                    {iconSource: Icons.rightPosition},
                    {iconSource: Icons.bottomLeftPosition},
                    {iconSource: Icons.bottomPosition},
                    {iconSource: Icons.bottomRightPosition}
                ]
            delegate: Button {
                id: button
                required property int index
                required property url iconSource

                icon.source: iconSource
                
                Layout.fillHeight: true
                Layout.fillWidth: true

                selected: root.checkedIndex == index
                rectangle.topLeftRadius: index == 0 ? 4 : 0
                rectangle.topRightRadius: index == 2 ? 4 : 0
                rectangle.bottomLeftRadius: index == 6 ? 4 : 0
                rectangle.bottomRightRadius: index == 8 ? 4 : 0
                rectangle.border.width: 0

                onPressed: {
                    if(root.checkedIndex != index) {
                        root.checked(index);
                    }
                }
            }
        }
    }

    Rectangle {
        id: backgroundBorder
        anchors.fill: parent
        color: "transparent"
        border.width: 1
        border.color: Colors.primary.border
        radius: 4
    }

    Rectangle {
        id: selectedBorder
        color: "transparent"
        border.width: 1
        border.color: Colors.secondary.border
        width: parent.width / 3
        height: parent.height / 3
        x: (root.checkedIndex % 3) * width
        y: Math.floor(root.checkedIndex / 3) * height
        topLeftRadius: root.checkedIndex == 0 ? 4 : 0
        topRightRadius: root.checkedIndex == 2 ? 4 : 0
        bottomLeftRadius: root.checkedIndex == 6 ? 4 : 0
        bottomRightRadius: root.checkedIndex == 8 ? 4 : 0
    }
}
