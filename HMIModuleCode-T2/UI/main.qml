import QtQuick 2.7
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.0
import QtQuick.Window 2.2
import ALPaintedItem 1.0

Window {
    id: root
    width: Screen.width // 1366
    height: Screen.height - 1 //767
    visible: true
    title: qsTr("NewWireSplice")
    flags: Qt.WindowStaysOnTopHint | Qt.FramelessWindowHint|Qt.Window
//    flags: Qt.FramelessWindowHint |Qt.Window //| Qt.WindowSystemMenuHint | 0x00800000 | Qt.WindowFullscreenButtonHint
    signal dialogReturn(bool reb)
    //     flags: Qt.Window | 0x00800000

    Component.onCompleted: {
//        root.showMaximized()
        //w.setWindowFlags(w.windowFlags()& ~Qt::WindowMaximizeButtonHint&  ~Qt::WindowMinimizeButtonHint);
//        w.showMaximized();
//        root.showFullScreen()
    }

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
        if (contentLoader.source == "qrc:/UI/Calibration.qml")
            hmiAdaptor.maintenanceStop(0);
        else if (contentLoader.source == "qrc:/UI/AdvancedMaintenance.qml")
            hmiAdaptor.maintenanceStop(2);
        else if (contentLoader.source == "qrc:/UI/ToolChange.qml")
            hmiAdaptor.maintenanceStop(1);
        else if (contentLoader.source == "qrc:/UI/MaintenanceCount.qml")
            hmiAdaptor.maintenanceStop(3);

        contentLoader.source = ""
        switch (index) {
        case 0:
        case 1:
            partModel.getPartInfo(false,0,"")
            contentLoader.source = "qrc:/UI/Content.qml"
            headBar.titleText = qsTr("Create New")
            break;
        case 2:
            headBar.titleText = qsTr("Operate")
            contentLoader.source = "qrc:/UI/Operate.qml"
            break;
        case 3:
            headBar.titleText = qsTr("Test")
            contentLoader.source = "qrc:/UI/TestSpliceLibrary.qml"
            break;
        case 4:
            contentLoader.source = "qrc:/UI/Calibration.qml"
            break;
        case 5:
            contentLoader.source = "qrc:/UI/ToolChange.qml"
            break;
        case 6:
            headBar.titleText = qsTr("Advanced Maintenance")
            contentLoader.source = "qrc:/UI/AdvancedMaintenance.qml"
            break;
        case 7:
            hmiAdaptor.maintenanceCountExecute("_Recall")
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
            hmiAdaptor.dataCommunicationExecute("_Recall");
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
            hmiAdaptor.weldDefaultsExecute("_Recall");
            contentLoader.source = "qrc:/UI/WeldDefalut.qml"
            break;
        case 16:
            hmiAdaptor.permissionsettingExecute("_Recall")
            contentLoader.source = "qrc:/UI/UserLibrarySetting.qml"
            break;
        case 17:
            hmiAdaptor.dataCommunicationExecute("_Recall");
            contentLoader.source = "qrc:/UI/DataCommunication.qml"
            break;
//        case 18:
//            contentLoader.source = "qrc:/UI/BransonSetting.qml"
//            break;
        case 19:
            contentLoader.source = "qrc:/UI/EditWire.qml"
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

    function showDialog(okVisable,cancelVisable,okText,cancelText,typeIco,titleText,centerText)
    {
        cdialog.okvisible = okVisable
        cdialog.cancelvisible = cancelVisable
        cdialog.okText = okText
        cdialog.cancelText = cancelText
        cdialog.centerText = centerText
        cdialog.msgTypeIco = typeIco
        cdialog.titleText = titleText
        cdialog.visible = true
    }

    CDialog {
        id: cdialog
        anchors.centerIn: parent
        visible: false
        z: 20
        onCliceTo: {
            dialogReturn(reb)
        }
        Connections {
            target: hmiAdaptor
            onSignalEnableDialog: {
                cdialog.okvisible = okVisable
                cdialog.cancelvisible = cancelVisable
                cdialog.okText = okText
                cdialog.cancelText = cancelText
                cdialog.centerText = centerText
                cdialog.msgTypeIco = typeIco
                cdialog.titleText = titleText
                cdialog.visible = true
            }
        }
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

    HeadBar {
        id: headBar
        visible: false
        height: 79
        z: 10
        anchors.top: statusBar.bottom
    }

    Loader {
        id: contentLoader
        anchors.top: headBar.bottom
        width: Screen.width
        height: Screen.height - 104
        z: 3
        onLoaded: {
            if (initIndex == 1) {
                contentLoader.item.bIsEdit = true
                contentLoader.item.bIsFirst = true
            }
        }
    }
    Connections {
        target: contentLoader.item
        onTitleTextChanged: {
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
}
