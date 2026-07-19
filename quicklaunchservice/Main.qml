import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import QuickLaunchService 1.0

Window {
    id: root

    readonly property int contentMargin: 16

    visible: false
    color: "transparent"

    flags: Qt.BypassWindowManagerHint | Qt.WindowStaysOnTopHint

    Rectangle {
        id: content
        radius: 10
        border.width: 2
        border.color: Colors.secondary
        color: Colors.primary

        Column {
            id: column
            anchors.centerIn: parent
            spacing: 8

            Label {
                id: profileTitle
                anchors.horizontalCenter: parent.horizontalCenter
                font.pixelSize: 20
            }

            Loader {
                id: profileViewLoader
                onLoaded: {
                    profileViewLoader.item.launchedExecutionTargetByIndex.connect(backend.launchExecutionTargetByIndex);
                    root.transformWindow();
                    root.positionContent();
                    backend.maskWindow(root,Qt.rect(content.x,content.y,content.width,content.height));
                    root.showWindow();
                    content.forceActiveFocus();
                }
            }
        }
    }

    Backend {
        id: backend

        onShowProfile: (profile) => {
            profileTitle.text = profile.name;
            const source = backend.executionTargetViewSource(profile.view);

            const availableContentWidth = backend.availableContentWidth();
            const availableContentHeight = backend.availableContentHeight();

            profileViewLoader.setSource(source, {
                executionTargets: profile.executionTargets,
                availableWidth: availableContentWidth - root.contentMargin*2,
                availableHeight: (availableContentHeight - profileTitle.height - column.spacing - root.contentMargin*2)
            });
            content.Keys.pressed.connect(profileViewLoader.item.keyPressed);
        }

        onHideWindow: {
            root.hide();
        }
    }

    onActiveChanged: {
        if (!active && !root.suppressInactive) {
            backend.hideWindow();
        }
    }

    function transformWindow() {
        const currentScreenRect = backend.currentScreenRect();
        root.x = currentScreenRect.x;
        root.width = currentScreenRect.width;
        root.y = currentScreenRect.y;
        root.height = currentScreenRect.height;
    }

    function positionContent() {
        content.width = profileViewLoader.width + root.contentMargin * 2;
        content.height = profileViewLoader.height + profileTitle.height + column.spacing + root.contentMargin * 2;
        const contentPosition = backend.contentPosition(content.width,content.height);
        content.x = contentPosition.x;
        content.y = contentPosition.y;
    }

    function showWindow() {
        root.show();
        root.raise();
        if(!root.active) {
            root.requestActivate();
        }
        root.suppressInactive = true;
        suppressInactiveTimer.restart();
    }

    property bool suppressInactive: false

    Timer {
        id: suppressInactiveTimer
        interval: 100
        onTriggered: {
            root.suppressInactive = false
        }
    }
}
