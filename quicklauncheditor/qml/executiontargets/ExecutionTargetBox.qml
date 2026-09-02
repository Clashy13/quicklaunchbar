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
                return desktopApplicationContent;
            case 1:
                return executableFileContent;
            case 2:
                return commandContent;
            case 3:
                return openFileContent;
            case 4:
                return openUrlContent;
            case 5:
                return groupContent;
        }
    }

    Component {
        id: desktopApplicationContent
        DesktopApplicationContent {
            executionTarget: root.executionTarget
        }
    }

    Component {
        id: executableFileContent
        ExecutableFileContent {
            executionTarget: root.executionTarget
        }
    }

    Component {
        id: commandContent
        CommandContent {
            executionTarget: root.executionTarget
        }
    }

    Component {
        id: openFileContent
        OpenFileContent {
            executionTarget: root.executionTarget
        }
    }

    Component {
        id: openUrlContent
        OpenUrlContent {
            executionTarget: root.executionTarget
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