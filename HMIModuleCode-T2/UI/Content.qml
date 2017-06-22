/*******************************************************************
Copyright:http://www.sinux.com.cn
Date:2016/12/26
Author:zhangjiyong&lilongfei
Description: Part to create interface.data is from spliceModel&partModel
&colorModel&workModel
The function interface:
    selectSplice()
    partModel.getPartOnlineOrOffLine()
    partModel.setPartSpliceListClear()
    hmiAdaptor.comepareCurrentValue()
*******************************************************************/
import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import QtQuick.Window 2.2
import QtQuick.Controls 1.1
import QtQuick.Dialogs 1.2

Item {
    id: content
    width: Screen.width
    height: Screen.height

    property var selectSpliceId: -1
    property var qtyIndex: -1
    property int partId: -1
    property int spliceId: -1
    property bool bIsBasic: true
    property bool bIsDrag: false
    property bool bIsEdit: false
    property bool bIsBoard: true
    property bool bIsEditSplice: false
    property bool bIsFirst: false
    property bool bIsSequence: false
    property bool bIsHarness: false
    property bool bIsEditQty: false
    property string draColor: ""

    property variant arrayzone: ["A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P"]
    property variant arrayColor: ["#ff6699","#ff0033","#33FFCC","#cc99ff","#cc0099","#930202","#99ccff","#f79428",
        "#0000cc","Olive","#ffff33","#ffcc00","#cc9909","#66ff00","#009900","#00cc66","#3366ff","#cc33cc","#cc9966","#9400D3"]
    signal titleTextChanged(var myTitleText)

    Component.onCompleted: {
        if (mainRoot.initIndex == 1)
            initSequence()
        else if (mainRoot.initIndex == 0)
            initHarness()

        if (mainRoot.bIsEditHarness)
        {
            bIsEdit = true
            var editHarnessId = hmiAdaptor.getEditPartId();
            selectPartUpdataPage(editHarnessId,partModel.getPartName(editHarnessId))
            mainRoot.bIsEditHarness = false
        }
        else if (mainRoot.bIsEditSequence)
        {
            bIsEdit = true
            var editSequenceId = hmiAdaptor.getEditPartId();
            selectSequenceUpdataPage(editSequenceId,sequenceModel.getSequenceName(editSequenceId))
            mainRoot.bIsEditSequence = false
        }
    }

    Image {
        anchors.fill: parent
        source: "qrc:/images/images/bg.png"
    }

    Connections {
        target: mainRoot
        onSignalStackViewPop: {
            if (content.selectSpliceId != -1)
                content.selectSplice(content.selectSpliceId)

        }
    }

    function initSequence()
    {
        bIsSequence = true
        tabButton2.enabled = false
        tabButton2.textVisable = false
        tabButton1.tabbutton1text = qsTr("Sequence")
        workname.text = qsTr("Qty")
        edit6.defaultText = qsTr("Sequence Name")
        save.text = qsTr("SAVE SEQUENCE")
        upload.text = qsTr("EDIT EXISTING\nSEQUENCE")
        spliceList.bIsSequence = true
    }

    function initHarness()
    {
        bIsHarness = true
        tabButton1.tabbutton1text = qsTr("Splice")
        workname.text = qsTr("Zone/Workstation")
        edit6.defaultText = qsTr("Harness Name")
        save.text = qsTr("SAVE HARNESS")
        upload.text = qsTr("EDIT EXISTING\nHARNESS")
        spliceList.bIsSequence = false
    }

    function initEdit()
    {
        if (content.spliceId != -1)
        {
            bIsEditSplice = true
            spliceModel.editNew(content.spliceId)
            loader.source = "qrc:/UI/CreatWire.qml"
            loader.item.bIsFromLib = true
            titleTextChanged(qsTr("Edit Existing"))
        } else if (content.partId != -1) {
            var partName = partModel.getPartName(content.partId)
            selectPartUpdataPage(content.partId,partName)
        }
    }

    function selectSequenceUpdataPage(id,name)
    {
        hmiAdaptor.setEditPartId(id)
        sequenceModel.getSequenceInfo(true,id,name)
        edit6.inputText = name
        var nameList = new Array()
        nameList = sequenceModel.getCurrentSequenceOfSpliceName()
        var idList = new Array()
        idList = sequenceModel.getCurrentSequenceOfSpliceId()
        var qtyList = new Array()
        qtyList = sequenceModel.getCurrentSequenceOfSpliceQty()

        spliceList.listModel.clear()
        for (var i = 0; i < nameList.length; i++) {
            spliceList.listModel.append({"SpliceName":nameList[i],"stationColor":"white","station":"?","SpliceId":idList[i],"qty":qtyList[i]})
        }
    }


    function selectPartUpdataPage(id,name)
    {
        hmiAdaptor.setEditPartId(id)
        partModel.getPartInfo(true,id,name)
        edit1.inputText = partModel.getWorkStationCount()
        edit2.inputText = partModel.getWorkStationMaxSplicePerStation()
        edit3.inputText = partModel.getWorkStationRows()
        edit4.inputText = partModel.getWorkStationColumns()
        edit5.inputText = partModel.getWorkStationMaxSplicePerZone()
        edit6.inputText = name
        var corlorlist = new Array()
            corlorlist = partModel.getWorkStationCorlor()
        var zoneList = new Array()
        zoneList = partModel.geteWorkStationZone()
        var nameList = new Array()
        nameList = partModel.getCurrentPartOfSpliceName()
        var idList = new Array()
        idList = partModel.getCurrentPartOfSpliceId()
        spliceList.listModel.clear()
        for (var i = 0; i < nameList.length; i++) {
            if (corlorlist[i] == -1 || zoneList[i] == -1) {
                spliceList.listModel.append({"SpliceName":nameList[i],"stationColor":"white","station":"?","SpliceId":idList[i],"qty":0})
            } else {
                spliceList.listModel.append({"SpliceName":nameList[i],"stationColor":arrayColor[corlorlist[i]],"station":arrayzone[zoneList[i]],"SpliceId":idList[i],"qty":0})
            }
        }
        if (partModel.getPartOnlineOrOffLine())
            basicSwitch.state = "right"
        else
            basicSwitch.state = "left"

    }

    Connections {
        target: mainRoot
        onSignalSaveSplice: {
            if (bIsEdit) {
                content.selectSplice(content.selectSpliceId)
                for (var i = 0; i < listModel.count; i++) {
                    if (listModel.get(i).SpliceId == spliceId) {
                        listModel.set(i,{"SpliceName":spliceModel.getStructValue("SpliceName","")})
                    }
                }
            } else {
                spliceList.listModel.append({"SpliceName":spliceModel.getStructValue("SpliceName","") ,"stationColor":"white","station":"?","SpliceId":spliceId,"qty":0})
            }
            loader.source = ""
            if (bIsSequence)
                mainRoot.titleTextChanged("Create Sequence")
            else
                mainRoot.titleTextChanged("Create Harness")

        }
    }

    Connections {
        target: hmiAdaptor
        onSignalMovePart: {
            selectPartUpdataPage(id,name)
        }
        onSignalMoveSplice: {
            bIsEditSplice = true
            spliceModel.editNew(id)
            loader.source = "qrc:/UI/CreatWire.qml"
            loader.item.bIsFromLib = true
            titleTextChanged(qsTr("Edit Existing"))
        }
    }

    Connections {
        target: fileSelectLoader.item
        onSignalFileDialogCancel: {
            fileSelectLoader.source = ""
        }
        onSignalChoseFile: {
            fileSelectLoader.source = ""
            backGround.visible = true
            backGround.opacity = 0.7
            addExit.visible = true
            hmiAdaptor.importData(fileName)
        }
    }
    Loader {
        id: fileSelectLoader
        anchors.fill: parent
    }

    Loader {
        id: loader
        z: 10
        anchors.fill: parent
        onLoaded: {
            if (bIsEditSplice)
            {
                loader.item.bIsEditSplice = true
                var list = spliceModel.getWireIdList()
                loader.item.editSplice(list)
                bIsEditSplice = false
            }
            loader.item.firstComeIn = false
        }
    }
    ListModel{
        id: listModel
    }
    function unSelect()
    {
        content.selectSpliceId = -1
        insulation.visible = false
        spliceDetailsTips.visible = false
        spliceImage.source = "qrc:/images/images/bg.png"
    }

    function selectSplice(spliceId)
    {
        spliceModel.editNew(spliceId)
        var list = new Array
        list = spliceModel.getWireIdList()
        spliceDetailItem.clear()
        for (var i = 0; i < list.length;i++)
        {
            wireModel.addFromLibrary(list[i])
            spliceDetailItem.addWireFromSplice()
        }
        spliceImage.source = spliceModel.getStructValue("PicPath","") == " " ? "qrc:/images/images/bg.png" : spliceModel.getStructValue("PicPath","")

        var shrinkId = spliceModel.getStructValue("ShrinkId","");
        var shrinkTemp = spliceModel.getStructValue("ShrinkTemp","")
        var shrinkTime = spliceModel.getStructValue("ShrinkTime","")

        insulation.visible = spliceModel.getStructValue("Insulation","") == "left" ? true : false;
        spliceDetailsTips.visible = true
        insulation.text = qsTr("  Insulation: ") + shrinkId + qsTr(" Temp:") + shrinkTemp + qsTr(" Time:") + shrinkTime

        spliceDetailsTips.text = qsTr("TOTAL CROSS SECTION ") + spliceModel.getStructValue("Cross Section","")
    }

    SwipeView {
        width: Screen.width * 0.3
        height: parent.height
        id: swipeView
        currentIndex: tabBar.currentIndex
        Page {
            id: splice
            z: 10
            Rectangle {
                anchors.fill: parent
                color: "#052a40"
            }
            Label {
                id: listname
                anchors.top: parent.top
                anchors.topMargin: tabBar.height+10
                anchors.left: parent.left
                horizontalAlignment: Qt.AlignHCenter
                height: 20
                width: parent.width/2
                clip: true
                font.pointSize: 13
                font.family: "arial"
                text: qsTr("Splice")
                color: "white"
            }
            Label {
                id: workname
                anchors.top: parent.top
                anchors.topMargin: tabBar.height+10
                anchors.left: listname.right
                horizontalAlignment: Qt.AlignHCenter
                height: 20
                width: parent.width/2
                clip: true
                font.pointSize: 13
                font.family: "arial"
                text: qsTr("Zone/Workstation")
                color: "white"
            }
            Rectangle {
                id: tipsRec
                anchors.top: workname.bottom
                anchors.topMargin: 4
                anchors.left: parent.left
                anchors.leftMargin: 10
                width: parent.width -20
                height: 1
                color: "#375566"
            }
            SpliceListView {
                id: spliceList
                listModel: listModel
                anchors.top: tipsRec.bottom
                anchors.topMargin: 6
                anchors.bottom: tipsRec2.top
                bIsWorkShow: !bIsBasic
                z: 10

                onCurrentSelecte: {
                    if (index != -1) {
                        content.selectSpliceId = listModel.get(index).SpliceId
                        content.selectSplice(content.selectSpliceId)
                    }
                    else {
                        content.unSelect()
                        content.selectSpliceId = -1
                    }
                }
                onCurrentWorkStation: {
                    stationSet.index = index
                    stationSet.visible = true
                    backGround2.visible = true
                    backGround2.opacity = 0.5
                }
            }
            Rectangle {
                id: tipsRec2
                anchors.bottom: addNewSplice.top
                anchors.bottomMargin: 5
                anchors.left: parent.left
                anchors.leftMargin: 10
                width: parent.width -20
                height: 1
                color: "#375566"
            }
            CButton {
                id: addNewSplice
                anchors.bottom: addExitSplice.top
                anchors.left: parent.left
                anchors.leftMargin: 10
                text: qsTr("+ ADD NEW SPLICE")
                textColor: "white"
                width: parent.width - 20
                pointSize: 16
                onClicked: {
                    spliceModel.createNew()
//                    loader.source = "qrc:/UI/CreatWire.qml"
                    mainRoot.checkNeedPassWd(-1)
//                    titleTextChanged("Create Splice")
                }
            }
            CButton {
                id: addExitSplice
                anchors.bottom: upload.top
                anchors.left: parent.left
                anchors.leftMargin: 10
                text: qsTr("+ ADD EXISTING SPLICE")
                textColor: "white"
                width: parent.width - 20
                pointSize: 16
                onClicked: {
                    backGround.visible = true
                    backGround.opacity = 0.7
                    addExit.visible = true
                    addExit.listModel = null
                    addExit.listModel = spliceModel

                    addExit.titleName = qsTr("Add Existing Splice")
                    addExit.componentName = qsTr("SPLICE NAME")
                    addExit.componentData = qsTr("DATE CREATED")
                    addExit.componentMiddle = qsTr("OperatorName")
                    addExit.componenttype = qsTr("CROSS SECTION")
                    addExit.bIsOnlyOne = false
                    addExit.componentCount = qsTr("# OF WIRES")
                }
            }
            CButton {
                id: upload
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 5
                anchors.left: parent.left
                anchors.leftMargin: 10
                text: qsTr("IMPORT SPLICE")
                textColor: "white"
                width: (parent.width-20) / 2 - 12
                pointSize: 16
                onClicked: {
                    backGround.visible = true
                    backGround.opacity = 0.7
                    addExit.visible = true
                    if (upload.text == qsTr("EDIT EXISTING\nHARNESS"))
                    {
                        addExit.listModel = partModel
                        addExit.titleName = qsTr("Add Harness")
                        addExit.componentName = qsTr("Harness Name")
                        addExit.componentData = qsTr("Date Created")
                        addExit.componentMiddle = qsTr("Total Steps")
                        addExit.componenttype = qsTr("Process Mode")
                        addExit.bIsOnlyOne = true
                        addExit.componentCount = "Of WorkStation"

//                        addExit.componentCount = "MaxSplicesPerZone"
                    }
                    else if (upload.text == qsTr("EDIT EXISTING\nSEQUENCE"))
                    {
                        addExit.listModel = sequenceModel
                        addExit.titleName = qsTr("Add Sequence")
                        addExit.componentName = qsTr("Sequence Name")
                        addExit.componentData = qsTr("Date Created")
                        addExit.componentMiddle = qsTr("User Name")
                        addExit.componenttype = qsTr("Total Steps")
                        addExit.bIsOnlyOne = true
                        addExit.componentCount = "Total Splices"
                    }

//                    fileSelectLoader.source = "qrc:/UI/MySelectFileDialog.qml"
                }
            }

            CButton {
                id: save
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 5
                anchors.right: parent.right
                anchors.rightMargin: 10
                text: qsTr("SAVE PART")
                textColor: "white"
                width: (parent.width-20) / 2 - 12
                pointSize: 16
                onClicked: {
                    if (edit6.inputText.length == 0) {
                        dialog.visible = true
                        backGround.visible = true
                        backGround.opacity = 0.5
                    } else {
                        if (bIsHarness)
                        {
                            if (partModel.getPartOnlineOrOffLine()) {
                                for (var i = 0; i < listModel.count; i++) {
                                    if (listModel.get(i).station == "?") {
                                        mainRoot.showDialog(true,false,qsTr("OK"),"","","",qsTr("Please Set WorkStation!"))
                                        return
                                    }
                                }
                            }
                            partModel.setPartSpliceListClear()
                            for (var i = 0; i < listModel.count; i++) {
                                partModel.setPartSpliceList(listModel.get(i).SpliceName,listModel.get(i).SpliceId,arrayColor.indexOf(listModel.get(i).stationColor),arrayzone.indexOf(listModel.get(i).station),i+1)
                            }
                            partModel.savePartInfo(content.bIsEdit, hmiAdaptor.getCurrentOperatorId())
                            mainRoot.popStackView()
                        }
                        else if (bIsSequence)
                        {
                            sequenceModel.sequenceSpliceListClear()
                            for (var i = 0; i < listModel.count; i++) {
                                sequenceModel.setSpliceData(i,listModel.get(i).SpliceId,listModel.get(i).SpliceName,listModel.get(i).qty)
                            }
                            if (bIsEdit)
                                sequenceModel.updateRecordIntoTable(hmiAdaptor.getEditPartId(),edit6.inputText, hmiAdaptor.getCurrentOperatorId())
                            else
                                sequenceModel.insertRecordIntoTable(edit6.inputText, hmiAdaptor.getCurrentOperatorId())

                            mainRoot.popStackView()
                        }
                    }
                }
            }
        }

        Page {
            id: settting
            z: 9

            Rectangle {
                anchors.fill: parent
                color: "#052a40"
            }
            Label {
                id: processMode
                anchors.top: parent.top
                anchors.topMargin: tabBar.height+12
                anchors.left: parent.left
                anchors.leftMargin: 10
                color: "#8295a0"
                text: qsTr("PROCESS MODE")
                font.family: "arial"
                font.pointSize: 16
            }
            // default right is on, left is off
            Switch2 {
                id: basicSwitch
                anchors.top: processMode.bottom
                anchors.topMargin: 12
                anchors.left: parent.left
                anchors.leftMargin: 10
                width: parent.width * 0.6
                textLeft: qsTr("Basic")
                textRight: qsTr("Adv")
                state: partModel.getPartOnlineOrOffLine() ? "right" : "left"
                opacity: 0.8
                clip: true
                onOnChanged: {
                    if (basicSwitch.state == "left") {
                        borderSwitch.state = "right"
                        borderSwitch.visible = false
                        bIsBasic = true
                        partModel.setPartOffLineOrOnLine(false)
                    } else {
                        borderSwitch.state = "left"
                        borderSwitch.visible = true
                        bIsBasic = false
                        partModel.setPartOffLineOrOnLine(true)
                        workStationcolor.getAllWorkstationColor(partModel.getWorkStationCount())
                        for (var i = 0; i < listModel.count; i++) {
                            boardlayout.setBoardLayoutColor(true,arrayzone.indexOf(listModel.get(i).station),listModel.get(i).stationColor,i+1)
                            workStationcolor.setCurrentStationSPliceCountInit(listModel.get(i).stationColor,partModel.getWorkStationCount())
                        }
                    }
                }
                Component.onCompleted: {
                    if (basicSwitch.state == "left") {
                        borderSwitch.visible = false
                        borderSwitch.state = "right"
                    } else {
                        borderSwitch.state = "left"
                        borderSwitch.visible = true
                    }
                }
            }
            Label {
                id: lab1
                color: "#8295a0"
                visible: !bIsBasic
                anchors.top: basicSwitch.bottom
                anchors.topMargin: 24
                anchors.left: parent.left
                anchors.leftMargin: 10
                text: qsTr("WORKSTATIONS")
                font.family: "arial"
                font.pointSize: 16
            }

            MiniKeyNumInput {
                id: edit1
                visible: !bIsBasic
                anchors.top: lab1.bottom
                anchors.topMargin: 12
                anchors.left: parent.left
                anchors.leftMargin: 10
                width: parent.width-20
                height: 50
                inputWidth: edit1.width/3
                opacity: 0.7
                tipsText: qsTr("#of Workstations")
                inputText: partModel.getWorkStationCount()
                onInputFocusChanged: {
                    if (edit1.inputFocus) {
                        backGround.visible = true
                        backGround.opacity = 0.5
                        keyNum.visible = true
                        keyNum.titleText = edit1.tipsText
                        keyNum.currentValue = "0"
                        keyNum.minvalue = "1"
                        keyNum.maxvalue = "20"
                    }
                }
                onInputTextChanged: {
                    partModel.setPartWorkStationNum(edit1.inputText)
                    workStationcolor.getAllWorkstationColor(edit1.inputText)
                    workStationcolor.clearCurrentStationCount(edit1.inputText)
                    workStationcolor.allWorkTotal = edit1.inputText
                    for (var i = 0; i < listModel.count; i++) {
                        listModel.set(i,{"station":"?","stationColor":"white"})
                    }
                    boardlayout.clearBoardLayout()
                }
            }
            MiniKeyNumInput {
                id: edit2
                visible: !bIsBasic
                anchors.top: edit1.bottom
                anchors.topMargin: 12
                anchors.left: parent.left
                anchors.leftMargin: 10
                width: parent.width-20
                height: 50
                inputWidth: edit2.width/3
                tipsText: qsTr("Max Splices per Workstations")
//                regExp: RegExpValidator{regExp: /([1-9]|1[0-9]|20)/}
                opacity: 0.7
                inputText: partModel.getWorkStationMaxSplicePerStation()
                onInputFocusChanged: {
                    if (edit2.inputFocus) {
                        backGround.visible = true
                        backGround.opacity = 0.5
                        keyNum.visible = true
                        keyNum.titleText = edit2.tipsText
                        keyNum.currentValue = "0"
                        keyNum.minvalue = "1"
                        keyNum.maxvalue = "20"
                    }
                }
                onInputTextChanged: {
                    partModel.setPartMaxSplicePerWorkStation(edit2.inputText)
                    workStationcolor.maxSpliceNum = edit2.inputText
                    boardlayout.reSetBoardLayoutColor(edit2.inputText,edit1.inputText)
                }
            }
            Label {
                id: lab2
                visible: !bIsBasic
                anchors.top: edit2.bottom
                anchors.topMargin: 6
                anchors.left: parent.left
                anchors.leftMargin: 10
                color: "#8295a0"
                text: qsTr("BOARD LAYOUT")
                font.family: "arial"
                font.pointSize: 16
            }
            MiniKeyNumInput {
                id: edit3
                visible: !bIsBasic
                anchors.top: lab2.bottom
                anchors.topMargin: 12
                anchors.left: parent.left
                anchors.leftMargin: 10
                width: (parent.width-30) / 2
                height: 50
                inputWidth: edit3.width/2
                tipsText: qsTr("Rows")
//                regExp: RegExpValidator{regExp: /^[1-4]{1}$/}
                opacity: 0.7
                inputText: partModel.getWorkStationRows()
                onInputFocusChanged: {
                    if (edit3.inputFocus) {
                        backGround.visible = true
                        backGround.opacity = 0.5
                        keyNum.visible = true
                        keyNum.titleText = edit3.tipsText
                        keyNum.currentValue = "0"
                        keyNum.minvalue = "1"
                        keyNum.maxvalue = "4"
                    }
                }
                onInputTextChanged: {
                    partModel.setPartRows(edit3.inputText)
                    boardlayout.rows = edit3.inputText
                    for (var i = 0; i < listModel.count; i++) {
                        listModel.set(i,{"station":"?","stationColor":"white"})
                    }
                    workStationcolor.getAllWorkstationColor(edit1.inputText)
                    workStationcolor.clearCurrentStationCount(edit1.inputText)
//                    for (var i = 0; i< workModel.count; i++) {
//                        workModel.get(i).workStation.destroy()
//                    }
//                    workModel.clear()
                }
            }

            MiniKeyNumInput {
                id: edit4
                visible: !bIsBasic
                anchors.top: lab2.bottom
                anchors.topMargin: 12
                anchors.left: edit3.right
                anchors.leftMargin: 10
                width: (parent.width-30)/2
                height: 50
                inputWidth: edit4.width/2
                tipsText: qsTr("Columns")
                opacity: 0.7
                inputText: partModel.getWorkStationColumns()
                onInputFocusChanged: {
                    if (edit4.inputFocus) {
                        backGround.visible = true
                        backGround.opacity = 0.5
                        keyNum.visible = true
                        keyNum.titleText = edit4.tipsText
                        keyNum.currentValue = "0"
                        keyNum.minvalue = "1"
                        keyNum.maxvalue = "4"
                    }
                }
                onInputTextChanged: {
                    partModel.setPartColumns(edit4.inputText)
                    boardlayout.columns = edit4.inputText
                    for (var i = 0; i < listModel.count; i++) {
                        listModel.set(i,{"station":"?","stationColor":"white"})
                    }
                    workStationcolor.getAllWorkstationColor(edit1.inputText)
                    workStationcolor.clearCurrentStationCount(edit1.inputText)
                }
            }
            MiniKeyNumInput {
                id: edit5
                visible: !bIsBasic
                anchors.top: edit4.bottom
                anchors.topMargin: 12
                anchors.left: parent.left
                anchors.leftMargin: 10
                width: parent.width-20
                height: 50
                inputWidth: edit5.width/3
                tipsText: qsTr("Max Splice Per Zone")
                opacity: 0.7
                inputText: partModel.getWorkStationMaxSplicePerZone()
                onInputFocusChanged: {
                    if (edit5.inputFocus) {
                        backGround.visible = true
                        backGround.opacity = 0.5
                        keyNum.visible = true
                        keyNum.titleText = edit5.tipsText
                        keyNum.currentValue = "0"
                        keyNum.minvalue = "1"
                        keyNum.maxvalue = "12"
                    }
                }
                onInputTextChanged: {
                    partModel.setPartMaxSplicePerZone(edit5.inputText)
                    boardlayout.reSetBoardLayoutStation(edit5.inputText)
                }
            }
        }
    }
    TabBar {        
        width: Screen.width * 0.3
        id: tabBar
        currentIndex: swipeView.currentIndex
        anchors.top: parent.top
        anchors.leftMargin: 10
        height: Screen.height * 0.08
        spacing: 0
        TabButton {
            id: tabButton1
            property alias tabbutton1text: tabbutton1Text.text
            height: parent.height
            Rectangle {
                anchors.fill: parent
                color:  "#052a40"  //tabBar.currentIndex == 0 ? "black" : "#48484a"
            }
            Text {
                id: tabbutton1Text
                anchors.centerIn: parent
                font.family: "arial"
                font.pointSize: 17.5
                text: qsTr("SPLICE")
                color: tabBar.currentIndex == 0 ? "white" : "#969ea5"
            }
            Rectangle {
                anchors.left: parent.left
                anchors.leftMargin: 10
                width: parent.width - 10
                height: 6
                color:  "#F79428"
                anchors.bottom: parent.bottom
                visible: tabBar.currentIndex == 0 ? true : false
            }
        }
        TabButton {
            id: tabButton2
            height: parent.height
            property alias textVisable: tabbutton2text.visible
            Rectangle {
                anchors.fill: parent
                color:  "#052a40"
            }
            Text {
                id: tabbutton2text
                anchors.centerIn: parent
                font.family: "arial"
                font.pointSize: 17.5
                text: qsTr("SETTINGS")
                color: tabBar.currentIndex == 1 ? "white" : "#969ea5"
            }
            Rectangle {
                width: parent.width-10
                height: 6
                color:  "#F79428"
                anchors.bottom: parent.bottom
                visible: tabBar.currentIndex == 1 ? true : false
            }
        }
    }

    Item {
        id: rightArea
        anchors.left: swipeView.right
        //width: Screen.width * 0.7
        anchors.right: parent.right
        height: parent.height
        MouseArea {
            anchors.fill: parent
        }
        ListModel {
            id: colorModel
        }
        ListModel {
            id: workModel
        }
        Image {
            anchors.fill: parent
            source: "qrc:/images/images/bg.png"
        }
        MyLineEdit {
            id: edit6
            anchors.top: parent.top
            anchors.topMargin: 4
            anchors.left: boardlayout.left
            width: boardlayout.width*0.65
            height: 43
            inputWidth: boardlayout.width*0.65
            inputHeight: 40
//            horizontalAlignment: Qt.AlignHCenter
            defaultText: qsTr("PART NAME")
            //regExp: RegExpValidator{regExp: /^[1-9]{1,2}$/}
            maxSize: 60
            clip: true
            onTextChange: {
                if (template.text != "Template") {
                    partModel.setPartName(edit6.inputText + template.text)
                } else {
                    partModel.setPartName(edit6.inputText)
                }
            }
        }
        Rectangle {
            id: template
            property alias text: name.text
            anchors.top: parent.top
            anchors.topMargin: 4
            anchors.right: boardlayout.right
            width: parent.width*0.26
            color: "#052a40"
            height: 43
            visible: false
            Text {
                id: name
                anchors.left: parent.left
                anchors.leftMargin: 10
                width: parent.width-40
                anchors.verticalCenter: parent.verticalCenter
                horizontalAlignment: Qt.AlignHCenter
                clip: true
                elide: Text.ElideRight
                text: qsTr("Template")
                font.family: "arial"
                font.pixelSize: 27
                color: "#969ea5"
                onTextChanged: {
                    partModel.setPartName(edit6.inputText + name.text)
                }
            }
            Image {
                anchors.left: name.right
                anchors.verticalCenter: parent.verticalCenter
                source: "qrc:/images/images/down.png"
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    backGround.visible = true
                    backGround.opacity = 0.5
                    template2.visible = true
                }
            }
        }
        Text {
            id: boardText
            anchors.top: edit6.bottom
            anchors.topMargin: 24
            anchors.left: boardlayout.left
            color: "white"
            opacity: 0.5
            width: 100
            font.family: "arial"
            font.pointSize: 16
            visible: !bIsBasic
            text: qsTr("Board Layout")
        }
        Switch2 {
            id: borderSwitch
            anchors.top: edit6.bottom
            anchors.topMargin: 10
            anchors.left: parent.left
            anchors.leftMargin: 20
            textLeft: qsTr("Board")
            textRight: qsTr("Splice")
            state: "left"
            width: parent.width * 0.25
            onStateChanged: {
                if (state == "left")
                    bIsBoard = true
                else if (state == "right")
                    bIsBoard = false
            }
        }
        Switch2 {
            id: wireSwitch
            anchors.top: edit6.bottom
            anchors.topMargin: 10
            anchors.right: parent.right
            anchors.rightMargin: 20
            textLeft: qsTr("Wire")
            textRight: qsTr("Image")
            state: "left"
            width: parent.width * 0.25
            visible: !bIsBoard
        }

        Label {
            id: spliceDetailsTips
            anchors.top: borderSwitch.bottom
            anchors.topMargin: 10
            anchors.left: parent.left
            anchors.leftMargin: 20
            text: qsTr("TOTAL CROSS SECTION ")
            font.pointSize: 12
            font.family: "arial"
            color: "white"
            opacity: 0.5
        }

        Text {
            id: insulation
            anchors.top: borderSwitch.bottom
            anchors.topMargin: 10
            anchors.left: spliceDetailsTips.right
            font.pointSize: 12
            font.family: "arial"
            color: "white"
            opacity: 0.5
        }

        SpliceDetails {
            id: spliceDetailItem
            anchors.top: spliceDetailsTips.bottom
            anchors.topMargin: 10
            anchors.left: parent.left
            anchors.leftMargin: 20
            anchors.right: parent.right
            anchors.rightMargin: 20
            anchors.bottom: editSplice.top
            anchors.bottomMargin: 10
            visible: !bIsBoard
            centerVisable: false
            Component.onCompleted: {
            }
        }

        Item {
            id: selectImage
            visible: wireSwitch.state == "left" ? false : true
            anchors.fill: spliceDetailItem
            onVisibleChanged: {
                if (visible)
                    spliceImage.source = spliceModel.getStructValue("PicPath","") == " " ? "qrc:/images/images/bg.png" : spliceModel.getStructValue("PicPath","")
            }

            Image {
                id: spliceImage
                anchors.fill: parent
            }
        }
        Loader {
            id: imageLoader
            anchors.fill: parent
        }

        BoardLayOut {
            id: boardlayout
            anchors.top: boardText.bottom
            anchors.topMargin: 10
            anchors.left: parent.left
            anchors.leftMargin: 20
            anchors.right: parent.right
            anchors.rightMargin: 20
            anchors.bottom: editSplice.top
            anchors.bottomMargin: 10
            visible: bIsBoard
            columns: 0
            rows: 0
            maxSplicePerWork: edit2.inputText
            maxSplicePerZone: edit5.inputText
            onSpliceModelUpdata: {
                listModel.set(index-1,{"stationColor":"white","station":"?"})
                workStationcolor.setCurrentStationSPliceCount(false,color)
            }
        }

//        Component {
//            id: dragColor
//            Rectangle {
//                id: dragItem
//                width: 35
//                height: 35
//                radius: 35
//                border.color: "white"
//                border.width: 1
//                Drag.active: dragArea.drag.active
//                Drag.supportedActions: Qt.MoveAction
//                Drag.dragType: Drag.Internal
//                Drag.mimeData: {"color": color, "width": width, "height": height};
//                MouseArea {
//                    id: dragArea;
//                    anchors.fill: parent
//                    drag.target: parent
//                    drag.minimumX: 0
//                    drag.maximumX: boardlayout.width-35
//                    drag.minimumY: 0
//                    drag.maximumY: boardlayout.height-35
//                    onPositionChanged: {
//                        draColor = dragItem.color
//                        bIsDrag = true
//                    }
//                    onReleased: {
//                        bIsDrag = false
//                    }
//                }
//            }
//        }

//        DropArea {
//            id: dropContainer;
//            property bool bFollow: followArea.visible
//            anchors.top: boardText.bottom
//            anchors.topMargin: 6
//            anchors.left: parent.left
//            anchors.leftMargin: 50
//            width: boardlayout.width-35
//            height: boardlayout.height-35
//            onEntered: {
//                drag.accepted = true;
//                if (!bIsDrag) {
//                    followArea.visible = false
//                    followArea.color = drag.getDataAsString("color");
//                } else {
//                    followArea.color = draColor
//                }
//            }
//            onPositionChanged: {
//                drag.accepted = true;
//                followArea.visible = true
//                followArea.x = drag.x
//                followArea.y = drag.y
//            }
//            onDropped: {
//                if(drop.supportedActions == Qt.CopyAction){
//                    var component =  dragColor.createObject(boardlayout,{
//                                                          "x": drop.x,
//                                                          "y": drop.y,
//                                                          "width": parseInt(drop.getDataAsString("width")),
//                                                          "height": parseInt(drop.getDataAsString("height")),
//                                                          "color": drop.getDataAsString("color"),
//                                                          "Drag.supportedActions": Qt.MoveAction,
//                                                          "Drag.dragType": Drag.Internal
//                                                      });
//                    workModel.append({"workStation":component})
//                    followArea.visible = false
//                }
//                drop.acceptProposedAction();
//                drop.accepted = true;
//            }
//            Rectangle {
//                id: followArea
//                radius: 35
//                width: 35
//                height: 35
//                border.color: "white"
//                border.width: 1
//                visible: parent.containsDrag
//                onVisibleChanged: {
////                    console.log("aaaaaaaaa",followArea.visible)
//                }
//            }
//        }
        CButton {
            id: editSplice
            anchors.bottom: bIsBoard ? testSplice.top : parent.bottom
            anchors.bottomMargin: 14
            anchors.right: bIsBoard ? boardlayout.right : testSplice.left
            anchors.rightMargin: bIsBoard ? 0 : 14
            text: qsTr("EDIT SPLICE")
            textColor: "white"
            width: 250
            pointSize: 16
            onClicked: {
                if (content.selectSpliceId != -1)
                {
                    mainRoot.bIsEditSplice = true
                    spliceModel.editNew(content.selectSpliceId)
                    mainRoot.checkNeedPassWd(-1)
//                    loader.source = "qrc:/UI/CreatWire.qml"
                    mainRoot.titleTextChanged(qsTr("Edit Splice"))
                }

            }

        }

        CButton {
            id: testSplice
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 14
            anchors.right: boardlayout.right
            text: qsTr("DELETE SPLICE")
            textColor: "white"
            width: 250
            pointSize: 16
            onClicked: {
                if (content.selectSpliceId != -1)
                {
                    spliceList.deleteSplice()
//                    hmiAdaptor.setTestSpliceId(selectSpliceId)
//                    mainRoot.checkNeedPassWd(3)
                }
            }
        }
        Text {
            id: workStation
            anchors.top: boardlayout.bottom
            anchors.topMargin: 5
            anchors.left: boardlayout.left
            visible:  bIsBoard
            text: qsTr("WORKSTATIONS")
            color: "white"
            opacity: 0.5
            font.family: "arial"
            font.pointSize: 16
        }

        WorkStationColor {
            id: workStationcolor
            visible: bIsBoard
            anchors.top: workStation.bottom
            anchors.left: boardlayout.left
            allWorkTotal: 0
            maxSpliceNum: 0
            onLeftClick: {
                var count = 0
                for (var i = 0; i < listModel.count; i++) {
                    if (listModel.get(i).stationColor == color) {
                        ++count
                    }
                }
                workStationcolor.leftClickSetCurrentStationSPliceCount(index,count)
            }
            onRightClick: {
                var count = 0
                for (var i = 0; i < listModel.count; i++) {
                    if (listModel.get(i).stationColor == color) {
                        ++count
                    }
                }
                workStationcolor.rightClickSetCurrentStationSpliceCount(index,count)
            }
        }
    }
    Rectangle {
        id: backGround
        anchors.fill: parent
        color: "black"
        opacity: 0.7
        visible: false //content.bIsEdit ? true : false
        MouseArea {
            anchors.fill: parent
            onClicked: {
                if (templateModel.count == 0 && template2.visible && temPlateDialog.visible == false) {
                    backGround.visible = false
                    backGround.opacity = 0
                    template2.visible = false
                }
            }
        }
    }
    Image {
        id: dialog
        anchors.centerIn: parent
        width: 639
        height: 390
        visible: false
        source: "qrc:/images/images/dialogbg.png"
        Text {
            anchors.centerIn: parent
            anchors.verticalCenterOffset: -30
            font.family: "arial"
            font.pixelSize: 24
            color: "white"
            text: bIsSequence == true ? qsTr("Please Input Sequence Name") : qsTr("Please Input Harness Name")
        }

        CButton {
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 15
            anchors.horizontalCenter: parent.horizontalCenter
            width: parent.width/3
            iconSource: "qrc:/images/images/OK.png"
            text: qsTr("OK")
            onClicked: {
                dialog.visible = false
                backGround.visible = false
                backGround.opacity = 0
            }
        }
    }

    Rectangle {
        id: backGround2
        anchors.fill: parent
        color: "black"
        visible: false
        opacity: 0
        MouseArea {
            anchors.fill: parent
            onClicked: {
                backGround2.visible = false
                backGround2.opacity = 0
                stationSet.visible = false
                stationSet.selecteColor = ""
                stationSet.selecteZone = ""
                var station = listModel.get(stationSet.index).station
                var stationColor = listModel.get(stationSet.index).stationColor
                if (station == "?" && stationColor != "white") {
                    listModel.set(stationSet.index,{"stationColor":"white"})
                } else if (station != "?" && stationColor == "white") {
                    listModel.set(stationSet.index,{"station":"?"})
                }
            }
        }
    }
    WorkStationSet {
        id: stationSet
        anchors.centerIn: parent
        width: 560
        height: 280
        allWorkTotal: workStationcolor.allWorkTotal
        allZoneTotal: boardlayout.columns*boardlayout.rows
        visible: false
        onSelecteZoneChanged: {
            if (stationSet.selecteZone == "") {
                return
            }
            if (stationSet.selecteColor != "") {
                var reslut
                if (listModel.get(stationSet.index).station == "?") {
                    reslut = boardlayout.setBoardLayoutColor(true,stationSet.selecteIndex,stationSet.selecteColor,stationSet.index+1)
                    if (reslut != -1) {
                        workStationcolor.setCurrentStationSPliceCount(true,stationSet.selecteColor)
                    }
                } else {
                    reslut = boardlayout.setBoardLayoutColor(false,stationSet.selecteIndex,stationSet.selecteColor,stationSet.index+1)
                    if (reslut != -1) {
                        workStationcolor.setCurrentStationSPliceCount(false,listModel.get(stationSet.index).stationColor)
                        workStationcolor.setCurrentStationSPliceCount(true,stationSet.selecteColor)
                    }
                }
                if (reslut != -1) {
                    listModel.set(stationSet.index,{"stationColor":stationSet.selecteColor,"station":stationSet.selecteZone})
                } else {
                    if (listModel.get(stationSet.index).station == "?") {
                        listModel.set(stationSet.index,{"stationColor":"white","station":"?"})
                    }
                }
                stationSet.visible = false
                stationSet.selecteColor = ""
                stationSet.selecteZone = ""
                backGround2.visible = false
                backGround2.opacity = 0
            }

        }
        onSelecteColorChanged: {
            if (stationSet.selecteColor == "") {
                return
            }
            if (stationSet.selecteZone != "") {
                var reslut
                if (listModel.get(stationSet.index).station == "?") {
                    reslut = boardlayout.setBoardLayoutColor(true,stationSet.selecteIndex,stationSet.selecteColor,stationSet.index+1)
                    if (reslut != -1) {
                        workStationcolor.setCurrentStationSPliceCount(true,stationSet.selecteColor)
                    }
                } else {
                    reslut = boardlayout.setBoardLayoutColor(false,stationSet.selecteIndex,stationSet.selecteColor,stationSet.index+1)
                    if (reslut != -1) {
                        workStationcolor.setCurrentStationSPliceCount(false,listModel.get(stationSet.index).stationColor)
                        workStationcolor.setCurrentStationSPliceCount(true,stationSet.selecteColor)
                    }
                }
                if (reslut != -1) {
                    listModel.set(stationSet.index,{"stationColor":stationSet.selecteColor,"station":stationSet.selecteZone})
                } else {
                    if (listModel.get(stationSet.index).station == "?") {
                        listModel.set(stationSet.index,{"stationColor":"white","station":"?"})
                    }
                }
                stationSet.visible = false
                stationSet.selecteColor = ""
                stationSet.selecteZone = ""
                backGround2.visible = false
                backGround2.opacity = 0
            }
        }
    }
    AddExistingSpliceWire {
        id: addExit
        anchors.centerIn: parent
        width: parent.width*0.9
        height: parent.width*0.4
        visible: content.bIsFirst ? true : false
        listModel: content.bIsFirst ? partModel : spliceModel
        titleName: content.bIsFirst ? qsTr("Add Harness") : qsTr("Add Existing Splice")
        componentName: content.bIsFirst ? qsTr("Part Name") : qsTr("Splice Name")
        componentData: qsTr("Date Created")
        componentMiddle: content.bIsFirst ? qsTr("# OF SPLICE") : qsTr("User Name")
        componenttype: qsTr("Cross Section")
        bIsOnlyOne: (addExit.listModel == partModel) ? true : false
        componentCount: content.bIsFirst ? "" : qsTr("Total Wires")
        onSignalAddExistCancel: {
            backGround.visible = false
            backGround.opacity = 0
            addExit.visible = false
            content.bIsFirst = false
        }
        onSignalAddExistSelectClick: {
            //que hanshu
            if (addExit.listModel == partModel) {
                content.bIsEdit = true
                selectPartUpdataPage(modelId,name)
            } else if (addExit.listModel == spliceModel) {
//                var bIsFind = false
//                for (var i = 0; i < listModel.count; i++) {
//                    if (listModel.get(i).SpliceName == name) {
//                        bIsFind = true;
//                        break;
//                    }
//                }
//                if (bIsFind) {
//                    var ret = spliceModel.copySplice(modelId)
//                    if (ret > 0)
//                        spliceList.listModel.append({"SpliceName":spliceModel.getSpliceName(ret),"stationColor":"white","station":"?","SpliceId":ret,"qty":0})
//                }
//                else
//                    spliceList.listModel.append({"SpliceName":name,"stationColor":"white","station":"?","SpliceId":modelId,"qty":0})


                spliceList.listModel.append({"SpliceName":name,"stationColor":"white","station":"?","SpliceId":modelId,"qty":0})

            }
            else if (addExit.listModel == sequenceModel) {
                content.bIsEdit = true
                selectSequenceUpdataPage(modelId,name)
            }

            backGround.visible = false
            backGround.opacity = 0
            addExit.visible = false
            content.bIsFirst = false
        }
        onVisibleChanged: {
            if (addExit.visible) {
                addExit.clearSelect()
            }
        }
    }
    Item {
        id: template2
        anchors.top: parent.top
        anchors.topMargin: 50
        anchors.right: parent.right
        anchors.rightMargin: 10
        width: template.width
        height: parent.height*0.5
        visible: false
        Image {
            anchors.fill: parent
            source: "qrc:/images/images/dialogbg.png"
        }
        CButton {
            id: addNew
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.leftMargin: 20
            height: 40
            width: parent.width / 2
            pixelSize: 20
            text: qsTr("Add New")
        }

        Rectangle {
            id: addNewBack
            anchors.top: parent.top
            anchors.left: parent.left
            width: parent.width-30
            height: 40
            color: "black"
            opacity: 0
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    addNewBack.opacity = 0.5
                    addnewBlack.visible = true
                    temPlateDialog.visible = true
                }
            }
        }
        ListModel {
            id: templateModel
            Component.onCompleted: {
                var templateList = new Array()
                templateList = hmiAdaptor.getCarTempLate()
                for (var i = 0; i < templateList.length; i++) {
                    templateModel.append({name:templateList[i]})
                }
            }
        }
        Image {
            id: scrollUp
            anchors.top: parent.top
            anchors.topMargin: 4
            anchors.left: templateView.right
            width: 17
            height: 10
            visible: templateView.contentHeight > templateView.height ? true : false
            source: "qrc:/images/images/up.png"
        }
        Image {
            id: scrollDown
            anchors.bottom: templateView.bottom
            anchors.bottomMargin: 4
            anchors.left: templateView.right
            width: 17
            height: 10
            visible: templateView.contentHeight > templateView.height ? true : false
            source: "qrc:/images/images/down.png"
        }
        Rectangle {
            id: scrollbar
            width: 10
            anchors.bottom: scrollDown.top
            anchors.top: scrollUp.bottom
            anchors.left: templateView.right
            anchors.leftMargin: 4
            color: "#585858"
            radius: 10
            visible: templateView.contentHeight > templateView.height ? true : false
            Rectangle {
                id: button
                anchors.left: parent.left
                y: (templateView.visibleArea.yPosition < 0 ) ? 0 : (templateView.contentY+templateView.height>templateView.contentHeight) ?
                    scrollbar.height - button.height : templateView.visibleArea.yPosition * scrollbar.height
                width: 10
                height: templateView.visibleArea.heightRatio * scrollbar.height;
                color: "#ccbfbf"
                radius: 10
                // 鼠标区域
                MouseArea {
                    id: mouseArea
                    anchors.fill: button
                    drag.target: button
                    drag.axis: Drag.YAxis
                    drag.minimumY: 0
                    drag.maximumY: scrollbar.height - button.height
                    // 拖动
                    onMouseYChanged: {
                        templateView.contentY = button.y / scrollbar.height * templateView.contentHeight
                    }
                }
            }
        }
        ListView {
            id: templateView
            anchors.top: addNew.bottom
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 10
            width: parent.width-30
            height: parent.height-40
            model: templateModel
            clip: true
            delegate: Item {
                width: parent.width
                height: 40
                Text {
                    id: temPlateName
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    anchors.leftMargin: 20
                    anchors.right: close.left
                    anchors.rightMargin: 6
                    text: name
                    font.pixelSize: 20
                    font.family: "arial"
                    color: "white"
                    elide: Text.ElideRight
                }
                Rectangle {
                    id: back
                    anchors.fill: parent
                    color: "black"
                    opacity: 0
                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            backGround.visible = false
                            backGround.opacity = 0
                            template2.visible = false
                            template.text = temPlateName.text
                        }
                        onPressed: {
                            back.opacity = 0.5
                        }
                        onReleased: {
                            back.opacity = 0
                        }
                    }
                }
                Image {
                    id: close
                    anchors.right: parent.right
                    anchors.verticalCenter: parent.verticalCenter
                    source: "qrc:/images/images/close.png"
                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            templateModel.remove(index)
                            hmiAdaptor.removeCarTemplate(templateNameInput.inputText)
                        }
                    }
                }
            }
        }
        Rectangle {
            id: addnewBlack
            anchors.fill: parent
            color: "black"
            opacity: 0.5
            visible: false
            MouseArea {
                anchors.fill: parent
            }
        }
    }
    Image {
        id: temPlateDialog
        anchors.centerIn: parent
        width: 462
        height: 524
        visible: false
        source: "qrc:/images/images/dialogbg.png"
        Text {
            id: titleHead
            anchors.top: parent.top
            anchors.topMargin: 22
            anchors.left: parent.left
            anchors.leftMargin: 15
            font.pixelSize: 20
            font.family: "arial"
            color: "white"
            text: qsTr("Part Number Template -Add New")
        }
        Text {
            id: lineHead
            anchors.top: titleHead.bottom
            anchors.topMargin: 50
            anchors.left: titleHead.left
            font.pixelSize: 20
            font.family: "arial"
            color: "white"
            text: qsTr("Template Name")
        }
        MyLineEdit {
            id: templateNameInput
            anchors.left: titleHead.left
            height: 70
            width: parent.width-30
            anchors.top: lineHead.bottom
            anchors.topMargin: 8
            inputColor: "white"
            inputWidth: parent.width-36
            inputHeight: 68
            horizontalAlignment: Qt.AlignHCenter
            clip: true
        }
        Text {
            id: lineHead2
            anchors.top: templateNameInput.bottom
            anchors.topMargin: 20
            anchors.left: titleHead.left
            font.pixelSize: 20
            font.family: "arial"
            color: "white"
            text: qsTr("Part Name")
        }
        MyLineEdit {
            id: partNumberInput
            anchors.left: titleHead.left
            height: 70
            width: parent.width-30
            anchors.top: lineHead2.bottom
            anchors.topMargin: 8
            inputColor: "white"
            inputWidth: parent.width-36
            inputHeight: 68
            horizontalAlignment: Qt.AlignHCenter
            clip: true
        }
        CButton {
            id: saveButton
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 24
            anchors.left: cancelButton.right
            anchors.leftMargin: 14
            width: (partNumberInput.width-20)/2
            text: qsTr("Save")
            textColor: "white"
            onClicked: {
                edit6.inputText = partNumberInput.inputText
                template.text = templateNameInput.inputText
                templateModel.append({name:templateNameInput.inputText})
                hmiAdaptor.addCarTempLate(templateNameInput.inputText)
                temPlateDialog.visible = false
                backGround.visible = false
                template2.visible = false
                backGround.opacity = 0
                addNewBack.opacity = 0
                addnewBlack.visible = false
            }
        }
        CButton {
            id: cancelButton
            anchors.bottom: saveButton.bottom
            anchors.left: titleHead.left
            width: (partNumberInput.width-20)/2
            text: qsTr("Cancel")
            textColor: "white"
            onClicked: {
//                backGround.visible = false
//                backGround.opacity = 0
                addnewBlack.visible = false
                temPlateDialog.visible = false
                addNewBack.opacity = 0
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
        pointVisable: true
        onCurrentClickIndex: {
            if (index == 15) {
                if (hmiAdaptor.comepareCurrentValue(keyNum.minvalue,keyNum.maxvalue,keyNum.inputText)) {
                    if (bIsEditQty) {
                        spliceList.listModel.set(qtyIndex,{"qty":hmiAdaptor.stringToInt(keyNum.inputText)})
                    }
                    else if (edit1.inputFocus) {
                        edit1.inputText = keyNum.inputText
                        edit1.inputFocus = false
                    } else if (edit2.inputFocus) {
                        edit2.inputText = keyNum.inputText
                        edit2.inputFocus = false
                    } else if (edit3.inputFocus) {
                        edit3.inputText = keyNum.inputText
                        edit3.inputFocus = false
                    } else if (edit4.inputFocus) {
                        edit4.inputText = keyNum.inputText
                        edit4.inputFocus = false
                    } else if (edit5.inputFocus) {
                        edit5.inputText = keyNum.inputText
                        edit5.inputFocus = false
                    }
                    backGround.visible = false
                    backGround.opacity = 0
                    keyNum.visible = false
                    keyNum.inputText = ""
                    keyNum.tempValue = ""
                } else {
                    keyNum.timeRun = true
                }
            } else if (index == 11) {
                if (edit1.inputFocus) {
                    edit1.inputFocus = false
                } else if (edit2.inputFocus) {
                    edit2.inputFocus = false
                } else if (edit3.inputFocus) {
                    edit3.inputFocus = false
                } else if (edit4.inputFocus) {
                    edit4.inputFocus = false
                } else if (edit5.inputFocus) {
                    edit5.inputFocus = false
                }
                backGround.visible = false
                backGround.opacity = 0
                keyNum.visible = false
                keyNum.inputText = ""
                keyNum.tempValue = ""
            }
            bIsEditQty = false
        }
        onInputTextChanged: {
            if (keyNum.inputText != "") {
                if (edit1.inputFocus) {
                    edit1.inputText = keyNum.inputText
                } else if (edit2.inputFocus) {
                    edit2.inputText = keyNum.inputText
                } else if (edit3.inputFocus) {
                    edit3.inputText = keyNum.inputText
                } else if (edit4.inputFocus) {
                    edit4.inputText = keyNum.inputText
                } else if (edit5.inputFocus) {
                    edit5.inputText = keyNum.inputText
                }
            }
        }
    }

    Connections {
        target: spliceList
        onChangeNumRecVisable: {
            changeNumRec.visible = isVisable
            if (isVisable)
                mouseBack.visible = true
            changeNumRec.anchors.topMargin = y
        }
        onCurrentQty: {
            qtyIndex = index
            bIsEditQty = true
            backGround.visible = true
            backGround.opacity = 0.5
            keyNum.visible = true
            keyNum.titleText = name
            keyNum.currentValue = count
            keyNum.minvalue = "1"
            keyNum.maxvalue = "20"
        }
    }

    MouseArea {
        id: mouseBack
        anchors.fill: parent
        propagateComposedEvents: true
        onPressed: {
            mouse.accepted = false
            changeNumRec.visible = false
            mouseBack.visible = false
        }
    }

    Rectangle {
        id: changeNumRec
        visible: false
        width: 90
        height: 90
        anchors.left: swipeView.right
        anchors.top: parent.top
        color: "#052a40"
        MouseArea {
            anchors.fill: parent
        }

        CButton {
            id: upbutton
            width: 90
            height: 40
            text: qsTr("Up")
            onClicked: {
                spliceList.changeUp()
//                changeNumRec.visible = false
            }
        }
        CButton {
            width: 90
            height: 40
            anchors.top: upbutton.bottom
            anchors.topMargin: 10
            text: qsTr("Down")
            onClicked: {
                spliceList.changeDown()
//                changeNumRec.visible = false
            }
        }
    }
}
