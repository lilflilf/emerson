import QtQuick 2.7
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.0
import QtQuick.Window 2.2
import ALPaintedItem 1.0

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
            contentLoader.source = "qrc:/UI/Content.qml"
            break;
        case 2:
            contentLoader.source = "qrc:/UI/Operate.qml"
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
//    Rectangle {
//        anchors.fill: parent
//        color: "#626465"
//    }
    Image {
        anchors.fill: parent
        source: "qrc:/images/images/bg.png"
    }

    CStatusBar {
        id: statusBar
        height: 25//Screen.desktopAvailableHeight * 0.03
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
        height: 79//Screen.desktopAvailableHeight * 0.07
        anchors.top: statusBar.bottom
        z: 10
    }

//    CButton {
//        id: testButton
//        width: 300
//        height: 100
//        onClicked: {
//            //alpaint.clear()
//            alpaint.draw()
//        }
//    }

//    Canvas {
//        id: mycanvas
//        width: Screen.desktopAvailableWidth
//        height: Screen.desktopAvailableHeight
//        onPaint: {
//            var ctx = getContext("2d");
//            ctx.fillStyle = Qt.rgba(1, 0, 0, 1);
//            ctx.fillRect(0, 0, width, height);
//        }
//    }

//    Rectangle {
//        id:photoMarkedRoot
//        color: "transparent"
//        property alias painter: painter
//        anchors.top: testButton.bottom
//        width: Screen.desktopAvailableWidth
//        height: Screen.desktopAvailableHeight
//        Component.onCompleted: {
//            painter.penWidth = 2//initHeight/647.0*3
//            painter.penColor = "red"
//            painter.init()
//        }

//        ALPaintedItem {
//            id: painter;
//            width: photoMarkedRoot.width
//            height: photoMarkedRoot.height
//            onWidthChanged: {
//                painter.init()
//            }
//            onHeightChanged: {
//                painter.init()
//            }
//        }
//    }
}
