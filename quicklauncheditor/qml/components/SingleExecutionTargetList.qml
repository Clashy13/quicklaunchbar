import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import QuickLaunchEditor 1.0

import "qrc:/components"
import "qrc:/executiontargets"

ExecutionTargetListBase {
    id: root
    allowGroup: false
    delegate: SingleExecutionTargetBox {
        required property int index
        required property var item
        dragParent: root.dragParent
        width: parent.width
        executionTarget: item
        onRemoved: {
            root.showDeleteWindow(index)
        }
    }
}