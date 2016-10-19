import QtQuick 2.7
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.0
import QtQuick.Window 2.2

//ApplicationWindow {
Window {
    id: root
    visible: true
    width: Screen.desktopAvailableWidth
    height: Screen.desktopAvailableHeight
    title: qsTr("NewWireSplice")
    property var initIndex: 0
    function menuInit(index)
    {
        initIndex = index
        contentLoader.source = ""
        switch (index) {
        case 0:
        case 1:
            contentLoader.source = "qrc:/Content.qml"
            break;
        case 2:
            contentLoader.source = "qrc:/Operate.qml"
            break;
        default:
            break;
        }

    }
    Component.onCompleted: {

        //root.showMaximized()
//        w.setWindowFlags(w.windowFlags()& ~Qt::WindowMaximizeButtonHint&  ~Qt::WindowMinimizeButtonHint);
//        w.showMaximized();
        root.showFullScreen()
    }

    CStatusBar {
        id: statusBar
        height: Screen.desktopAvailableHeight * 0.03
    }

//    Content {
//        z:3
//        anchors.top: headBar.bottom
//        width: Screen.desktopAvailableWidth
//        height: Screen.desktopAvailableHeight
//    }

    Loader {
        id: contentLoader
        z:3
        anchors.top: headBar.bottom
        width: Screen.desktopAvailableWidth
        height: Screen.desktopAvailableHeight
        onLoaded: {
            if (initIndex == 1)
                contentLoader.item.bIsEdit = true
        }
    }
    Connections {
        target: contentLoader.item
        onTitleTextChanged: {
            console.log("myTitleText = ",myTitleText)
            headBar.titleText = myTitleText
        }
    }

    HeadBar {
        id: headBar
        height: Screen.desktopAvailableHeight * 0.07
        anchors.top: statusBar.bottom
        z: 10
    }
}
