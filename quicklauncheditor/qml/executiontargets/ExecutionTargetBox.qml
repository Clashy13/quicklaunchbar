import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import QuickLaunchEditor 1.0

import "qrc:/components"

SingleExecutionTargetBox {
    id: root

    signal childItemAdded(top: int, bottom: int)

    sourceContentComponent: {
        switch(root.executionTarget.type) {
            case 0:
                return root.desktopApplicationContent();
            case 1:
                return root.executableFileContent();
            case 2:
                return root.commandContent();
            case 3:
                return root.openFileContent();
            case 4:
                return root.openUrlContent();
            case 5:
                return groupContent;
        }
    }

    Component {
        id: groupContent
        GroupContent {
            executionTarget: root.executionTarget
            onItemAdded: (top,bottom) => {
                const localY = mapToItem(root, 0, 0).y
                root.childItemAdded(localY+top,localY+bottom);
            }
        }
    }
}