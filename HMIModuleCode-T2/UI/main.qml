import QtQuick 2.7
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.0
import QtQuick.Window 2.2
import ALPaintedItem 1.0

//ApplicationWindow {
Window {
    id: root
    visible: true
//    width: Screen.width
//    height: Screen.height
    title: qsTr("NewWireSplice")
    flags: Qt.FramelessWindowHint|Qt.Window

    property var initIndex: 0
    /*0-- create
      1-- edit
      2-- Operate
      3-- Test
      4-- maintenance perssion setting
      13-- view data version information
      14-- settings Permission Setting
      15-- settings Weld Defaults
      16-- settings operator library
      17-- settings Data Communication
      18--settings Branson Setting
      */
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
        case 3:
            contentLoader.source = "qrc:/UI/TestSpliceLibrary.qml"
            break;
        case 4:
            contentLoader.source = "qrc:/UI/Calibration.qml"
            break;
        case 5:
            contentLoader.source = "qrc:/UI/ToolChange.qml"
            break;
        case 6:
            contentLoader.source = "qrc:/UI/AdvancedMaintenance.qml"
            break;
        case 7:
            contentLoader.source = "qrc:/UI/MaintenanceCount.qml"
            break;
        case 8:
            contentLoader.source = "qrc:/UI/MaintenanceLog.qml"
            break;
        case 12:
            contentLoader.source = "qrc:/UI/ViewLibrary.qml"
            break;
        case 13:
            contentLoader.source = "qrc:/UI/ViewVersion.qml"
        case 9:
            contentLoader.source = "qrc:/UI/ViewWorkOrder.qml"
            break;
        case 14:
            contentLoader.source = "qrc:/UI/PermissionSetting.qml"
            break;
        case 15:
            contentLoader.source = "qrc:/UI/WeldDefalut.qml"
            break;
        case 16:
            contentLoader.source = "qrc:/UI/UserLibrarySetting.qml"
            break;
        case 17:
            contentLoader.source = "qrc:/UI/DataCommunication.qml"
            break;
        case 18:
            contentLoader.source = "qrc:/UI/BransonSetting.qml"
            break;
        default:
            break;
        }
    }
    Component.onCompleted: {
        console.log(width,height)
        //root.showMaximized()
        //w.setWindowFlags(w.windowFlags()& ~Qt::WindowMaximizeButtonHint&  ~Qt::WindowMinimizeButtonHint);
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
        height: 25//Screen.height * 0.03
    }

//    Content {
//        z:3
//        anchors.top: headBar.bottom
//        width: Screen.width
//        height: Screen.height
//    }

    Loader {
        id: contentLoader
        z:3
        anchors.top: headBar.bottom
        width: Screen.width
        height: Screen.height - 104
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
        height: 79//Screen.height * 0.07
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
//        width: Screen.width
//        height: Screen.height
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
//        width: Screen.width
//        height: Screen.height
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
