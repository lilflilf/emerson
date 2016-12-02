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
    property bool detailIsChang: true
    property variant colorArray: ["#ff6699","#ff0033","#33FFCC","#cc99ff","#cc0099","#930202","#99ccff","#f79428",
        "#0000cc","Olive","#ffff33","#ffcc00","#cc9909","#66ff00","#009900","#00cc66","#3366ff","#cc33cc","#cc9966","#9400D3"]

//    function wireChanged(selectColor,selectPosition,selectText)
//    {
//        spliceDetailsItem.selectColor = selectColor
//        spliceDetailsItem.selectText = selectText
//        spliceDetailsItem.selectPosition = selectPosition
//    }

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
                defaultText: "WIRE NAME"
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
                    width: 80
                    height: 34
                    color: "green"
                    anchors.right: parent.right
                    anchors.rightMargin: 150
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
                Rectangle {
                    id: backColor
                    property var pickColor: ""
                    width: 550
                    height: 170
                    Grid {
                        id: colorGrid
                        anchors.left: parent.left
                        anchors.leftMargin: 16
                        anchors.top: parent.top
                        anchors.topMargin: 10
                        columns: 10
                        rows: 2
                        spacing: 2
                        Repeater {
                            model: colorArray.length
                            Rectangle {
                                id: colorRec
                                width: 50
                                height: 50
                                color: colorArray[index]
                                Rectangle {
                                    id: border
                                    width: colorRec.width + 2
                                    height: colorRec.height + 2
                                    color: Qt.rgba(0,0,0,0)
                                    border.color: "black"
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
                                            console.log("color picker == ",colorArray[index])
                                        }
                                    }
                                }
                            }
                        }
                    }
                    Row {
                        id: bottomRow
                        spacing: 30
                        anchors.right: parent.right
                        anchors.rightMargin: 20
                        anchors.bottom: parent.bottom
                        anchors.bottomMargin: 10
                        CButton {
                            width: 150
                            height: 40
                            text: qsTr("CANCEL")
                            textColor: "black"
                            backgroundComponent: Component {
                                Item {
                                    Rectangle {
                                        anchors.centerIn: parent
                                        anchors.fill: parent
                                        color: Qt.rgba(255,255,255,0.3)
                                        border.color: "blue"
                                        border.width: 2
                                    }
                                }
                            }
                            onClicked: {
                                colorLoader.sourceComponent = null
                            }
                        }
                        CButton {
                            width: 150
                            height: 40
                            text: qsTr("OK")
                            textColor: "black"
                            backgroundComponent: Component {
                                Item {
                                    Rectangle {
                                        anchors.centerIn: parent
                                        anchors.fill: parent
                                        color: Qt.rgba(255,255,255,0.3)
                                        border.color: "blue"
                                        border.width: 2
                                    }
                                }
                            }
                            onClicked: {
                                if (pickColor == "")
                                    return
                                itemColor.color = pickColor
//                                spliceDetailsItem.selectColor = pickColor
                                colorLoader.sourceComponent = null
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
                    width: 80
                    height: 34
                    color: "green"
                    anchors.right: parent.right
                    anchors.rightMargin: 150
                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            colorLoader.sourceComponent = stripePicker
                        }
                    }
                }
            }

            Component {
                id: stripePicker
                Rectangle {
                    id: backStripe
                    width: 550
                    height: 270
                    Row {
                        spacing: 30
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.top: parent.top
                        anchors.topMargin: 30
                        Rectangle {
                            width: 100
                            height: 40
                            border.width: 2
                            border.color: "black"
                            Rectangle {
                                color: "green"
                                height: 5
                                width: parent.width
                                anchors.verticalCenter: parent.verticalCenter
                            }
                            Rectangle {
                                id: border
                                width: parent.width + 10
                                height: parent.height + 10
                                color: Qt.rgba(0,0,0,0)
                                border.color: "black"
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
                                }
                            }

                        }
                        Rectangle {
                            width: 100
                            height: 40
                            border.width: 2
                            border.color: "black"
                            Rectangle {
                                color: "green"
                                height: 5
                                width: parent.width
                                anchors.centerIn: parent
                                rotation: 17
                            }
                            Rectangle {
                                width: parent.width + 10
                                height: parent.height + 10
                                color: Qt.rgba(0,0,0,0)
                                border.color: "black"
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
                                }
                            }
                        }
                        Rectangle {
                            width: 100
                            height: 40
                            border.width: 2
                            border.color: "black"
                            Rectangle {
                                color: "green"
                                height: 5
                                width: parent.width
                                anchors.verticalCenter: parent.verticalCenter
                            }
                            Rectangle {
                                width: parent.width + 10
                                height: parent.height + 10
                                color: Qt.rgba(0,0,0,0)
                                border.color: "black"
                                border.width: 2
                                anchors.centerIn: parent
                                visible: radioButton2.checked ? true : false
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
                                }
                            }
                        }
                        Rectangle {
                            width: 100
                            height: 40
                            border.width: 2
                            border.color: "black"
                            Rectangle {
                                color: "green"
                                height: 5
                                width: parent.width
                                anchors.verticalCenter: parent.verticalCenter
                            }
                            Rectangle {
                                width: parent.width + 10
                                height: parent.height + 10
                                color: Qt.rgba(0,0,0,0)
                                border.color: "black"
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
                    anchors.rightMargin: 150
                    width: 80
                    height: 34
                    inputWidth: 80//parent.width * 0.3
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
                            keyNum.currentValue = "1.12mm"
                            keyNum.minvalue = "1.00mm"
                            keyNum.maxvalue = "10.99mm"
                        }
                    }

                    onInputTextChanged: {
                        if(detailIsChang)
                            return
                        spliceDetailsItem.selectText = inputText
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
                        console.log("onStateChanged",wireDirection.state,spliceDetailsItem.selectDirection,detailIsChang)
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
                    RadioButton {
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

//    Rectangle {
//        id: backGround
//        anchors.fill: parent
//        color: "black"
//        opacity: 0.7
//        visible: false //content.bIsEdit ? true : false
//        MouseArea {
//            anchors.fill: parent
//            onClicked: {

//            }
//        }
//    }
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
                background.opacity = 0
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
