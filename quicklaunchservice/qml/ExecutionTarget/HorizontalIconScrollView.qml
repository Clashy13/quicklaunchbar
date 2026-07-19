import QtQuick
import QtQuick.Controls

import QuickLaunchService 1.0

FlowView {
    id: root

    width: scrollRow.width
    height: scrollRow.height

    onKeyPressed: (event) => {
        switch(event.key) {
            case Qt.Key_Left: 
                root.selectPreviousItem();
                scrollRow.moveTo(root.currentItemIndex);
                break;
            case Qt.Key_Right:
                root.selectNextItem();
                scrollRow.moveTo(root.currentItemIndex);
                break;
        }
    }

    MovableScrollRow {
        id: scrollRow
        maxWidth: root.availableWidth
        maxHeight: root.availableHeight
        model: root.executionTargets.length
        delegate: IconFlowElement {
            required property int index
            executionTarget: root.executionTargets[index]
            isSelected: root.currentItemIndex == index
            onLaunched: root.launchedExecutionTargetByIndex(index)
            onSelected: root.currentItemIndex = index
            supressMouseHover: scrollRow.scrollAnimRunning
        }
    }
}
