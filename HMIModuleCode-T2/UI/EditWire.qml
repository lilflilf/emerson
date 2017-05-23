/*******************************************************************
Copyright:http://www.sinux.com.cn
Date:2016/12/26
Author:zhangjiyong&lilongfei
Description:edit wire set interface
The function interface:
    signalSaveSplice()
*******************************************************************/
import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import QtQuick.Window 2.2
import QtQuick.Controls 1.1

Item {
    id: creatWire
    width: Screen.width
    height: Screen.height
    signal signalSaveSplice()
    property int editWirdId: -1
    property bool detailIsChang: true
    property variant colorArray: ["#000000","#7f7f7f","#880015","#ED1C24","#FF7F27","#FFF200","#22B14C","#00A2E8",
        "#3F48CC","#A349A4","#ffffff","#c3c3c3","#b97a57","#ffaec9","#ffc90e","#efe4b0","#b5e61d","#99d9ea","#7092be","#c8bfe7"]

//    function wireChanged(selectColor,selectPosition,selectText)
//    {
//        spliceDetailsItem.selectColor = selectColor
//        spliceDetailsItem.selectText = selectText
//        spliceDetailsItem.selectPosition = selectPosition
//    }

    Component.onCompleted: {
        editWirdId = hmiAdaptor.getEditWireId()
        initPage()
    }

    function initPage()
    {
        if (creatWire.editWirdId == -1)
            return
        wireModel.addFromLibrary(creatWire.editWirdId)

//        WireModelHash.insert("WireType",metalType);
//        WireModelHash.insert("WireColor",wireElement.Color);
//        WireModelHash.insert("WireName",wireElement.WireName);
//        WireModelHash.insert("WireDirection",(int)wireElement.Side);
//        WireModelHash.insert("WirePosition",wireElement.Position);
//        WireModelHash.insert("WireBasic",wireElement.VerticalSide);
//        WireModelHash.insert("WireId",wireElement.WireID);

        wireName.inputText = wireModel.getStructValue("WireName")
        itemColor.color = wireModel.getStructValue("WireColor")
        itemStripe.color = wireModel.getStructValue2("StripeColor","")
        itemStripe.stripeType = wireModel.getStructValue3("StripeType","")
        itemGauge.text = wireModel.getStructValue2("Gauge","current")
        itemType.state = wireModel.getStructValue("WireType") == 0 ? "left" : "right";
        itemSide.state = wireModel.getStructValue("WireDirection") == 0 ? "left" : "right";
        itemLocation.state = wireModel.getStructValue("WireBasic") == 0 ? "left" : "right";
        column1.positionIndex = wireModel.getStructValue("WirePosition")
        typeDirection.currentText = wireModel.getStructValue("ModuleType")
    }

    SpliceDetails {
        id: spliceDetailsItem
//        width: Screen.width * 0.8
        anchors.left: swipeView.right
        anchors.leftMargin: 20
        height: Screen.height *0.5
        anchors.bottom: save.top
        anchors.bottomMargin: 10
        anchors.right: parent.right
        anchors.rightMargin: 20
        centerVisable: true
        Component.onCompleted: {
            spliceDetailsItem.safeChange(true)
            spliceDetailsItem.addWireFromLibrary()
            spliceDetailsItem.selectPosition = "rightList"
            spliceDetailsItem.safeChange(false)
        }

    }

    SwipeView {
        width: Screen.width * 0.3
        height: parent.height
        id: swipeView
        currentIndex: tabBar.currentIndex
        Page {
            id: wireBuilder
//            Connections {
//                target: spliceDetailsItem
//                onWireSelected: {
//                    //signal wireSelected(var selectColor,var selectDirection,var selectPosition,var selectText)
//                    forground.visible = false
//                    rectcolor.color = selectColor
//                    wireDirection.state = selectDirection
//                    edit2.inputText = selectText
//                    topRadio.checked = true
//                }
//                onChanging: {
//                    console.log("onChanging",bIsChang)
//                    detailIsChang = bIsChang
//                }
//            }

            Rectangle {
                anchors.top: parent.top
                anchors.fill: parent
                color: "#052a40"
            }
//            Rectangle {
//                id: forground
//                anchors.top: parent.top
//                anchors.fill: parent
//                color: "#052a40"
//                z:10
//                Label {
//                    id: nowire
//                    color: "#8295a0"
//                    text: qsTr("No Wires Selected")
//                    anchors.top: parent.top
//                    anchors.topMargin: tabBar.height + 15
//                    anchors.left: parent.left
//                    anchors.leftMargin: 10
//                    font.family: "arial"
//                    font.pointSize: 16
//                }
//            }

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
                maxSize: 20
            }
            Label {
                id: properties
                color: "#8295a0"
                text: qsTr("PROPERTIES")
                anchors.top: wireName.bottom
                anchors.left: parent.left
                anchors.leftMargin: 10
                anchors.topMargin: 10
                font.family: "arial"
                font.pointSize: 16
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
                            //colorLoader.source = "qrc:/UI/MyColor.qml"
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
                                if (pickColor == "")
                                    return
                                if (colorLoader.sourceComponent == colorPicker)
                                {
                                    itemColor.color = pickColor
                                    spliceDetailsItem.selectColor = pickColor
                                    colorLoader.sourceComponent = null
                                }
                                else if (colorLoader.sourceComponent == stripePicker)
                                {
                                    if (colorLoader.item.radioCheck == -1)
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
                property alias color: stripeBack.color
                property var stripeType: -1
//                onColorChanged: {
//                    if(detailIsChang)
//                        return
//                    spliceDetailsItem.selectWireStripeColor = itemStripe.color
//                }
//                onStripeTypeChanged: {
//                    if(detailIsChang)
//                        return
//                    spliceDetailsItem.selectWireStripeType = itemStripe.stripeType
//                }

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
                    color: "green"
                    anchors.right: parent.right
                    anchors.rightMargin: 130
                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            colorLoader.sourceComponent = stripePicker
                        }
                    }
                    Rectangle {
                        color: "black"
                        height: 5
                        width: parent.width
                        anchors.verticalCenter: parent.verticalCenter
                        visible: itemStripe.stripeType == 0 ? true : false
                    }
                    Rectangle {
                        color: "black"
                        height: 5
                        width: parent.width
                        anchors.centerIn: parent
                        rotation: 17
                        visible: itemStripe.stripeType == 1 ? true : false
                    }
                    Rectangle {
                        color: "black"
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
//                    Row {
//                        height: parent.height
//                        anchors.horizontalCenter: parent.horizontalCenter
//                        spacing: 20
//                        visible: itemStripe.stripeType == 3 ? true : false
//                        Rectangle {
//                            color: "black"
//                            width: 5
//                            height: parent.height
//                        }
//                        Rectangle {
//                            color: "black"
//                            width: 5
//                            height: parent.height
//                        }
//                    }
                }
            }

            Component {
                id: stripePicker
                Image {
                    property var radioCheck: -1
                    id: backStripe
//                    width: 550
//                    height: 270
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
//                            Row {
//                                height: parent.height
//                                anchors.horizontalCenter: parent.horizontalCenter
//                                spacing: 20
//                                Rectangle {
//                                    color: "black"
//                                    width: 5
//                                    height: parent.height
//                                }
//                                Rectangle {
//                                    color: "black"
//                                    width: 5
//                                    height: parent.height
//                                }
//                            }


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
                            width: 180
                            height: 80
                            border.width: 2
                            border.color: "black"
                            Rectangle {
                                color: "black"
                                height: 15
                                width: parent.width
                                anchors.centerIn: parent
                                rotation: 17
                            }
                            Rectangle {
                                width: parent.width + 10
                                height: parent.height + 10
                                color: Qt.rgba(0,0,0,0)
                                border.color: "white"
                                border.width: 2
                                anchors.centerIn: parent
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
//                        Rectangle {
//                            width: 180
//                            height: 80
//                            border.width: 2
//                            border.color: "black"
//                            Row {
//                                height: parent.height
//                                anchors.horizontalCenter: parent.horizontalCenter
//                                spacing: 20
//                                Rectangle {
//                                    color: "black"
//                                    width: 5
//                                    height: parent.height
//                                }
//                                Rectangle {
//                                    color: "black"
//                                    width: 5
//                                    height: parent.height
//                                }
//                            }


//                            Rectangle {
//                                width: parent.width + 10
//                                height: parent.height + 10
//                                color: Qt.rgba(0,0,0,0)
//                                border.color: "white"
//                                border.width: 2
//                                anchors.centerIn: parent
//                                visible: radioButton3.checked ? true : false
//                            }
//                            RadioButton {
//                                id: radioButton3
//                                visible: false
//                                exclusiveGroup: stripePositionGroup
//                            }
//                            MouseArea {
//                                anchors.fill: parent
//                                onClicked: {
//                                    radioButton3.checked = !radioButton3.checked
//                                    if (radioButton3.checked)
//                                        radioCheck = 3
//                                }
//                            }
//                        }
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
                property alias text: edit2.inputText
                Label {
                    id: labelGauge
                    color: "#8295a0"
                    text: qsTr("Gauge")
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
//                    inputHeight: 34//parent.height
//                    horizontalAlignment: Qt.AlignHCenter
//                    maxSize: 20
                    opacity: 0.7
                    onInputFocusChanged: {
                        if (edit2.inputFocus) {
                            backGround.visible = true
                            backGround.opacity = 0.5
                            keyNum.visible = true
                            keyNum.titleText = labelGauge.text
                            keyNum.currentValue = wireModel.getStructValue2("Gauge","current") //"1.12mm"
                            keyNum.minvalue = wireModel.getStructValue2("Gauge","min") //"1.00mm"
                            keyNum.maxvalue = wireModel.getStructValue2("Gauge","max") //"10.99mm"
                        }
                    }

                    onInputTextChanged: {
//                        if(detailIsChang)
//                            return
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
                property alias state: typeSwitch.state
                Label {
                    id: labelType
                    color: "#8295a0"
                    text: qsTr("Type of Wire")
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

            Label {
                id: position
                color: "#8295a0"
                text: qsTr("POSITION")
                anchors.top: line3.bottom
                anchors.topMargin: 5
                font.family: "arial"
                font.pointSize: 14
                opacity: 0.5
                anchors.left: parent.left
                anchors.leftMargin: 10
                visible: false
            }
            Item {
                id: itemSide
                width: parent.width
                height: 34
                anchors.top: position.bottom
                anchors.topMargin: 15
                property alias state: wireDirection.state
                visible: false
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
                property alias state: basicSwitch.state
                visible: false
                Label {
                    id: labelLocation
                    color: "#8295a0"
                    text: qsTr("LOCATION") //VERTICAL
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
//                        if (basicSwitch.state == "left") {
//                            column1.visible = false
//                        } else {
//                            column1.visible = true
//                        }
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
                property var positionIndex: -1
                onPositionIndexChanged: {
                    topRadio.checked = false
                    midRadio.checked = false
                    bottomRadio.checked = false

                    if (column1.positionIndex == 0)
                        topRadio.checked = true
                    else if(column1.positionIndex == 1)
                        midRadio.checked = true
                    else if (column1.positionIndex == 2)
                        bottomRadio.checked = true
                }

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
                                column1.positionIndex = 0
//                                spliceDetailsItem.selectLocation = "top"
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
                                column1.positionIndex = 1
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
                                column1.positionIndex = 2
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
//                    anchors.verticalCenter: wireDirection.verticalCenter
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
        }
    }

    CButton {
        id: save
        text: qsTr("SAVE")
        pointSize: 12
        anchors.bottom: parent.bottom
        width: swipeView.width * 0.5
        anchors.right: parent.right
        anchors.rightMargin: 10
        anchors.bottomMargin: 10
        onClicked: {
//          int WireModel::insertValueToTable(QString type,QString wireName,int wireId,int operatorId,QString color,QString stripeColor,int stripeType,int gauge, int awgGauge,int wireType,int side,int verside,int position)
            var wireType;
            var side;
            var location;
            var gauge;
            var awg;
            gauge = wireModel.getStructValue3("Gauge",itemGauge.text)
            awg = wireModel.getStructValue3("awg",itemGauge.text)

            wireType = itemType.state == "left" ? 0 : 1
            side = itemSide.state == "left" ? 0 : 1
            location = itemLocation.state == "left" ? 0 : 1
            wireModel.insertValueToTable("update",wireName.inputText,creatWire.editWirdId,hmiAdaptor.getCurrentOperatorId(),itemColor.color,
                                         itemStripe.color,itemStripe.stripeType,gauge,awg,wireType,side,location,column1.positionIndex,typeDirection.currentText)
            mainRoot.popStackView()
        }
    }



    TabBar {
        width: Screen.width * 0.3
        id: tabBar
        currentIndex: swipeView.currentIndex
        anchors.top: parent.top
        height: Screen.height * 0.08
        spacing: 0
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
    }
    Item {
        id: rightArea
        anchors.left: swipeView.right
        width: Screen.width * 0.7
        height: parent.height // * 0.5
        Loader {
            id: colorLoader
            anchors.left: parent.left
            anchors.leftMargin: 20
            anchors.top: parent.top
            anchors.topMargin: 100
            z: 10
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
                }
                backGround.visible = false
                backGround.opacity = 0
                keyNum.visible = false
                keyNum.inputText = ""
                keyNum.tempValue = ""
            } else if (index == 11) {
                if (edit2.inputFocus) {
                    edit2.inputFocus = false
                }
                backGround.visible = false
                backGround.opacity = 0
                keyNum.visible = false
                keyNum.inputText = ""
                keyNum.tempValue = ""
            }
        }
        onInputTextChanged: {
            if (keyNum.inputText != "") {
                if (edit2.inputFocus) {
                    edit2.inputText = keyNum.inputText
                }
            }
        }
    }

}
