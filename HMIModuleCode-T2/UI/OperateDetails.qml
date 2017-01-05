import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.0
import QtQuick.Window 2.2

Item {
    id: operateDetail
    property var spliceList: new Array
    property int showFlag: 3 /*1:inLine 2:offLine 3:signal*/
    property int cycleCount: 0
    property int qliantity: 0
    property int maxCount: partModel.getCurrentPartSpliceCount()
    Rectangle {
        anchors.fill: parent
        color: "#626465"
        MouseArea {
            anchors.fill: parent
        }
    }
    Connections {
        target: hmiAdaptor
        onSignalWeldCycleCompleted: {
            progressBar.current++
            spliceLocation.setTreeModelOver()
            progressBar.moveToNext()
            selectSplice(spliceList[progressBar.current-1])
            if (showFlag == 2)
                offline.setStusOffLineUpdate(progressBar.current)
            else if (showFlag == 1)
                spliceLocation.updateTreeModel(progressBar.current)
//            console.log("333333331111",operateDetail.cycleCount,operateDetail.qliantity)
//            if (operateDetail.cycleCount == operateDetail.qliantity) {
//                cdialog.visible = true
//                return
//            }
        }
        onSignalMantenaneceCount: {
            progressBar3.value = count
        }
    }
    onCycleCountChanged: {
        if (operateDetail.cycleCount == operateDetail.qliantity) {
            cdialog.visible = true
            hmiAdaptor.operateProcessExec("Stop")
        }
    }

//    Component.onCompleted: {
//        hmiAdaptor.operateProcessExec("Start")
//    }
//    Component.onDestruction: {
//        hmiAdaptor.operateProcessExec("Stop")
//    }

    function setData()
    {
        qualityWindow.partCount = progressBar.current - 1
        qualityWindow.timeModel = alarmModel.getPointList("Time",spliceModel.getStructValue("SpliceName",""),spliceModel.getHashCode())
        qualityWindow.powerModel = alarmModel.getPointList("Power",spliceModel.getStructValue("SpliceName",""),spliceModel.getHashCode())
        qualityWindow.preModel = alarmModel.getPointList("Pre-Height",spliceModel.getStructValue("SpliceName",""),spliceModel.getHashCode())
        qualityWindow.postModel = alarmModel.getPointList("Post-Height",spliceModel.getStructValue("SpliceName",""),spliceModel.getHashCode())

        qualityWindow.qualityModel.clear()
        if (qualityWindow.timeModel.length > 0) {
            qualityWindow.qualityModel.append({"redMax":spliceModel.getRawData("Time+"),"redMin":spliceModel.getRawData("Time-"),"yellowMax":hmiAdaptor.controlLimitProcess("Time+",qualityWindow.timeModel,spliceModel.getRawData("Time+"),spliceModel.getRawData("Time-")),"yellowMin":hmiAdaptor.controlLimitProcess("Time-",qualityWindow.timeModel,spliceModel.getRawData("Time+"),spliceModel.getRawData("Time-")),"current":qualityWindow.timeModel[qualityWindow.timeModel.length - 1],"currentText":spliceModel.actualTimeToString(qualityWindow.timeModel[qualityWindow.timeModel.length - 1])})
            qualityWindow.qualityModel.append({"redMax":spliceModel.getRawData("Power+"),"redMin":spliceModel.getRawData("Power-"),"yellowMax":hmiAdaptor.controlLimitProcess("Power+",qualityWindow.powerModel,spliceModel.getRawData("Power+"),spliceModel.getRawData("Power-")),"yellowMin":hmiAdaptor.controlLimitProcess("Power-",qualityWindow.powerModel,spliceModel.getRawData("Power+"),spliceModel.getRawData("Power-")),"current":qualityWindow.powerModel[qualityWindow.powerModel.length - 1],"currentText":spliceModel.actualPowerToString(qualityWindow.powerModel[qualityWindow.powerModel.length - 1])})
            qualityWindow.qualityModel.append({"redMax":spliceModel.getRawData("Pre-Height+"),"redMin":spliceModel.getRawData("Pre-Height-"),"yellowMax":hmiAdaptor.controlLimitProcess("Time+",qualityWindow.preModel,spliceModel.getRawData("Pre-Height+"),spliceModel.getRawData("Pre-Height-")),"yellowMin":hmiAdaptor.controlLimitProcess("Pre-Height-",qualityWindow.preModel,spliceModel.getRawData("Pre-Height+"),spliceModel.getRawData("Pre-Height-")),"current":qualityWindow.preModel[qualityWindow.preModel.length - 1],"currentText":spliceModel.actualPreHeightToString(qualityWindow.preModel[qualityWindow.preModel.length - 1])})
            qualityWindow.qualityModel.append({"redMax":spliceModel.getRawData("Post-Height+"),"redMin":spliceModel.getRawData("Post-Height-"),"yellowMax":hmiAdaptor.controlLimitProcess("Time+",qualityWindow.postModel,spliceModel.getRawData("Post-Height+"),spliceModel.getRawData("Post-Height-")),"yellowMin":hmiAdaptor.controlLimitProcess("Post-Height-",qualityWindow.postModel,spliceModel.getRawData("Post-Height+"),spliceModel.getRawData("Post-Height-")),"current":qualityWindow.postModel[qualityWindow.postModel.length - 1],"currentText":spliceModel.actualHeightToString(qualityWindow.postModel[qualityWindow.postModel.length - 1])})
        }
        else {
            qualityWindow.qualityModel.append({"redMax":spliceModel.getRawData("Time+"),"redMin":spliceModel.getRawData("Time-"),"yellowMax":-1,"yellowMin":-1,"current":-1,"currentText":"23"})
            qualityWindow.qualityModel.append({"redMax":spliceModel.getRawData("Power+"),"redMin":spliceModel.getRawData("Power-"),"yellowMax":-1,"yellowMin":-1,"current":-1,"currentText":"123"})
            qualityWindow.qualityModel.append({"redMax":spliceModel.getRawData("Pre-Height+"),"redMin":spliceModel.getRawData("Pre-Height-"),"yellowMax":-1,"yellowMin":-1,"current":-1,"currentText":"2512"})
            qualityWindow.qualityModel.append({"redMax":spliceModel.getRawData("Post-Height+"),"redMin":spliceModel.getRawData("Post-Height-"),"yellowMax":-1,"yellowMin":-1,"current":-1,"currentText":"43"})
        }

        qualityWindow.setData()

    }

    function selectSplice(spliceId)
    {
        spliceModel.editNew(spliceId)
        setData()
        var list = new Array
        list = spliceModel.getWireIdList()
        spliceDetailsItem.clear()
        spliceName.text = spliceModel.getStructValue("SpliceName","")
        spliceDetailsImage.source = spliceModel.getStructValue("PicPath","")
        for (var i = 0; i < list.length;i++)
        {
            wireModel.addFromLibrary(list[i])
            spliceDetailsItem.addWireFromSplice()
        }
        hmiAdaptor.setOperateProcess(spliceId, false)
        hmiAdaptor.operateProcessExec("Execute")
    }

    Text {
        id: operateTitle
        text: qsTr("Splice:")
        font.pointSize: 16
        font.family: "arial"
        color: "white"
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.leftMargin: 25
        anchors.topMargin: 15
    }
    Text {
        id: spliceName
        font.pointSize: 16
        font.family: "arial"
        color: "white"
        anchors.left: operateTitle.right
        anchors.top: parent.top
        anchors.topMargin: 15
    }
    Switch2 {
        width: Screen.width * 0.12
        height: Screen.height * 0.04
        anchors.right: spliceDetailsItem.right
        anchors.top: operateTitle.top
        textLeft: qsTr("Diagram")
        textRight: qsTr("Image")
        state: "left"
        onStateChanged: {
            if (state == "left") {
                spliceDetailsItem.visible = true
                spliceDetailsImage.visible = false
            }
            else
            {
                spliceDetailsItem.visible = false
                spliceDetailsImage.visible = true
            }
        }
    }

    Image {
        id: spliceDetailsImage
        anchors.fill: spliceDetailsItem
//        source: "qrc:/images/images/wiredemo.jpg"
    }
    QualityWindow {
        id: qualityWindow
        anchors.right: parent.right
        anchors.rightMargin: 30
        anchors.top: operateTitle.top
    }

    SpliceDetails {
        id: spliceDetailsItem
        width: Screen.width * 0.5
        height: Screen.height *0.45
        anchors.top: operateTitle.bottom
        anchors.left: operateTitle.left
        anchors.topMargin: 15
        centerVisable: false
    }

    Text {
        id: spliceTips
        anchors.top: spliceDetailsItem.bottom
        anchors.topMargin: 10
        anchors.left: operateTitle.left
        font.pointSize: 14
        font.family: "arial"
        text: qsTr("Insulation: 1 Temp(℃):260 Time(s):09.0")
        color: "white"
    }
    Text {
        id: totalcross
        anchors.top: spliceDetailsItem.bottom
        anchors.topMargin: 10
        anchors.right: spliceDetailsItem.right
        font.pointSize: 14
        font.family: "arial"
        text: qsTr("Total Cross Section: 2.3mm")
        color: "white"
    }
    ListModel {
        id: treeModel
        Component.onCompleted: {
            var array = ["A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P"]
            for (var i = 0; i < spliceLocation.rows*spliceLocation.columns; i++) {
                treeModel.append({"id":array[i],"level":0,"subNode":[]})
            }
            var zoneList = new Array();
            zoneList = partModel.geteWorkStationZone()
            var j = 0
            for ( j = 0; j < zoneList.length; j++) {
                if (j == 0) {
                    spliceLocation.workStation = array[zoneList[j]]
                    treeModel.get(zoneList[j]).subNode.append({"spliceNo":j+1,"spliceColor":"#00aa7e","level":1,"subNode":[]})
                } else if (j == 1) {
                    treeModel.get(zoneList[j]).subNode.append({"spliceNo":j+1,"spliceColor":"#00afe9","level":1,"subNode":[]})
                } else {
                    treeModel.get(zoneList[j]).subNode.append({"spliceNo":j+1,"spliceColor":"white","level":1,"subNode":[]})
                }
            }
        }
    }

    SpliceLocation {
        id: spliceLocation
        anchors.top: spliceTips.bottom
        anchors.topMargin: 10
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        anchors.left: operateTitle.left
        width: Screen.width * 0.37
        columns: partModel.getWorkStationColumns()
        rows: partModel.getWorkStationRows()
        visible: showFlag == 1 ? true : false
        listModel: treeModel
        maxNum: maxCount
    }
    onShowFlagChanged: {
//        console.log("555555555555555",showFlag)
    }

    SpliceStatusOffLine {
        id: offline
        anchors.top: spliceTips.bottom
        anchors.topMargin: 10
        anchors.left: operateTitle.left
        anchors.bottom: partCount2.top
        anchors.bottomMargin: 20
        width: Screen.width * 0.37
        maxNum: maxCount
        listModel: maxCount > 8 ? 8 : maxCount
        visible: showFlag == 2 ? true : false
        Component.onCompleted: {
            offLineInit()
        }
    }

    Rectangle {
        id: currentSplice
        anchors.top:  spliceTips.bottom
        anchors.topMargin: 12
        anchors.left: spliceLocation.right
        anchors.leftMargin: 10
        radius: 15
        width: 15
        height: 15
        color: "#00aa7e"
        visible:  showFlag == 1 ? true : false
    }
    Text {
        id: currentspliceTips
        anchors.top: spliceTips.bottom
        anchors.topMargin: 10
        anchors.left: currentSplice.right
        anchors.leftMargin: 6
        font.pointSize: 13
        font.family: "arial"
        color: "white"
        text: qsTr("CURRENT SPLICE")
        visible:  showFlag == 1 ? true : false
    }
    Rectangle {
        id: nextSPlice
        anchors.top:  currentspliceTips.bottom
        anchors.topMargin: 26
        anchors.left: spliceLocation.right
        anchors.leftMargin: 10
        radius: 15
        width: 15
        height: 15
        color: "#00afe9"
        visible:   showFlag == 1 ? true : false
    }
    Text {
        id: nextSPliceTips
        anchors.top: currentspliceTips.bottom
        anchors.topMargin: 24
        anchors.left: nextSPlice.right
        anchors.leftMargin: 6
        font.pointSize: 13
        font.family: "arial"
        color: "white"
        text: qsTr("NEXT SPLICE")
        visible:   showFlag == 1 ? true : false
    }
    Rectangle {
        id: missSplice
        anchors.top:  nextSPliceTips.bottom
        anchors.topMargin: 26
        anchors.left: spliceLocation.right
        anchors.leftMargin: 10
        radius: 15
        width: 15
        height: 15
        color: "#d31145"
        visible:   showFlag == 1 ? true : false
    }
    Text {
        id: missSpliceTips
        anchors.top: nextSPliceTips.bottom
        anchors.topMargin: 24
        anchors.left: missSplice.right
        anchors.leftMargin: 6
        font.pointSize: 13
        font.family: "arial"
        color: "white"
        text: qsTr("MISSED SPLICE")
        visible:   showFlag == 1 ? true : false
    }
    Rectangle {
        id: completeMiss
        anchors.top: partModel.getPartOnlineOrOffLine() ? missSpliceTips.bottom : spliceTips.bottom
        anchors.topMargin: partModel.getPartOnlineOrOffLine() ? 24 : 12
        anchors.left: spliceLocation.right
        anchors.leftMargin: 10
        anchors.bottom: partModel.getPartOnlineOrOffLine() ? parent.bottom : partCount2.top
        anchors.bottomMargin: partModel.getPartOnlineOrOffLine() ? 10 : 20
        width: spliceDetailsItem.width-spliceLocation.width-10
        color: "#6d6e71"
        opacity: 1
        visible: showFlag != 3 ? true : false
        Rectangle {
            id: tipsRec
            anchors.left: parent.left
            width: 17
            height: parent.height
            color: "#d31145"
        }
        Text {
            id: tipsText
            anchors.left: tipsRec.right
            anchors.leftMargin: 10
            width: parent.width-tipsRec.width-10
            height: parent.height
            verticalAlignment: Qt.AlignVCenter
            text: qsTr("Complete\nMissed\nSplie")
            color: "white"
            font.pointSize: 16
            font.family: "arial"
        }
        MouseArea {
            anchors.fill: parent
            onPressed: {
                completeMiss.opacity = 0.5
            }
            onReleased: {
                completeMiss.opacity = 1
            }
        }
    }
    Text {
        id: partCount2
        anchors.left: showFlag != 1 ? offline.left : qualityWindow.left
        anchors.bottom: progressBar2.top
        anchors.bottomMargin: 6
        font.pointSize: 13
        font.family: "arial"
        text: qsTr("PART COUNTER 0/")+ qliantity
        color: "white"
        Connections {
            target: progressBar
            onCycleDone: {
                cycleCount++
                if (cycleCount > qliantity)
                    return
                selectSplice(spliceList[0])
                partCount2.text = qsTr("PART COUNTER ") + cycleCount + "/" + qliantity;
                progressBar2.value = cycleCount
            }
        }
    }
    CProgressBar {
        id: progressBar2
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 20
        anchors.left: showFlag != 1 ? offline.left : qualityWindow.left
        width: showFlag != 1 ? spliceDetailsItem.width : qualityWindow.width/2 - 20
        height: 10
        maximum: qliantity
        minimum: 0
        value: 0
    }
    Text {
        id: progresstracking2
        anchors.top: offline.top
        anchors.topMargin: 10
        anchors.left: offline.left
        font.pointSize: 16
        font.family: "arial"
        text: qsTr("Progress and Tracking")
        color: "white"
        visible: showFlag == 3 ? true : false
    }
    Text {
        id: progresstracking
        anchors.bottom: workStation.top
        anchors.bottomMargin: 4
        anchors.left: qualityWindow.left
        font.pointSize: 16
        font.family: "arial"
        text: qsTr("Progress and Tracking")
        color: "white"
        visible: showFlag != 3 ? true : false
    }
    Text {
        id: workStation
        anchors.bottom: progressBar.top
        anchors.bottomMargin: 6
        anchors.left: qualityWindow.left
        font.pointSize: 13
        font.family: "arial"
        text: partModel.getPartOnlineOrOffLine() ? qsTr("Work Station: ") + spliceLocation.workStation : qsTr("PART TASKS: ") + progressBar.current + "-" + progressBar.total
        color: "white"
        visible: showFlag != 3 ? true : false
    }
    Text {
        id: partTask
        anchors.right: parent.right
        anchors.rightMargin: 30
        anchors.bottom: progressBar.top
        anchors.bottomMargin: 6
        font.pointSize: 13
        font.family: "arial"
        visible: partModel.getPartOnlineOrOffLine()
        text: qsTr("PART TASKS: ") + progressBar.current + "-" + progressBar.total
        color: "white"
    }
    CButton {
        id: leftButton
        anchors.verticalCenter: progressBar.verticalCenter
        anchors.left: qualityWindow.left
        width: 41
        height: 63
        iconSource: "qrc:/images/images/left_operate.png"
        backgroundEnabled: false
        clip: true
        visible: showFlag != 3 ? true : false
        onClicked: {
            if (progressBar.current > 1) {
				progressBar.current--
                progressBar.jumpToAbove()
                selectSplice(spliceList[progressBar.current-1])
                spliceLocation.setTreeModelBack(progressBar.current)
                offline.setStusOffLineBack(progressBar.current)
            }
        }
    }
    Progressbar {
        id: progressBar
        anchors.left: leftButton.right
        anchors.leftMargin: 25
        anchors.right: rightButton.left
        anchors.rightMargin: 25
        anchors.bottom: partCount2.top
        anchors.bottomMargin: 4
        width: Screen.width*0.4-150
        height: 64
        total: operateDetail.spliceList.length
        current: 1
        visible: showFlag != 3 ? true : false
    }
    CButton {
        id: rightButton
        anchors.verticalCenter: progressBar.verticalCenter
        anchors.right: qualityWindow.right
        width: 41
        height: 63
        iconSource: "qrc:/images/images/right_operate.png"
        backgroundEnabled: false
        clip: true
        visible: showFlag != 3 ? true : false
        onClicked: {
            progressBar.current++
            progressBar.jumpToNext()
            selectSplice(spliceList[progressBar.current-1])
            spliceLocation.setTreeModelOver(progressBar.current)
            offline.setSatusOffLineOver(progressBar.current)
        }
    }
    Text {
        id: maintenance
        anchors.right: showFlag != 3 ? qualityWindow.right : spliceDetailsItem.right
        anchors.left: showFlag == 1 ? partCount2.right : (showFlag == 2 ? qualityWindow.left : spliceDetailsItem.left)
        horizontalAlignment: showFlag == 1 ? Qt.AlignRight : Qt.AlignLeft
        anchors.bottom: progressBar3.top
        anchors.bottomMargin: 6
        font.pointSize: 13
        font.family: "arial"
        text: qsTr("MAINTENANCE COUNTER") + hmiAdaptor.maintenanceCountGetValue(0,3) + "/" + hmiAdaptor.maintenanceCountGetValue(0,2)
        color: "white"
    }
    CProgressBar {
        id: progressBar3
        anchors.right: showFlag != 3 ? qualityWindow.right : spliceDetailsItem.right
        anchors.bottom: showFlag != 3 ? parent.bottom : partCount2.top
        anchors.bottomMargin: 20
        width: showFlag == 1 ? qualityWindow.width/2-20 : (showFlag == 2 ? qualityWindow.width : spliceDetailsItem.width)
        height: 10
        maximum: hmiAdaptor.maintenanceCountGetValue(0,2)
        minimum: 0
        value: hmiAdaptor.maintenanceCountGetValue(0,3)
    }
    CDialog {
        id: cdialog
        anchors.centerIn: parent
        okvisible: true
        okText: "OK"
        cancelvisible: false
        cancelText: "CANCEL"
        centerText: "Operate complete"
        visible: false
        onCliceTo: {
            if (reb)
                root.checkNeedPassWd(2)
        }
    }
}
