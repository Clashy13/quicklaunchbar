import QtQuick

Item {
    id: root

    required property var executionTargets
    property int currentItemIndex: 0
    required property int availableWidth
    required property int availableHeight

    signal launchedExecutionTargetByIndex(index: int)
    signal keyPressed(event: KeyEvent)
    signal selectedItem()

    onKeyPressed: (event) => {
        if(event.key === Qt.Key_Return) {
            root.launchCurrentExecutionTarget();
        }
    }

    function selectNextItem() {
        if(root.currentItemIndex + 1 < root.executionTargets.length) {
            root.currentItemIndex = root.currentItemIndex + 1;
            root.selectedItem();
        }
    }

    function selectPreviousItem() {
        if(root.currentItemIndex > 0) {
            root.currentItemIndex = root.currentItemIndex - 1;
            root.selectedItem();
        }
    }

    function selectPreviousFlowItem(flowLength) {
        const currentFlowIndex = Math.floor(root.currentItemIndex / flowLength);
        const prevFlowIndex = currentFlowIndex - 1;
        if(prevFlowIndex < 0) {
            return currentFlowIndex;
        }
        root.currentItemIndex = root.currentItemIndex - flowLength;
        root.selectedItem();
        return prevFlowIndex;
    }

    function selectNextFlowItem(flowLength) {
        const currentFlowIndex = Math.floor(root.currentItemIndex / flowLength);
        const nextFlowIndex = currentFlowIndex + 1;
        if(nextFlowIndex >= root.executionTargets.length) {
            return currentFlowIndex;
        }
        root.currentItemIndex = Math.min(root.executionTargets.length-1,root.currentItemIndex + flowLength);
        root.selectedItem();
        return nextFlowIndex;
    }

    function launchCurrentExecutionTarget() {
        if(root.currentItemIndex >= 0 && root.currentItemIndex < root.executionTargets.length) {
            root.launchedExecutionTargetByIndex(root.currentItemIndex);
        }
    }
}
