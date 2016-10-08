import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import QtQuick.Window 2.2
import QtQuick.Controls 1.4

Item {
    id: creatWire
    width: Screen.desktopAvailableWidth
    height: Screen.desktopAvailableHeight

//    function onColorChanged(color)
//    {
//        console.log("111111111111",color)
//    }

    SwipeView {
        width: Screen.desktopAvailableWidth * 0.2
        height: parent.height
        id: swipeView
        currentIndex: tabBar.currentIndex
        Page {
            id: wireBuilder
            Rectangle {
                anchors.top: parent.top
                anchors.fill: parent
                color: "#48484a"
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
                    //console.log("sseeeeeeeeeeeeeeeeeeeee",color)
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
                    width: parent.width * 0.5
                    height: parent.height
                    anchors.left: labelSide.right
                    textLeft: qsTr("Left")
                    textRight: qsTr("Right")
                    state: "left"
                    opacity: 0.8
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
                    width: parent.width * 0.5
                    height: parent.height
                    anchors.left: labelLocation.right
                    textLeft: qsTr("Basic")
                    textRight: qsTr("Adv")
                    state: "left"
                    opacity: 0.8
                }
            }
            Column {
                anchors.top: itemLocation.bottom
                anchors.topMargin: 20
                anchors.left: parent.left
                anchors.leftMargin: 20
                spacing: 20
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
                        scale: 2
                        checked: true
                        anchors.right: parent.right
                        anchors.rightMargin: 100
                        exclusiveGroup: tabPositionGroup
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
                        scale: 2
                        anchors.right: parent.right
                        anchors.rightMargin: 100
                        exclusiveGroup: tabPositionGroup
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
                    settingsModel.append({"name":"Energy"})
                    settingsModel.append({"name":"Trigger"})
                    settingsModel.append({"name":"Amplitu"})
                    settingsModel.append({"name":"Weld Pre"})
                    settingsModel.append({"name":"Width"})
                    settingsModel.append({"name":"Amplitude"})
                }
            }
            ListModel {
                id: settingsModel2
                Component.onCompleted: {
                    settingsModel2.append({"name":"Button1"})
                    settingsModel2.append({"name":"Button2"})
                    settingsModel2.append({"name":"Button3"})
                    settingsModel2.append({"name":"Button4"})
                    settingsModel2.append({"name":"Button5"})
                    settingsModel2.append({"name":"Button6"})
                    settingsModel2.append({"name":"Button7"})
                    settingsModel2.append({"name":"Button8"})
                }
            }

            Grid {
                id: settingLayout
                anchors.top: parent.top
                anchors.topMargin: tabBar.height
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
                        text: name
                    }
                }
            }
            Row {
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 100
                spacing: 10
                height: 50
                width: parent.width
                CButton {
                    width: parent.width * 0.4
                    height: 50
                    onClicked: {
                        repeater.model = settingsModel2
                    }
                }
                CButton {
                    width: parent.width * 0.4
                    height: 50
                }
            }
        }
    }
    TabBar {
        id: tabBar
        currentIndex: swipeView.currentIndex
        anchors.top: parent.top
        width: Screen.desktopAvailableWidth * 0.2
        TabButton {
            Rectangle {
                anchors.fill: parent
                color: tabBar.currentIndex == 0 ? "black" : "#48484a"
            }
            Text {
                anchors.centerIn: parent
                font.family: "arial"
                font.pointSize: 14
                color: "white"
                text: qsTr("WIRE BUILDER")
                opacity: 0.5
                width: parent.width
                clip: true
            }
        }
        TabButton {
            Rectangle {
                anchors.fill: parent
                color: tabBar.currentIndex == 1 ? "black" : "#48484a"
            }
            Text {
                anchors.centerIn: parent
                font.family: "arial"
                font.pointSize: 14
                color: "white"
                text: qsTr("WELD SETTINGS")
                opacity: 0.5
                width: parent.width
                clip: true
            }
        }
    }

    Item {
        id: rightArea
        anchors.left: swipeView.right
        width: Screen.desktopAvailableWidth * 0.8
        height: parent.height // * 0.5
        Rectangle {
            anchors.fill: parent
            color: "#626465"
        }
        MyLineEdit {
            id: edit1
            width: 300
            height: 50
            anchors.top: parent.top
            inputWidth: parent.width * 0.3
            inputHeight: parent.height * 0.05
            defaultText: "SPLICE NAME"
            anchors.topMargin: 8
            anchors.left: parent.left
            anchors.leftMargin: 20
            clip: true
            //displayText: qsTr("SPLICE NAME")
        }


    }
}

