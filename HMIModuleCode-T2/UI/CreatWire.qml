/*******************************************************************
Copyright:http://www.sinux.com.cn
Date:2016/12/26
Author:zhangjiyong&lilongfei
Description: wire to create interface,data is from wireModel,spliceModel,
settingsModel2,settingsModel,weldListModel,weldSettingModel,widthModel,
heightModel,
The function interface:
    editSplice()
    wireModel.getStructValue3()
    spliceModel.getStructValue()
*******************************************************************/
import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import QtQuick.Window 2.2
import QtQuick.Controls 1.1
import QtQuick.Controls.Styles 1.1
Item {
    id: creatWire
    width: Screen.width
    height: Screen.height

    property var weldModel: -1
    property var stepModel: -1
    property var selectModel: -1
    property var currentSpliceId: -1
    property var totalGauge: 0
    property int selectIndex: 0
    property bool bIsFromLib: false
    property bool firstComeIn: true
    property bool crossSection: false
    property bool detailIsChang: true
    property bool bIsStep: false
    property bool bIsEditSplice: false
    property string stepSetText: ""
    signal signalSaveSplice(var spliceId,var bIsEdit)

    property variant colorArray: ["#000000","#7f7f7f","#880015","#ED1C24","#FF7F27","#FFF200","#22B14C","#00A2E8",
        "#3F48CC","#A349A4","#ffffff","#c3c3c3","#b97a57","#ffaec9","#ffc90e","#efe4b0","#b5e61d","#99d9ea","#7092be","#c8bfe7"]

    Component.onCompleted: {
        if (mainRoot.bIsEditSplice)
        {
            bIsEditSplice = true
            currentSpliceId = hmiAdaptor.getTestSpliceId()
            var list = spliceModel.getWireIdList()
            editSplice(list)
            mainRoot.bIsEditSplice = false

        }
        if (mainRoot.bIsTest)
        {
            countDown.start()
        }
        firstComeIn = false

    }

    Component.onDestruction: {
        hmiAdaptor.setWorkFlow(3,0,"")
        hmiAdaptor.operateProcessExec("Stop")
    }

    Timer{
        id:countDown;
        interval: 500;
        repeat: false;
        triggeredOnStart: false;
        onTriggered: {
            tabBar.currentIndex = 1
            mainRoot.bIsTest = false
        }
    }

    Connections {
        target: hmiAdaptor
        onSignalWeldCycleCompleted: {
            qualityTitleModel.set(0,{"bottomText":alarmModel.getAxes2("Time")})
            qualityTitleModel.set(1,{"bottomText":alarmModel.getAxes2("Power")})
            qualityTitleModel.set(2,{"bottomText":alarmModel.getAxes2("Pre-Height")})
            qualityTitleModel.set(3,{"bottomText":alarmModel.getAxes2("Post-Height")})

            resultModel.set(0,{"bottomText":alarmModel.getAxes2("Energy")})
            resultModel.set(1,{"bottomText":alarmModel.getAxes2("T.Pressure")})
            resultModel.set(2,{"bottomText":alarmModel.getAxes2("W.Pressure")})
            resultModel.set(3,{"bottomText":alarmModel.getAxes2("Amplitude")})
            resultModel.set(4,{"bottomText":alarmModel.getAxes2("Width")})
        }
    }

    ListModel {
        id: resultModel
        Component.onCompleted: {
            resultModel.append({"bottomText":""})
            resultModel.append({"bottomText":""})
            resultModel.append({"bottomText":""})
            resultModel.append({"bottomText":""})
            resultModel.append({"bottomText":""})
        }
    }



    function editSplice(editWireList)
    {
        creatWire.bIsEditSplice = true
        var list = new Array
        list = editWireList
        for (var i = 0; i < list.length;i++)
        {
            wireModel.addFromLibrary(list[i])
            spliceDetailsItem.addWireFromSplice()
        }
        edit1.inputText = spliceModel.getStructValue("SpliceName","");
    }

    function wireChanged(selectColor,selectPosition,selectText)
    {
        spliceDetailsItem.selectColor = selectColor
        spliceDetailsItem.selectText = selectText
        spliceDetailsItem.selectPosition = selectPosition
    }
    function initSettings()
    {
        settingsModel.clear();

        settingsModel.append({"tipText":   qsTr("Energy"),
                              "topText":   qsTr(""),
                              "bottomText":spliceModel.getStructValue("Energy","current"),
                              "maxText":   spliceModel.getStructValue("Energy","max"),
                              "minText":   spliceModel.getStructValue("Energy","min")
                             })
        settingsModel.append({"tipText":   qsTr("T.P"),
                              "topText":   qsTr(""),
                              "bottomText":spliceModel.getStructValue("Trigger Pressure","current"),
                              "maxText":   spliceModel.getStructValue("Trigger Pressure","max"),
                              "minText":   spliceModel.getStructValue("Trigger Pressure","min")
                             })
        settingsModel.append({"tipText":   qsTr("W.P"),
                              "topText":   qsTr(""),
                              "bottomText":spliceModel.getStructValue("Weld Pressure","current"),
                              "maxText":   spliceModel.getStructValue("Weld Pressure","max"),
                              "minText":   spliceModel.getStructValue("Weld Pressure","min")
                             })
        settingsModel.append({"tipText":   qsTr("Amplitude"),
                              "topText":   qsTr(""),
                              "bottomText":spliceModel.getStructValue("Amplitude","current"),
                              "maxText":   spliceModel.getStructValue("Amplitude","max"),
                              "minText":   spliceModel.getStructValue("Amplitude","min")
                             })
        settingsModel.append({"tipText":   qsTr("Width"),
                              "topText":   qsTr(""),
                              "bottomText":spliceModel.getStructValue("Width","current"),
                              "maxText":   spliceModel.getStructValue("Width","max"),
                              "minText":   spliceModel.getStructValue("Width","min")
                             })
        if (tabBar.currentIndex == 1)
            freshProcess()
    }
    function freshProcess()
    {
        setProcessData()
        if (bIsEditSplice)
            hmiAdaptor.setProcess("Edit")
        else
            hmiAdaptor.setProcess("Create")
        hmiAdaptor.operateProcessExec("Execute")
        hmiAdaptor.operateProcessExec("Start")
    }

    function setProcessData()
    {
        spliceModel.setProcessValue("SpliceId",currentSpliceId);
        spliceModel.setProcessValue("SpliceName",edit1.inputText);
        spliceModel.setProcessValue("OperatorId",hmiAdaptor.getCurrentOperatorId());
        spliceModel.setProcessValue("Total Cross",spliceDetailsTip2.text)
//        spliceModel.setProcessValue("WireMap",list)

        spliceModel.setProcessValue("Energy",settingsModel.get(0).bottomText);
        spliceModel.setProcessValue("Trigger Pressure",settingsModel.get(1).bottomText);
        spliceModel.setProcessValue("Weld Pressure",settingsModel.get(2).bottomText);
        spliceModel.setProcessValue("Amplitude",settingsModel.get(3).bottomText);
        spliceModel.setProcessValue("Width",settingsModel.get(4).bottomText);

        spliceModel.setProcessValue("Time-",settingsModel2.get(0).bottomText);
        spliceModel.setProcessValue("Time+",settingsModel2.get(1).bottomText);
        spliceModel.setProcessValue("Power-",settingsModel2.get(2).bottomText);
        spliceModel.setProcessValue("Power+",settingsModel2.get(3).bottomText);
        spliceModel.setProcessValue("Pre-Height-",settingsModel2.get(4).bottomText);
        spliceModel.setProcessValue("Pre-Height+",settingsModel2.get(5).bottomText);
        spliceModel.setProcessValue("Post-Height-",settingsModel2.get(6).bottomText);
        spliceModel.setProcessValue("Post-Height+",settingsModel2.get(7).bottomText);

        spliceModel.setProcessValue("Step-Energy",stepSetModel.get(0).centerText);
        spliceModel.setProcessValue("Step-Time",stepSetModel.get(1).centerText);
        spliceModel.setProcessValue("Step-Power",stepSetModel.get(2).centerText);
        spliceModel.setProcessValue("Amplitude B",stepSetModel.get(4).centerText);

        spliceModel.setProcessValue("ShrinkId",shrinkSet.shrinkId );
        spliceModel.setProcessValue("ShrinkTemp",shrinkSet.shrinkTemp);
        spliceModel.setProcessValue("ShrinkTime",shrinkSet.shrinkTime);
        spliceModel.setProcessValue("ShrinkLock",shrinkSet.shrinkLock);

    }

    SwipeView {
        width: Screen.width * 0.3
        height: parent.height
        id: swipeView
        currentIndex: tabBar.currentIndex
        Page {
            id: wireBuilder

            Connections {
                target: spliceDetailsItem
                onWireSelected: {
//                    signal wireSelected(var selectColor,var selectDirection,var selectPosition,var selectText,var selectWireName, var selectWireType, var selectWireStripeColor, var selectWireStripeType)
                    forground.visible = false
                    rectcolor.color = selectColor
                    wireDirection.state = selectDirection
                    edit2.inputText = selectText
                    wireName.inputText = selectWireName

                    topRadio.checked = true
                    tabPositionGroup.current = null
                    if (selectPosition == "rightList" || selectPosition == "leftList")
                        midRadio.checked = true
                    else if (selectPosition == "topLeft" || selectPosition == "topRight")
                        topRadio.checked = true
                    else if (selectPosition == "bottomLeft" || selectPosition == "bottomRight")
                        bottomRadio.checked = true

                    if (selectWireType == 0)
                        typeSwitch.state = "left"
                    else if (selectWireType == 1)
                        typeSwitch.state = "right"


                    itemStripe.color = selectWireStripeColor
                    itemStripe.stripeType = selectWireStripeType
                    typeDirection.currentText = selectModuleType

                }
                onChanging: {
                    detailIsChang = bIsChang
                } //
                onGaugeChanged: {
                    if (type == "add")
                        totalGauge+= value
                    else if (type == "sub")
                        totalGauge-= value
                    if (spliceDetailsTip2.text != spliceModel.getString("CrossSection",totalGauge))
                        spliceDetailsTip2.text = spliceModel.getString("CrossSection",totalGauge)
                }
                onWireDetailHide: {
                    forground.visible = true
                }
            }

            Rectangle {
                anchors.top: parent.top
                anchors.fill: parent
                color: "#052a40"
            }
            Rectangle {
                id: forground
                anchors.top: parent.top
                anchors.fill: parent
                color: "#052a40"
                z:11
                Label {
                    id: nowire
                    color: "#8295a0"
                    text: qsTr("No Wires Selected")
                    anchors.top: parent.top
                    anchors.topMargin: tabBar.height + 15
                    anchors.left: parent.left
                    anchors.leftMargin: 10
                    font.family: "arial"
                    font.pointSize: 16
                }
                MouseArea {
                    anchors.fill: parent
                }
            }

            MyLineEdit {
                id: wireName
                width: parent.width-20
                height: 50
                anchors.top: parent.top
                anchors.topMargin: tabBar.height + 15
                anchors.left: parent.left
                anchors.leftMargin: 10
                inputWidth: parent.width-20
                inputHeight: 48
                inputColor: "#8295a0"
                borderColor: "#375566"
                defaultText: qsTr("WIRE NAME")
                maxSize: 21
                onTextChange: {
                    if (detailIsChang)
                        return
                    spliceDetailsItem.wireName = wireName.inputText
                }
            }
            Label {
                id: properties
                color: "#8295a0"
                anchors.top: wireName.bottom
                anchors.left: parent.left
                anchors.leftMargin: 10
                font.family: "arial"
                font.pointSize: 16
                height: 1
            }
            Item {
                id: itemColor
                width: parent.width
                height: 34
                anchors.top: properties.bottom
                anchors.topMargin: 10
                property alias color: rectcolor.color
                Label {
                    id: labelColor
                    color: "#8295a0"
                    text: qsTr("Color")
                    font.family: "arial"
                    font.pointSize: 14
                    anchors.right: parent.right
                    anchors.rightMargin: 290
                }
                Rectangle {
                    id: rectcolor
                    width: 100
                    height: 34
                    color: "green"
                    anchors.right: parent.right
                    anchors.rightMargin: 130
                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            colorLoader.sourceComponent = colorPicker
                        }
                    }
                }
            }
            ExclusiveGroup {
                id: colorPositionGroup;
            }
            ExclusiveGroup {
                id: stripePositionGroup;
            }
            Component {
                id: colorPicker
                Image {
                    id: backColor
                    property var pickColor: ""
                    width: 852
                    height: 384
                    source: "qrc:/images/images/colorPickerBg.png"
                    Grid {
                        id: colorGrid
                        anchors.left: parent.left
                        anchors.leftMargin: 20
                        anchors.top: parent.top
                        anchors.topMargin: 60
                        columns: 10
                        rows: 2
                        spacing: 2
                        Repeater {
                            model: colorArray.length
                            Rectangle {
                                id: colorRec
                                width: 80
                                height: 80
                                color: colorArray[index]
                                Rectangle {
                                    id: border
                                    width: colorRec.width + 2
                                    height: colorRec.height + 2
                                    color: Qt.rgba(0,0,0,0)
                                    border.color: "white"
                                    border.width: 4
                                    anchors.centerIn: colorRec
                                    visible: radioButton.checked ? true : false
                                }
                                RadioButton {
                                    id: radioButton
                                    visible: false
                                    exclusiveGroup: colorPositionGroup
                                }
                                MouseArea {
                                    anchors.fill: parent
                                    onClicked: {
                                        radioButton.checked = !radioButton.checked
                                        if (radioButton.checked) {
                                            backColor.pickColor = colorArray[index]
                                        }
                                    }
                                }
                            }
                        }
                    }
                    Row {
                        id: bottomRow
                        spacing: 20
                        anchors.right: parent.right
                        anchors.rightMargin: 20
                        anchors.bottom: parent.bottom
                        anchors.bottomMargin: 20
                        CButton {
                            width: 200
                            text: qsTr("CANCEL")
                            textColor: "white"
                            onClicked: {
                                colorLoader.sourceComponent = null
                            }
                        }
                        CButton {
                            width: 200
                            iconSource: "qrc:/images/images/OK.png"
                            text: qsTr("OK")
                            textColor: "white"
                            onClicked: {
                                if (colorLoader.sourceComponent == colorPicker && pickColor != "")
                                {
                                    itemColor.color = pickColor
                                    spliceDetailsItem.selectColor = pickColor
                                    colorLoader.sourceComponent = null
                                }
                                else if (colorLoader.sourceComponent == stripePicker)
                                {
                                    if (colorLoader.item.radioCheck == -1 )
                                        return

                                    if (colorLoader.item.radioCheck != 3 && pickColor == "")
                                        return

                                    itemStripe.color = pickColor
                                    itemStripe.stripeType = colorLoader.item.radioCheck
                                    spliceDetailsItem.selectWireStripeColor = pickColor
                                    spliceDetailsItem.selectWireStripeType = colorLoader.item.radioCheck
                                    colorLoader.sourceComponent = null

                                }
                            }
                        }
                    }

                }
            }

            Item {
                id: itemStripe
                width: parent.width
                height: 34
                anchors.top: itemColor.bottom
                anchors.topMargin: 10
                property var color: "" //stripeBack.color
                property var stripeType: -1
                property alias wireColor: stripeBack.color

                Label {
                    id: labelStripe
                    color: "#8295a0"
                    text: qsTr("Stripe")
                    font.family: "arial"
                    font.pointSize: 14
                    anchors.right: parent.right
                    anchors.rightMargin: 290
                    anchors.verticalCenter: stripeBack.verticalCenter
                }
                Rectangle {
                    id: stripeBack
                    width: 100
                    height: 34
                    color: itemColor.color
                    anchors.right: parent.right
                    anchors.rightMargin: 130
                    clip: true
                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            colorLoader.sourceComponent = stripePicker
                        }
                    }
                    Rectangle {
                        color: itemStripe.color //"black"
                        height: 5
                        width: parent.width
                        anchors.verticalCenter: parent.verticalCenter
                        visible: itemStripe.stripeType == 0 ? true : false
                    }
                    Rectangle {
                        color: itemStripe.color //"black"
                        height: 5
                        width: parent.width + 10
                        anchors.centerIn: parent
                        rotation: 22
                        visible: itemStripe.stripeType == 1 ? true : false
                    }
                    Rectangle {
                        color: itemStripe.color //"black"
                        width: 5
                        height: parent.height
                        anchors.horizontalCenter: parent.horizontalCenter
                        visible: itemStripe.stripeType == 2 ? true : false
                    }
                    Text {
                        text: qsTr("None")
                        font.family: "Arial"
                        font.pointSize: 16
                        color: "black"
                        visible: itemStripe.stripeType == 3 ? true : false
                        anchors.centerIn: parent
                    }
                }
            }

            Component {
                id: stripePicker
                Image {
                    property var radioCheck: -1
                    id: backStripe
                    source: "qrc:/images/images/colorPickerBg.png"
                    width: 852
                    height: 504
                    Row {
                        spacing: 30
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.top: parent.top
                        anchors.topMargin: 20


                        Rectangle {
                            width: 180
                            height: 80
                            border.width: 2
                            border.color: "black"
                            Text {
                                text: qsTr("None")
                                color: "black"
                                anchors.centerIn: parent
                                font.pointSize: 20
                                font.family: "Arial"
                            }

                            Rectangle {
                                width: parent.width + 10
                                height: parent.height + 10
                                color: Qt.rgba(0,0,0,0)
                                border.color: "white"
                                border.width: 2
                                anchors.centerIn: parent
                                visible: radioButton3.checked ? true : false
                            }
                            RadioButton {
                                id: radioButton3
                                visible: false
                                exclusiveGroup: stripePositionGroup
                            }
                            MouseArea {
                                anchors.fill: parent
                                onClicked: {
                                    radioButton3.checked = !radioButton3.checked
                                    if (radioButton3.checked)
                                        radioCheck = 3
                                }
                            }
                        }

                        Rectangle {
                            width: 180
                            height: 80
                            border.width: 2
                            border.color: "black"
                            Rectangle {
                                color: "black"
                                height: 15
                                width: parent.width
                                anchors.verticalCenter: parent.verticalCenter
                            }
                            Rectangle {
                                id: border
                                width: parent.width + 10
                                height: parent.height + 10
                                color: Qt.rgba(0,0,0,0)
                                border.color: "white"
                                border.width: 2
                                anchors.centerIn: parent
                                visible: radioButton.checked ? true : false
                            }
                            RadioButton {
                                id: radioButton
                                visible: false
                                exclusiveGroup: stripePositionGroup
                            }
                            MouseArea {
                                anchors.fill: parent
                                onClicked: {
                                    radioButton.checked = !radioButton.checked
                                    if (radioButton.checked)
                                        radioCheck = 0
                                }
                            }
                        }
                        Rectangle {
                            id: rectRotation
                            width: 180
                            height: 80
                            border.width: 2
                            border.color: "black"
                            Item {
                                anchors.fill: parent
                                clip: true
                                Rectangle {
                                    color: "black"
                                    height: 15
                                    width: parent.width + 15
                                    anchors.centerIn: parent
                                    rotation: 27
                                }
                            }
                            Rectangle {
                                width: rectRotation.width + 10
                                height: rectRotation.height + 10
                                color: Qt.rgba(0,0,0,0)
                                border.color: "white"
                                border.width: 2
                                anchors.centerIn: rectRotation
                                visible: radioButton1.checked ? true : false
                            }
                            RadioButton {
                                id: radioButton1
                                visible: false
                                exclusiveGroup: stripePositionGroup
                            }
                            MouseArea {
                                anchors.fill: parent
                                onClicked: {
                                    radioButton1.checked = !radioButton1.checked
                                    if (radioButton1.checked)
                                        radioCheck = 1
                                }
                            }
                        }

                        Rectangle {
                            width: 180
                            height: 80
                            border.width: 2
                            border.color: "black"
                            Rectangle {
                                width: parent.width + 10
                                height: parent.height + 10
                                color: Qt.rgba(0,0,0,0)
                                border.color: "white"
                                border.width: 2
                                anchors.centerIn: parent
                                visible: radioButton2.checked ? true : false
                            }
                            Rectangle {
                                color: "black"
                                width: 15
                                height: parent.height
                                anchors.horizontalCenter: parent.horizontalCenter
                            }
                            RadioButton {
                                id: radioButton2
                                visible: false
                                exclusiveGroup: stripePositionGroup
                            }
                            MouseArea {
                                anchors.fill: parent
                                onClicked: {
                                    radioButton2.checked = !radioButton2.checked
                                    if (radioButton2.checked)
                                        radioCheck = 2
                                }
                            }
                        }
                    }
                    Loader {
                        anchors.bottom: parent.bottom
                        sourceComponent: colorPicker
                    }
                }
            }

            Item {
                id: itemGauge
                width: parent.width
                height: 34
                anchors.top: itemStripe.bottom
                anchors.topMargin: 10
                Label {
                    id: labelGauge
                    color: "#8295a0"
                    text: qsTr("Size")
                    font.family: "arial"
                    font.pointSize: 14
                    anchors.right: parent.right
                    anchors.rightMargin: 290
                    anchors.verticalCenter: edit2.verticalCenter
                }
                MiniKeyNumInput {
                    id: edit2
                    anchors.right: parent.right
                    anchors.rightMargin: 130
                    width: 100
                    height: 34
                    inputWidth: 100 //parent.width * 0.3
                    opacity: 0.7
                    onInputFocusChanged: {
                        if (edit2.inputFocus) {
                            backGround.visible = true
                            backGround.opacity = 0.5
                            keyNum.visible = true
                            keyNum.titleText = labelGauge.text
                            keyNum.currentValue = edit2.inputText //wireModel.getStructValue2("Gauge","current") //"1.12mm"
                            keyNum.minvalue = wireModel.getStructValue2("Gauge","min") //"1.00mm"
                            keyNum.maxvalue = wireModel.getStructValue2("Gauge","max") //"10.99mm"
                        }
                    }

                    onInputTextChanged: {
                        if(detailIsChang)
                            return
                        spliceDetailsItem.selectText = hmiAdaptor.getStringValue(inputText) //inputText
                        spliceDetailsItem.selectWireGauge = wireModel.getStructValue3("Gauge",inputText);
                        spliceDetailsItem.selectWireAWG = wireModel.getStructValue3("awg",inputText);
                    }
                }
            }
            Item {
                id: itemType
                width: parent.width
                height: 34
                anchors.top: itemGauge.bottom
                anchors.topMargin: 10
                Label {
                    id: labelType
                    color: "#8295a0"
                    text: qsTr("Conductor")
                    font.family: "arial"
                    font.pointSize: 14
                    anchors.right: parent.right
                    anchors.rightMargin: 290
                    anchors.verticalCenter: typeSwitch.verticalCenter
                }
                Switch2 {
                    id: typeSwitch
                    width: parent.width * 0.4
                    height: 34
                    anchors.left: parent.left
                    anchors.leftMargin: width + 10
                    textLeft: qsTr("Copper")
                    textRight: qsTr("Alum")
                    state: "left"
                    opacity: 0.8
                    onStateChanged: {
                        if(detailIsChang)
                            return
                        if (state == "left")
                            spliceDetailsItem.selectWireType = 0
                        else if (state == "right")
                            spliceDetailsItem.selectWireType = 1
                    }
                }
            }

            Rectangle {
                id: line3
                anchors.top: itemType.bottom
                anchors.topMargin: 5
                anchors.left: parent.left
                anchors.leftMargin: 10
                width: parent.width-20
                color: "#375566"
                height: 1
            }

            Item {
                id: itemSide
                width: parent.width
                height: 34
                anchors.top: line3.bottom
                anchors.topMargin: 64
                z: 3
                Label {
                    id: labelSide
                    color: "#8295a0"
                    text: qsTr("Side")
                    font.family: "arial"
                    font.pointSize: 14
                    anchors.right: parent.right
                    anchors.rightMargin: 290
                    anchors.verticalCenter: wireDirection.verticalCenter
                }
                Switch2 {
                    id: wireDirection
                    width: parent.width * 0.4
                    height: 34
                    anchors.left: parent.left
                    anchors.leftMargin: width + 10
                    textLeft: qsTr("Left")
                    textRight: qsTr("Right")
                    state: "left"
                    opacity: 0.8
                    onStateChanged: {
                        if(detailIsChang)
                            return
                        if (spliceDetailsItem.selectDirection != wireDirection.state)
                            spliceDetailsItem.selectDirection = wireDirection.state
                    }
                }
            }
            Item {
                id: itemLocation
                width: parent.width
                height: 34
                anchors.top: itemSide.bottom
                anchors.topMargin: 15
                Label {
                    id: labelLocation
                    color: "#8295a0"
                    text: qsTr("Location") //VERTICAL
                    font.family: "arial"
                    font.pointSize: 14
                    anchors.right: parent.right
                    anchors.rightMargin: 290
                    anchors.verticalCenter: basicSwitch.verticalCenter
                }
                Switch2 {
                    id: basicSwitch
                    width: parent.width * 0.4
                    height: 34
                    anchors.left: parent.left
                    anchors.leftMargin: width + 10
                    textLeft: qsTr("Basic")
                    textRight: qsTr("Adv")
                    state: "left"
                    opacity: 0.8
                    onOnChanged: {
                        if (basicSwitch.state == "left") {
                            column1.visible = false
                        } else {
                            column1.visible = true
                        }
                    }
                }
            }
            Column {
                id: column1
                anchors.top: itemLocation.bottom
                anchors.topMargin: 20
                anchors.left: parent.left
                anchors.leftMargin: 20
                anchors.right: parent.right
                spacing: 10
                visible: false
                ExclusiveGroup {
                    id: tabPositionGroup;
                }
                ExclusiveGroup {
                    id: tabPositionGroup2;
                }
                Item {
                    width: parent.width
                    height: 30
                    Label {
                        id: labelTop
                        text: qsTr("Top")
                        font.pointSize: 14
                        font.family: "arial"
                        color: "#8295a0"
                        anchors.right: parent.right
                        anchors.rightMargin: 210
                    }
                    Image {
                        anchors.right: parent.right
                        anchors.rightMargin: 10
                        anchors.verticalCenter: labelTop.verticalCenter
                        source: "qrc:/images/images/up.png"
                    }
                    MouseArea {
                        id: mouse1
                        anchors.fill: parent
                        property bool isDialog: false
                        onClicked: {
                            if (spliceDetailsItem.changeTop()) {
                                mainRoot.showDialog(true,true,qsTr("OK"),qsTr("CANCEL"),"","",qsTr("Would you want to move the activated wire to the selected position?"))
                                isDialog = true
                                return
                            }
                            topRadio.checked = !topRadio.checked
                        }
                        Connections {
                            target: mainRoot
                            onDialogReturn: {
                                if (!mouse1.isDialog)
                                    return
                                if (reb) {
                                    topRadio.checked = !topRadio.checked
                                    mouse1.isDialog = false
                                }
                            }
                        }
                    }
                    RadioButton {
                        id: topRadio
                        scale: 2
                        checked: false
                        anchors.left: parent.left
                        anchors.leftMargin: 80
                        anchors.verticalCenter: labelTop.verticalCenter
                        exclusiveGroup: tabPositionGroup
                        onCheckedChanged: {
                            if (detailIsChang)
                                return
                            if (checked)
                                spliceDetailsItem.selectLocation = "top"
                        }
                    }
                }

                Item {
                    width: parent.width
                    height: 30
                    Label {
                        id: labelMiddle
                        text: qsTr("Middle")
                        font.pointSize: 14
                        font.family: "arial"
                        color: "#8295a0"
                        anchors.right: parent.right
                        anchors.rightMargin: 210
                    }
                    MouseArea {
                        anchors.fill: parent
                        onClicked: midRadio.checked = !midRadio.checked
                    }

                    RadioButton {
                        id: midRadio
                        scale: 2
                        anchors.left: parent.left
                        anchors.leftMargin: 80
                        anchors.verticalCenter: labelMiddle.verticalCenter
                        exclusiveGroup: tabPositionGroup
                        onCheckedChanged: {
                            if (detailIsChang)
                                return
                            if (checked)
                                spliceDetailsItem.selectLocation = "middle"
                        }
                    }
                }
                Item {
                    width: parent.width
                    height: 30
                    Label {
                        id: labelBottom
                        text: qsTr("Bottom")
                        font.pointSize: 14
                        font.family: "arial"
                        color: "#8295a0"
                        anchors.right: parent.right
                        anchors.rightMargin: 210
                    }
                    Image {
                        anchors.right: parent.right
                        anchors.rightMargin: 10
                        anchors.verticalCenter: labelBottom.verticalCenter
                        source: "qrc:/images/images/down.png"
                    }
                    MouseArea {
                        id: mouse2
                        anchors.fill: parent
                        property bool isDialog: false
                        onClicked: {
                            if (spliceDetailsItem.changeBottom()) {
                                mainRoot.showDialog(true,true,qsTr("OK"),qsTr("CANCEL"),"","",qsTr("Would you want to move the activated wire to the selected position?"))
                                isDialog = true
                                return
                            }
                            bottomRadio.checked = !bottomRadio.checked
                        }
                        Connections {
                            target: mainRoot
                            onDialogReturn: {
                                if (!mouse2.isDialog)
                                    return
                                if (reb) {
                                    bottomRadio.checked = !bottomRadio.checked
                                    mouse2.isDialog = false
                                }
                            }
                        }
                    }
                    RadioButton {
                        id: bottomRadio
                        scale: 2
                        anchors.left: parent.left
                        anchors.leftMargin: 80
                        anchors.verticalCenter: labelBottom.verticalCenter
                        exclusiveGroup: tabPositionGroup
                        onCheckedChanged: {
                            if (detailIsChang)
                                return
                            if (checked)
                                spliceDetailsItem.selectLocation = "bottom"
                        }
                    }
                }
            }
            Rectangle {
                id: line2
                anchors.bottom: save.top
                anchors.bottomMargin: 10
                anchors.left: parent.left
                anchors.leftMargin: 10
                width: parent.width-20
                color: "#375566"
                height: 1
                z:11
            }

            Item {
                id: type
                width: parent.width
                height: 34
                anchors.top: line3.bottom
                anchors.topMargin: 15
                z: 10

                Label {
                    id: typeText
                    color: "#8295a0"
                    text: qsTr("Type")
                    font.family: "arial"
                    font.pointSize: 14
                    anchors.right: parent.right
                    anchors.rightMargin: 290
                }
                MyCombox {
                    id: typeDirection
                    width: parent.width * 0.4
                    height: 34
                    anchors.left: parent.left
                    anchors.leftMargin: width + 10
                    items: [
                    { lang: "n/a", img: "" },
                    { lang: "DIN", img: "" },
                    { lang: "ISO", img: "" },
                    { lang: "SAE", img: "" },
                    { lang: "JIS", img: "" }

                    ]
                    backGroundColor: "#052a40"
                    dropDownColor: "#052a40"
                    onCurrentTextChanged: {
                        spliceDetailsItem.selectModuleType = currentText
                    }
                }
            }

            CButton {
                id: editExistingSplice
                text: qsTr("EDIT EXISTING\nSPLICE")
                pointSize: 12
                anchors.bottom: parent.bottom
                width: parent.width * 0.5
                anchors.right: save.left
                anchors.rightMargin: 10
                onClicked: {
                    spliceDetailsItem.clear()
                    edit1.inputText = ""
                    backGround.visible = true
                    backGround.opacity = 0.5
                    addWireLibrary.visible = true
                    addWireLibrary.listModel = spliceModel

                    addWireLibrary.titleName = qsTr("Splice Library")
                    addWireLibrary.componentName = qsTr("Splice Name")
                    addWireLibrary.componentData = qsTr("Date Created")
                    addWireLibrary.componentMiddle = qsTr("User Name")
                    addWireLibrary.componenttype = qsTr("Cross Section")
                    addWireLibrary.componentCount = qsTr("Total Wires")
                }
                z:11

            }

            CButton {
                id: save
                text: qsTr("SAVE TO WIRE\nLIBRARY")
                pointSize: 12
                anchors.bottom: parent.bottom
                width: parent.width * 0.5
                anchors.right: parent.right
                anchors.rightMargin: 10
                onClicked: {
                    var wireType = typeSwitch.state == "left" ? 0 : 1
                    var side = wireDirection.state == "left" ? 0 : 1
                    var verside = basicSwitch.state == "left" ? 0 : 1
                    var positionside;
                    if (topRadio.checked)
                        positionside = 0;
                    else if (midRadio.checked)
                        positionside = 1;
                    else if (bottomRadio.checked)
                        positionside = 2;

                    wireModel.insertValueToTable("insert",wireName.inputText,-1,
                                                 hmiAdaptor.getCurrentOperatorId(),
                                                 rectcolor.color,
                                                 itemStripe.color,
                                                 itemStripe.stripeType,
                                                 spliceDetailsItem.selectWireGauge,
                                                 spliceDetailsItem.selectWireAWG,
                                                 wireType,side,verside,positionside,
                                                 typeDirection.currentText
                                                 )
                }
            }

        }

        Page {
            id: weldSettting
            Rectangle {
                anchors.topMargin: tabBar.height
                anchors.top: parent.top
                anchors.fill: parent
                color: "#052a40"
            }
            ListModel {
                id: settingsModel
                Component.onCompleted: {
                      initSettings()
                }
            }
            ListModel {
                id: settingsModel2
                Component.onCompleted: {
                    settingsModel2.append({"topText":   qsTr(""),
                                           "bottomText":spliceModel.getStructValue("Time-","current"),
                                           "maxText":   spliceModel.getStructValue("Time-","max"),
                                           "minText":   spliceModel.getStructValue("Time-","min")})
                    settingsModel2.append({"topText":   qsTr(""),
                                           "bottomText":spliceModel.getStructValue("Time+","current"),
                                           "maxText":   spliceModel.getStructValue("Time+","max"),
                                           "minText":   spliceModel.getStructValue("Time+","min")})
                    settingsModel2.append({"topText":   qsTr(""),
                                           "bottomText":spliceModel.getStructValue("Power-","current"),
                                           "maxText":   spliceModel.getStructValue("Power-","max"),
                                           "minText":   spliceModel.getStructValue("Power-","min")})
                    settingsModel2.append({"topText":   qsTr(""),
                                           "bottomText":spliceModel.getStructValue("Power+","current"),
                                           "maxText":   spliceModel.getStructValue("Power+","max"),
                                           "minText":   spliceModel.getStructValue("Power+","min")})
                    settingsModel2.append({"topText":   qsTr(""),
                                           "bottomText":spliceModel.getStructValue("Pre-Height-","current"),
                                           "maxText":   spliceModel.getStructValue("Pre-Height-","max"),
                                           "minText":   spliceModel.getStructValue("Pre-Height-","min")})
                    settingsModel2.append({"topText":   qsTr(""),
                                           "bottomText":spliceModel.getStructValue("Pre-Height+","current"),
                                           "maxText":   spliceModel.getStructValue("Pre-Height+","max"),
                                           "minText":   spliceModel.getStructValue("Pre-Height+","min")})
                    settingsModel2.append({"topText":   qsTr(""),
                                           "bottomText":spliceModel.getStructValue("Post-Height-","current"),
                                           "maxText":   spliceModel.getStructValue("Post-Height-","max"),
                                           "minText":   spliceModel.getStructValue("Post-Height-","min")})
                    settingsModel2.append({"topText":   qsTr(""),
                                           "bottomText":spliceModel.getStructValue("Post-Height+","current"),
                                           "maxText":   spliceModel.getStructValue("Post-Height+","max"),
                                           "minText":   spliceModel.getStructValue("Post-Height+","min")})
                }
            }
            Row {
                id: upper
                anchors.top: parent.top
                anchors.topMargin: tabBar.height + 5
                spacing: 20
                anchors.left: parent.left
                anchors.leftMargin: 100
                width: parent.width-20
                visible: true
                Text {
                    text: qsTr("Setting")
                    font.pointSize: 14
                    font.family: "arial"
                    color: "white"
                    width: (parent.width-100)/2
                    anchors.verticalCenter: parent.verticalCenter
                    horizontalAlignment: Qt.AlignHCenter
                }
                Text {
                    font.pointSize: 14
                    font.family: "arial"
                    width: (parent.width-100)/2
                    color: "white"
                    text: qsTr("Actual")
                    anchors.verticalCenter: parent.verticalCenter
                    horizontalAlignment: Qt.AlignHCenter
                }
            }

            Column {
                anchors.top: settingLayout.top
                anchors.left: settingLayout.right
                anchors.leftMargin: -130
                width: parent.width-20
                height: 250
                Repeater {
                    model: resultModel
                    Recsetting {
                        localbordercolor: "#ffffff" //"#48484a"
                        width: (settingLayout.width-120)/2
                        height: (settingLayout.height-60)/5
                        centervalue: bottomText
                    }
                }
            }

            Column {
                id: settingLayout
                anchors.top: parent.top
                anchors.topMargin: tabBar.height + 30
                anchors.left: parent.left
                anchors.leftMargin: 10
                width: parent.width-20
                height: 250
                Repeater {
                    id: repeater
                    model: settingsModel
                    Row {
                        width: (settingLayout.width-100)/2
                        height: (settingLayout.height-60)/5
                        property alias localbordercolor: tempRec.localbordercolor
                        Text {
                            id: lineTip
                            text: tipText
                            width: 100
                            color: "white"
                            font.pointSize: 16
                            font.family: "arial"
                            horizontalAlignment: Qt.AlignHCenter
                        }
                        Recsetting {
                            id: tempRec
                            headTitle: topText
                            centervalue: bottomText
                            width: (settingLayout.width-100)/2
                            height: (settingLayout.height-60)/5
                            onMouseAreaClick: {
                                creatWire.selectModel = 1
                                creatWire.selectIndex = index
                                backGround.visible = true
                                backGround.opacity = 0.5
                                if (repeater.model == settingsModel && index == 3 && bIsStep) {
                                    stepTimeSet.visible = true
                                } else {
                                    localbordercolor = "#05f91c"
                                    keyNum.visible = true
                                    keyNum.titleText = topText
                                    keyNum.currentValue = bottomText
                                    keyNum.minvalue = minText
                                    keyNum.maxvalue = maxText
                                }
                            }
                        }
                    }
                }
            }

            ListModel {
                id: qualityTitleModel
                Component.onCompleted: {
                    qualityTitleModel.append({"title":"Time","bottomText":""})
                    qualityTitleModel.append({"title":"Peak\nPower","bottomText":""})
                    qualityTitleModel.append({"title":"Pre-\nHeight","bottomText":""})
                    qualityTitleModel.append({"title":"Post-\nHeight","bottomText":""})

                }
            }

            Column {
                anchors.top: settingLayout2.top
                anchors.bottom: settingLayout2.bottom
                anchors.left: parent.left
                width: 100
                Repeater {
                    model: qualityTitleModel
                    Item {
                        width: (settingLayout2.width-120)/2
                        height: (settingLayout2.height)/4
                        Text {
                            color: "#ffffff"
                            font.family: "Arial"
                            font.pointSize: 16
                            text: title
                            anchors.centerIn: parent
                        }
                    }
                }
            }

            Column {
                anchors.top: settingLayout2.top
                anchors.bottom: settingLayout2.bottom
                anchors.left: settingLayout2.right
                anchors.leftMargin: -230
                width: parent.width-20
                Repeater {
                    model: qualityTitleModel
                    Item {
                        width: (settingLayout2.width-120)/2
                        height: (settingLayout2.height)/4
                        Recsetting {
                            localbordercolor: "#ffffff" //"#48484a"
                            width: (settingLayout2.width-120)/2
                            height: (settingLayout2.height)/8
                            anchors.centerIn: parent
                            centervalue: bottomText
                        }
                    }
                }
            }

            Text {
                font.pointSize: 16
                font.family: "arial"
                color: "white"
                text: qsTr("Quality Window")
                anchors.bottom: settingLayout2.top
                anchors.bottomMargin: 5
                anchors.left: parent.left
                anchors.leftMargin: 5
            }

            Column {
                id: settingLayout2
                anchors.top: settingLayout.bottom
                anchors.left: parent.left
                anchors.leftMargin: 110
                width: parent.width-20
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 10
                Repeater {
                    id: repeater2
                    model: settingsModel2
                    Recsetting {
                        headTitle: topText
                        centervalue: bottomText
                        width: (settingLayout2.width-100)/2
                        height: (settingLayout2.height)/8
                        onMouseAreaClick: {
                            creatWire.selectModel = 2
                            creatWire.selectIndex = index
                            backGround.visible = true
                            backGround.opacity = 0.5
//                            if (repeater.model == settingsModel && index == 2 && bIsStep) {
//                                stepTimeSet.visible = true
//                            } else {
                                localbordercolor = "#05f91c"
                                keyNum.visible = true
                                keyNum.titleText = topText
                                keyNum.currentValue = bottomText
                                keyNum.minvalue = minText
                                keyNum.maxvalue = maxText
//                            }
                        }
                    }
                }
            }



        }
    }


    TabBar {
        width: Screen.width * 0.3
        id: tabBar
        currentIndex: swipeView.currentIndex
        anchors.top: parent.top
        height: Screen.height * 0.08
        spacing: 0
        onCurrentIndexChanged: {
            if (currentIndex == 0)
            {
                spliceDetailsItem.centerFuncVisable = true
                wireLibrary.visible = true
                wirelibrary.visible = true
                addWire.visible = true
                bottomButton.visible = false
                hmiAdaptor.operateProcessExec("Stop")
            }
            else if (currentIndex == 1)
            {
                spliceDetailsItem.centerFuncVisable = false
                wireLibrary.visible = false
                wirelibrary.visible = false
                addWire.visible = false
                bottomButton.visible = true
                setProcessData()
                if (bIsEditSplice)
                    hmiAdaptor.setProcess("Edit")
                else
                    hmiAdaptor.setProcess("Create")
                hmiAdaptor.operateProcessExec("Execute")
                hmiAdaptor.operateProcessExec("Start")
            }
        }

        TabButton {
            height: parent.height
            Rectangle {
                anchors.fill: parent
                color:  "#052a40"  //tabBar.currentIndex == 0 ? "black" : "#48484a"
            }
            Text {
                anchors.centerIn: parent
                font.family: "arial"
                font.pointSize: 17.5
                text: qsTr("WIRE BUILDER")
                color: tabBar.currentIndex == 0 ? "white" : "#969ea5"
            }
            Rectangle {
                anchors.left: parent.left
                anchors.leftMargin: 10
                width: parent.width-10
                height: 6
                color:  "#F79428"
                anchors.bottom: parent.bottom
                visible: tabBar.currentIndex == 0 ? true : false
            }

            onClicked: {
                settingRightArea.visible = false
            }
        }
        TabButton {
            height: parent.height
            Rectangle {
                anchors.fill: parent
                color:  "#052a40"  //tabBar.currentIndex == 0 ? "black" : "#48484a"
            }
            Text {
                anchors.centerIn: parent
                font.family: "arial"
                font.pointSize: 17.5
                text: qsTr("WELD SETTINGS")
                color: tabBar.currentIndex == 1 ? "white" : "#969ea5"
            }
            Rectangle {
                anchors.right: parent.right
                anchors.rightMargin: 10
                width: parent.width-10
                height: 6
                color:  "#F79428"
                anchors.bottom: parent.bottom
                visible: tabBar.currentIndex == 1 ? true : false
            }
        }
    }

    Rectangle {
        id: pickerBg
        anchors.fill: parent
        color: "black"
        opacity: 0.5
        z: 9
        visible: false
        MouseArea {
            anchors.fill: parent
        }
    }
    Loader {
        id: colorLoader
        anchors.centerIn: parent
        z: 10
        onSourceComponentChanged: {
            if (sourceComponent != null)
                pickerBg.visible = true
            else
                pickerBg.visible = false
        }
    }


    Item {
        id: rightArea
        anchors.left: swipeView.right
        width: Screen.width * 0.7
        height: parent.height // * 0.5

        Rectangle {
            anchors.fill: parent
            color: "#626465"
            MouseArea {
                anchors.fill: parent
            }
        }
        MyLineEdit {
            id: edit1
            width: parent.width*0.6
            height: 50
            anchors.top: parent.top
            inputWidth: parent.width * 0.6
            inputHeight: 48
            defaultText: qsTr("SPLICE NAME")
            anchors.topMargin: 8
            anchors.left: parent.left
            anchors.leftMargin: 20
            clip: true
        }
        Label {
            id: spliceDetails
            anchors.top: edit1.bottom
            anchors.topMargin: 10
            anchors.left: edit1.left
            text: qsTr("SpliceDetails")
            font.pointSize: 16
            font.family: "arial"
            color: "white"
        }
        Label {
            id: spliceDetailsTips
            anchors.top: spliceDetails.bottom
            anchors.topMargin: 10
            anchors.left: spliceDetails.left
            text: qsTr("TOTAL CROSS SECTION ")
            font.pointSize: 12
            font.family: "arial"
            color: "white"
            opacity: 0.5
        }
        Label {
            id: spliceDetailsTip2
            anchors.top: spliceDetails.bottom
            anchors.topMargin: 10
            anchors.left: spliceDetailsTips.right
            text: "0mm²"
            font.pointSize: 12
            font.family: "arial"
            color: "white"
            opacity: 0.5
            onTextChanged: {

                if (firstComeIn)
                    return
//                if (crossSection)
//                    return
                if (crossSection == true ) // && bIsEditSplice == false
                {
                    spliceModel.setStructValue("Total Cross",spliceDetailsTip2.text)
                    spliceModel.calculateSpliceData()
                    initSettings()
                    crossSection = false
                }
            }
        }
        Text {
            id: insulation
            anchors.top: spliceDetails.bottom
            anchors.topMargin: 10
            anchors.left: spliceDetailsTip2.right
            font.pointSize: 12
            font.family: "arial"
            color: "white"
            opacity: 0.5
        }

        Switch2 {
            id: wireSwitch
            anchors.bottom: spliceDetailsItem.top
            anchors.bottomMargin: 10
            anchors.right: parent.right
            anchors.rightMargin: 20
            textLeft: qsTr("Wire")
            textRight: qsTr("Image")
            state: "left"
            width: parent.width * 0.25
        }

        SpliceDetails {
            id: spliceDetailsItem
            width: Screen.width * 0.8
            height: Screen.height *0.5
            anchors.top: spliceDetailsTips.bottom
            anchors.topMargin: 10
            anchors.bottom: addWire.top
            anchors.bottomMargin: 10
            anchors.left: spliceDetails.left
            anchors.right: parent.right
            anchors.rightMargin: 20
            centerVisable: true
            onNoWireSelected: {
                forground.visible = noWire
            }
        }

        Item {
            id: selectImage
            visible: wireSwitch.state == "left" ? false : true
            anchors.fill: spliceDetailsItem
            onVisibleChanged: {
                if (visible)
                    spliceImage.source = spliceModel.getStructValue("PicPath","") == " " ? "qrc:/images/images/bg.png" : spliceModel.getStructValue("PicPath","")
            }
            Image {
                anchors.fill: parent
                source: "qrc:/images/images/bg.png"
            }

            Image {
                id: spliceImage
                anchors.fill: parent
            }
            Text {
                anchors.right: parent.right
                font.pointSize: 20
                font.family: "arial"
                color: "white"
                text: qsTr("Click to Select Picture")
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    imageLoader.source = "qrc:/UI/MyFileDialog.qml"
                }
                Connections {
                    target: imageLoader.item
                    onSignalFileDialogCancel: {
                        imageLoader.source = ""
                    }
                    onSignalChoseFile: {
                        imageLoader.source = ""
                        var path = hmiAdaptor.copyFileToPath(fileName)
                        if (path != "") {
                            spliceImage.source = "file:///"+path
                            spliceModel.setStructValue("PicPath",spliceImage.source)
                        }
                    }
                }
            }
        }
        Loader {
            id: imageLoader
            anchors.fill: parent
        }

        Row {
            id: bottomButton
            anchors.left: wireLibrary.left
            anchors.top: wireLibrary.top
            spacing: 24
            height: 61
            width: (spliceDetailsItem.width-72)/2
            visible: false
            CButton {
                pointSize: 14
                width: (spliceDetailsItem.width-72)/4
                text: qsTr("ADVANCED\nSETTING")
                onClicked: {
                    settingRightArea.visible = true
                }
            }
            CButton {
                pointSize: 14
                width: (spliceDetailsItem.width-72)/4
                text: qsTr("Graph")
                onClicked: {
                    myCanvas.visible = !myCanvas.visible
                }
            }
            CButton {
                pointSize: 14
                width: (spliceDetailsItem.width-72)/4
                text: qsTr("Cancel")
                onClicked: {
                    mainRoot.popStackView()
                }
            }
        }


        CButton {
            id: wireLibrary
            pointSize: 14
            width: (spliceDetailsItem.width-72)/4
            anchors.right: wirelibrary.left
            anchors.rightMargin: 24
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 14
            text: qsTr("WIRE LIBRARY")
            onClicked: {
                backGround.visible = true
                backGround.opacity = 0.5
                addWireLibrary.listModel = wireModel

                addWireLibrary.visible = true
                wireModel.setTemplateModelList()

                addWireLibrary.titleName = qsTr("Wire Library")
                addWireLibrary.componentName = qsTr("WireName")
                addWireLibrary.componentData = qsTr("DateCreated")
                addWireLibrary.componentMiddle = qsTr("OperatorName")
                addWireLibrary.componenttype = qsTr("Color")
                addWireLibrary.componentCount = qsTr("Gauge")
            }
        }
        CButton {
            id: wirelibrary
            pointSize: 14
            width: (spliceDetailsItem.width-72)/4
            anchors.right: addWire.left
            anchors.rightMargin: 24
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 14
            text: qsTr("+ ADD WIRE")
            onClicked: {
                wireModel.createNew()
                spliceDetailsItem.addWire()
            }

        }
        CButton {
            id: addWire
            pointSize: 14
            width: (spliceDetailsItem.width-72)/4
            anchors.right: saveSplice.left
            anchors.rightMargin: 24
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 14
            iconSource: "qrc:/images/images/cancel.png"
            text: qsTr("DELETE WIRE")
            onClicked: spliceDetailsItem.deleteWire()

        }
        CButton {
            id: saveSplice
            pointSize: 14
            anchors.right: spliceDetailsItem.right
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 14
            width: (spliceDetailsItem.width-72)/4
            text: qsTr("SAVE SPLICE")
            onClicked: {

                var list = spliceDetailsItem.saveAllWire()

                if (edit1.inputText.length == 0)
                {
                    dialog.visible = true
                    backGround.visible = true
                    backGround.opacity = 0.5
                    return;
                }
                spliceModel.setStructValue("SpliceName",edit1.inputText);
                spliceModel.setStructValue("OperatorId",hmiAdaptor.getCurrentOperatorId());
                spliceModel.setStructValue("Total Cross",spliceDetailsTip2.text)
                spliceModel.setStructValue("WireMap",list)

                spliceModel.setStructValue("Energy",settingsModel.get(0).bottomText);
                spliceModel.setStructValue("Trigger Pressure",settingsModel.get(1).bottomText);
                spliceModel.setStructValue("Weld Pressure",settingsModel.get(2).bottomText);
                spliceModel.setStructValue("Amplitude",settingsModel.get(3).bottomText);
                spliceModel.setStructValue("Width",settingsModel.get(4).bottomText);

                spliceModel.setStructValue("Time-",settingsModel2.get(0).bottomText);
                spliceModel.setStructValue("Time+",settingsModel2.get(1).bottomText);
                spliceModel.setStructValue("Power-",settingsModel2.get(2).bottomText);
                spliceModel.setStructValue("Power+",settingsModel2.get(3).bottomText);
                spliceModel.setStructValue("Pre-Height-",settingsModel2.get(4).bottomText);
                spliceModel.setStructValue("Pre-Height+",settingsModel2.get(5).bottomText);
                spliceModel.setStructValue("Post-Height-",settingsModel2.get(6).bottomText);
                spliceModel.setStructValue("Post-Height+",settingsModel2.get(7).bottomText);

                spliceModel.setStructValue("Step-Energy",stepSetModel.get(0).centerText);
                spliceModel.setStructValue("Step-Time",stepSetModel.get(1).centerText);
                spliceModel.setStructValue("Step-Power",stepSetModel.get(2).centerText);
                spliceModel.setStructValue("Amplitude B",stepSetModel.get(4).centerText);

                spliceModel.setStructValue("ShrinkId",shrinkSet.shrinkId );
                spliceModel.setStructValue("ShrinkTemp",shrinkSet.shrinkTemp);
                spliceModel.setStructValue("ShrinkTime",shrinkSet.shrinkTime);
                spliceModel.setProcessValue("ShrinkLock",shrinkSet.shrinkLock);



                spliceModel.setStructValue("WeldModel",weldListModel.model1)
                spliceModel.setStructValue("StepModel",weldListModel.model2)
                spliceModel.setStructValue("Pre Burst",weldSettingModel.get(0).textValue)
                spliceModel.setStructValue("After Burst",weldSettingModel.get(1).textValue)
                spliceModel.setStructValue("Squeeze Time",weldSettingModel.get(2).textValue)
                spliceModel.setStructValue("Hold Time",weldSettingModel.get(3).textValue)

                spliceModel.setStructValue("ActualWidth",widthModel.get(1).textValue)
                spliceModel.setStructValue("ActualHeight",heightModel.get(1).textValue)
                spliceModel.setStructValue("DisplayWidth",widthModel.get(0).textValue)
                spliceModel.setStructValue("DisplayHeight",heightModel.get(0).textValue)

//                spliceModel.setStructValue("Unload Time",loadValue.inputText)
//                spliceModel.setStructValue("Load Time",loadValue2.inputText)

//                spliceModel.setStructValue("Anti-Side",thirdSwitchModel.get(0).switchState == "left" ? true : false)
//                spliceModel.setStructValue("Cut Off",cutteronoroff.state == "left" ? true : false)
                spliceModel.setStructValue("Insulation",thirdSwitchModel.get(0).switchState == "left" ? true : false)

//                spliceModel.setStructValue("CutterTime",cutterModel.get(0).switchState == "left" ? true : false)
//                spliceModel.setStructValue("CutterPeakPower",cutterModel.get(1).switchState == "left" ? true : false)
//                spliceModel.setStructValue("CutterPreHeight",cutterModel.get(2).switchState == "left" ? true : false)
//                spliceModel.setStructValue("CutterPostHeight",cutterModel.get(3).switchState == "left" ? true : false)

                var spliceId = spliceModel.saveSplice(creatWire.bIsEditSplice)
                wireModel.updateSpliceIdToWire(list, spliceId)
                if(creatWire.bIsFromLib)
                    return

//                if (spliceId != -1 && !creatWire.bIsEditSplice)
                 mainRoot.signalSaveSplice(spliceId,creatWire.bIsEditSplice)
                 mainRoot.popStackView()

            }
        }
    }

    Item {
        id: settingRightArea
        anchors.left: swipeView.right
        width: Screen.width * 0.7
        height: parent.height
        visible: false
        clip: true
        Image {
            anchors.fill: parent
            source: "qrc:/images/images/bg.png"
            MouseArea {
                anchors.fill: parent
            }
        }
        Item {
            id: rect1
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.leftMargin: 15
            anchors.topMargin: 6
            anchors.right: parent.right
            clip: true
            height: 150
            Text {
                id: weldModel
                text: qsTr("Weld Mode")
                color: "white"
                font.pointSize: 16
                font.family: "arial"
                anchors.top: parent.top
                anchors.left: parent.left
                anchors.topMargin: 5
                anchors.leftMargin: 15
            }

            ExclusiveGroup {
                id: weldModelSetting
            }
            Component {
                id: buttonBackBlue
                Item {
                    Rectangle {
                        anchors.centerIn: parent
                        anchors.fill: parent
                        radius: 3
                        color: "#0079c1"
                        Rectangle{
                            anchors.fill: parent
                            anchors.margins: 1
                            radius: 3
                            anchors.centerIn: parent
                            color: "#0079c1"
                        }
                    }
                }
            }
            Component {
                id: buttonBackWhite
                Item {
                    Rectangle {
                        anchors.centerIn: parent
                        anchors.fill: parent
                        radius: 3
                        color: "#ffffff"
                        Rectangle{
                            anchors.fill: parent
                            anchors.margins: 1
                            radius: 3
                            anchors.centerIn: parent
                            color: "#ffffff"
                        }
                    }
                }
            }
            ListModel {
                id: weldListModel
                property var model1: 1
                property var model2: -1
                Component.onCompleted: {
                    weldListModel.append({"buttonName":qsTr("Energy")})
                    weldListModel.append({"buttonName":qsTr("Time")})
                    weldListModel.append({"buttonName":qsTr("Height")})
                    weldListModel.append({"buttonName":qsTr("Energy/Height")})
                    weldListModel.append({"buttonName":qsTr("Step-Energy")})
                    weldListModel.append({"buttonName":qsTr("Step-Time")})
                    weldListModel.append({"buttonName":qsTr("Step-Power")})
                }
            }

            Grid {
                anchors.top: weldModel.bottom
                anchors.topMargin: 6
                width: parent.width
                anchors.bottom: parent.bottom
                anchors.left: parent.left
                anchors.leftMargin: 20
                columnSpacing: 20
                rowSpacing: 10
                rows: 2
                columns: 4
                Repeater {
                    model: weldListModel
                    CButton {
                        id: weldModelButton
                        width: 200
                        height: 50
                        backgroundComponent: buttonBackWhite
                        text: buttonName
                        pointSize: 14
                        textColor: weldModelCheck.checked ? "white" : "black"
                        RadioButton {
                            id: weldModelCheck
                            exclusiveGroup: index < 4 ? tabPositionGroup : tabPositionGroup2
                            visible: false
                            checked: index < 4 ? spliceModel.getWeldMode("weld",index) : spliceModel.getWeldMode("step",index - 4)  //index == 0 ? true : false
                            onCheckedChanged: {
                                if (weldModelCheck.checked) {
                                    weldModelButton.backgroundComponent = buttonBackBlue
                                    if (index < 4)
                                        weldListModel.model1 = index
                                    else if (index >=4 )
                                        weldListModel.model2 = index - 4
                                }
                                else
                                    weldModelButton.backgroundComponent = buttonBackWhite
                            }
                        }
                        onClicked: {
                            if (index >=4 )
                                stepSetText =  buttonName
                            weldModelCheck.checked = !weldModelCheck.checked
                            if (index >= 4 && weldModelCheck.checked) {
                                bIsStep = true
                                weldListModel.model2 = index - 4
                            }
                            else if (index >= 4 && !weldModelCheck.checked){
                                bIsStep = false
                                weldListModel.model2 = -1
                            }
                            else if (index < 4 && weldModelCheck.checked)
                                weldListModel.model1 = index
                            else if (index < 4 && !weldModelCheck.checked)
                                weldListModel.model1 = -1
                        }
                    }
                }
            }
        }

        Item {
            id: rect2
            anchors.top: rect1.bottom
            anchors.left: rect1.left
            anchors.right: parent.right
            anchors.bottom: line5.top
            anchors.bottomMargin: 20
            clip: true
            ListModel {
                id: weldSettingModel
                Component.onCompleted: {
                    weldSettingModel.append({"headText":qsTr("Pre Burst:"),"textValue":spliceModel.getStructValue("Pre Burst","current"),"maxText":spliceModel.getStructValue("Pre Burst","max"),"minText":spliceModel.getStructValue("Pre Burst","min")})
                    weldSettingModel.append({"headText":qsTr("After Burst:"),"textValue":spliceModel.getStructValue("After Burst","current"),"maxText":spliceModel.getStructValue("After Burst","max"),"minText":spliceModel.getStructValue("After Burst","min")})
                    weldSettingModel.append({"headText":qsTr("Squeeze:"),"textValue":spliceModel.getStructValue("Squeeze Time","current"),"maxText":spliceModel.getStructValue("Squeeze Time","max"),"minText":spliceModel.getStructValue("Squeeze Time","min")})
                    weldSettingModel.append({"headText":qsTr("Hold:"),"textValue":spliceModel.getStructValue("Hold Time","current"),"maxText":spliceModel.getStructValue("Hold Time","max"),"minText":spliceModel.getStructValue("Hold Time","min")})
                }
            }
            Column {
                id: weldSetting
                property bool weldSetVisible: false
                anchors.top: parent.top
                anchors.left: parent.left
                anchors.leftMargin: 20
                width: (parent.width-20)/3
                height: parent.height*0.46+30
                clip: true
                spacing: 8
                Repeater {
                    id: weldRepeater
                    model: weldSettingModel
                    delegate: Item {
                        property alias myfocus: inputText.inputFocus
                        width: parent.width ///2-20
                        height: (weldSetting.height-30)/4
                        Text {
                            id: headName
                            anchors.top: parent.top
                            anchors.verticalCenter: parent.verticalCenter
                            verticalAlignment: Qt.AlignVCenter
                            anchors.left: parent.left
                            anchors.leftMargin: 10
                            width: parent.width/3 + 10
                            font.pointSize: 16
                            font.family: "arial"
                            text: headText
                            color: "white"
                            clip: true
                        }
                        MiniKeyNumInput {
                            id: inputText
                            anchors.verticalCenter: headName.verticalCenter
                            anchors.left: headName.right
                            width: parent.width/2
                            height: parent.height
                            inputWidth: parent.width/2
                            clip: true
                            inputText: textValue
                            onInputFocusChanged: {
                                if (inputText.inputFocus) {
                                    weldSetting.weldSetVisible = true
                                    creatWire.selectIndex = index
                                    backGround.visible = true
                                    backGround.opacity = 0.5
                                    keyNum.visible = true
                                    keyNum.titleText = headText
                                    keyNum.currentValue = textValue
                                    keyNum.minvalue = minText
                                    keyNum.maxvalue = maxText
                                }
                            }

                        }
                    }
                }
            }
//            Text {
//                id: cutterText
//                anchors.top: widthSettingText.top
//                anchors.left: widthSetting.right
//                verticalAlignment: Qt.AlignVCenter
//                text: qsTr("Cutter")
//                color: "white"
//                font.pointSize: 16
//                font.family: "arial"
//                height: parent.height * 0.1
//                visible: false
//            }

//            Switch2 {
//                id: cutteronoroff
//                visible: false
//                anchors.top: widthSetting.top
//                anchors.left: cutterText.left
//                width: loadValue.width - 20
//                height: loadValue.height
//                textLeft: qsTr("ON")
//                textRight: qsTr("OFF")
//                clip: true
//                state: spliceModel.getStructValue("Cut Off","current")
//                onStateChanged: {
//                    if (cutteronoroff.state == "left"){
//                        cutterColumn.visible = true
//                        loadName2.visible = true
//                        loadValue2.visible = true
//                    }
//                    else {
//                        cutterColumn.visible = false
//                        loadName2.visible = false
//                        loadValue2.visible = false
//                    }
//                }
//            }

//            ListModel {
//                id: cutterModel
//                Component.onCompleted: {
//                    cutterModel.append({"headText":qsTr("Time"),"switchState":"left"})
//                    cutterModel.append({"headText":qsTr("Peak Power"),"switchState":"left"})
//                    cutterModel.append({"headText":qsTr("Pre-Height"),"switchState":"left"})
//                    cutterModel.append({"headText":qsTr("Post-Height"),"switchState":"left"})
//                }
//            }

//            Column {
//                id: cutterColumn
//                anchors.top: loadValue2.bottom
//                anchors.topMargin: 8
//                anchors.left: cutteronoroff.left
//                width: (parent.width-40)/3
//                height: parent.height*0.46+30
//                clip: true
//                spacing: 8
//                visible: cutteronoroff.state == "left" ? true : false
//                Repeater {
//                    model: cutterModel
//                    delegate: Item {
//                        height: (cutterColumn.height-30)/4
//                        width: parent.width
//                        Text {
//                            id: cutterColumnName
//                            anchors.verticalCenter: parent.verticalCenter
//                            verticalAlignment: Qt.AlignVCenter
//                            anchors.left: parent.left
//                            anchors.leftMargin: 10
//                            width: parent.width/3
//                            font.pointSize: 16
//                            font.family: "arial"
//                            text: headText
//                            color: "white"
//                            clip: true
//                        }
//                        Switch2 {
//                            id: columnOnoroff
//                            anchors.verticalCenter: cutterColumnName.verticalCenter
//                            anchors.left: cutterColumnName.right
//                            anchors.leftMargin: 13
//                            width: loadValue.width - 20
//                            height: loadValue.height
//                            textLeft: qsTr("ON")
//                            textRight: qsTr("OFF")
//                            state: switchState
//                            clip: true
//                            onStateChanged: {
//                            }
//                        }
//                    }
//                }
//            }


            Text {
                id: widthSettingText
                anchors.top: weldSetting.top
                anchors.left: weldSetting.right
                anchors.leftMargin: 10
                verticalAlignment: Qt.AlignVCenter
                text: qsTr("Width off-set:")
                color: "white"
                font.pointSize: 16
                font.family: "arial"
                height: parent.height * 0.1
            }
            ListModel {
                id: widthModel
                Component.onCompleted: {
                    widthModel.append({"widthText":qsTr("Displayed:"),"textValue":spliceModel.getStructValue("DisplayedWidth","current"),"maxText":spliceModel.getStructValue("DisplayedWidth","max"),"minText":spliceModel.getStructValue("DisplayedWidth","min")})
                    widthModel.append({"widthText":qsTr("Actual:"),"textValue":spliceModel.getStructValue("ActualWidth","current"),"maxText":spliceModel.getStructValue("ActualWidth","max"),"minText":spliceModel.getStructValue("ActualWidth","min")})
                }
            }
            Column {
                id: widthSetting
                property bool widthSetVisible: false
                anchors.top: widthSettingText.bottom
                anchors.topMargin: 8
                anchors.left: weldSetting.right
                anchors.leftMargin: 10
                width: (parent.width-40)/3
                height: parent.height*0.24 + 8
                clip: true
                spacing: 8
                Repeater {
                    id: widthRepeater
                    model: widthModel
                    delegate: Item {
                        property alias myfocus: widthValue.inputFocus
                        width: parent.width  ///2-20
                        height: (parent.height-8)/2
                        Text {
                            id: widthName
                            anchors.verticalCenter: parent.verticalCenter
                            verticalAlignment: Qt.AlignVCenter
                            anchors.left: parent.left
                            width: parent.width/3
                            font.pointSize: 16
                            font.family: "arial"
                            text: widthText
                            color: "white"
                            clip: true
                        }
                        MiniKeyNumInput {
                            id: widthValue
                            anchors.left: widthName.right
                            anchors.verticalCenter: widthName.verticalCenter
                            width: parent.width/2
                            height: parent.height
                            inputWidth: parent.width/2
                            clip: true
                            inputText: textValue
                            onInputFocusChanged: {
                                if (widthText == qsTr("Displayed:"))
                                    return
                                if (widthValue.inputFocus) {
                                    widthSetting.widthSetVisible = true
                                    creatWire.selectIndex = index
                                    backGround.visible = true
                                    backGround.opacity = 0.5
                                    keyNum.visible = true
                                    keyNum.titleText = widthText
                                    keyNum.currentValue = textValue
                                    keyNum.minvalue = minText
                                    keyNum.maxvalue = maxText
                                }
                            }
                        }
                    }
                }
            }
            Text {
                id: heightSettingText
                anchors.top: widthSetting.bottom
                anchors.topMargin: 8
                anchors.left: widthSettingText.left
                verticalAlignment: Qt.AlignVCenter
                text: qsTr("Height off-set:")
                color: "white"
                font.pointSize: 16
                font.family: "arial"
                height: parent.height * 0.12
            }
            ListModel {
                id: heightModel
                Component.onCompleted: {
                    heightModel.append({"heightText":qsTr("Displayed:"),"textValue":spliceModel.getStructValue("DisplayedHeight","current"),"maxText":spliceModel.getStructValue("DisplayedHeight","max"),"minText":spliceModel.getStructValue("DisplayedHeight","min")})
                    heightModel.append({"heightText":qsTr("Actual:"),"textValue":spliceModel.getStructValue("ActualHeight","current"),"maxText":spliceModel.getStructValue("ActualHeight","max"),"minText":spliceModel.getStructValue("ActualHeight","min")})
                }
            }
            Column {
                id: heightSetting
                property bool heightSetVisible: false
                anchors.top: heightSettingText.bottom
                anchors.topMargin: 8
                anchors.left: widthSettingText.left
                width: (parent.width-40)/3
                height: parent.height*0.24 + 8
                clip: true
                spacing: 8
                Repeater {
                    id: heightRepeater
                    model: heightModel
                    delegate: Item {
                        property alias myfocus: heightValue.inputFocus
                        width: parent.width ///2-20
                        height: (parent.height-8)/2
                        Text {
                            id: heightName
                            anchors.verticalCenter: parent.verticalCenter
                            verticalAlignment: Qt.AlignVCenter
                            anchors.left: parent.left
                            width: parent.width/3
                            font.pointSize: 16
                            font.family: "arial"
                            text: heightText
                            color: "white"
                            clip: true
                        }
                        MiniKeyNumInput {
                            id: heightValue
                            anchors.left: heightName.right
                            anchors.verticalCenter: heightName.verticalCenter
                            width: parent.width/2
                            height: parent.height
                            inputWidth: parent.width/2
                            clip: true
                            inputText: textValue
                            onInputFocusChanged: {
                                if (heightText == qsTr("Displayed:"))
                                    return
                                if (heightValue.inputFocus) {
                                    heightSetting.heightSetVisible = true
                                    creatWire.selectIndex = index
                                    backGround.visible = true
                                    backGround.opacity = 0.5
                                    keyNum.visible = true
                                    keyNum.titleText = heightText
                                    keyNum.currentValue = textValue
                                    keyNum.minvalue = minText
                                    keyNum.maxvalue = maxText
                                }
                            }
                        }
                    }
                }
            }
            ListModel {
                id: thirdSwitchModel
                Component.onCompleted: {
//                    thirdSwitchModel.append({"thirdSwitchText":qsTr("Anti-Side:"),"switchState":spliceModel.getStructValue("Anti-Side","current")})
//                    thirdSwitchModel.append({"thirdSwitchText":qsTr("Cut Off:"),"switchState":spliceModel.getStructValue("Cut Off","current")})
                    thirdSwitchModel.append({"thirdSwitchText":qsTr("Insulation:"),"switchState":spliceModel.getStructValue("Insulation","current")})
                }
            }
            Column {
                id: thirdSwitch
                anchors.top: weldSetting.bottom
                anchors.topMargin: 0
//                anchors.bottom: parent.bottom
                anchors.left: weldSetting.left
                height: parent.height*0.12
                width: (parent.width-40)/3 -25
                spacing: 24
                clip: true
                Repeater {
                    model: thirdSwitchModel
                    delegate: Item {
                        height: thirdSwitch.height //(thirdSwitch.height-12)/2
                        width: parent.width
                        Text {
                            id: thirdSwitchName
                            anchors.verticalCenter: parent.verticalCenter
                            verticalAlignment: Qt.AlignVCenter
                            anchors.left: parent.left
                            anchors.leftMargin: 10
                            width: parent.width/3
                            font.pointSize: 16
                            font.family: "arial"
                            text: thirdSwitchText
                            color: "white"
                            clip: true
                        }
                        Switch2 {
                            id: onoroff
                            anchors.verticalCenter: thirdSwitchName.verticalCenter
                            anchors.left: thirdSwitchName.right
                            anchors.leftMargin: 20
                            width: (rect2.width-40)/6 //rect2.width/4 - 60
                            height: rect2.height * 0.12
                            textLeft: qsTr("ON")
                            textRight: qsTr("OFF")
                            state: switchState
                            clip: true
                            onStateChanged: {
                                thirdSwitchModel.set(index,{"switchState":onoroff.state})
                                if (thirdSwitchText == "Insulation:")
                                {
                                    if (onoroff.state == "left"){
                                        instulationButton.visible = true
                                        insulation.visible = true
                                    }
                                    else {
                                        instulationButton.visible = false
                                        insulation.visible = false
                                    }
                                }
//                                else if(thirdSwitchText == "Anti-Side:")
//                                {
//                                    if (onoroff.state == "left"){
//                                        loadValue.visible = true
//                                        loadName.visible = true
//                                    }
//                                    else {
//                                        loadValue.visible = false
//                                        loadName.visible = false
//                                    }
//                                }
                            }
                        }
                    }
                }
            }
//            Text {
//                id: loadName
//                anchors.top: thirdSwitch.top
//                anchors.topMargin: 100
//                anchors.left: weldSetting.left
//                anchors.leftMargin: 10
//                width: (parent.width/2-40)/3
//                height: parent.height*0.06
//                verticalAlignment: Qt.AlignVCenter
//                font.pointSize: 16
//                font.family: "arial"
//                text: qsTr("Unload:")
//                color: "white"
//                clip: true
//                visible: false
//            }
//            MiniKeyNumInput {
//                id: loadValue
//                visible: false
//                anchors.verticalCenter: loadName.verticalCenter
//                anchors.left: loadName.right
//                anchors.leftMargin: -30
//                width: parent.width/4 - 60
////                horizontalAlignment: Qt.AlignHCenter
//                height: parent.height*0.12
//                inputWidth: parent.width/4-80
////                inputHeight: parent.height*0.12
////                inputColor: "white"
//                clip: true
//                inputText: spliceModel.getStructValue("Unload Time","current")  //qsTr("0.00mm")
//                onInputFocusChanged: {
//                    if (loadValue.inputFocus) {
//                        backGround.visible = true
//                        backGround.opacity = 0.5
//                        keyNum.visible = true
//                        keyNum.titleText = loadName.text
//                        keyNum.currentValue = loadValue.inputText
//                        keyNum.minvalue = spliceModel.getStructValue("Unload Time","min")
//                        keyNum.maxvalue = spliceModel.getStructValue("Unload Time","max")
//                    }
//                }
//            }
//            Text {
//                id: loadName2
//                anchors.top: cutteronoroff.bottom
//                anchors.topMargin: 32
//                anchors.left: cutteronoroff.left
//                anchors.leftMargin: 10
//                width: loadName.width //(parent.width/2-40)/3
//                height: loadName.height //thirdSwitch.height/3-6
//                verticalAlignment: Qt.AlignVCenter
//                font.pointSize: 16
//                font.family: "arial"
//                text: qsTr("Load:")
//                color: "white"
//                clip: true
//                visible: cutteronoroff.state == "left" ? true : false
//            }
//            MiniKeyNumInput {
//                id: loadValue2
//                visible: loadName2.visible
//                anchors.verticalCenter: loadName2.verticalCenter
//                anchors.left: loadName2.right
//                anchors.leftMargin: -15
//                width: parent.width/4-60
////                horizontalAlignment: Qt.AlignHCenter
//                height: parent.height*0.12
//                inputWidth: parent.width/4-80
////                inputHeight: parent.height*0.12
////                inputColor: "white"
//                clip: true
//                inputText: spliceModel.getStructValue("Load Time","current") //qsTr("0.00mm")
//                onInputFocusChanged: {
//                    if (loadValue2.inputFocus) {
//                        backGround.visible = true
//                        backGround.opacity = 0.5
//                        keyNum.visible = true
//                        keyNum.titleText = loadName2.text
//                        keyNum.currentValue = loadValue2.inputText
//                        keyNum.minvalue = spliceModel.getStructValue("Load Time","min")
//                        keyNum.maxvalue = spliceModel.getStructValue("Load Time","max")
//                    }
//                }
//            }
//            Text {
//                id: instulationText
//                anchors.top: loadName2.bottom
//                anchors.topMargin: 6
//                anchors.left: loadName.left
//                width: (parent.width/2-40)/3
//                height: thirdSwitch.height/3-6
//                verticalAlignment: Qt.AlignVCenter
//                text: ""
//                color: "white"
//                font.pointSize: 16
//                font.family: "arial"
//            }

            CButton {
                id: instulationButton
//                anchors.verticalCenter: instulationText.verticalCenter
//                anchors.verticalCenterOffset: 8
//                anchors.left: instulationText.right
                anchors.right: thirdSwitch.right
                anchors.top: thirdSwitch.bottom
                anchors.topMargin: 15
                width: parent.width/4-20
                height: parent.height*0.12 + 10
                text: qsTr("Insulation Setting")
                onClicked: {
                    backGround.visible = true
                    backGround.opacity = 0.5
                    shrinkSet.visible = true
                }
            }
        }
        Rectangle {
            id: line5
            anchors.bottom: bottomRow.top
            anchors.bottomMargin: 10
            anchors.left: rect1.left
            anchors.right: rect1.right
            border.color: "white"
            border.width: 2
            height: 4
        }
        Row {
            id: bottomRow
            spacing: 30
            anchors.right: parent.right
            anchors.rightMargin: 20
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 10
            CButton {
                width: 200
                text: qsTr("Back")
                textColor: "white"
                onClicked: {
                    settingRightArea.visible = false
                }
            }

            CButton {
                width: 200
                text: qsTr("Save")
                textColor: "white"
                visible: true
                onClicked: {
                    spliceModel.setProcessValue("WeldModel",weldListModel.model1)
                    spliceModel.setProcessValue("StepModel",weldListModel.model2)
                    spliceModel.setProcessValue("Pre Burst",weldSettingModel.get(0).textValue)
                    spliceModel.setProcessValue("After Burst",weldSettingModel.get(1).textValue)
                    spliceModel.setProcessValue("Squeeze Time",weldSettingModel.get(2).textValue)
                    spliceModel.setProcessValue("Hold Time",weldSettingModel.get(3).textValue)

                    spliceModel.setProcessValue("ActualWidth",widthModel.get(1).textValue)
                    spliceModel.setProcessValue("ActualHeight",heightModel.get(1).textValue)
                    spliceModel.setProcessValue("DisplayWidth",widthModel.get(0).textValue)
                    spliceModel.setProcessValue("DisplayHeight",heightModel.get(0).textValue)

//                    spliceModel.setProcessValue("Unload Time",loadValue.inputText)
//                    spliceModel.setProcessValue("Load Time",loadValue2.inputText)

//                    spliceModel.setProcessValue("Anti-Side",thirdSwitchModel.get(0).switchState == "left" ? true : false)
//                    spliceModel.setProcessValue("Cut Off",cutteronoroff.state == "left" ? true : false)
                    spliceModel.setProcessValue("Insulation",thirdSwitchModel.get(0).switchState == "left" ? true : false)

//                    spliceModel.setProcessValue("CutterTime",cutterModel.get(0).switchState == "left" ? true : false)
//                    spliceModel.setProcessValue("CutterPeakPower",cutterModel.get(1).switchState == "left" ? true : false)
//                    spliceModel.setProcessValue("CutterPreHeight",cutterModel.get(2).switchState == "left" ? true : false)
//                    spliceModel.setProcessValue("CutterPostHeight",cutterModel.get(3).switchState == "left" ? true : false)

                    settingRightArea.visible = false

                }
            }
        }
    }
    Rectangle {
        id: backGround
        anchors.fill: parent
        color: "black"
        opacity: 0.7
        visible: false
        MouseArea {
            anchors.fill: parent
            onClicked: {

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
            text: qsTr("Please Input Splice Name")
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
    ShrinkSet {
        id: shrinkSet
        anchors.centerIn: parent
        width: 639
        height: 390
        visible: false
        Component.onCompleted: {
            shrinkSet.shrinkId = spliceModel.getStructValue("ShrinkId","");
            shrinkSet.shrinkTemp = spliceModel.getStructValue("ShrinkTemp","")
            shrinkSet.shrinkTime = spliceModel.getStructValue("ShrinkTime","")
            shrinkSet.shrinkLock = spliceModel.getStructValue("shrinkLock","")
            insulation.text = qsTr("  Insulation: ") + shrinkSet.shrinkId + qsTr(" Temp:") + shrinkSet.shrinkTemp + qsTr(" Time:") + shrinkSet.shrinkTime
        }

        onSureClick: {
            shrinkSet.visible = false
            backGround.opacity = 0
            backGround.visible = false
            insulation.text = qsTr("  Insulation: ") + shrinkSet.shrinkId + qsTr(" Temp:") + shrinkSet.shrinkTemp + qsTr(" Time:") + shrinkSet.shrinkTime
            hmiAdaptor.addInsulation(shrinkSet.shrinkId,shrinkSet.shrinkTemp,shrinkSet.shrinkTime)
        }
        onCancelClick: {
            shrinkSet.visible = false
            backGround.opacity = 0
            backGround.visible = false
        }
    }
    Image {
        id: stepTimeSet
        anchors.centerIn: parent
        width: 700
        height: 525
        source: "qrc:/images/images/dialogbg.png"
        visible: false
        Component.onCompleted: {
            stepSetModel.append({"myVisable":false,"topText":qsTr("Step-Energy"),"centerText":spliceModel.getStructValue("Step-Energy","current"),"maxText":spliceModel.getStructValue("Step-Energy","max"),"minText":spliceModel.getStructValue("Step-Energy","min")})
            stepSetModel.append({"myVisable":false,"topText":qsTr("Step-Time"),"centerText":spliceModel.getStructValue("Step-Time","current"),"maxText":spliceModel.getStructValue("Step-Time","max"),"minText":spliceModel.getStructValue("Step-Time","min")})
            stepSetModel.append({"myVisable":false,"topText":qsTr("Step-Power"),"centerText":spliceModel.getStructValue("Step-Power","current"),"maxText":spliceModel.getStructValue("Step-Power","max"),"minText":spliceModel.getStructValue("Step-Power","min")})
            stepSetModel.append({"myVisable":true,"topText":qsTr("Amplitude A"),"centerText":spliceModel.getStructValue("Amplitude A","current"),"maxText":spliceModel.getStructValue("Amplitude A","max"),"minText":spliceModel.getStructValue("Amplitude A","min")})
            stepSetModel.append({"myVisable":true,"topText":qsTr("Amplitude B"),"centerText":spliceModel.getStructValue("Amplitude B","current"),"maxText":spliceModel.getStructValue("Amplitude B","max"),"minText":spliceModel.getStructValue("Amplitude B","min")})
        }
        onVisibleChanged: {
            if (visible)
            {
                if (stepSetText == qsTr("Step-Energy")) {
                    stepSetModel.set(0,{"myVisable":true})
                    stepSetModel.set(1,{"myVisable":false})
                    stepSetModel.set(2,{"myVisable":false})
                }
                else if (stepSetText == qsTr("Step-Time")) {
                    stepSetModel.set(1,{"myVisable":true})
                    stepSetModel.set(0,{"myVisable":false})
                    stepSetModel.set(2,{"myVisable":false})
                }
                else if (stepSetText == qsTr("Step-Power")) {
                    stepSetModel.set(2,{"myVisable":true})
                    stepSetModel.set(0,{"myVisable":false})
                    stepSetModel.set(1,{"myVisable":false})
                }
            }
        }


        Text {
            id: stepTitle
            anchors.top: parent.top
            anchors.topMargin: 24
            anchors.horizontalCenter: parent.horizontalCenter
            font.family: "arial"
            font.pixelSize: 25
            color: "white"
            text: stepSetText
        }
        ListModel {
            id: stepSetModel
        }
        Row {
            id: stepRow
            anchors.top: stepTitle.bottom
            anchors.topMargin: 50
            anchors.left: parent.left
            anchors.leftMargin: 24
            anchors.right: parent.right
            anchors.rightMargin: 24
            spacing: 20
            Repeater {
                id: stepRepeater
                model: stepSetModel
                Recsetting {
                    visible: myVisable
                    headTitle: topText
                    centervalue: centerText
                    width: (stepRow.width-40)/3
                    height: 154
                    onMouseAreaClick: {
                        creatWire.selectIndex = index
                        localbordercolor = "#05f91c"
                        keyNum.visible = true
                        keyNum.titleText = topText
                        keyNum.currentValue = centerText
                        keyNum.minvalue = minText
                        keyNum.maxvalue = maxText
                    }
                }
            }
        }
        CButton {
            id: okButton
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 24
            anchors.right: parent.right
            anchors.rightMargin: 20
            width: parent.width/3
            text: qsTr("OK")
            pixelSize: 20
            iconSource: "qrc:/images/images/OK.png"
            onClicked: {
                backGround.visible = false
                stepTimeSet.visible = false
            }
        }
    }
    AddExistingSpliceWire {
        id: addWireLibrary
        anchors.centerIn: parent
        width: parent.width*0.9
        height: parent.width*0.4
        visible: false
        listModel: spliceModel

        titleName: qsTr("Wire Library")
        componentName: qsTr("WireName")
        componentData: qsTr("DateCreated")
        componentMiddle: qsTr("OperatorName")
        componenttype: qsTr("Color")
        componentCount: qsTr("Gauge")
        onSignalAddExistCancel: {
            backGround.visible = false
            backGround.opacity = 0
            addWireLibrary.visible = false
        }
        onSignalAddExistSelectClick: {
            backGround.visible = false
            backGround.opacity = 0
            addWireLibrary.visible = false
            //modelId
            if (addWireLibrary.listModel == wireModel) {
                currentSpliceId = modelId
                wireModel.addFromLibrary(modelId)
                spliceDetailsItem.addWireFromLibrary()
            }
            else if (addWireLibrary.listModel == spliceModel)
            {
                spliceModel.editNew(modelId)
                var list = new Array
                list = spliceModel.getWireIdList()
                editSplice(list)
            }
        }
        onVisibleChanged: {
            if (addWireLibrary.visible)
                addWireLibrary.clearSelect()
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
                if (edit2.inputFocus) {
                    edit2.inputText = keyNum.inputText
                    edit2.inputFocus = false
                } else if (heightSetting.heightSetVisible) {
                    heightModel.set(creatWire.selectIndex,{"textValue":keyNum.inputText})
                    heightRepeater.itemAt(creatWire.selectIndex).myfocus = false
                    heightSetting.heightSetVisible = false
                } else if (widthSetting.widthSetVisible) {
                    widthModel.set(creatWire.selectIndex,{"textValue":keyNum.inputText})
                    widthRepeater.itemAt(creatWire.selectIndex).myfocus = false
                    widthSetting.widthSetVisible = false
                } else if (weldSetting.weldSetVisible) {
                    weldSettingModel.set(creatWire.selectIndex,{"textValue":keyNum.inputText})
                    weldRepeater.itemAt(creatWire.selectIndex).myfocus = false
                    weldSetting.weldSetVisible = false
                } else if (stepTimeSet.visible) {
                    stepRepeater.model.set(creatWire.selectIndex,{"centerText":keyNum.inputText})
                    stepRepeater.itemAt(creatWire.selectIndex).localbordercolor = "#0079c1"
                    keyNum.visible = false
                    keyNum.inputText = ""
                    keyNum.tempValue = ""
                    return
                } else {
                    var tempString;
                    if (creatWire.selectModel == 1)
                    {
                        if (creatWire.selectIndex == 0)
                            tempString = hmiAdaptor.dataProcessing("Energy", keyNum.inputText)
                        else if (creatWire.selectIndex == 1)
                            tempString = hmiAdaptor.dataProcessing("T.P", keyNum.inputText)
                        else if (creatWire.selectIndex == 2)
                            tempString = hmiAdaptor.dataProcessing("W.P", keyNum.inputText)
                        else if (creatWire.selectIndex == 3)
                            tempString = hmiAdaptor.dataProcessing("Amplitude", keyNum.inputText)
                        else if (creatWire.selectIndex == 4)
                            tempString = hmiAdaptor.dataProcessing("Width", keyNum.inputText)

                        repeater.model.set(creatWire.selectIndex,{"bottomText":tempString})
                        repeater.itemAt(creatWire.selectIndex).localbordercolor = "#0079c1"
                    }
                    else if (creatWire.selectModel == 2)
                    {

                        if (creatWire.selectIndex == 0)
                            tempString = hmiAdaptor.dataProcessing("Time-", keyNum.inputText)
                        else if (creatWire.selectIndex == 1)
                            tempString = hmiAdaptor.dataProcessing("Time+", keyNum.inputText)
                        else if (creatWire.selectIndex == 2)
                            tempString = hmiAdaptor.dataProcessing("Power-", keyNum.inputText)
                        else if (creatWire.selectIndex == 3)
                            tempString = hmiAdaptor.dataProcessing("Power+", keyNum.inputText)
                        else if (creatWire.selectIndex == 4)
                            tempString = hmiAdaptor.dataProcessing("Pre-Height-", keyNum.inputText)
                        else if (creatWire.selectIndex == 5)
                            tempString = hmiAdaptor.dataProcessing("Pre-Height+", keyNum.inputText)
                        else if (creatWire.selectIndex == 6)
                            tempString = hmiAdaptor.dataProcessing("Post-Height-", keyNum.inputText)
                        else if (creatWire.selectIndex == 7)
                            tempString = hmiAdaptor.dataProcessing("Post-Height+", keyNum.inputText)
                        repeater2.model.set(creatWire.selectIndex,{"bottomText":tempString})
                        repeater2.itemAt(creatWire.selectIndex).localbordercolor = "#0079c1"
                    }
                }
                backGround.visible = false
                backGround.opacity = 0
                keyNum.visible = false
                keyNum.inputText = ""
                keyNum.tempValue = ""
                freshProcess()

            } else if (index == 11) {
                if (edit2.inputFocus) {
                    edit2.inputFocus = false
                }
//                else if (loadValue2.inputFocus) {
//                    loadValue2.inputFocus = false
//                } else if (loadValue.inputFocus) {
//                    loadValue.inputFocus = false
//                }
                else if (heightSetting.heightSetVisible) {
                    heightRepeater.itemAt(creatWire.selectIndex).myfocus = false
                    heightSetting.heightSetVisible = false
                } else if (widthSetting.widthSetVisible) {
                    widthRepeater.itemAt(creatWire.selectIndex).myfocus = false
                    widthSetting.widthSetVisible = false
                } else if (weldSetting.weldSetVisible) {
                    weldRepeater.itemAt(creatWire.selectIndex).myfocus = false
                    weldSetting.weldSetVisible = false
                } else if (stepTimeSet.visible) {
                    stepRepeater.itemAt(creatWire.selectIndex).localbordercolor = "#0079c1"
                    keyNum.visible = false
                    keyNum.inputText = ""
                    keyNum.tempValue = ""
                    return
                } else {

                    if (creatWire.selectModel == 1)
                    {
                        repeater.itemAt(creatWire.selectIndex).localbordercolor = "#0079c1"
                    }
                    else if (creatWire.selectModel == 2)
                    {
                        repeater2.itemAt(creatWire.selectIndex).localbordercolor = "#0079c1"
                    }

//                    repeater.itemAt(creatWire.selectIndex).localbordercolor = "#0079c1"
                }
                backGround.visible = false
                backGround.opacity = 0
                keyNum.visible = false
                keyNum.inputText = ""
                keyNum.tempValue = ""
            }
        }
//        onInputTextChanged: {
//            if (keyNum.inputText != "") {
//                if (edit2.inputFocus) {
//                    edit2.inputText = keyNum.inputText
//                }
////                else if (loadValue2.inputFocus) {
////                    loadValue2.inputText = keyNum.inputText
////                } else if (loadValue.inputFocus) {
////                    loadValue.inputText = keyNum.inputText
////                }
//                else if (heightSetting.heightSetVisible) {
//                    heightModel.set(creatWire.selectIndex,{"textValue":keyNum.inputText})
//                } else if (widthSetting.widthSetVisible) {
//                    widthModel.set(creatWire.selectIndex,{"textValue":keyNum.inputText})
//                } else if (weldSetting.weldSetVisible) {
//                    weldSettingModel.set(creatWire.selectIndex,{"textValue":keyNum.inputText})
//                } else if (stepTimeSet.visible) {
//                    stepRepeater.model.set(creatWire.selectIndex,{"centerText":keyNum.inputText})
//                } else {
//                    if (creatWire.selectModel == 1)
//                    {
//                        repeater.model.set(creatWire.selectIndex,{"bottomText":keyNum.inputText})
//                    }
//                    else if (creatWire.selectModel == 2)
//                    {
//                        repeater2.model.set(creatWire.selectIndex,{"bottomText":keyNum.inputText})
//                    }
////                    repeater.model.set(creatWire.selectIndex,{"bottomText":keyNum.inputText})
//                }
//            }
//        }
    }

    Image {
        anchors.centerIn: myCanvas
        width: myCanvas.width + 50
        height: myCanvas.height + 100
        source: "qrc:/images/images/bg.png"
        visible: myCanvas.visible
        MouseArea {
            anchors.fill: parent
            onClicked: myCanvas.visible = false
        }
    }

    MyCanvas {
        id: myCanvas
        visible: false
        width: Screen.width * 0.43
        height: Screen.height * 0.5
        anchors.centerIn: parent
    }

//    Rectangle {
//        width: Screen.width * 0.63
//        height: Screen.height * 0.7
//        anchors.centerIn: parent
//        Image {
//            anchors.fill: parent
//            source: "qrc:/images/images/bg.png"
//        }
//        MyCanvas {
//            id: myCanvas
//            width: Screen.width * 0.43
//            height: Screen.height * 0.5
////            width: qualityParent.width
////            height: Screen.height * 0.5
////            anchors.top: qualityWindowTitle.bottom
////            anchors.topMargin: 30
//        }
//    }
}
