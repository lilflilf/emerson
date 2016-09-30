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

        }

        Page {
            id: weldSettting
            ListModel {
                id: settingsModel
                Component.onCompleted: {
                    settingsModel.append({"name":"Energy"})
                    settingsModel.append({"name":"Trigger"})
                    settingsModel.append({"name":"Amplitude"})
                    settingsModel.append({"name":"Weld Pressure"})
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

    Item {
        id: rightArea
        anchors.left: swipeView.right
        width: Screen.desktopAvailableWidth * 0.8
        height: parent.height // * 0.5
        Rectangle {
            anchors.fill: parent
            color: "#AAAAAA"
        }
        MyLineEdit {
            id: edit1
            width: 300
            height: 50
            anchors.top: parent.top
            inputWidth: parent.width * 0.3
            inputHeight: parent.height * 0.05
            //displayText: qsTr("SPLICE NAME")

        }
    }
}

