import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import QuickLaunchService 1.0

FlowView {
    id: root

    width: scrollRow.width
    height: scrollRow.height

    readonly property int rows: Math.floor(root.availableHeight / Constants.executionTargetIconItemHeight)
    readonly property int columns: Math.ceil(executionTargets.length / rows)
    property int currentColumnIndex

    onKeyPressed: (event) => {
        switch(event.key) {
            case Qt.Key_Up: 
                root.selectPreviousItem();
                currentColumnIndex = Math.floor(root.currentItemIndex / root.rows);
                scrollRow.moveTo(root.currentColumnIndex);
                break;
            case Qt.Key_Down:
                root.selectNextItem();
                currentColumnIndex = Math.floor(root.currentItemIndex / root.rows);
                scrollRow.moveTo(root.currentColumnIndex);
                break;
            case Qt.Key_Left:
                currentColumnIndex = root.selectPreviousFlowItem(root.rows);
                scrollRow.moveTo(root.currentColumnIndex);
                break;
            case Qt.Key_Right:
                currentColumnIndex = root.selectNextFlowItem(root.rows);
                scrollRow.moveTo(root.currentColumnIndex);
                break;
        }
    }

    MovableScrollRow {
        id: scrollRow
        maxWidth: root.availableWidth
        maxHeight: root.availableHeight
        model: root.columns
        delegate: Column {
            id: column
            required property int index

            Repeater {
                model: {
                    const start = column.index * root.rows;
                    if (start >= executionTargets.length) return 0;
                    return Math.min(root.rows, executionTargets.length - start);
                }

                delegate: IconFlowElement {
                    id: executionTargetItem
                    required property int index
                    readonly property int targetIndex: column.index * root.rows + executionTargetItem.index
                    executionTarget: root.executionTargets[executionTargetItem.targetIndex]
                    isSelected: root.currentItemIndex == executionTargetItem.targetIndex
                    onLaunched: root.launchedExecutionTargetByIndex(executionTargetItem.targetIndex)
                    onSelected: {
                        root.currentItemIndex = executionTargetItem.targetIndex;
                        root.currentColumnIndex = column.index;
                    }
                    supressMouseHover: scrollRow.scrollAnimRunning
                }
            }
        }
    }
}
