import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import QtQuick.Window 2.2

Item {
    width: Screen.desktopAvailableWidth
    height: Screen.desktopAvailableHeight

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
                    width: 40
                    height: 20
                    color: "green"
                    anchors.left: labelColor.right
                    anchors.leftMargin: 30
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

