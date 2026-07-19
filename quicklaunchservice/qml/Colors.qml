pragma Singleton
import QtQuick

import QuickLaunchService 1.0

QtObject {
    property bool isDarkMode: Theme.isDark
    readonly property color primary: isDarkMode ? "#202024" : "#f8f8f8"
    readonly property color secondary: isDarkMode ? "#404046" : "#a0a0a0"
}
