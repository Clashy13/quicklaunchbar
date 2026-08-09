pragma Singleton
import QtQuick

import QuickLaunchEditor 1.0

QtObject {
    property bool isDarkMode: Theme.isDark
    readonly property color background1: isDarkMode ? "#2e2e33" : "#f8f8f9"
    readonly property color background2: isDarkMode ? "#38383d" : "#fefefe"
    readonly property color background3: isDarkMode ? "#27272b" : "#d3d3d3"
    readonly property color background4: isDarkMode ? "#515158" : "#e9e9e9"
    readonly property color border1: isDarkMode ? "#202023" : "#c8c8ce"
    readonly property color border2: isDarkMode ? "#000000" : "#c8c8ce"
    readonly property color content: isDarkMode ? "#eeeeee" : "#212121"
    readonly property color checkbox: isDarkMode ? "#595961" : "#bfbfc0"
}
