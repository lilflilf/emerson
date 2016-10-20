import QtQuick 2.7
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.0
import QtQuick.Window 2.2

Item {
    width: Screen.desktopAvailableWidth * 0.4
    height: Screen.desktopAvailableHeight *0.4
    Text {
        id: qualityWindowTitle
        text: qsTr("QualityWindow")
        font.family: "arial"
        font.pointSize: 16
        color: "white"
    }
    Switch2 {
        width: Screen.desktopAvailableWidth * 0.12
        height: Screen.desktopAvailableHeight * 0.04
        anchors.right: parent.right
        textLeft: qsTr("Quality")
        textRight: qsTr("Graph")
        state: "left"
    }
    ListModel {
        id: qualityModel
    }
    ListView {
        id: qualityListView
        width: Screen.desktopAvailableWidth * 0.45
        height: Screen.desktopAvailableHeight *0.45
        orientation: Qt.Horizontal
        interactive: true
        anchors.top: qualityWindowTitle.bottom
        anchors.topMargin: 20
        delegate: qualityDelegate
        model: 4
    }
    Component {
        id: qualityDelegate
        Item {
            id: name
            width: Screen.desktopAvailableWidth * 0.1
            height: Screen.desktopAvailableHeight * 0.4
            Rectangle {
                width: 50
                height: Screen.desktopAvailableHeight * 0.4
                anchors.left: parent.left
                anchors.leftMargin: 10
                border.color: "white"
                border.width: 1
                color: Qt.rgba(0,0,0,0)
                Line {
                    anchors.top: parent.top
                    anchors.topMargin: parent.height / 2
                    lineColor: "white"
                    width: parent.width
                    height: 2
                }
                Line {
                    anchors.top: parent.top
                    anchors.topMargin: parent.height * 0.1
                    lineColor: "red"
                    width: parent.width
                    height: 2
                }
                Line {
                    anchors.top: parent.top
                    anchors.topMargin: parent.height * 0.2
                    lineColor: "yellow"
                    width: parent.width
                    height: 2
                }
                Line {
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: parent.height * 0.2
                    lineColor: "yellow"
                    width: parent.width
                    height: 2
                }
                Line {
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: parent.height * 0.1
                    lineColor: "red"
                    width: parent.width
                    height: 2
                }
                Text {
                    anchors.top: parent.bottom
                    font.family: "arial"
                    color: "white"
                    font.pointSize: 14
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: qsTr("POWER")
                }
            }
        }
    }
}
