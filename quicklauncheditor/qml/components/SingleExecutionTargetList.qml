import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import QuickLaunchEditor 1.0

import "qrc:/components"
import "qrc:/executiontargets"

ExecutionTargetListBase {
    id: root
    delegate: SingleExecutionTargetBox {
        required property int index
        required property var item
        width: parent.width
        executionTarget: item
        onRemoved: {
            root.showDeleteWindow(index)
        }
    }
}