import QtQuick 2.7
import QtQuick.Controls 1.1
import QtQuick.Layouts 1.0
import QtQuick.Window 2.2

Item {
    id: operateDetail
    property var spliceList: new Array
    property int showFlag: -1 /*1:inLine 2:offLine 3:signal*/
    property int cycleCount: 0
    property int qliantity: 0
    property int maxCount: partModel.getCurrentPartSpliceCount()
    property int workMode: 0
    property var counterString: "PART COUNTER"
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

            if (workMode == 2)
            {
                progressBar.current++
                if (operateDetail.cycleCount == operateDetail.qliantity && operateDetail.qliantity != -1) {
                    cdialog.visible = true
                    hmiAdaptor.operateProcessExec("Stop")
                    return
                }
                spliceLocation.setTreeModelOver()
                progressBar.moveToNext()
                selectSplice(spliceList[progressBar.current-1])
                if (showFlag == 2) {
                    offline.setStusOffLineUpdate(progressBar.current)
                }
                else if (showFlag == 1)
                    spliceLocation.updateTreeModel(progressBar.current)

            }
            else if (workMode == 1)
            {
                setData()
                if (progressBar2.value + 1 == progressBar2.maximum)
                {
                    progressBar2.value = 0
                    if (progressBar.current == progressBar.total) {
                        cdialog.visible = true
                        hmiAdaptor.operateProcessExec("Stop")
                        return
                    }
                    progressBar.current++
                    progressBar.moveToNext()
                    selectSplice(spliceList[progressBar.current-1])
                    partCount2.text = qsTr(counterString) + progressBar2.value + "/" + qliantity;
                }
                else if (progressBar2.value < progressBar2.maximum) {
                    progressBar2.value = progressBar2.value + 1
                    partCount2.text = qsTr(counterString) + progressBar2.value + "/" + qliantity;
                }
            }
            else if (workMode == 0)
            {
                if (qliantity == -1)
                    return
                setData()
                if (progressBar2.value < progressBar2.maximum - 1) {
                    progressBar2.value = progressBar2.value + 1
                    partCount2.text = qsTr(counterString) + progressBar2.value + "/" + qliantity;
                }
                else {
                    cdialog.visible = true
                    hmiAdaptor.operateProcessExec("Stop")
                    return
                }
            }

//            console.log("333333331111",operateDetail.cycleCount,operateDetail.qliantity)
//            if (operateDetail.cycleCount == operateDetail.qliantity) {
//                cdialog.visible = true
//                return
//            }
        }
        onSignalMantenaneceCount: {
            progressBar3.value = count
            maintenance.text = qsTr("MAINTENANCE COUNTER") + count + "/" + hmiAdaptor.maintenanceCountGetValue(0,2)
        }
    }

    Component.onCompleted: {
        var flag = hmiAdaptor.getWorkFlow("WorkMode")
        workMode = flag
        alarmModel.setStartTime();
        var list = new Array
        qliantity = spliceModel.getTeachModeValue("TestCount","","")
        if (flag == 0) {
            spliceList = spliceModel.getStructValue("SpliceId","")
            showFlag = 3
            selectSplice(spliceModel.getStructValue("SpliceId",""))
            counterString = "SPLICE COUNTER:"
        }
        else if (flag == 2) {
            spliceList = partModel.getSpliceList(hmiAdaptor.getWorkFlow("WorkId"))
            if (partModel.getPartOnlineOrOffLine()) {
                showFlag = 1
                workName.anchors.bottom = progresstracking.bottom
                workName.anchors.bottomMargin = 0
                workName.anchors.left = progresstracking.right
                workName.anchors.leftMargin = 20
            } else {
                if (spliceList.length == 1) {
                    showFlag = 3
                } else {
                    showFlag = 2
                    progressBar.width = 550
                }
            }
            selectSplice(spliceList[0])
            counterString = "HARNESS COUNTER"
            workName.text = qsTr("Harness Name: ") + partModel.getPartName(hmiAdaptor.getWorkFlow("WorkId"))
        }
        else if (flag == 1) {
            progressBar.width = 550
            spliceList = sequenceModel.getSpliceList(hmiAdaptor.getWorkFlow("WorkId"))
            showFlag = 2
            operateDetail.maxCount = spliceList.length
            selectSplice(spliceList[0])
            counterString = "SEQUENCE COUNTER"
            workName.text = qsTr("Sequence Name: ") + sequenceModel.getSequenceName(hmiAdaptor.getWorkFlow("WorkId"))
        }

        hmiAdaptor.operateProcessExec("Start")








//        if (mainRoot.headTitle = qsTr("Operate Sequence"))
//        {
//            showFlag = 2
//        }
//        else if (mainRoot.headTitle = qsTr("Operate Harness"))
//            showFlag = 1


//        alarmModel.setStartTime();
//        var list = new Array
//        list =  workOrderModel.getSpliceList(selectIndx)
//        if (list.length > 0) {
//            loader.item.spliceList = workOrderModel.getSpliceList(selectIndx)
//            if (partModel.getPartOnlineOrOffLine()) {
//                loader.item.showFlag = 1
//            } else {
//                if (loader.item.spliceList.length == 1) {
//                    loader.item.showFlag = 3
//                } else {
//                    loader.item.showFlag = 2
//                }
//            }
//            loader.item.selectSplice(workOrderModel.getSpliceList(selectIndx)[0])
//            loader.item.qliantity = workOrderModel.getValue(selectIndx, "QUANTITY")
//        }
//        hmiAdaptor.operateProcessExec("Start")

//        hmiAdaptor.operateProcessExec("Start")
    }
    Component.onDestruction: {
        hmiAdaptor.operateProcessExec("Stop")
    }

    function setData()
    {
        if (workMode == 1 || workMode == 0)
            qualityWindow.partCount = progressBar2.value + 1
        else if (workMode == 2)
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
        console.log("selectSplice",spliceId)
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
        if (workMode == 1)
            qliantity = sequenceModel.getSpliceQty(spliceId)
        else if (workMode == 2 || workMode == 0)
            qliantity = hmiAdaptor.getWorkValue("WorkCount")
        hmiAdaptor.setOperateProcess(spliceId, false)
        hmiAdaptor.operateProcessExec("Execute")
    }

    onShowFlagChanged: {
        if (showFlag == 1) {
            spliceLocation.visible = true
            currentSplice.visible = true
        }
        else {
            spliceLocation.visible = false
            currentSplice.visible = false
        }
        if (showFlag == 2) {
            offline.visible = true
        }
        else {
            offline.visible = false
        }
        if (workMode == 1) {
            offline.visible = false
            completeMiss.visible = false
            editSplice.visible = true
            progressBar.anchors.left = operateDetail.left
            progressBar.anchors.leftMargin = 87
            progressBar.anchors.bottom = operateDetail.bottom
            progressBar.anchors.bottomMargin = 14
            workStation.visible = false
            workStation.anchors.bottomMargin = 50

            maintenance.anchors.left = progressBar3.left
            partCount2.anchors.left = progressBar2.left
            progressBar2.anchors.bottom = progressBar.top
            progressBar2.anchors.bottomMargin = 14
            progressBar3.anchors.bottom = progressBar2.bottom
            progressBar3.anchors.bottomMargin = 0
            progressBar3.anchors.left = progressBar2.right
            progressBar3.anchors.leftMargin = 16

            progressBar3.width = progressBar3.width / 2 - 8
            progressBar2.width = progressBar2.width / 2 - 8
            progressBar3.height = 10
            editCounter.visible = false

        }
        else if (workMode == 0) {
            progressBar3.anchors.left = progressBar2.left
            editSplice.visible = true
            editCounter.visible = true
        }
        else if (workMode == 2 && showFlag == 1) {
            completeMiss.visible = false
            editSplice.visible = true
            editSplice.anchors.right = completeMiss.right
            editSplice.anchors.bottom = completeMiss.bottom
            editSplice.width = editSplice.width - 30
            progressBar3.anchors.left = progressBar2.right
            progressBar3.anchors.leftMargin = 40
            maintenance.anchors.left = progressBar3.left

        }
        else if (workMode == 2 && showFlag == 2)
        {
//            completeMiss.visible = false
//            editSplice.visible = true
//            editSplice.anchors.right = completeMiss.right
//            editSplice.anchors.bottom = completeMiss.bottom
//            editSplice.width = editSplice.width - 30

            offline.visible = false
            completeMiss.visible = false
            editSplice.visible = true
            progressBar.anchors.left = operateDetail.left
            progressBar.anchors.leftMargin = 87
            progressBar.anchors.bottom = operateDetail.bottom
            progressBar.anchors.bottomMargin = 14

            workStation.visible = false
            workStation.anchors.bottomMargin = 50

            maintenance.anchors.left = progressBar3.left
            partCount2.anchors.left = progressBar2.left
            progressBar3.width = progressBar3.width / 2 - 8
            progressBar2.width = progressBar2.width / 2 - 8
            progressBar3.height = 10
            progressBar2.anchors.bottom = progressBar.top
            progressBar2.anchors.bottomMargin = 14
            progressBar3.anchors.bottom = progressBar2.bottom
            progressBar3.anchors.bottomMargin = 0
            progressBar3.anchors.left = progressBar2.right
            progressBar3.anchors.leftMargin = 16


            editCounter.visible = true
        }
        else if (workMode == 2 && showFlag == 3) {
            progressBar3.anchors.left = progressBar2.left
            editSplice.visible = true
            editCounter.visible = true
        }

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
        visible: false
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
        visible:  currentSplice.visible
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
        visible:   currentSplice.visible
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
        visible:   currentSplice.visible
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
        visible:   currentSplice.visible
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
        visible:   currentSplice.visible
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
        text: qsTr(counterString) + "0/" + qliantity
        color: "white"
        Connections {
            target: progressBar
            onCycleDone: {
                if (workMode == 2) {
                    cycleCount++
                    if (cycleCount > qliantity)
                        return
                    selectSplice(spliceList[0])
                    partCount2.text = qsTr(counterString) + cycleCount + "/" + qliantity;
                    progressBar2.value = cycleCount
                }
                else if (workMode == 1)
                {

                }
            }
        }
    }
    CProgressBar {
        id: progressBar2

        //        anchors.right: showFlag != 3 ? qualityWindow.right : spliceDetailsItem.right
        anchors.left: partCount2.left
        anchors.bottom: showFlag != 3 ? parent.bottom : maintenance.top
        anchors.bottomMargin: 20

        width: showFlag != 1 ? spliceDetailsItem.width : qualityWindow.width/2 - 20
        height: 10
        maximum: qliantity
        minimum: 0
        value: 0
    }
    Text {
        id: workName
        anchors.bottom: progresstracking.top
        anchors.bottomMargin: 20
        anchors.left: progresstracking.left
        font.pointSize: 16
        font.family: "arial"
        text: qsTr("Harness Name:")
        color: "white"
    }

    //single
    Text {
        id: progresstracking2
        anchors.top: offline.top
        anchors.topMargin: 45
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
        anchors.left: leftButton.left
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
        text: partModel.getPartOnlineOrOffLine() ? qsTr("Work Station: ") + spliceLocation.workStation : qsTr("HARNESS TASKS: ") + progressBar.current + "-" + progressBar.total
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
        text: qsTr("HARNESS TASKS: ") + progressBar.current + "-" + progressBar.total
        color: "white"
    }
    CButton {
        id: leftButton
        anchors.verticalCenter: progressBar.verticalCenter
//        anchors.left: qualityWindow.left
        anchors.right: progressBar.left
        anchors.rightMargin: 25
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
//        anchors.left: leftButton.right
//        anchors.leftMargin: 25
//        anchors.right: rightButton.left
//        anchors.rightMargin: 25
        anchors.left: qualityWindow.left
        anchors.leftMargin: 63
        anchors.bottom: partCount2.top
        anchors.bottomMargin: 4
        width: 455//Screen.width*0.4-150
        height: 64
        total: operateDetail.spliceList.length
        current: 1
        visible: showFlag != 3 ? true : false
    }
    CButton {
        id: rightButton
        anchors.verticalCenter: progressBar.verticalCenter
//        anchors.right: qualityWindow.right
        anchors.left: progressBar.right
        anchors.leftMargin: 25
        width: 41
        height: 63
        iconSource: "qrc:/images/images/right_operate.png"
        backgroundEnabled: false
        clip: true
        visible: showFlag != 3 ? true : false
        onClicked: {
            progressBar.current++
            if (operateDetail.cycleCount == operateDetail.qliantity) {
                cdialog.visible = true
                hmiAdaptor.operateProcessExec("Stop")
                return
            }
            progressBar.jumpToNext()
            selectSplice(spliceList[progressBar.current-1])
            spliceLocation.setTreeModelOver(progressBar.current)
            offline.setSatusOffLineOver(progressBar.current)
        }
    }
    Text {
        id: maintenance
        anchors.right: showFlag != 3 ? qualityWindow.right : spliceDetailsItem.right
        anchors.left: showFlag == 1 ? progressBar3.left : (showFlag == 2 ? qualityWindow.left : spliceDetailsItem.left)
//        horizontalAlignment: showFlag == 1 ? Qt.AlignRight : Qt.AlignLeft
        anchors.bottom: progressBar3.top
        anchors.bottomMargin: 6
        font.pointSize: 13
        font.family: "arial"
        text: qsTr("MAINTENANCE COUNTER") + hmiAdaptor.maintenanceCountGetValue(0,3) + "/" + hmiAdaptor.maintenanceCountGetValue(0,2)
        color: "white"
    }
    CProgressBar {
        id: progressBar3
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 20
        anchors.left: showFlag != 1 ? offline.left : qualityWindow.left
        width: showFlag == 1 ? qualityWindow.width/2-20 : (showFlag == 2 ? qualityWindow.width : spliceDetailsItem.width)
        height: 10
        maximum: hmiAdaptor.maintenanceCountGetValue(0,2)
        minimum: 0
        value: hmiAdaptor.maintenanceCountGetValue(0,3)
    }

    CButton {
        id: editCounter
        anchors.right: editSplice.left
        anchors.rightMargin: 24
        anchors.bottom: editSplice.bottom
//        anchors.bottomMargin: 40
        width: 200
        height: 60
        text: qsTr("EDIT COUNTER")
        textColor: "white"
        visible: false
        onClicked: {
            spliceCounterSetting.visible = true
        }
    }

    CButton {
        id: editSplice
        anchors.right: qualityWindow.right
        anchors.bottom: operateDetail.bottom
        anchors.bottomMargin: 14
        width: 200
        height: 60
        text: qsTr("EDIT SPLICE")
        textColor: "white"
        visible: false
        onClicked: {
            if (progressBar.current-1 < 0)
                operateToEdit(spliceList[0])
            else
                operateToEdit(spliceList[progressBar.current-1])
        }
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
                mainRoot.checkNeedPassWd(2)
        }
    }

    Item {
        id: spliceCounterSetting
        visible: false
        width: 540
        height: 435
        anchors.centerIn: parent
        property var bIsEdit: false
        Image {
            anchors.fill: parent
            source: "qrc:/images/images/dialogbg.png"
        }

        Text {
            id: settingTitle
            anchors.top: parent.top
            anchors.topMargin: 40
            anchors.left: parent.left
            anchors.leftMargin: 24
            text: qsTr("EDIT COUNTER")
            color: "white"
            font.pointSize: 20
            font.family: "arial"
            clip: true
        }

        Text {
            id: setting1
            text: qsTr("CurrentCycle:")
            color: "white"
            font.pointSize: 20
            font.family: "arial"
            anchors.top: settingTitle.bottom
            anchors.topMargin: 46
            anchors.left: parent.left
            anchors.leftMargin: 50
        }
        CButton {
            id: resetButton
            anchors.left: setting1.right
            anchors.leftMargin: 78
            anchors.verticalCenter: setting1.verticalCenter
            height: 50
            width: 180
            text: qsTr("Reset") + "(" + progressBar2.value + ")"
            textColor: "white"
            onClicked: {
                progressBar2.value = 0
                resetButton.text = qsTr("Reset") + "(" + progressBar2.value + ")"
            }
        }

        Text {
            id: setting2
            anchors.top: setting1.bottom
            anchors.topMargin: 46
            anchors.left: setting1.left
            text: qsTr("Batch Size")
            color: "white"
            font.pointSize: 20
            font.family: "arial"
            clip: true
        }

        Image {
            id: lineEdit
            anchors.left: resetButton.left
            anchors.verticalCenter: setting2.verticalCenter
            height: 50
            width: 180
            source: "qrc:/images/images/advancesetting-bg1.png"
            Rectangle {
                id: backGroundd
                width: parent.width
                height: parent.height-2
                border.color: "#0079c1"
                border.width: 2
                color: Qt.rgba(0,0,0,0)
            }
            Text {
                id: defalut
                anchors.fill: parent
                font.pixelSize: 24
                font.family: "arial"
                horizontalAlignment: Qt.AlignHCenter
                verticalAlignment: Qt.AlignVCenter
                color: "white"
                text: qliantity
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    spliceCounterSetting.bIsEdit = true
                    keyNum.visible = true
                    keyNum.currentValue = defalut.text
                    keyNum.maxvalue = 80
                    keyNum.minvalue = 0
                }
            }
        }

        Row {
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 20
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: 14
            CButton {
                id: advanceSet
                width: 210
                height: 60
                text: qsTr("CANCEL")
                textColor: "white"
                onClicked: {
                   spliceCounterSetting.visible = false
                }
            }
            CButton {
                id: start
                width: 210
                height: 60
                text: qsTr("OK")
                textColor: "white"
                onClicked: {
                    if (spliceCounterSetting.bIsEdit) {
                        progressBar2.maximum = defalut.text
                        operateDetail.qliantity = defalut.text
                        if (workMode == 1)
                        {
                            if (progressBar.current-1 < 0)
                                sequenceModel.reSetSpliceCount(spliceList[0],defalut.text)
                            else
                                sequenceModel.reSetSpliceCount(spliceList[progressBar.current-1],defalut.text)
                        }
                        spliceCounterSetting.bIsEdit = false
                    }
                    spliceCounterSetting.visible = false
                }
            }
        }


    }

    KeyBoardNum {
        id: keyNum
        anchors.centerIn: parent
        width: 962
        height: 526
        visible: false
        titleText: ""
        maxvalue: "4"
        minvalue: "1"
        currentValue: "4"
        onCurrentClickIndex: {
            if (index == 15) {
                if (hmiAdaptor.comepareCurrentValue(keyNum.minvalue,keyNum.maxvalue,keyNum.inputText)) {
                    if (keyNum.inputText != "") {
                        defalut.text = keyNum.inputText
                    }
//                    defalut.text = keyNum.inputText
                    keyNum.visible = false
                    keyNum.inputText = ""
                    keyNum.tempValue = ""
                } else {
                    keyNum.timeRun = true
                }
            } else if (index == 11) {
                keyNum.visible = false
                keyNum.inputText = ""
                keyNum.tempValue = ""
            }
        }
        onInputTextChanged: {
            if (keyNum.inputText != "") {
                defalut.text = keyNum.inputText
            }
        }
    }

}
