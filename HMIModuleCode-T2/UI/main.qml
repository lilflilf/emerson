/*******************************************************************
Copyright:http://www.sinux.com.cn
Date:2016/12/26
Author:zhangjiyong&lilongfei
Description: main interface,load the welcome screen and menu interface
The function interface:
    checkNeedPassWd()
    showDialog()
    contentLoader
*******************************************************************/
import QtQuick 2.7
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.0
import QtQuick.Window 2.2
import ALPaintedItem 1.0

Window {
    id: mainRoot
    width: Screen.width // 1366
    height: Screen.height - 1 //767
    visible: true
    title: qsTr("NewWireSplice")
    flags: Qt.WindowStaysOnTopHint | Qt.FramelessWindowHint | Qt.Window
    signal dialogReturn(bool reb)
    signal signalStackViewPop()
    property bool bIsEditSplice: false

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
    function checkAllInterface(index)
    {
        if (index == 20) {
           if (hmiAdaptor.needPassWord("Teach Mode")) {
                return true
           } else {
               return false
           }
        } else {
            checkNeedPassWd(index)
        }
    }
    function popStackView()
    {
        var last = stackview.depth
        stackview.pop()
        signalStackViewPop()
        if (last <= 1 )
            stackview.clear()
    }

    function clearStackView()
    {
        stackview.pop(null)
        stackview.clear();
    }

    function checkNeedPassWd(index)
    {
//         ("Create New", "Edit Existing", "Operate", "Test", "Teach Mode", "Calibration",
//          "Tool Change", "Advanced Maintenance", "Maintenance Counter", "Maintenance Log",
//          "Work Order History", "Statistical Trend", "Error/Alarm Log", "Library",
//          "Version Information", "Permission Setting", "Weld Defaults", "Operator Library",
//          "Data/Communication", "Lock On Alarm")
        var source
        switch (index) {
//        case 0:
//            source = "Create New"
//            break;
//        case 1:
//            source = "Edit Existing"
//            break;
        case -1:
            source = "Splice"
            break;
        case 0:
            source = "Sequence"
            break;
        case 1:
            source = "Harness"
            break;
        case 2:
            source = "Operate"
            break;
        case 3:
            source = "Test"
            break;
        case 4:
            source = "Calibration"
            break;
        case 5:
            source = "Tool Change"
            break;
        case 6:
            source = "Advanced Maintenance"
            break;
        case 7:
            source = "Maintenance Counter"
            break;
        case 8:
            source = "Maintenance Log"
            break;
        case 9:
            source = "Work Order History"
            break;
        case 10:
            source = "Statistical Trend"
            break;
        case 11:
            source = "Error/Alarm Log"
            break;
        case 12:
            source = "Library"
            break;
        case 13:
            source = "Version Information"
            break
        case 14:
            source = "Permission Setting"
            break;
        case 15:
            source = "Weld Defaults"
            break;
        case 16:
            source = "Operator Library"
            break;
        case 17:
            source = "Data/Communication"
            break;
        case 19:
            source = "qrc:/UI/EditWire.qml"
            break;
        default:
            break;
        }
        if (hmiAdaptor.needPassWord(source)) {
            passwdLog.visible = true
            passwdLog.index = index
            passwdLog.pageName = source
        } else {
            menuInit(index)
        }
    }

    function menuInit(index)
    {
        initIndex = index
        contentLoader.source = ""
        switch (index) {
        case -1:
//            contentLoader.source = "qrc:/UI/CreatWire.qml"
            stackview.push("qrc:/UI/CreatWire.qml",{},StackView.Immediate)
            headBar.titleText = qsTr("Create Splice")
            break;
        case 0:
            partModel.getPartInfo(false,0,"")
            stackview.push("qrc:/UI/Content.qml")
//            contentLoader.source = "qrc:/UI/Content.qml"
            headBar.titleText = qsTr("Create Harness")
            break;
        case 1:
            partModel.getPartInfo(false,0,"")
            stackview.push("qrc:/UI/Content.qml")
//            contentLoader.source = "qrc:/UI/Content.qml"
            headBar.titleText = qsTr("Create Sequence")
            break;
        case 2:
            headBar.titleText = qsTr("Operate")
            stackview.push("qrc:/UI/Operate.qml")

//            contentLoader.source = "qrc:/UI/Operate.qml"
            break;
        case 3:
            headBar.titleText = qsTr("Test")
            stackview.push("qrc:/UI/TestSpliceLibrary.qml")

//            contentLoader.source = "qrc:/UI/TestSpliceLibrary.qml"
            break;
        case 4:
            headBar.titleText = qsTr("Calibration")
            stackview.push("qrc:/UI/Calibration.qml")

//            contentLoader.source = "qrc:/UI/Calibration.qml"
            break;
        case 5:
            headBar.titleText = qsTr("Tool Change")
            stackview.push("qrc:/UI/ToolChange.qml")

//            contentLoader.source = "qrc:/UI/ToolChange.qml"
            break;
        case 6:
            headBar.titleText = qsTr("Advanced Maintenance")
            stackview.push("qrc:/UI/AdvancedMaintenance.qml")

//            contentLoader.source = "qrc:/UI/AdvancedMaintenance.qml"
            break;
        case 7:
            headBar.titleText = qsTr("Maintenance Counter")
            hmiAdaptor.maintenanceCountExecute("_Recall")
            stackview.push("qrc:/UI/MaintenanceCount.qml")
//            contentLoader.source = "qrc:/UI/MaintenanceCount.qml"
            break;
        case 8:
            headBar.titleText = qsTr("Maintenance log")
            stackview.push("qrc:/UI/MaintenanceLog.qml")

//            contentLoader.source = "qrc:/UI/MaintenanceLog.qml"
            break;
        case 9:
            headBar.titleText = qsTr("Work Order History")
            stackview.push("qrc:/UI/ViewWorkOrder.qml")

//            contentLoader.source = "qrc:/UI/ViewWorkOrder.qml"
            break;
        case 10:
            headBar.titleText = qsTr("Statistical Trend")
            stackview.push("qrc:/UI/ViewTrend.qml")

//            contentLoader.source = "qrc:/UI/ViewTrend.qml"
            break;
        case 11:
            headBar.titleText = qsTr("Error/Alarm Log")
            stackview.push("qrc:/UI/ViewError.qml")

//            contentLoader.source = "qrc:/UI/ViewError.qml"
            break;
        case 12:
            headBar.titleText = qsTr("Library")
            hmiAdaptor.dataCommunicationExecute("_Recall");            
//            contentLoader.source = "qrc:/UI/ViewLibrary.qml"
            stackview.push("qrc:/UI/ViewLibrary.qml")

            break;
        case 13:
            headBar.titleText = qsTr("Version Information")            
//            contentLoader.source = "qrc:/UI/ViewVersion.qml"
            stackview.push("qrc:/UI/ViewVersion.qml")

            break
        case 14:
            headBar.titleText = qsTr("Permission Setting")
            hmiAdaptor.permissionsettingExecute("_Recall");
//            contentLoader.source = "qrc:/UI/PermissionSetting.qml"
            stackview.push("qrc:/UI/PermissionSetting.qml")

            break;
        case 15:
            headBar.titleText = qsTr("Weld Defaults")
            hmiAdaptor.weldDefaultsExecute("_Recall");
//            contentLoader.source = "qrc:/UI/WeldDefalut.qml"
            stackview.push("qrc:/UI/WeldDefalut.qml")

            break;
        case 16:
            headBar.titleText = qsTr("Operator Library")
            hmiAdaptor.permissionsettingExecute("_Recall")
//            contentLoader.source = "qrc:/UI/UserLibrarySetting.qml"
            stackview.push("qrc:/UI/UserLibrarySetting.qml")

            break;
        case 17:
            headBar.titleText = qsTr("Data Communication")
            hmiAdaptor.dataCommunicationExecute("_Recall");
//            contentLoader.source = "qrc:/UI/DataCommunication.qml"
            stackview.push("qrc:/UI/DataCommunication.qml")

            break;
//        case 18:
//            contentLoader.source = "qrc:/UI/BransonSetting.qml"
//            break;
        case 19:
            headBar.titleText = qsTr("Edit Existing")
//            contentLoader.source = "qrc:/UI/EditWire.qml"
            stackview.push("qrc:/UI/EditWire.qml")

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
            hmiAdaptor.msgBoxClick(reb)
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
                cdialog.bisQuit = isQuit
            }
            onSignalDisableDialog: {
                cdialog.visible = false

                cdialog.okvisible = false
                cdialog.cancelvisible = false
                cdialog.okText = ""
                cdialog.cancelText = ""
                cdialog.centerText = ""
                cdialog.msgTypeIco = ""
                cdialog.titleText = ""
                cdialog.isQuit = false
            }
        }
    }
    CPassWordDialog {
        id: passwdLog
        anchors.centerIn: parent
        visible: false
        z: 21
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

    StackView {
        id: stackview
        anchors.top: headBar.bottom
        width: Screen.width
        height: Screen.height - 104
        z: 4
    }

    Loader {
        id: contentLoader
        anchors.top: headBar.bottom
        width: Screen.width
        height: Screen.height - 104
        z: 3
        onLoaded: {
            if (initIndex == 1) {
//                contentLoader.item.bIsEdit = true
//                contentLoader.item.bIsFirst = true
                contentLoader.item.initSequence()

            }
            else if (initIndex == 3)
            {
                contentLoader.item.testSpliceId = hmiAdaptor.getTestSpliceId()
                contentLoader.item.initPage()
            }
            else if (initIndex == 0)
            {
                contentLoader.item.partId = hmiAdaptor.getEditPartId()
                contentLoader.item.spliceId = hmiAdaptor.getTestSpliceId()
                contentLoader.item.initEdit()
                contentLoader.item.initHarness()

            }
            else if (initIndex == 19)
            {
                contentLoader.item.editWirdId = hmiAdaptor.getEditWireId()
                contentLoader.item.initPage()
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
