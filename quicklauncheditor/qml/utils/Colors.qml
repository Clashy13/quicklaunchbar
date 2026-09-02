pragma Singleton
import QtQuick

import QuickLaunchEditor 1.0

QtObject {
    property bool isDarkMode: Theme.isDark

    enum Type {
        Primary,
        Secondary
    }

    readonly property color listItemSelected: isDarkMode ? '#424246' : '#dddddd'
    readonly property color listItemHovered: isDarkMode ? "#38383d" : '#ececec'

    readonly property color scrollBar: isDarkMode ? '#717174' : "#a9a9aa"
    readonly property color scrollBarHovered: isDarkMode ? Qt.darker(scrollBar,1.4) : Qt.lighter(scrollBar,1.2)
    readonly property color scrollBarPressed: markedBlue

    readonly property color text: isDarkMode ? "#eeeeee" : "#212121"
    readonly property color textDisabled: isDarkMode ? Qt.darker(text,1.6) : '#afafaf'

    readonly property color markedBlue: "#1f9ede"
    readonly property color markedRed: '#ea2929'
    readonly property color markedGreen: isDarkMode ? '#62a03c' : '#78ca45'
    
    readonly property color checkboxChecked: markedBlue
    readonly property color checkboxUnchecked: isDarkMode ? '#48484d' : "#dcdddf"

    property QtObject primary: QtObject {
        readonly property color background: isDarkMode ? "#2e2e33" : "#ffffff"
        readonly property color border: isDarkMode ? '#202023' : "#c8c8ce"

        readonly property color textInput: isDarkMode ? '#27272b' : '#dddde0'

        readonly property color button: isDarkMode ? "#333338" : "#fefefe"
        readonly property color buttonSelected: isDarkMode ? '#27272b' : "#d3d3d4"
        readonly property color buttonHovered: isDarkMode ?  Qt.lighter(button,1.2) : '#eeeded'
    }

    property QtObject secondary: QtObject {
        readonly property color background: isDarkMode ? '#222225' : '#ebebed'
        readonly property color border: isDarkMode ? '#050506' : "#cbcbd0"

        readonly property color textInput: button

        readonly property color button: isDarkMode ? "#36363d" : "#fcfcfc"
        readonly property color buttonSelected: isDarkMode ? '#1d1d20' : "#c8c8ca"
        readonly property color buttonHovered: isDarkMode ? Qt.lighter(button,1.2) : Qt.darker(button,1.2)
    }
}
