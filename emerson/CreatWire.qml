import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import QtQuick.Window 2.2
import QtQuick.Controls 1.4

Item {
    id: creatWire
    width: Screen.desktopAvailableWidth
    height: Screen.desktopAvailableHeight
    property bool detailIsChang: true
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
                    anchors.left: parent.left
                    anchors.leftMargin: 40
                }
                Rectangle {
                    id: rectcolor
                    width: 40
                    height: 20
                    color: "green"
                    anchors.left: labelColor.right
                    anchors.leftMargin: 30
                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            colorLoader.source = "qrc:/MyColor.qml"
                        }
                    }
                }
            }
            Loader {
                id: colorLoader
            }
            Connections {
                target: colorLoader.item
                onColorChanged: {
                    itemColor.color = color
                    spliceDetailsItem.selectColor = color
                    colorLoader.source = ""
                }
            }

            Item {
                id: itemStripe
                width: parent.width
                height: parent.height * 0.05
                anchors.top: itemColor.bottom
                Label {
                    id: labelStripe
                    color: "white"
                    text: qsTr("Stripe")
                    font.family: "arial"
                    font.pointSize: 14
                    anchors.left: parent.left
                    anchors.leftMargin: 40
                }
                Rectangle {
                    width: 40
                    height: 20
                    color: "green"
                    anchors.left: labelStripe.right
                    anchors.leftMargin: 30
                }
            }
            Item {
                id: itemGauge
                width: parent.width
                height: parent.height * 0.05
                anchors.top: itemStripe.bottom
                Label {
                    id: labelGauge
                    color: "white"
                    text: qsTr("Gauge")
                    font.family: "arial"
                    font.pointSize: 14
                    anchors.left: parent.left
                    anchors.leftMargin: 40
                }
                MyLineEdit {
                    id: edit2
                    anchors.left: labelGauge.right
                    anchors.leftMargin: 30
                    width: 300
                    height: 50
                    inputWidth: parent.width * 0.3
                    inputHeight: parent.height
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
                height: parent.height * 0.05
                anchors.top: itemGauge.bottom
                anchors.topMargin: 15
                Label {
                    id: labelType
                    color: "white"
                    text: qsTr("Type of Wire")
                    font.family: "arial"
                    font.pointSize: 14
                    anchors.left: parent.left
                    anchors.leftMargin: 20
                }
                Switch2 {
                    width: parent.width * 0.5
                    height: parent.height
                    anchors.left: labelType.right
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
            }
            Item {
                id: itemSide
                width: parent.width
                height: parent.height * 0.05
                anchors.top: position.bottom
                anchors.topMargin: 15
                Label {
                    id: labelSide
                    color: "white"
                    text: qsTr("Side")
                    font.family: "arial"
                    font.pointSize: 14
                    anchors.left: parent.left
                    anchors.leftMargin: 20
                }
                Switch2 {
                    id: wireDirection
                    width: parent.width * 0.5
                    height: parent.height
                    anchors.left: labelSide.right
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
                height: parent.height * 0.05
                anchors.top: itemSide.bottom
                anchors.topMargin: 15
                Label {
                    id: labelLocation
                    color: "white"
                    text: qsTr("VERTICAL LOCATION")
                    font.family: "arial"
                    font.pointSize: 10
                    anchors.left: parent.left
                    anchors.leftMargin: 10
                }
                Switch2 {
                    id: basicSwitch
                    width: parent.width * 0.5
                    height: parent.height
                    anchors.left: labelLocation.right
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
                Item {
                    width: Screen.desktopAvailableWidth * 0.2
                    height: 30
                    Label {
                        id: labelTop
                        text: qsTr("Top")
                        font.pointSize: 14
                        font.family: "arial"
                        color: "white"
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
                anchors.bottomMargin: 50
                anchors.right: parent.right
                anchors.rightMargin: 30

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
                    settingsModel.append({"topText":"Amplitu","bottomText":"micron"})
                    settingsModel.append({"topText":"Weld\nPressure","bottomText":"50PSI"})
                    settingsModel.append({"topText":"Width","bottomText":"12.5mm"})
                }
            }
            ListModel {
                id: settingsModel2
                Component.onCompleted: {
                    settingsModel2.append({"topText":"Time","bottomText":"40%"})
                    settingsModel2.append({"topText":"Time","bottomText":"40%"})
                    settingsModel2.append({"topText":"Power","bottomText":"40%"})
                    settingsModel2.append({"topText":"Power","bottomText":"40%"})
                    settingsModel2.append({"topText":"Pre-Height","bottomText":"40%"})
                    settingsModel2.append({"topText":"Pre-Height","bottomText":"40%"})
                    settingsModel2.append({"topText":"Height","bottomText":"40%"})
                    settingsModel2.append({"topText":"Height","bottomText":"40%"})


                }
            }

            Grid {
                id: settingLayout
                anchors.top: parent.top
                anchors.topMargin: tabBar.height + 10
                anchors.left: parent.left
                anchors.leftMargin: 15
                rows: 4
                columns: 2
                width: 220
                height: 380
                spacing: 20
                Repeater {
                    id: repeater
                    model: settingsModel
                    CButton {
                        width: 100
                        height: 80
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
                        }
                        Text {
                            text: qsTr(bottomText)
                            anchors.top: buttonTop.bottom
                            anchors.topMargin: 3
                            anchors.left: parent.left
                            anchors.leftMargin: 3
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
                        repeater.model = settingsModel2
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
        Rectangle {
            anchors.fill: parent
            color: "#626465"
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
            anchors.left: edit1.left
            text: qsTr("SpliceDetails")
            font.pointSize: 16
            font.family: "arial"
            color: "white"
        }
        Label {
            id: spliceDetailsTips
            anchors.top: spliceDetails.bottom
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
            anchors.topMargin: 10
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
            text: qsTr("WIRE LIBRARY")
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
            color: "#626465"
        }
        Rectangle {
            id: rect1
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.leftMargin: 15
            anchors.topMargin: 10
            opacity: 0.33
            anchors.right: parent.right
            height: 40
            border.width: 1
            border.color: "blue"
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
            border.width: 1
            border.color: "blue"
            anchors.left: rect1.left
            anchors.right: parent.right
            color: Qt.rgba(255,255,255,0.3)
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
                        color: "blue"
                        Rectangle{
                            anchors.fill: parent
                            anchors.margins: 1
                            radius: 3
                            anchors.centerIn: parent
                            color: "blue"
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
                        width: 150
                        height: 40
                        backgroundComponent: buttonBackWhite
                        text: buttonName
                        pointSize: 14
                        textColor: weldModelCheck.checked ? "white" : "black"
                        RadioButton {
                            id: weldModelCheck
                            exclusiveGroup: tabPositionGroup
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
            border.width: 1
            border.color: "blue"
            anchors.left: rect1.left
            anchors.right: parent.right
            color: Qt.rgba(255,255,255,0.3)
            height: 350
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
            anchors.bottomMargin: 30
            CButton {
                width: 150
                height: 40
                text: qsTr("Back")
                textColor: "white"
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
            }
            CButton {
                width: 150
                height: 40
                text: qsTr("Save")
                textColor: "white"
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
            }
        }
    }
}

