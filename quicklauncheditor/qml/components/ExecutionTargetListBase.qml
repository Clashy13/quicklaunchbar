import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import QuickLaunchEditor 1.0

import "qrc:/components"
import "qrc:/executiontargets"

Item {
    id: root

    required property var dragParent
    required property var executionTargets
    property Component delegate
    property alias repeater: repeater
    property bool allowGroup: true
    property bool insideGroup: false
    implicitHeight: emptyExtended ? extendedItemIndex == -1 ? 20 : extendedItemHeight : column.height
    property int spacing: 0
    signal itemAdded(top: int, bottom: int)

    property int extendedItemIndex: -1
    property int extendedItemHeight: 0
    property bool emptyExtended: (insideGroup && repeater.count == 0) || repeater.count == 1 && repeater.itemAt(0).collapsed
    property int extendedEndHeight: 0

    DropArea {
        anchors.fill: parent
    }

    Rectangle {
        width: parent.width
        height: repeater.count == 0 ? itemColumn.height + root.extendedItemHeight : itemColumn.height
        visible: repeater.count > 1 || (repeater.count == 0 && emptyExtended && extendedItemIndex >= 0) || (repeater.count == 1 && extendedItemIndex != -1)
        color: Colors.listItemSelected
        border.width: 1
        border.color: Colors.secondary.border
    }

    Column {
        id: column
        width: parent.width
        spacing: 0

        Column {
            id: itemColumn
            width: parent.width
            spacing: root.spacing
            Repeater {
                id: repeater
                model: root.executionTargets
                onItemAdded: (index, item) => {
                    let top = 0;
                    for(let i = 0; i < index; i++) {
                        top += repeater.itemAt(i).height + root.spacing;
                    }
                    root.itemAdded(top,top + item.height);
                }
                delegate: Column {
                    id: executionTargetItem
                    required property int index
                    required property var item
                    spacing: 0

                    width: parent.width
                    height: children.reduce((total, child) => total + child.height, 0);

                    property bool collapsed: {
                        if(itemContent.executionTarget.Drag.active) {
                            if(itemContent.executionTarget.dragItemIndex != index) {
                                return true;
                            } else if(itemContent.executionTarget.dragTargetList != root) {
                                return true;
                            }
                        }
                        return false;
                    }
                    property int extendedHeight: !itemContent.executionTarget.Drag.active && root.extendedItemIndex == index && repeater.count > 0 ? root.extendedItemHeight + root.spacing : 0
                    property bool anchorBottom: false
                    property bool isGroup: itemContent.executionTarget != null && itemContent.executionTarget.isGroup

                    states: [
                        State {
                            when: itemContent.executionTarget != null && itemContent.executionTarget.Drag.active
                            ParentChange {
                                target: itemContent.executionTarget
                                parent: root.dragParent
                            }
                            PropertyChanges {
                                target: itemContent.executionTarget
                                collapsed: true
                            }
                        }
                    ]

                    Item {
                        height: anchorBottom ? extendedHeight : 0
                        width: 1
                    }

                    Item {
                        id: itemContent
                        width: parent.width
                        height: executionTarget == null || executionTargetItem.collapsed ? 0 : executionTarget.height

                        property Item executionTarget
                        Component.onCompleted: {
                            executionTarget = root.delegate.createObject(itemContent, {
                                index: index,
                                item: item,
                                dragTargetList: root
                            });

                            executionTarget.width = Qt.binding(() => {return itemContent.width})
                            executionTargetItem.indexChanged.connect(() => {executionTarget.index = executionTargetItem.index});
                            executionTarget.dragStarted.connect(() => {
                                root.dragParent.extendedEndHeight = executionTarget.height - executionTarget.topbarHeight;
                                root.extendedItemIndex = index;
                                root.extendedItemHeight = Qt.binding(() => {return executionTarget.height});
                                executionTarget.dragItemIndex = index;
                                executionTarget.trueIndex = index;
                            })
                            executionTarget.dragFinished.connect(() => {
                                root.dragParent.extendedEndHeight = 0;
                                if(executionTarget.dragTargetList == root) {
                                    root.dropItem(executionTarget, index);
                                } else {
                                    root.moveItemToOtherList(executionTarget, index);
                                }
                            })
                        }

                        ColumnLayout {
                            anchors.fill: parent

                            DropArea {
                                Layout.fillWidth: true
                                Layout.fillHeight: true
                                onEntered: (drag) => {
                                    if(drag.source != itemContent.executionTarget) {
                                        root.handleItemDrag(index,drag,true);
                                    }
                                }
                            }
                            DropArea {
                                Layout.fillWidth: true
                                Layout.fillHeight: true
                                enabled: !itemContent.executionTarget.isGroup
                                onEntered: (drag) => {
                                    if(drag.source != itemContent.executionTarget) {
                                        root.handleItemDrag(index,drag,false);
                                    }
                                }
                            }
                        }
                    }

                    Item {
                        height: anchorBottom ? 0 : extendedHeight
                        width: 1
                    }
                }
            }
        }

        Item {
            id: extendedEnd
            visible: !root.insideGroup
            width: parent.width
            height: root.extendedEndHeight

            DropArea {
                anchors.fill: parent
                onEntered: (drag) => {
                    const index = repeater.count > 1 && drag.source.trueIndex == repeater.count-1 ? repeater.count-2 : repeater.count-1
                    root.handleItemDrag(index,drag,false);
                }
            }
        }
    }


    function insertExecutionTargetFrom(dragItemIndex, list, index) {
        root.extendedItemIndex = -1;
        const newIndex = Math.ceil(dragItemIndex);
        root.executionTargets.insertItem(newIndex,list.itemAt(index));
    }

    function dropItem(executionTarget,index) {
        root.extendedItemIndex = -1;
        const newIndex = executionTarget.dragItemIndex < index ? Math.ceil(executionTarget.dragItemIndex) : Math.floor(executionTarget.dragItemIndex)
        root.executionTargets.moveItem(index,newIndex);
    }

    function moveItemToOtherList(executionTarget,index) {
        executionTarget.dragTargetList.insertExecutionTargetFrom(executionTarget.dragItemIndex, root.executionTargets,index);
        root.executionTargets.removeItem(index);
    }

    function handleItemDrag(index, drag, dropInTopHalf) {
        repeater.itemAt(index).anchorBottom = dropInTopHalf;
        if(drag.source.dragTargetList == root) {
            if(drag.source.dragItemIndex != index) {
                root.extendedItemIndex = index;
                root.extendedItemHeight = drag.source.height;
                drag.source.dragItemIndex = dropInTopHalf ? index - 0.5 : index + 0.5;
            }
        } else if(drag.source.isGroup && !root.allowGroup) {
            return;
        } else {
            drag.source.dragTargetList.extendedItemIndex = -1;
            drag.source.dragTargetList = root;

            root.extendedItemIndex = index;
            root.extendedItemHeight = drag.source.height;
            drag.source.dragItemIndex = dropInTopHalf ? index - 0.5 : index + 0.5;
        }
    }

    function showDeleteWindow(index) {
        deleteWindow.index = index;
        deleteWindow.showCentered(root.Window.window);
    }

    ToolWindow {
        id: deleteWindow
        minimumWidth: 200
        minimumHeight: 100
        maximumWidth: 200
        maximumHeight: 100

        property int index: -1
        onButtonPressed: (index) =>  {
            if(index == 1 && deleteWindow.index != -1) {
                if(ProfileManager.currentProfile) {
                    root.executionTargets.removeItem(deleteWindow.index);
                }
                deleteWindow.index = -1;
            }
        }

        buttonModel: [ { name: "Cancel" }, { name: "Delete" } ]

        Text {
            anchors.fill: parent
            anchors.margins: 6
            text: "Do you really want to delete this execution target?"
            wrapMode: Text.WordWrap
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }
    }
}
