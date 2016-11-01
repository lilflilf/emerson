import QtQuick 2.7
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.0
import QtQuick.Window 2.2

Item {
    id: qualityParent
    width: Screen.width * 0.43
    height: Screen.height *0.4
    property var clickType: 0
    Text {
        id: qualityWindowTitle
        text: qsTr("QualityWindow")
        font.family: "arial"
        font.pointSize: 16
        color: "white"
    }
    Switch2 {
        id: switch2
        width: Screen.width * 0.12
        height: Screen.height * 0.04
        anchors.right: parent.right
        textLeft: qsTr("Quality")
        textRight: qsTr("Graph")
        state: "left"
        onStateChanged: {
            if (switch2.state == "left") {
                qualityListViewTwo.visible = true
                myCanvas.visible = false
                qualityListView.visible = true
                qualityWindowTitle.text = qsTr("QualityWindow")
            }
            else {
                myCanvas.visible = true
                qualityListViewTwo.visible = false
                qualityListView.visible = false
                qualityWindowTitle.text = qsTr("GraphWindow")
            }
        }
    }
    ListModel {
        id: qualityModel
    }
    ListView {
        id: qualityListView
        width: Screen.width * 0.45
        height: Screen.height *0.25
        orientation: Qt.Horizontal
        interactive: false
        anchors.top: qualityWindowTitle.bottom
        anchors.topMargin: 20
        delegate: qualityDelegate
        model: 4
    }
    Component {
        id: qualityDelegate
        Item {
            id: name
            width: Screen.width * 0.1 //qualityParent.width / 4 //
            height: Screen.height * 0.25 //qualityParent.height / 2 //
            Rectangle {
                width: 40
                height: Screen.height * 0.25
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
                    Text {
                        id: lineValue
                        text: qsTr("170")
                        font.family: "arial"
                        color: "white"
                        font.pointSize: 12
                        anchors.left: parent.right
                    }
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
                    id: bottomText
                    anchors.top: parent.bottom
                    font.family: "arial"
                    color: "white"
                    font.pointSize: 12
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: qsTr("POWER")
                    Component.onCompleted: {
                        if (index == 0)
                            bottomText.text = qsTr("POWER")
                        else if (index == 1)
                            bottomText.text = qsTr("PRE-HEIGHT")
                        else if (index == 2)
                            bottomText.text = qsTr("POST-HEIGHT")
                        else if (index == 3)
                            bottomText.text = qsTr("TIME")

                    }
                }
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    console.log("clickkkkkk")
                    if (index == 0)
                        clickType = 20
                    else if (index == 1)
                        clickType = 40
                    else if (index == 2)
                        clickType = 60
                    else if (index == 3)
                        clickType = 80
                    qualityListViewTwo.model = 0
                    qualityListViewTwo.model = 100
                }
            }
        }
    }

    Rectangle {
        anchors.fill: qualityListViewTwo
        color: "#6d6e71"
        visible: qualityListViewTwo.visible
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
    }

    ListView {
        id: qualityListViewTwo
        width: qualityParent.width //Screen.width * 0.35
        height: Screen.height *0.25
        orientation: Qt.Horizontal
        interactive: false
        anchors.top: qualityListView.bottom
        anchors.topMargin: 40
        delegate: qualityListViewTwoDelegate
        model: 100
    }
    Component {
        id: qualityListViewTwoDelegate
        Item {
            width: 8
            height: Screen.height * 0.25
            Rectangle {
                id: point
                radius: 100
                width: 4
                height: 4
                anchors.top: parent.top
//                anchors.topMargin: 50
                Component.onCompleted: {
                    point.anchors.topMargin = index + clickType
                }
            }
        }
    }

    MyCanvas {
        id: myCanvas
        width: qualityParent.width //Screen.width * 0.35
        height: Screen.height * 0.5
        anchors.top: qualityWindowTitle.bottom
        anchors.topMargin: 30
    }
}
