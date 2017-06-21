import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import QtQuick.Window 2.2
import QtQuick.Controls 1.1
import QtQuick.Dialogs 1.2

Item {
    id: operate
    property int selectIndx: 0
    property int selectWorkId: -1
    property int setCheckIndex: -1

    Component.onDestruction: {
        hmiAdaptor.operateProcessExec("Stop")
    }

    Image {
        anchors.fill: parent
        source: "qrc:/images/images/bg.png"
    }
    ExclusiveGroup {
        id: listviewPositionGroup;
    }
    Loader {
        id: loader
        z: 10
        anchors.fill: parent
        onLoaded: {
//            if (loader.source == "qrc:/UI/OperateDetails.qml")
//            {
//                alarmModel.setStartTime();
//                var list = new Array
//                list =  workOrderModel.getSpliceList(selectIndx)
//                if (list.length > 0) {
//                    loader.item.spliceList = workOrderModel.getSpliceList(selectIndx)
//                    if (partModel.getPartOnlineOrOffLine()) {
//                        loader.item.showFlag = 1
//                    } else {
//                        if (loader.item.spliceList.length == 1) {
//                            loader.item.showFlag = 3
//                        } else {
//                            loader.item.showFlag = 2
//                        }
//                    }
//                    loader.item.selectSplice(workOrderModel.getSpliceList(selectIndx)[0])
//                    loader.item.qliantity = workOrderModel.getValue(selectIndx, "QUANTITY")
//                }
//                hmiAdaptor.operateProcessExec("Start")
//            }
        }
    }
    Connections{
        target: loader.item
        onSignalFileDialogCancel: {
            loader.source = ""
        }
        onSignalChoseFile: {
            loader.source = ""
            hmiAdaptor.importData(fileName)
        }
    }
    Text {
        id: scanEdit
        visible: false
        width: 150
        height: 60
        Component.onCompleted: {
            forceActiveFocus()
        }
        Keys.enabled: true
        Keys.onReturnPressed: {
            var spliceIndex = spliceModel.searchIndexByName(scanEdit.text)
            if (spliceIndex != -1)
            {
                selectIndx = spliceIndex
                listView.currentIndex = spliceIndex
            }
            scanEdit.text = ""
        }
        Keys.onPressed: {
            scanEdit.text = scanEdit.text + event.text
        }
    }
    Row {
        id: headTitle
        anchors.top: parent.top
        anchors.topMargin: 30
        anchors.left: parent.left
        anchors.leftMargin: 52
        anchors.right: parent.right
        anchors.rightMargin: 52
        spacing: 40
        height: 40
        Text {
            anchors.verticalCenter: parent.verticalCenter
            color: "white"
            width: (parent.width-120)/4
            font.pixelSize: 25
            clip: true
            font.family: "arial"
            text: qsTr("Splice Name")
        }
        Text {
            anchors.verticalCenter: parent.verticalCenter
            color: "white"
            width: (parent.width-120)/4
            font.pixelSize: 25
            clip: true
            font.family: "arial"
            text: qsTr("Date Created")
        }
        Text {
            anchors.verticalCenter: parent.verticalCenter
            color: "white"
            width: (parent.width-120)/4
            font.pixelSize: 25
            clip: true
            font.family: "arial"
            text: qsTr("Total Wires")
        }
        Text {
            anchors.verticalCenter: parent.verticalCenter
            color: "white"
            width: (parent.width-120)/4
            font.pixelSize: 25
            clip: true
            font.family: "arial"
            text: qsTr("Cross Section")
        }
    }
    Rectangle {
        id: tipsRec
        anchors.top: headTitle.bottom
        anchors.topMargin: 20
        anchors.left: parent.left
        anchors.leftMargin: 20
        width: parent.width - 40
        clip: true
        height: 1
        color: "#ffffff"
    }
    Rectangle {
        id: tipsRec2
        anchors.top: tipsRec.bottom
        anchors.left: parent.left
        anchors.leftMargin: 20
        width: parent.width - 40
        clip: true
        height: 1
        color: "#0d0f11"
    }

    ListView {
        id: listView
        anchors.top: tipsRec2.bottom
        anchors.left: parent.left
        anchors.leftMargin: 52
        anchors.bottom: bottomTip.top
        width: parent.width - 104
        clip: true
        model: spliceModel
        delegate: listDelegate
        highlight: Rectangle { color: "black"; opacity: 0.3; radius: 5 }
        focus: true
        highlightResizeVelocity: 500000
        highlightMoveVelocity: 500000
    }
    Image {
        id: scrollUp
        anchors.top: tipsRec2.bottom
        anchors.topMargin: 2
        anchors.left: listView.right
        width: 17
        height: 10
        visible: listView.contentHeight > listView.height ? true : false
        source: "qrc:/images/images/up.png"
    }
    Image {
        id: scrollDown
        anchors.bottom: bottomTip.top
        anchors.bottomMargin: 2
        anchors.left: listView.right
        width: 17
        height: 10
        visible: listView.contentHeight > listView.height ? true : false
        source: "qrc:/images/images/down.png"
    }
    Rectangle {
        id: scrollbar
        width: 10
        height: listView.height-24
        anchors.top: scrollUp.bottom
        anchors.left: listView.right
        anchors.leftMargin: 4
        color: "#585858"
        radius: 10
        visible: listView.contentHeight > listView.height ? true : false
        Rectangle {
            id: button
            anchors.left: parent.left
            y: (listView.visibleArea.yPosition < 0 ) ? 0 : (listView.contentY+listView.height>listView.contentHeight) ?
                scrollbar.height - button.height : listView.visibleArea.yPosition * scrollbar.height
            width: 10
            height: listView.visibleArea.heightRatio * scrollbar.height;
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
                    listView.contentY = button.y / scrollbar.height * listView.contentHeight
                }
            }
        }
    }
    Component {
        id: listDelegate
        Item {
            width: listView.width
            height: 50
            Text {
                id: headName
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                width: (parent.width-120)/4
                elide: Text.ElideRight
                text: SpliceName
                clip: true
                color: "white"
                font.pixelSize: 20
                font.family: "arial"
            }
            Text {
                id: headData
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: headName.right
                anchors.leftMargin: 40
                width: (parent.width-120)/4
                text: DateCreated
                clip: true
                color: "white"
                font.pixelSize: 20
                font.family: "arial"
            }
            Text {
                id: headMiddle
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: headData.right
                anchors.leftMargin: 40
                width: (parent.width-120)/4
                text: TotalWires
                elide: Text.ElideRight
                clip: true
                color: "white"
                font.pixelSize: 20
                font.family: "arial"
            }
            Text {
                id: headCount
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: headMiddle.right
                anchors.leftMargin: 40
                width: (parent.width-120)/4
                text: CrossSection
                elide: Text.ElideRight
                color: "white"
                clip: true
                font.pixelSize: 20
                font.family: "arial"
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    operate.selectIndx = index
                    operate.selectWorkId = SpliceId
                    selectCheck.checked = !selectCheck.checked
                    listView.currentIndex = index
                }
            }
            Rectangle {
                id: backGround
                anchors.fill: parent
                color: "black"
                opacity: 0//opacityValue
                RadioButton {
                    id: selectCheck
                    exclusiveGroup: listviewPositionGroup
                    visible: false
                    onCheckedChanged: {
//                        if (checked)
//                            backGround.opacity = 0.3
//                        else
//                            backGround.opacity = 0
                    }
                }
            }
        }
    }
    Rectangle {
        id: bottomTip
        anchors.bottom: bottomTip2.top
        anchors.left: parent.left
        anchors.leftMargin: 20
        width: parent.width - 40
        clip: true
        height: 1
        color: "#ffffff"
    }
    Rectangle {
        id: bottomTip2
        anchors.bottom: selectOk.top
        anchors.bottomMargin: 24
        anchors.left: parent.left
        anchors.leftMargin: 20
        width: parent.width - 40
        clip: true
        height: 1
        color: "#0d0f11"
    }
    /*
    CButton {
        id: addnewOrder
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 15
        width: (parent.width-100)/5
        spacing: 10
        iconSource: "qrc:/images/images/Add.png"
        text: qsTr("ADD NEW")
        pointSize: 20
        clip: true
        textColor: "white"
        onClicked: {
            backGround.visible = true
            backGround.opacity = 0.5
            dialog.bIsEdit = false
            dialog.visible = true
        }
    }
    CButton {
        id: editExistingOrder
        anchors.bottom: addnewOrder.bottom
        anchors.left: addnewOrder.right
        anchors.leftMargin: 15
        width: (parent.width-100)/5
        spacing: 10
        iconSource: "qrc:/images/images/stting.png"
        text: qsTr("EDIT")
        pointSize: 20
        clip: true
        textColor: "white"
        onClicked: {
            if(workOrderModel.count() == 0 || selectIndx == -1) {
                return
            }
            backGround.visible = true
            backGround.opacity = 0.5
            dialog.bIsEdit = true
            dialog.visible = true
        }
    }
    CButton {
        id: deleOrder
        anchors.bottom: addnewOrder.bottom
        anchors.left: editExistingOrder.right
        anchors.leftMargin: 15
        width: (parent.width-100)/5
        spacing: 10
        iconSource: "qrc:/images/images/cancel.png"
        text: qsTr("DELETE")
        pointSize: 20
        clip: true
        textColor: "white"
        onClicked: {
            if (selectIndx < 0)
                return
            spliceModel.removeValue(spliceModel.getValue(selectIndx,"SpliceId"),spliceModel.getValue(selectIndx,"SpliceName"))
        }
    }
    CButton {
        id: importOrder
        anchors.bottom: addnewOrder.bottom
        anchors.left: deleOrder.right
        anchors.leftMargin: 15
        width: (parent.width-100)/5
        spacing: 10
        iconSource: "qrc:/images/images/import.png"
        text: qsTr("IMPORT")
        pointSize: 20
        clip: true
        textColor: "white"
        onClicked: {
            loader.source = "qrc:/UI/MySelectFileDialog.qml"
        }
    }
    */
    CButton {
        id: selectOk
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        anchors.right: parent.right
        anchors.rightMargin: 20
        width: (parent.width-100)/5
        spacing: 10
        iconSource: "qrc:/images/images/OK.png"
        text: qsTr("OK")
        pointSize: 20
        clip: true
        textColor: "white"
        onClicked: {
//            if (operate.selectIndx != -1) {
//                workOrderModel.editNew(workOrderModel.getPartId(operate.selectIndx),operate.selectWorkId)
//                partModel.getPartInfo(true,workOrderModel.getPartId(selectIndx),workOrderModel.getValue(selectIndx,"PART"))
//                hmiAdaptor.maintenanceCountExecute("_Recall")
//                loader.source = "qrc:/UI/OperateDetails.qml"
//            }
            if (operate.selectIndx != -1) {
                backGround.visible = true
                backGround.opacity = 0.5
                testDialog.visible = true
                mainRoot.bIsEditSplice = true
                spliceModel.editNew(spliceModel.getValue(selectIndx,"SpliceId"))
                //            mainRoot.checkNeedPassWd(-1)
                testDialog.setData()
            }
        }
    }
    Rectangle {
        id: backGround
        anchors.fill: parent
        color: "black"
        opacity: 0
        visible: false
        MouseArea {
            anchors.fill: parent
            onClicked: {
            }
        }
    }

    /*
    Image {
        id: dialog
        visible: false
        anchors.centerIn: parent
        property bool bIsEdit: false
        property var oldWorkOrderName: ""
        width: 670
        height: 390
        source: "qrc:/images/images/dialogbg.png"
        onBIsEditChanged: {
            if (bIsEdit) {
               inputworkId.inputText = workOrderModel.getValue(selectIndx, "WorkOrderName")
               selectPart.text = workOrderModel.getValue(selectIndx, "PART")
               inputquantity.inputText = workOrderModel.getValue( selectIndx, "QUANTITY")
            }
        }
        onVisibleChanged: {
            if (dialog.bIsEdit && dialog.visible) {
                dialog.oldWorkOrderName = workOrderModel.getValue(selectIndx, "WorkOrderName")
            } else if (!dialog.bIsEdit && dialog.visible) {
                inputquantity.inputText = ""
                inputworkId.inputText = ""
            }
        }

        Text {
            id: orderId
            anchors.top: parent.top
            anchors.topMargin: 60
            anchors.right: inputworkId.left
            anchors.rightMargin: 20
            width: 150
            height: 60
            font.pointSize: 18
            font.family: "arial"
            text: qsTr("Work Order Name")
            verticalAlignment: Qt.AlignVCenter
            horizontalAlignment: Qt.AlignRight
            color: "white"
        }
        MyLineEdit {
            id: inputworkId
            anchors.top: parent.top
            anchors.topMargin: 60
            anchors.right: parent.right
            anchors.rightMargin: 72
            horizontalAlignment: Qt.AlignHCenter
            width: 375
            height: 60
            inputWidth: 375
            inputColor: "white"
            inputHeight: 60
            inputText: dialog.bIsEdit ? workOrderModel.getValue(selectIndx, "WorkOrderName") : ""
        }
        Text {
            id: selectTips
            anchors.top: inputworkId.bottom
            anchors.topMargin: 20
            anchors.right: selectPart.left
            anchors.rightMargin: 20
            width: 150
            height: 60
            font.pointSize: 18
            font.family: "arial"
            text: qsTr("Select Part")
            verticalAlignment: Qt.AlignVCenter
            horizontalAlignment: Qt.AlignRight
            color: "white"
        }
        CButton {
            id: selectPart
            property var partId: 1
            anchors.top: inputworkId.bottom
            anchors.topMargin: 20
            anchors.right: parent.right
            anchors.rightMargin: 72
            width: 375
            height: 60
            clip: true
            text: dialog.bIsEdit ? workOrderModel.getValue(selectIndx, "PART") : qsTr("SELECT PART")
            onClicked: {
                addExit.visible = true
            }
        }
        Text {
            id: quantity
            anchors.top: selectTips.bottom
            anchors.topMargin: 20
            anchors.right: inputquantity.left
            anchors.rightMargin: 20
            width: 150
            height: 60
            font.pointSize: 18
            font.family: "arial"
            text: qsTr("Quantity")
            verticalAlignment: Qt.AlignVCenter
            horizontalAlignment: Qt.AlignRight
            color: "white"
        }
        MiniKeyNumInput {
            id: inputquantity
            anchors.top: selectTips.bottom
            anchors.topMargin: 20
            anchors.right: parent.right
            anchors.rightMargin: 72
            width: 375
            height: 60
            inputWidth: 375
            inputText: dialog.bIsEdit ? workOrderModel.getValue( selectIndx, "QUANTITY") : ""
            onInputFocusChanged: {
                if (inputquantity.inputFocus) {
                    keyNum.visible = true
                    keyNum.titleText = quantity.text
                    keyNum.currentValue = inputquantity.inputText
                    if (inputquantity.inputText == "") {
                        keyNum.minvalue = hmiAdaptor.getTestQuantity(0,false)
                        keyNum.maxvalue = hmiAdaptor.getTestQuantity(0,true)
                    } else {
                        keyNum.minvalue = hmiAdaptor.getTestQuantity(inputquantity.inputText,false)
                        keyNum.maxvalue = hmiAdaptor.getTestQuantity(inputquantity.inputText,true)
                    }
                }
            }
        }
        CButton {
            id: cancel
            anchors.right: sure.left
            anchors.rightMargin: 15
            anchors.top: quantity.bottom
            anchors.topMargin: 16
            width: 180
            text: qsTr("CANCEL")
            textColor: "white"
            iconSource: "qrc:/images/images/cancel.png"
            onClicked: {
                backGround.visible = false
                backGround.opacity = 0
                dialog.visible = false
                dialog.bIsEdit = false
                if (!dialog.bIsEdit) {
                    selectPart.text = qsTr("SELECT PART")
                }
            }
        }



        CButton {
            id: sure
            anchors.right: parent.right
            anchors.rightMargin: 72
            anchors.top: quantity.bottom
            anchors.topMargin: 16
            width: 180
            text: qsTr("OK")
            textColor: "white"
            iconSource: "qrc:/images/images/OK.png"
            onClicked: {
                backGround.visible = false
                backGround.opacity = 0
                dialog.visible = false
                if (dialog.bIsEdit)
                    workOrderModel.updateRecordIntoTable(workOrderModel.getValue(selectIndx, "WorkOrderId"),dialog.oldWorkOrderName, inputworkId.inputText,selectPart.partId,selectPart.text, inputquantity.inputText )
                else {
                    workOrderModel.insertRecordIntoTable(inputworkId.inputText,selectPart.partId,selectPart.text,inputquantity.inputText)
                    selectPart.text = qsTr("SELECT PART")
                }
                dialog.bIsEdit = false
            }
        }
    }

    AddExistingSpliceWire {
        id: addExit
        anchors.centerIn: parent
        width: parent.width*0.9
        height: parent.width*0.4
        visible: false
        listModel: partModel
        titleName: qsTr("ADD PART")
        componentName: qsTr("PART NAME")
        componentData: qsTr("DATE CREATED")
        componentMiddle: qsTr("# OF SPLICE")
        componenttype: qsTr("CROSS SECTION")
        componentCount: ""
        bIsOnlyOne: true
        onSignalAddExistCancel : {
            addExit.visible = false
        }
        onSignalAddExistSelectClick: {
            selectPart.partId = modelId
            selectPart.text = name
            addExit.visible = false
        }
        onVisibleChanged: {
            if (addExit.visible) {
                addExit.clearSelect()
            }
        }
    }

    */

    Connections {
        target: loader.item
        onSignalCancel: {
            loader.source = ""
            mainRoot.headTitle = qsTr("Operate")
        }
        onSignalAdvanceOk: {
            loader.source = ""
            mainRoot.headTitle = qsTr("Operate")
            testDialog.visible = true
        }
    }

    TestSetingDialog {
        id: testDialog
        visible: false
        anchors.centerIn: parent
        width: 435
        height: 540
        onVisibleChanged: {
        }

        onSignalAdvanceSettingStart: {
            operate.setCheckIndex = checkIndex
//            if (mainRoot.checkAllInterface(20)) {
//                passDialog.visible = true
//                passDialog.pageName = "Teach Mode"
//            } else {
//                loader.source = "qrc:/UI/AdvanceSetting.qml"
//            }

            loader.source = "qrc:/UI/AdvanceSetting.qml"
            mainRoot.headTitle = qsTr("Teach Mode")

        }
        onSignalTestStart: {
            testDialog.visible = false
            backGround.visible = false
//            loader.source = "qrc:/UI/TestDetail.qml"

            if (index == 0)
            {
//                hmiAdaptor.setWorkFlow(3, 0)
//                hmiAdaptor.setWorkFlow(0, spliceModel.getValue(selectIndx,"SpliceId"))
                mainRoot.checkNeedPassWd(-5)
            }
            else if (index == 1)
            {
                mainRoot.bIsTest = true
                hmiAdaptor.setTestSpliceId(spliceModel.getValue(selectIndx,"SpliceId"))
                mainRoot.bIsEditSplice = true
                spliceModel.editNew(spliceModel.getValue(selectIndx,"SpliceId"))
                mainRoot.checkNeedPassWd(-2)
            }
            else if (index == 2)
            {
                mainRoot.bIsTest = true
                hmiAdaptor.setTestSpliceId(spliceModel.getValue(selectIndx,"SpliceId"))
                mainRoot.bIsEditSplice = true
                spliceModel.editNew(spliceModel.getValue(selectIndx,"SpliceId"))
                mainRoot.checkNeedPassWd(-3)
            }
            else if (index == 3)
            {
                mainRoot.bIsTest = true
                hmiAdaptor.setTestSpliceId(spliceModel.getValue(selectIndx,"SpliceId"))
                mainRoot.bIsEditSplice = true
                spliceModel.editNew(spliceModel.getValue(selectIndx,"SpliceId"))
                mainRoot.checkNeedPassWd(-4)
            }

        }
        onSignalInputNum: {
            keyNum.visible = true
            keyNum.titleText = qsTr("#of Splices")
            if (text == qsTr("#of Splices")) {
                keyNum.currentValue = "0"
                keyNum.maxvalue = hmiAdaptor.getTestQuantity(0,true)
                keyNum.minvalue = hmiAdaptor.getTestQuantity(0,false)
            } else {
                keyNum.currentValue = text
                keyNum.maxvalue = hmiAdaptor.getTestQuantity(text,true)
                keyNum.minvalue = hmiAdaptor.getTestQuantity(text,false)
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
//                    if (inputquantity.inputFocus) {
//                        inputquantity.inputText = keyNum.inputText
//                        inputquantity.inputFocus = false
//                    }
                    testDialog.inputNum = keyNum.inputText
                    keyNum.visible = false
                    keyNum.inputText = ""
                    keyNum.tempValue = ""
                } else {
                    keyNum.timeRun = true
                }
            } else if (index == 11) {
//                if (inputquantity.inputFocus) {
//                    inputquantity.inputFocus = false
//                }
                keyNum.visible = false
                keyNum.inputText = ""
                keyNum.tempValue = ""
            }
        }
        onInputTextChanged: {
            if (keyNum.inputText != "") {
                testDialog.inputNum = keyNum.inputText

//                if (inputquantity.inputFocus) {
//                    inputquantity.inputText = keyNum.inputText
//                }
            }
        }
    }
}
