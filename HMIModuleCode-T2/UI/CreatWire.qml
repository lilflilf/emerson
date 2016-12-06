import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import QtQuick.Window 2.2
import QtQuick.Controls 1.4

Item {
    id: creatWire
    width: Screen.width
    height: Screen.height
    signal signalSaveSplice()
    property int selectIndex: 0
    property bool detailIsChang: true
    property bool bIsStep: false
    property string stepSetText: ""
    property var totalGauge: 0
    property variant colorArray: ["#ff6699","#ff0033","#33FFCC","#cc99ff","#cc0099","#930202","#99ccff","#f79428",
        "#0000cc","Olive","#ffff33","#ffcc00","#cc9909","#66ff00","#009900","#00cc66","#3366ff","#cc33cc","#cc9966","#9400D3"]

    function wireChanged(selectColor,selectPosition,selectText)
    {
        spliceDetailsItem.selectColor = selectColor
        spliceDetailsItem.selectText = selectText
        spliceDetailsItem.selectPosition = selectPosition
    }
    function initSettings()
    {
        settingsModel.clear();
        settingsModel.append({"topText":"Energy","bottomText":spliceModel.getStructValue("Energy","current"),"maxText":spliceModel.getStructValue("Energy","max"),"minText":spliceModel.getStructValue("Energy","min")})
        settingsModel.append({"topText":"Trigger Pressure","bottomText":spliceModel.getStructValue("Trigger Pressure","current"),"maxText":spliceModel.getStructValue("Trigger Pressure","max"),"minText":spliceModel.getStructValue("Trigger Pressure","min")})
        settingsModel.append({"topText":"Amplitude","bottomText":spliceModel.getStructValue("Amplitude","current"),"maxText":spliceModel.getStructValue("Amplitude","max"),"minText":spliceModel.getStructValue("Amplitude","min")})
        settingsModel.append({"topText":"Weld Pressure","bottomText":spliceModel.getStructValue("Weld Pressure","current"),"maxText":spliceModel.getStructValue("Weld Pressure","max"),"minText":spliceModel.getStructValue("Weld Pressure","min")})
        settingsModel.append({"topText":"Width","bottomText":spliceModel.getStructValue("Width","current"),"maxText":spliceModel.getStructValue("Width","max"),"minText":spliceModel.getStructValue("Width","min")})

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

                }
                onChanging: {
                    detailIsChang = bIsChang
                } //
                onGaugeChanged: {
                    if (type == "add")
                        totalGauge+= value
                    else if (type == "sub")
                        totalGauge-= value
                    spliceDetailsTip2.text = spliceModel.getString("CrossSection",totalGauge)
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
                z:10
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
                defaultText: "WIRE NAME"
                maxSize: 20
                onTextChange: {
                    if (detailIsChang)
                        return
                    spliceDetailsItem.wireName = wireName.inputText
                }
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
                    Row {
                        height: parent.height
                        anchors.horizontalCenter: parent.horizontalCenter
                        spacing: 20
                        visible: itemStripe.stripeType == 3 ? true : false
                        Rectangle {
                            color: "black"
                            width: 5
                            height: parent.height
                        }
                        Rectangle {
                            color: "black"
                            width: 5
                            height: parent.height
                        }
                    }
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
                            Rectangle {
                                color: "black"
                                height: 5
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
                                height: 5
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
                                width: 5
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
                        Rectangle {
                            width: 180
                            height: 80
                            border.width: 2
                            border.color: "black"
                            Row {
                                height: parent.height
                                anchors.horizontalCenter: parent.horizontalCenter
                                spacing: 20
                                Rectangle {
                                    color: "black"
                                    width: 5
                                    height: parent.height
                                }
                                Rectangle {
                                    color: "black"
                                    width: 5
                                    height: parent.height
                                }
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
            }
            Item {
                id: itemSide
                width: parent.width
                height: 34
                anchors.top: position.bottom
                anchors.topMargin: 15
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
                                root.showDialog(true,true,"OK","CANCEL","Would you want to move the activated wire to the selected position?")
                                isDialog = true
                                return
                            }
                            topRadio.checked = !topRadio.checked
                        }
                        Connections {
                            target: root
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
                                root.showDialog(true,true,"OK","CANCEL","Would you want to move the activated wire to the selected position?")
                                isDialog = true
                                return
                            }
                            bottomRadio.checked = !bottomRadio.checked
                        }
                        Connections {
                            target: root
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
//                    settingsModel.append({"topText":"Energy","bottomText":spliceModel.getStructValue("Energy","current"),"maxText":spliceModel.getStructValue("Energy","max"),"minText":spliceModel.getStructValue("Energy","min")})
//                    settingsModel.append({"topText":"Trigger Pressure","bottomText":spliceModel.getStructValue("Trigger Pressure","current"),"maxText":spliceModel.getStructValue("Trigger Pressure","max"),"minText":spliceModel.getStructValue("Trigger Pressure","min")})
//                    settingsModel.append({"topText":"Amplitude","bottomText":spliceModel.getStructValue("Amplitude","current"),"maxText":spliceModel.getStructValue("Amplitude","max"),"minText":spliceModel.getStructValue("Amplitude","min")})
//                    settingsModel.append({"topText":"Weld Pressure","bottomText":spliceModel.getStructValue("Weld Pressure","current"),"maxText":spliceModel.getStructValue("Weld Pressure","max"),"minText":spliceModel.getStructValue("Weld Pressure","min")})
//                    settingsModel.append({"topText":"Width","bottomText":spliceModel.getStructValue("Width","current"),"maxText":spliceModel.getStructValue("Width","max"),"minText":spliceModel.getStructValue("Width","min")})

                }
            }
            ListModel {
                id: settingsModel2
                Component.onCompleted: {
                    settingsModel2.append({"topText":"Time","bottomText":spliceModel.getStructValue("Time-","current"),"maxText":spliceModel.getStructValue("Time-","max"),"minText":spliceModel.getStructValue("Time-","min")})
                    settingsModel2.append({"topText":"Time","bottomText":spliceModel.getStructValue("Time+","current"),"maxText":spliceModel.getStructValue("Time+","max"),"minText":spliceModel.getStructValue("Time+","min")})
                    settingsModel2.append({"topText":"Power","bottomText":spliceModel.getStructValue("Power-","current"),"maxText":spliceModel.getStructValue("Power-","max"),"minText":spliceModel.getStructValue("Power-","min")})
                    settingsModel2.append({"topText":"Power","bottomText":spliceModel.getStructValue("Power+","current"),"maxText":spliceModel.getStructValue("Power+","max"),"minText":spliceModel.getStructValue("Power+","min")})
                    settingsModel2.append({"topText":"Pre-Height","bottomText":spliceModel.getStructValue("Pre-Height-","current"),"maxText":spliceModel.getStructValue("Pre-Height-","max"),"minText":spliceModel.getStructValue("Pre-Height-","min")})
                    settingsModel2.append({"topText":"Pre-Height","bottomText":spliceModel.getStructValue("Pre-Height+","current"),"maxText":spliceModel.getStructValue("Pre-Height+","max"),"minText":spliceModel.getStructValue("Pre-Height+","min")})
                    settingsModel2.append({"topText":"Post-Height","bottomText":spliceModel.getStructValue("Post-Height-","current"),"maxText":spliceModel.getStructValue("Post-Height-","max"),"minText":spliceModel.getStructValue("Post-Height-","min")})
                    settingsModel2.append({"topText":"Post-Height","bottomText":spliceModel.getStructValue("Post-Height+","current"),"maxText":spliceModel.getStructValue("Post-Height+","max"),"minText":spliceModel.getStructValue("Post-Height+","min")})


                }
            }
            Row {
                id: upper
                anchors.top: parent.top
                anchors.topMargin: tabBar.height + 5
                spacing: 20
                anchors.left: parent.left
                anchors.leftMargin: 10
                width: parent.width-20
                visible: false
                Text {
                    text: qsTr("Lower Limit")
                    font.pointSize: 14
                    font.family: "arial"
                    color: "#8295a0"
                    width: (parent.width-20)/2
                    anchors.verticalCenter: parent.verticalCenter
                    horizontalAlignment: Qt.AlignHCenter
                }
                Text {
                    font.pointSize: 14
                    font.family: "arial"
                    width: (parent.width-20)/2
                    color: "#8295a0"
                    text: qsTr("Upper Limit")
                    anchors.verticalCenter: parent.verticalCenter
                    horizontalAlignment: Qt.AlignHCenter
                }
            }

            Grid {
                id: settingLayout
                anchors.top: parent.top
                anchors.topMargin: tabBar.height + 30
                anchors.left: parent.left
                anchors.leftMargin: 10
                width: parent.width-20
                anchors.bottom: bottomButton.top
                anchors.bottomMargin: 10
                rows: 4
                columns: 2
                columnSpacing: 30
                rowSpacing: 20
                Repeater {
                    id: repeater
                    model: settingsModel
                    Recsetting {
                        headTitle: qsTr(topText)
                        centervalue: qsTr(bottomText)
                        width: (settingLayout.width-30)/2
                        height: (settingLayout.height-60)/4
                        onMouseAreaClick: {
                            creatWire.selectIndex = index
                            backGround.visible = true
                            backGround.opacity = 0.5
                            if (repeater.model == settingsModel && index == 2 && bIsStep) {
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
            Row {
                id: bottomButton
                anchors.bottom: parent.bottom
                anchors.left: parent.left
                anchors.leftMargin: 10
                spacing: 10
                height: 61
                width: parent.width-20

                CButton {
                    pointSize: 14
                    width: (parent.width-10)/2
                    text: qsTr("QUALITY\nWINDOW")
                    onClicked: {
                        if (repeater.model == settingsModel){
                            repeater.model = settingsModel2
                            text = "WELD\nSETTINGS"
                            upper.visible = true
                        }
                        else {
                            text = "QUALITY\nWINDOW"
                            repeater.model = settingsModel
                            upper.visible = false
                        }
                    }
                }
                CButton {
                    pointSize: 14
                    width: (parent.width-10)/2
                    text: qsTr("ADVANCED\nSETTING")
                    onClicked: {
                        settingRightArea.visible = true
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

//        anchors.left: parent.left
//        anchors.leftMargin: 20
//        anchors.top: parent.top
//        anchors.topMargin: 100
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
            defaultText: "SPLICE NAME"
            anchors.topMargin: 8
            anchors.left: parent.left
            anchors.leftMargin: 20
            clip: true
            //displayText: qsTr("SPLICE NAME")
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
            text: qsTr("0mm")
            font.pointSize: 12
            font.family: "arial"
            color: "white"
            opacity: 0.5
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
        }
        CButton {
            id: wirelibrary
            pointSize: 14
            width: (spliceDetailsItem.width-72)/4
            anchors.right: addWire.left
            anchors.rightMargin: 24
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 14
            text: qsTr("ADD WIRE")
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
                signalSaveSplice()
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
                text: qsTr("Weld Model")
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
                Component.onCompleted: {
                    weldListModel.append({"buttonName":"Energy"})
                    weldListModel.append({"buttonName":"Time"})
                    weldListModel.append({"buttonName":"Height"})
                    weldListModel.append({"buttonName":"Energy/Height"})
                    weldListModel.append({"buttonName":"Step-Energy"})
                    weldListModel.append({"buttonName":"Step-Time"})
                    weldListModel.append({"buttonName":"Step-Power"})
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
                            checked: index == 0 ? true : false
                            onCheckedChanged: {
                                if (weldModelCheck.checked)
                                    weldModelButton.backgroundComponent = buttonBackBlue
                                else
                                    weldModelButton.backgroundComponent = buttonBackWhite
                            }
                        }
                        onClicked: {
                            stepSetText =  buttonName
                            weldModelCheck.checked = !weldModelCheck.checked
                            if (index >= 4 && weldModelCheck.checked) {
                                bIsStep = true
                            } else {
                                bIsStep = false
                            }
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
                    weldSettingModel.append({"headText":"Pre Burst:","textValue":"0.00s"})
                    weldSettingModel.append({"headText":"Hold Time:","textValue":"0.00s"})
                    weldSettingModel.append({"headText":"After Burst:","textValue":"0.00s"})
                    weldSettingModel.append({"headText":"Squeeze Time:","textValue":"0.00s"})
                }
            }
            Grid {
                id: weldSetting
                property bool weldSetVisible: false
                anchors.top: parent.top
                anchors.left: parent.left
                anchors.leftMargin: 20
                width: parent.width-40
                height: parent.height*0.23+6
                clip: true
                columns: 2
                rows:2
                columnSpacing: 20
                rowSpacing: 6
                Repeater {
                    id: weldRepeater
                    model: weldSettingModel
                    delegate: Item {
                        property alias myfocus: inputText.inputFocus
                        width: parent.width/2-20
                        height: (weldSetting.height-6)/2
                        Text {
                            id: headName
                            anchors.top: parent.top
                            anchors.verticalCenter: parent.verticalCenter
                            verticalAlignment: Qt.AlignVCenter
                            anchors.left: parent.left
                            anchors.leftMargin: 10
                            width: parent.width/3
                            font.pointSize: 16
                            font.family: "arial"
                            text: qsTr(headText)
                            color: "white"
                            clip: true
                        }
                        MiniKeyNumInput {
                            id: inputText
                            anchors.verticalCenter: headName.verticalCenter
                            anchors.left: headName.right
                            width: parent.width/2
//                            horizontalAlignment: Qt.AlignHCenter
                            height: parent.height
                            inputWidth: parent.width/2
//                            inputHeight: parent.height
//                            inputColor: "white"
                            clip: true
                            inputText: qsTr(textValue)
                            onInputFocusChanged: {
                                if (inputText.inputFocus) {
                                    weldSetting.weldSetVisible = true
                                    creatWire.selectIndex = index
                                    backGround.visible = true
                                    backGround.opacity = 0.5
                                    keyNum.visible = true
                                    keyNum.titleText = headText
                                    keyNum.currentValue = textValue
                                    keyNum.minvalue = "0.00mm"
                                    keyNum.maxvalue = "20.00mm"
                                }
                            }
                        }
                    }
                }
            }
            Text {
                id: widthSettingText
                anchors.top: weldSetting.bottom
                anchors.left: parent.left
                anchors.leftMargin: 30
                verticalAlignment: Qt.AlignVCenter
                text: qsTr("Width off-set:")
                color: "white"
                font.pointSize: 16
                font.family: "arial"
            }
            ListModel {
                id: widthModel
                Component.onCompleted: {
                    widthModel.append({"widthText":"Displayed:","textValue":"0.00mm"})
                    widthModel.append({"widthText":"Actual:","textValue":"0.00mm"})
                }
            }
            Grid {
                id: widthSetting
                property bool widthSetVisible: false
                anchors.top: widthSettingText.bottom
                anchors.left: parent.left
                anchors.leftMargin: 20
                width: parent.width-40
                height: parent.height*0.12
                clip: true
                columns: 2
                rows: 1
                columnSpacing: 20
                Repeater {
                    id: widthRepeater
                    model: widthModel
                    delegate: Item {
                        property alias myfocus: widthValue.inputFocus
                        width: parent.width/2-20
                        height: parent.height
                        Text {
                            id: widthName
                            anchors.verticalCenter: parent.verticalCenter
                            verticalAlignment: Qt.AlignVCenter
                            anchors.left: parent.left
                            anchors.leftMargin: 10
                            width: parent.width/3
                            font.pointSize: 16
                            font.family: "arial"
                            text: qsTr(widthText)
                            color: "white"
                            clip: true
                        }
                        MiniKeyNumInput {
                            id: widthValue
                            anchors.left: widthName.right
                            anchors.verticalCenter: widthName.verticalCenter
                            width: parent.width/2
//                            horizontalAlignment: Qt.AlignHCenter
                            height: parent.height
                            inputWidth: parent.width/2
//                            inputHeight: parent.height
//                            inputColor: "white"
                            clip: true
                            inputText: qsTr(textValue)
                            onInputFocusChanged: {
                                if (widthValue.inputFocus) {
                                    widthSetting.widthSetVisible = true
                                    creatWire.selectIndex = index
                                    backGround.visible = true
                                    backGround.opacity = 0.5
                                    keyNum.visible = true
                                    keyNum.titleText = widthText
                                    keyNum.currentValue = textValue
                                    keyNum.minvalue = "0.00mm"
                                    keyNum.maxvalue = "20.00mm"
                                }
                            }
                        }
                    }
                }
            }
            Text {
                id: heightSettingText
                anchors.top: widthSetting.bottom
                anchors.left: parent.left
                anchors.leftMargin: 30
                verticalAlignment: Qt.AlignVCenter
                text: qsTr("Height off-set:")
                color: "white"
                font.pointSize: 16
                font.family: "arial"
            }
            ListModel {
                id: heightModel
                Component.onCompleted: {
                    heightModel.append({"heightText":"Displayed:","textValue":"0.00mm"})
                    heightModel.append({"heightText":"Actual:","textValue":"0.00mm"})
                }
            }
            Grid {
                id: heightSetting
                property bool heightSetVisible: false
                anchors.top: heightSettingText.bottom
                anchors.left: parent.left
                anchors.leftMargin: 20
                width: parent.width-40
                height: parent.height*0.12
                clip: true
                columns: 2
                rows: 1
                columnSpacing: 20
                Repeater {
                    id: heightRepeater
                    model: heightModel
                    delegate: Item {
                        property alias myfocus: heightValue.inputFocus
                        width: parent.width/2-20
                        height: parent.height
                        Text {
                            id: heightName
                            anchors.verticalCenter: parent.verticalCenter
                            verticalAlignment: Qt.AlignVCenter
                            anchors.left: parent.left
                            anchors.leftMargin: 10
                            width: parent.width/3
                            font.pointSize: 16
                            font.family: "arial"
                            text: qsTr(heightText)
                            color: "white"
                            clip: true
                        }
                        MiniKeyNumInput {
                            id: heightValue
                            anchors.left: heightName.right
                            anchors.verticalCenter: heightName.verticalCenter
                            width: parent.width/2
//                            horizontalAlignment: Qt.AlignHCenter
                            height: parent.height
                            inputWidth: parent.width/2
//                            inputHeight: parent.height
//                            inputColor: "white"
                            clip: true
                            inputText: qsTr(textValue)
                            onInputFocusChanged: {
                                if (heightValue.inputFocus) {
                                    heightSetting.heightSetVisible = true
                                    creatWire.selectIndex = index
                                    backGround.visible = true
                                    backGround.opacity = 0.5
                                    keyNum.visible = true
                                    keyNum.titleText = heightText
                                    keyNum.currentValue = textValue
                                    keyNum.minvalue = "0.00mm"
                                    keyNum.maxvalue = "20.00mm"
                                }
                            }
                        }
                    }
                }
            }
            ListModel {
                id: thirdSwitchModel
                Component.onCompleted: {
                    thirdSwitchModel.append({"thirdSwitchText":"Anti-Side:"})
                    thirdSwitchModel.append({"thirdSwitchText":"Cutf Off:"})
                    thirdSwitchModel.append({"thirdSwitchText":"Shrink Tube:"})
                }
            }
            Column {
                id: thirdSwitch
                anchors.top: heightSetting.bottom
                anchors.topMargin: 6
                anchors.bottom: parent.bottom
                anchors.left: parent.left
                anchors.leftMargin: 20
                width: parent.width/2-40
                spacing: 6
                clip: true
                Repeater {
                    model: thirdSwitchModel
                    delegate: Item {
                        height: (thirdSwitch.height-12)/3
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
                            text: qsTr(thirdSwitchText)
                            color: "white"
                            clip: true
                        }
                        Switch2 {
                            id: onoroff
                            anchors.verticalCenter: thirdSwitchName.verticalCenter
                            anchors.left: thirdSwitchName.right
                            width: parent.width/2
                            height: parent.height
                            textLeft: qsTr("ON")
                            textRight: qsTr("OFF")
                            state: "left"
                            clip: true
                        }
                    }
                }
            }
            Text {
                id: loadName
                anchors.top: thirdSwitch.top
                anchors.left: parent.left
                anchors.leftMargin: parent.width/2+10
                width: (parent.width/2-40)/3
                height: thirdSwitch.height/3-6
                verticalAlignment: Qt.AlignVCenter
                font.pointSize: 16
                font.family: "arial"
                text: qsTr("unload Time:")
                color: "white"
                clip: true
            }
            MiniKeyNumInput {
                id: loadValue
                anchors.verticalCenter: loadName.verticalCenter
                anchors.left: loadName.right
                width: parent.width/4
//                horizontalAlignment: Qt.AlignHCenter
                height: parent.height*0.12
                inputWidth: parent.width/4-20
//                inputHeight: parent.height*0.12
//                inputColor: "white"
                clip: true
                inputText: qsTr("0.00mm")
                onInputFocusChanged: {
                    if (loadValue.inputFocus) {
                        backGround.visible = true
                        backGround.opacity = 0.5
                        keyNum.visible = true
                        keyNum.titleText = loadName.text
                        keyNum.currentValue = loadValue.inputText
                        keyNum.minvalue = "0.00mm"
                        keyNum.maxvalue = "20.00mm"
                    }
                }
            }
            Text {
                id: loadName2
                anchors.top: loadName.bottom
                anchors.topMargin: 6
                anchors.left: loadName.left
                width: (parent.width/2-40)/3
                height: thirdSwitch.height/3-6
                verticalAlignment: Qt.AlignVCenter
                font.pointSize: 16
                font.family: "arial"
                text: qsTr("unload Time:")
                color: "white"
                clip: true
            }
            MiniKeyNumInput {
                id: loadValue2
                anchors.verticalCenter: loadName2.verticalCenter
                anchors.left: loadName2.right
                width: parent.width/4-20
//                horizontalAlignment: Qt.AlignHCenter
                height: parent.height*0.12
                inputWidth: parent.width/4-20
//                inputHeight: parent.height*0.12
//                inputColor: "white"
                clip: true
                inputText: qsTr("0.00mm")
                onInputFocusChanged: {
                    if (loadValue2.inputFocus) {
                        backGround.visible = true
                        backGround.opacity = 0.5
                        keyNum.visible = true
                        keyNum.titleText = loadName2.text
                        keyNum.currentValue = loadValue2.inputText
                        keyNum.minvalue = "0.00mm"
                        keyNum.maxvalue = "20.00mm"
                    }
                }
            }
            Text {
                id: instulationText
                anchors.top: loadName2.bottom
                anchors.topMargin: 6
                anchors.left: loadName.left
                width: (parent.width/2-40)/3
                height: thirdSwitch.height/3-6
                verticalAlignment: Qt.AlignVCenter
                text: qsTr("Insulation:")
                color: "white"
                font.pointSize: 16
                font.family: "arial"
            }
            CButton {
                id: instulationButton
                anchors.verticalCenter: instulationText.verticalCenter
                anchors.left: instulationText.right
                width: parent.width/4-20
                height: parent.height*0.12
                text: qsTr("Insulation")
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
                onClicked: {
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
        visible: content.bIsEdit ? true : false
        MouseArea {
            anchors.fill: parent
            onClicked: {

            }
        }
    }
    ShrinkSet {
        id: shrinkSet
        anchors.centerIn: parent
        width: parent.width*0.65
        height: parent.height*0.5
        visible: false
        onSureClick: {
            shrinkSet.visible = false
            backGround.opacity = 0
            backGround.visible = false
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
        Text {
            id: stepTitle
            anchors.top: parent.top
            anchors.topMargin: 24
            anchors.horizontalCenter: parent.horizontalCenter
            font.family: "arial"
            font.pixelSize: 25
            color: "white"
            text: qsTr(stepSetText)
        }
        ListModel {
            id: stepSetModel
            Component.onCompleted: {
                stepSetModel.append({"topText":"Step Point","centerText":"0.00s"})
                stepSetModel.append({"topText":"Amplitude A","centerText":"1μm"})
                stepSetModel.append({"topText":"Amplitude B","centerText":"2μm"})
            }
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
                    headTitle: qsTr(topText)
                    centervalue: qsTr(centerText)
                    width: (stepRow.width-40)/3
                    height: 154
                    onMouseAreaClick: {
                        creatWire.selectIndex = index
                        localbordercolor = "#05f91c"
                        keyNum.visible = true
                        keyNum.titleText = topText
                        keyNum.currentValue = centerText
                        keyNum.minvalue = "0"
                        keyNum.maxvalue = "100"
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

    KeyBoardNum {
        id: keyNum
        anchors.centerIn: parent
        width: 962
        height: 526
        visible: false
        titleText: qsTr("")
        maxvalue: "4"
        minvalue: "1"
        currentValue: "4"
        onCurrentClickIndex: {
            if (index == 15) {
                if (edit2.inputFocus) {
                    edit2.inputText = keyNum.inputText
                    edit2.inputFocus = false
                } else if (loadValue2.inputFocus) {
                    loadValue2.inputText = keyNum.inputText
                    loadValue2.inputFocus = false
                } else if (loadValue.inputFocus) {
                    loadValue.inputText = keyNum.inputText
                    loadValue.inputFocus = false
                } else if (heightSetting.heightSetVisible) {
                    heightModel.set(creatWire.selectIndex,{"textValue":keyNum.inputText})
                    heightRepeater.itemAt(creatWire.selectIndex).myfocus = false
                } else if (widthSetting.widthSetVisible) {
                    widthModel.set(creatWire.selectIndex,{"textValue":keyNum.inputText})
                    widthRepeater.itemAt(creatWire.selectIndex).myfocus = false
                } else if (weldSetting.weldSetVisible) {
                    weldSettingModel.set(creatWire.selectIndex,{"textValue":keyNum.inputText})
                    weldRepeater.itemAt(creatWire.selectIndex).myfocus = false
                } else if (stepTimeSet.visible) {
                    stepRepeater.model.set(creatWire.selectIndex,{"centerText":keyNum.inputText})
                    stepRepeater.itemAt(creatWire.selectIndex).localbordercolor = "#0079c1"
                    keyNum.visible = false
                    keyNum.inputText = ""
                    keyNum.tempValue = ""
                    return
                } else {
                    repeater.model.set(creatWire.selectIndex,{"bottomText":keyNum.inputText})
                    repeater.itemAt(creatWire.selectIndex).localbordercolor = "#0079c1"
                }
                backGround.visible = false
                backGround.opacity = 0
                keyNum.visible = false
                keyNum.inputText = ""
                keyNum.tempValue = ""
            } else if (index == 11) {
                if (edit2.inputFocus) {
                    edit2.inputFocus = false
                } else if (loadValue2.inputFocus) {
                    loadValue2.inputFocus = false
                } else if (loadValue.inputFocus) {
                    loadValue.inputFocus = false
                } else if (heightSetting.heightSetVisible) {
                    heightRepeater.itemAt(creatWire.selectIndex).myfocus = false
                } else if (widthSetting.widthSetVisible) {
                    widthRepeater.itemAt(creatWire.selectIndex).myfocus = false
                } else if (weldSetting.weldSetVisible) {
                    weldRepeater.itemAt(creatWire.selectIndex).myfocus = false
                } else if (stepTimeSet.visible) {
                    stepRepeater.itemAt(creatWire.selectIndex).localbordercolor = "#0079c1"
                    keyNum.visible = false
                    keyNum.inputText = ""
                    keyNum.tempValue = ""
                    return
                } else {
                    repeater.itemAt(creatWire.selectIndex).localbordercolor = "#0079c1"
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
                } else if (loadValue2.inputFocus) {
                    loadValue2.inputText = keyNum.inputText
                } else if (loadValue.inputFocus) {
                    loadValue.inputText = keyNum.inputText
                } else if (heightSetting.heightSetVisible) {
                    heightModel.set(creatWire.selectIndex,{"textValue":keyNum.inputText})
                } else if (widthSetting.widthSetVisible) {
                    widthModel.set(creatWire.selectIndex,{"textValue":keyNum.inputText})
                } else if (weldSetting.weldSetVisible) {
                    weldSettingModel.set(creatWire.selectIndex,{"textValue":keyNum.inputText})
                } else if (stepTimeSet.visible) {
                    stepRepeater.model.set(creatWire.selectIndex,{"centerText":keyNum.inputText})
                } else {
                    repeater.model.set(creatWire.selectIndex,{"bottomText":keyNum.inputText})
                }
            }
        }
    }
}
