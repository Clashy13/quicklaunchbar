import QtQuick
import QtQuick.Controls

import QuickLaunchService 1.0

FlowView {
    id: root

    width: scrollColumn.width
    height: scrollColumn.height

    onKeyPressed: (event) => {
        switch(event.key) {
            case Qt.Key_Up: 
                root.selectPreviousItem();
                scrollColumn.moveTo(root.currentItemIndex);
                break;
            case Qt.Key_Down:
                root.selectNextItem();
                scrollColumn.moveTo(root.currentItemIndex);
                break;
        }
    }

    MovableScrollColumn {
        id: scrollColumn
        maxWidth: root.availableWidth
        maxHeight: root.availableHeight
        model: root.executionTargets.length
        delegate: IconFlowElement {
            required property int index
            executionTarget: root.executionTargets[index]
            isSelected: root.currentItemIndex == index
            onLaunched: root.launchedExecutionTargetByIndex(index)
            onSelected: root.currentItemIndex = index
            supressMouseHover: scrollColumn.scrollAnimRunning
        }
    }
}
