import QtQuick 2.7
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.0
import QtQuick.Window 2.2
import ALPaintedItem 1.0

Window {
    id: root
    visible: true
    title: qsTr("NewWireSplice")
    flags: Qt.FramelessWindowHint //|Qt.Window | Qt.WindowSystemMenuHint | 0x00800000 | Qt.WindowFullscreenButtonHint
//     flags: Qt.Window | 0x00800000
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
            headBar.titleText = qsTr("Create Assembly")
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
        case 9:
            contentLoader.source = "qrc:/UI/ViewWorkOrder.qml"
            break;
        case 10:
            contentLoader.source = "qrc:/UI/ViewTrend.qml"
            break;
        case 11:
            contentLoader.source = "qrc:/UI/ViewError.qml"
            break;
        case 12:
            contentLoader.source = "qrc:/UI/ViewLibrary.qml"
            break;
        case 13:
            contentLoader.source = "qrc:/UI/ViewVersion.qml"
            break
        case 14:
            hmiAdaptor.permissionsettingExecute("_Recall");
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
    function logoff()
    {
        headBar.visible = false
        statusBar.visible = false
        contentLoader.source = ""
        welcome.source = "qrc:/UI/Welcome.qml"
    }

    Component.onCompleted: {
//        root.showMaximized()
        //w.setWindowFlags(w.windowFlags()& ~Qt::WindowMaximizeButtonHint&  ~Qt::WindowMinimizeButtonHint);
//        w.showMaximized();
        root.showFullScreen()

    }

    Image {
        anchors.fill: parent
        source: "qrc:/images/images/bg.png"
    }
    Loader {
        id: welcome
        anchors.fill: parent
        source: "qrc:/UI/Welcome.qml"
    }
    CStatusBar {
        id: statusBar
        visible: false
        height: 25//Screen.height * 0.03
    }

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
    Connections {
        target: welcome.item
        onPassWordInputOk: {
            headBar.visible = true
            statusBar.visible = true
            welcome.source = ""
        }
    }

    HeadBar {
        id: headBar
        visible: false
        height: 79
        anchors.top: statusBar.bottom
        z: 10
    }
    TextInput {
        id: input
        width: 300
        height: 80

        anchors.centerIn: parent
        //inputMethodHints: Qt.ImhDialableCharactersOnly
        Component.onCompleted:
        {
//            VirtualKeyboardSettings.styleName = "retro"
        }
    }
}
