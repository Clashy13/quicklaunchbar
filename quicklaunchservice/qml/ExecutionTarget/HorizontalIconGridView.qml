import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import QuickLaunchService 1.0

FlowView {
    id: root

    width: scrollColumn.width
    height: scrollColumn.height

    readonly property int columns: Math.floor(root.availableWidth / Constants.executionTargetIconItemWidth)
    readonly property int rows: Math.ceil(executionTargets.length / columns)
    property int currentRowIndex

    onKeyPressed: (event) => {
        switch(event.key) {
            case Qt.Key_Left: 
                root.selectPreviousItem();
                currentRowIndex = Math.floor(root.currentItemIndex / root.columns);
                scrollColumn.moveTo(root.currentRowIndex);
                break;
            case Qt.Key_Right:
                root.selectNextItem();
                currentRowIndex = Math.floor(root.currentItemIndex / root.columns);
                scrollColumn.moveTo(root.currentRowIndex);
                break;
            case Qt.Key_Up:
                currentRowIndex = root.selectPreviousFlowItem(root.columns);
                scrollColumn.moveTo(root.currentRowIndex);
                break;
            case Qt.Key_Down:
                currentRowIndex = root.selectNextFlowItem(root.columns);
                scrollColumn.moveTo(root.currentRowIndex);
                break;
        }
    }

    MovableScrollColumn {
        id: scrollColumn
        maxWidth: root.availableWidth
        maxHeight: root.availableHeight
        model: root.rows
        delegate: Row {
            id: row
            required property int index

            Repeater {
                model: {
                    const start = row.index * root.columns;
                    if (start >= executionTargets.length) return 0;
                    return Math.min(root.columns, executionTargets.length - start);
                }

                delegate: IconFlowElement {
                    id: executionTargetItem
                    required property int index
                    readonly property int targetIndex: row.index * root.columns + executionTargetItem.index
                    executionTarget: root.executionTargets[executionTargetItem.targetIndex]
                    isSelected: root.currentItemIndex == executionTargetItem.targetIndex
                    onLaunched: root.launchedExecutionTargetByIndex(executionTargetItem.targetIndex)
                    onSelected: {
                        root.currentItemIndex = executionTargetItem.targetIndex;
                        root.currentRowIndex = row.index;
                    }
                    supressMouseHover: scrollColumn.scrollAnimRunning
                }
            }
        }
    }
}
