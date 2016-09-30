import QtQuick 2.7
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.0
import QtQuick.Window 2.2

ApplicationWindow {
    id: root
    visible: true
    width: Screen.desktopAvailableWidth
    height: Screen.desktopAvailableHeight
    title: qsTr("Hello World")
    function menuInit(index)
    {
        console.log("creat splice")
        contentLoader.source = ""
        contentLoader.source = "qrc:/Content.qml"
    }
    Component.onCompleted: {
        root.showFullScreen()
    }

    CStatusBar {
        id: statusBar
        height: Screen.desktopAvailableHeight * 0.03
    }
    HeadBar {
        id: headBar
        height: Screen.desktopAvailableHeight * 0.07
        anchors.top: statusBar.bottom
    }

    Loader {
        id: contentLoader
        anchors.top: headBar.bottom
        width: Screen.desktopAvailableWidth
        height: Screen.desktopAvailableHeight
    }
}
