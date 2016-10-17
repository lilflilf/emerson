import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import QtQuick.Window 2.2
import QtQuick.Controls 1.4

Item {
    id: creatWire
    width: Screen.desktopAvailableWidth
    height: Screen.desktopAvailableHeight
    signal signalSaveSplice()
    property bool detailIsChang: true
    property variant colorArray: ["#ff6699","#ff0033","#33FFCC","#cc99ff","#cc0099","#930202","#99ccff","#f79428",
        "#0000cc","Olive","#ffff33","#ffcc00","#cc9909","#66ff00","#009900","#00cc66","#3366ff","#cc33cc","#cc9966","#9400D3"]

    function wireChanged(selectColor,selectPosition,selectText)
    {
        spliceDetailsItem.selectColor = selectColor
        spliceDetailsItem.selectText = selectText
        spliceDetailsItem.selectPosition = selectPosition
    }

    SwipeView {
        width: Screen.desktopAvailableWidth * 0.3
        height: parent.height
        id: swipeView
        currentIndex: tabBar.currentIndex
        Page {
            id: wireBuilder

            Connections {
                target: spliceDetailsItem
                onWireSelected: {
                    //signal wireSelected(var selectColor,var selectDirection,var selectPosition,var selectText)
                    forground.visible = false
                    rectcolor.color = selectColor
                    wireDirection.state = selectDirection
                    edit2.inputText = selectText
                    topRadio.checked = true
                }
                onChanging: {
                    console.log("onChanging",bIsChang)
                    detailIsChang = bIsChang
                }
            }

            Rectangle {
                anchors.top: parent.top
                anchors.fill: parent
                color: "#48484a"
            }
            Rectangle {
                id: forground
                anchors.top: parent.top
                anchors.fill: parent
                color: "#48484a"
                z:10
                Label {
                    id: nowire
                    color: "white"
                    text: qsTr("No Wires Selected")
                    anchors.top: parent.top
                    anchors.topMargin: tabBar.height + 15
                    font.family: "arial"
                    font.pointSize: 16
                    opacity: 0.5
                }
            }

            MyLineEdit {
                id: wireName
                width: 300
                height: 50
                anchors.top: parent.top
                anchors.topMargin: tabBar.height + 15
                inputWidth: parent.width * 0.8
                inputHeight: parent.height * 0.05
                defaultText: "WIRE NAME"
                maxSize: 20
            }
            Label {
                id: properties
                color: "white"
                text: qsTr("PROPERTIES")
                anchors.top: wireName.bottom
                font.family: "arial"
                font.pointSize: 16
                opacity: 0.5
                anchors.left: parent.left
                anchors.leftMargin: 10
                anchors.topMargin: 10
            }
            Item {
                id: itemColor
                width: parent.width
                height: parent.height * 0.05
                anchors.top: properties.bottom
                property alias color: rectcolor.color
                Label {
                    id: labelColor
                    color: "white"
                    text: qsTr("Color")
                    font.family: "arial"
                    font.pointSize: 14
                    anchors.right: parent.right
                    anchors.rightMargin: 290
                }
                Rectangle {
                    id: rectcolor
                    width: 80
                    height: 40
                    color: "green"
                    anchors.right: parent.right
                    anchors.rightMargin: 150
                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            //colorLoader.source = "qrc:/MyColor.qml"
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
                                spliceDetailsItem.selectColor = pickColor
                                colorLoader.sourceComponent = null
                            }
                        }
                    }

                }
            }

            Item {
                id: itemStripe
                width: parent.width
                height: parent.height * 0.05
                anchors.top: itemColor.bottom
                anchors.topMargin: 10
                Label {
                    id: labelStripe
                    color: "white"
                    text: qsTr("Stripe")
                    font.family: "arial"
                    font.pointSize: 14
                    anchors.right: parent.right
                    anchors.rightMargin: 290
                }
                Rectangle {
                    width: 80
                    height: 40
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
                height: parent.height * 0.05
                anchors.top: itemStripe.bottom
                anchors.topMargin: 10
                Label {
                    id: labelGauge
                    color: "white"
                    text: qsTr("Gauge")
                    font.family: "arial"
                    font.pointSize: 14
                    anchors.right: parent.right
                    anchors.rightMargin: 290
                }
                MyLineEdit {
                    id: edit2
                    anchors.right: parent.right
                    anchors.rightMargin: 150
                    width: 80
                    height: 40
                    inputWidth: 80//parent.width * 0.3
                    inputHeight: 40//parent.height
                    horizontalAlignment: Qt.AlignHCenter
                    maxSize: 20
                    opacity: 0.7
                    onTextChange: {
                        if(detailIsChang)
                            return
                        spliceDetailsItem.selectText = inputText
                    }
                }
            }
            Item {
                id: itemType
                width: parent.width
                height: parent.height * 0.04
                anchors.top: itemGauge.bottom
                anchors.topMargin: 15
                Label {
                    id: labelType
                    color: "white"
                    text: qsTr("Type of Wire")
                    font.family: "arial"
                    font.pointSize: 14
                    anchors.right: parent.right
                    anchors.rightMargin: 290
                }
                Switch2 {
                    width: parent.width * 0.4
                    height: parent.height
                    anchors.left: parent.left
                    anchors.leftMargin: width + 10
                    textLeft: qsTr("Copper")
                    textRight: qsTr("Alum")
                    state: "left"
                    opacity: 0.8

                }
            }
            Label {
                id: position
                color: "white"
                text: qsTr("POSITION")
                anchors.top: itemType.bottom
                font.family: "arial"
                font.pointSize: 14
                opacity: 0.5
                anchors.left: parent.left
                anchors.leftMargin: 10
            }
            Item {
                id: itemSide
                width: parent.width
                height: parent.height * 0.04
                anchors.top: position.bottom
                anchors.topMargin: 15
                Label {
                    id: labelSide
                    color: "white"
                    text: qsTr("Side")
                    font.family: "arial"
                    font.pointSize: 14
                    anchors.right: parent.right
                    anchors.rightMargin: 290
                }
                Switch2 {
                    id: wireDirection
                    width: parent.width * 0.4
                    height: parent.height
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
                height: parent.height * 0.04
                anchors.top: itemSide.bottom
                anchors.topMargin: 15
                Label {
                    id: labelLocation
                    color: "white"
                    text: qsTr("LOCATION") //VERTICAL
                    font.family: "arial"
                    font.pointSize: 14
                    anchors.right: parent.right
                    anchors.rightMargin: 290
//                    anchors.left: parent.left
//                    anchors.leftMargin: 10
                }
                Switch2 {
                    id: basicSwitch
                    width: parent.width * 0.4
                    height: parent.height
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
                spacing: 20
                visible: false
                ExclusiveGroup {
                    id: tabPositionGroup;
                }
                ExclusiveGroup {
                    id: tabPositionGroup2;
                }
                Item {
                    width: Screen.desktopAvailableWidth * 0.2
                    height: 30
                    Label {
                        id: labelTop
                        text: qsTr("Top")
                        font.pointSize: 14
                        font.family: "arial"
                        color: "white"
                        anchors.right: parent.right
                        anchors.rightMargin: 175
                    }
                    RadioButton {
                        id: topRadio
                        scale: 2
                        checked: false
                        anchors.right: parent.right
                        anchors.rightMargin: 100
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
                    width: Screen.desktopAvailableWidth * 0.2
                    height: 30
                    Label {
                        id: labelMiddle
                        text: qsTr("Middle")
                        font.pointSize: 14
                        font.family: "arial"
                        color: "white"
                        anchors.right: parent.right
                        anchors.rightMargin: 175
                    }
                    RadioButton {
                        id: midRadio
                        scale: 2
                        anchors.right: parent.right
                        anchors.rightMargin: 100
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
                    width: Screen.desktopAvailableWidth * 0.2
                    height: 30
                    Label {
                        id: labelBottom
                        text: qsTr("Bottom")
                        font.pointSize: 14
                        font.family: "arial"
                        color: "white"
                        anchors.right: parent.right
                        anchors.rightMargin: 175
                    }
                    RadioButton {
                        scale: 2
                        anchors.right: parent.right
                        anchors.rightMargin: 100
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
            CButton {
                text: qsTr("SAVE TO WIRE\nLIBRARY")
                pointSize: 12
                anchors.bottom: parent.bottom
                width: parent.width * 0.5
                height: parent.height * 0.05
                anchors.bottomMargin: 100
                anchors.right: parent.right
                anchors.rightMargin: 30
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
                color: "#48484a"
            }
            ListModel {
                id: settingsModel
                Component.onCompleted: {
                    settingsModel.append({"topText":"Energy","bottomText":"30J"})
                    settingsModel.append({"topText":"Trigger\npressure","bottomText":"50PSI"})
                    settingsModel.append({"topText":"Amplitu","bottomText":"25um"})
                    settingsModel.append({"topText":"Weld\nPressure","bottomText":"50PSI"})
                    settingsModel.append({"topText":"Width","bottomText":"12.5mm"})
                }
            }
            ListModel {
                id: settingsModel2
                Component.onCompleted: {
                    settingsModel2.append({"topText":"Time","bottomText":"5.00s"})
                    settingsModel2.append({"topText":"Time","bottomText":"0.00s"})
                    settingsModel2.append({"topText":"Power","bottomText":"3960W"})
                    settingsModel2.append({"topText":"Power","bottomText":"0W"})
                    settingsModel2.append({"topText":"Pre-Height","bottomText":"15.00mm"})
                    settingsModel2.append({"topText":"Pre-Height","bottomText":"0.00mm"})
                    settingsModel2.append({"topText":"Height","bottomText":"15.00mm"})
                    settingsModel2.append({"topText":"Height","bottomText":"0.00mm"})


                }
            }
            Row {
                id: upper
                anchors.top: parent.top
                anchors.topMargin: tabBar.height + 5
                spacing: 105
                anchors.left: parent.left
                anchors.leftMargin: 60
                visible: false
                Text {
                    text: qsTr("Upper Limit")
                    font.pointSize: 14
                    font.family: "arial"
                    color: "white"
                    opacity: 0.5
                }
                Text {
                    font.pointSize: 14
                    font.family: "arial"
                    color: "white"
                    text: qsTr("Lower Limit")
                    opacity: 0.5
                }
            }

            Grid {
                id: settingLayout
                anchors.top: parent.top
                anchors.topMargin: tabBar.height + 30
                anchors.left: parent.left
                anchors.leftMargin: 35
                rows: 4
                columns: 2
                width: 220
                height: 380
                columnSpacing: 50
                rowSpacing: 20
                Repeater {
                    id: repeater
                    model: settingsModel
                    CButton {
                        width: 150
                        height: 120
                        backgroundComponent: Item {
                            Rectangle {
                                anchors.centerIn: parent
                                anchors.fill: parent
                                radius: 3
                                color: "#000000"
                                Rectangle{
                                    anchors.fill: parent
                                    anchors.margins: 1
                                    radius: 3
                                    anchors.centerIn: parent
                                    color: "#000000"
                                }
                            }
                        }
                        Text {
                            id: buttonTop
                            text: qsTr(topText)
                            anchors.top: parent.top
                            anchors.topMargin: 3
                            anchors.left: parent.left
                            anchors.leftMargin: 3
                            font.pointSize: 12
                            font.family: "arial"
                            color: "white"
                            opacity: 0.5
                        }
                        Text {
                            anchors.centerIn: parent
                            text: qsTr(bottomText)
//                            anchors.top: buttonTop.bottom
//                            anchors.topMargin: 3
//                            anchors.left: parent.left
//                            anchors.leftMargin: 3
                            font.pointSize: 16
                            font.family: "arial"
                            color: "white"

                        }
                    }
                }
            }
            Row {
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 100
                anchors.left: parent.left
                anchors.leftMargin: 15
                spacing: 20
                height: 50
                width: parent.width
                CButton {
                    pointSize: 14
                    width: parent.width * 0.45
                    height: 50
                    text: qsTr("QUALITY WINDOW\nSETTINGS")
                    onClicked: {
                        if (repeater.model == settingsModel){
                            repeater.model = settingsModel2
                            text = "WELD SETTINGS"
                            upper.visible = true
                        }
                        else {
                            text = "QUALITY WINDOW\nSETTINGS"
                            repeater.model = settingsModel
                            upper.visible = false
                        }
                    }
                }
                CButton {
                    pointSize: 14
                    text: qsTr("ADVANCED WELD\nSETTINGS")
                    width: parent.width * 0.45
                    height: 50
                    onClicked: {
                        settingRightArea.visible = true
                    }
                }
            }
        }
    }

    TabBar {
        width: Screen.desktopAvailableWidth * 0.3
        id: tabBar
        currentIndex: swipeView.currentIndex
        anchors.top: parent.top
        TabButton {
            font.family: "arial"
            font.pointSize: 16
            text: qsTr("WIRE BUILDER")
            opacity: 0.33
        }
        TabButton {
            font.family: "arial"
            font.pointSize: 16
            text: qsTr("WELD SETTINGS")
            opacity: 0.33
        }
    }

    //    TabBar {
    //        id: tabBar
    //        currentIndex: swipeView.currentIndex
    //        anchors.top: parent.top
    //        width: Screen.desktopAvailableWidth * 0.3
    //        TabButton {
    //            Rectangle {
    //                anchors.fill: parent
    //                color: tabBar.currentIndex == 0 ? "black" : "#48484a"
    //                Text {
    //                    anchors.centerIn: parent
    //                    font.family: "arial"
    //                    font.pointSize: 14
    //                    color: "white"
    //                    text: qsTr("WIRE BUILDER")
    //                    opacity: 0.5
    //                    width: parent.width
    //                    clip: true
    //                }
    //            }

    //        }
    //        TabButton {
    //            Rectangle {
    //                anchors.fill: parent
    //                color: tabBar.currentIndex == 1 ? "black" : "#48484a"
    //                Text {
    //                    anchors.centerIn: parent
    //                    font.family: "arial"
    //                    font.pointSize: 14
    //                    color: "white"
    //                    text: qsTr("WELD SETTINGS")
    //                    opacity: 0.5
    //                    width: parent.width
    //                    clip: true
    //                }
    //            }
    //        }
    //    }

    Item {
        id: rightArea
        anchors.left: swipeView.right
        width: Screen.desktopAvailableWidth * 0.7
        height: parent.height // * 0.5
        Loader {
            id: colorLoader
            anchors.left: parent.left
            anchors.leftMargin: 20
            anchors.top: parent.top
            anchors.topMargin: 100
            z: 10
        }
        Rectangle {
            anchors.fill: parent
            color: "#626465"
            MouseArea {
                anchors.fill: parent
            }
        }
        MyLineEdit {
            id: edit1
            width: 600
            height: 50
            anchors.top: parent.top
            inputWidth: parent.width * 0.6
            inputHeight: parent.height * 0.05
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
            text: qsTr("TOTAL CROSS SECTION 0mm")
            font.pointSize: 12
            font.family: "arial"
            color: "white"
            opacity: 0.5
        }
        SpliceDetails {
            id: spliceDetailsItem
            width: Screen.desktopAvailableWidth * 0.8
            height: Screen.desktopAvailableHeight *0.5
            anchors.top: spliceDetailsTips.bottom
            anchors.topMargin: 10
            anchors.left: spliceDetails.left
            anchors.right: parent.right
            anchors.rightMargin: 40

        }

        CButton {
            id: addWire
            pointSize: 14
            width: 200
            height: 50
            anchors.left: spliceDetailsItem.left
            anchors.top: spliceDetailsItem.bottom
            anchors.topMargin: 20
            text: qsTr("ADD WIRE")
        }

        CButton {
            id: wirelibrary
            pointSize: 14
            width: 200
            height: 50
            anchors.left: spliceDetailsItem.left
            anchors.top: addWire.bottom
            anchors.topMargin: 10
            text: qsTr("WIRE LIBRARY")
        }

        CButton {
            id: saveSplice
            pointSize: 14
            width: 200
            height: 50
            anchors.right: spliceDetailsItem.right
            anchors.bottom: wirelibrary.bottom
            text: qsTr("SAVE SPLICE")
            onClicked: {
                signalSaveSplice()
            }
        }
    }
    Item {
        id: settingRightArea
        anchors.left: swipeView.right
        width: Screen.desktopAvailableWidth * 0.7
        height: parent.height // * 0.5
        visible: false
        Rectangle {
            anchors.fill: parent
            color: "#6d6e71"
            MouseArea {
                anchors.fill: parent
            }
        }
        Rectangle {
            id: rect1
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.leftMargin: 15
            anchors.topMargin: 10
            opacity: 0.1
            anchors.right: parent.right
            height: 40
        }
        Text {
            text: qsTr("Splice#:KKK0003BAC")
            anchors.left: rect1.left
            anchors.leftMargin: 10
            anchors.verticalCenter: rect1.verticalCenter
            color: "white"
            font.pointSize: 14
            font.family: "arial"
        }
        Rectangle {
            id: line1
            anchors.top: rect1.bottom
            anchors.topMargin: 10
            anchors.left: rect1.left
            anchors.right: rect1.right
            border.color: "white"
            border.width: 2
            height: 4
        }
        Rectangle {
            id: rect2
            anchors.top: line1.bottom
            anchors.topMargin: 10
            anchors.left: rect1.left
            anchors.right: parent.right
            color: Qt.rgba(255,255,255,0.1)
            height: 170
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
                anchors.topMargin: 10
                width: parent.width
                anchors.bottom: parent.bottom
                anchors.left: parent.left
                anchors.leftMargin: 20
                spacing: 20
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
                            weldModelCheck.checked = !weldModelCheck.checked
                        }
                    }
                }
            }
        }

        Rectangle {
            id: rect3
            anchors.top: rect2.bottom
            anchors.topMargin: 10
            anchors.left: rect1.left
            anchors.right: parent.right
            color: Qt.rgba(255,255,255,0.1)
            height: 350
            clip: true
            Text {
                id: adWeldSetting
                text: qsTr("Advanced Weld Setting")
                color: "white"
                font.pointSize: 16
                font.family: "arial"
                anchors.top: parent.top
                anchors.left: parent.left
                anchors.topMargin: 5
                anchors.leftMargin: 15
            }
            ListModel {
                id: weldSettingModel
                Component.onCompleted: {
                    weldSettingModel.append({"headText":"Pre Burst:","textValue":"0.00s"})
                    weldSettingModel.append({"headText":"Hold Time:","textValue":"0.00s"})
                    weldSettingModel.append({"headText":"Squeeze Time:","textValue":"0.00s"})
                    weldSettingModel.append({"headText":"After Burst:","textValue":"0.00s"})
                }
            }
            Grid {
                id: weldSetting
                anchors.top: adWeldSetting.bottom
                anchors.left: parent.left
                anchors.leftMargin: 20
                width: parent.width-40
                height: parent.height/2-50
                columns: 2
                rows:2
                columnSpacing: 20
                rowSpacing: 15
                Repeater {
                    model: weldSettingModel
                    delegate: Item {
                        width: parent.width/2-20
                        height: parent.height/2-20
                        Text {
                            id: headName
                            anchors.top: parent.top
                            anchors.topMargin: 20
                            anchors.left: parent.left
                            anchors.leftMargin: 10
                            width: parent.width/3
                            font.pointSize: 16
                            font.family: "arial"
                            text: qsTr(headText)
                            color: "white"
                            clip: true
                        }
                        MyLineEdit {
                            id: inputText
                            anchors.left: headName.right
                            anchors.top: parent.top
                            anchors.topMargin: 15
                            width: parent.width/2
                            horizontalAlignment: Qt.AlignHCenter
                            height: 40
                            inputWidth: parent.width/2
                            inputHeight: 40
                            inputColor: "black"
                            clip: true
                            backgroundcolor: "white"
                            inputText: qsTr(textValue)
                        }
                    }
                }
            }
            Text {
                id: widthSettingText
                anchors.top: weldSetting.bottom
                anchors.left: parent.left
                anchors.leftMargin: 30
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
                anchors.top: widthSettingText.bottom
                anchors.left: parent.left
                anchors.leftMargin: 20
                width: parent.width-40
                height: parent.height/3-40
                columns: 2
                rows: 1
                columnSpacing: 20
                rowSpacing: 15
                Repeater {
                    model: widthModel
                    delegate: Item {
                        width: parent.width/2-20
                        height: parent.height/2-20
                        Text {
                            id: widthName
                            anchors.top: parent.top
                            anchors.topMargin: 20
                            anchors.left: parent.left
                            anchors.leftMargin: 10
                            width: parent.width/3
                            font.pointSize: 16
                            font.family: "arial"
                            text: qsTr(widthText)
                            color: "white"
                            clip: true
                        }
                        MyLineEdit {
                            id: widthValue
                            anchors.left: widthName.right
                            anchors.top: parent.top
                            anchors.topMargin: 15
                            width: parent.width/2
                            horizontalAlignment: Qt.AlignHCenter
                            height: 40
                            inputWidth: parent.width/2
                            inputHeight: 40
                            inputColor: "black"
                            clip: true
                            backgroundcolor: "white"
                            inputText: qsTr(textValue)
                        }
                    }
                }
            }
            Text {
                id: antiText
                anchors.top: widthSetting.bottom
                anchors.topMargin: 8
                anchors.left: parent.left
                anchors.leftMargin: 30
                width: parent.width/6-13
                text: qsTr("Anti-Side:")
                color: "white"
                font.pointSize: 16
                font.family: "arial"
            }
            Switch2 {
                id: onoroff
                anchors.top: widthSetting.bottom
                anchors.left: antiText.right
                width: parent.width/4-20
                height: 38
                textLeft: qsTr("ON")
                textRight: qsTr("OFF")
                state: "left"
                clip: true
            }
            Text {
                id: instulationText
                anchors.top: widthSetting.bottom
                anchors.topMargin: 8
                anchors.left: onoroff.right
                anchors.leftMargin: parent.width/8-26
                width: parent.width/6-13
                text: qsTr("Insulation:")
                color: "white"
                font.pointSize: 16
                font.family: "arial"
            }
            CButton {
                id: instulationButton
                anchors.top: widthSetting.bottom
                anchors.left: instulationText.right
                width: parent.width/4-20
                height: 38
                text: qsTr("Insulation")
                onClicked: {
                    shrinkSet.visible = true
                }
            }
        }
        Rectangle {
            id: line2
            anchors.top: rect3.bottom
            anchors.topMargin: 10
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
            anchors.top: line2.bottom
            anchors.topMargin: 10
            anchors.bottomMargin: 30
            CButton {
                width: 200
                height: 50
                text: qsTr("Back")
                textColor: "white"
//                backgroundComponent: Component {
//                    Item {
//                        Rectangle {
//                            anchors.centerIn: parent
//                            anchors.fill: parent
//                            color: Qt.rgba(255,255,255,0.3)
//                            border.color: "blue"
//                            border.width: 2
//                        }
//                    }
//                }
                onClicked: {
                    settingRightArea.visible = false
                }
            }
            CButton {
                width: 200
                height: 50
                text: qsTr("Save")
                textColor: "white"
//                backgroundComponent: Component {
//                    Item {
//                        Rectangle {
//                            anchors.centerIn: parent
//                            anchors.fill: parent
//                            color: Qt.rgba(255,255,255,0.3)
//                            border.color: "blue"
//                            border.width: 2
//                        }
//                    }
//                }
                onClicked: {
                    settingRightArea.visible = false
                }
            }
        }
        ShrinkSet {
            id: shrinkSet
            anchors.centerIn: parent
            width: parent.width*0.8
            height: parent.height*0.6
            visible: false
        }
    }
}
