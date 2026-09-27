import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import QuickLaunchEditor 1.0

import "qrc:/components"
import "qrc:/executiontargets"

Item {
    id: root

    Item {
        id: content
        anchors.fill: parent

        ScrollListBase {
            id: scrollview
            anchors.fill: parent
            anchors.margins: 0
            anchors.rightMargin: scrollview.contentHeight > scrollview.height ? 1 : 0
            repeater: executionTargetList.repeater
            spacing: -2

            ExecutionTargetList {
                id: executionTargetList
                width: scrollview.contentHeight > scrollview.height ? scrollview.width - 10 : scrollview.width
                spacing: -2
                executionTargets: {
                    if(ProfileManager.currentProfile) {
                        return ProfileManager.currentProfile.executionTargets
                    } else {
                        return []
                    }
                }
                onExecutionTargetsChanged: {
                    scrollview.reload();
                    scrollview.moveTo(0,0);
                }
                onChildItemAdded: (index,top,bottom) => {
                    scrollview.moveToSubItem(index,top,bottom);
                }
            }
        }   

        Rectangle {
            anchors.fill: parent
            color: "transparent"
            border.width: 1
            border.color: Colors.secondary.border  
        }
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
                    ProfileManager.currentProfile.executionTargets.removeItem(deleteWindow.index);
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
