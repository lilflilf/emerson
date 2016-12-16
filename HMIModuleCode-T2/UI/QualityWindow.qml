import QtQuick 2.7
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.0
import QtQuick.Window 2.2

Item {
    id: qualityParent
    width: Screen.width * 0.43
    height: Screen.height *0.4
    property var clickType: 0
    property alias qualityModel: qualityModel
    property alias timeModel : timeModel
    property alias powerModel: powerModel
    property alias preModel: preModel
    property alias postModel: postModel
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
    ListModel {
        id: timeModel
    }
    ListModel {
        id: powerModel
    }
    ListModel {
        id: preModel
    }
    ListModel {
        id: postModel
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
        anchors.left: parent.left
        anchors.leftMargin: 10
        model: qualityModel
    }
    ExclusiveGroup {
        id: bottomGroup
    }
    Component {
        id: qualityDelegate
        Item {
            id: name
            width: Screen.width * 0.12 //qualityParent.width / 4 //
            height: Screen.height * 0.25 //qualityParent.height / 2 //
            Rectangle {
                width: 40
                height: Screen.height * 0.25
                anchors.left: parent.left
                anchors.leftMargin: 10
                border.color: "white"
                border.width: 1
                color: Qt.rgba(0,0,0,0)
                Image {
                    id: currentArrow
                    anchors.left: parent.right
                    source: "qrc:/images/images/current_operate.png"
                    visible: current == -1 ? false : true
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: ((current - redMin) / redMax * (parent.height * 0.8) + (parent.height * 0.1) - currentArrow.height / 2) > parent.height ?
                                              parent.height - currentArrow.height / 2 : (current - redMin) / redMax * (parent.height * 0.8) + (parent.height * 0.1) - currentArrow.height / 2

                    Text {
                        id: lineValue
                        text: current //qsTr("170")
                        font.family: "arial"
                        color: "white"
                        font.pointSize: 16
                        anchors.left: parent.right
                    }
                }
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
                    Text {
                        text: redMax //qsTr("170")
                        font.family: "arial"
                        color: "white"
                        font.pointSize: 12
                        anchors.right: parent.left
                        anchors.verticalCenter: parent.verticalCenter
                        opacity: 0.5
                    }
                }
                Line {
                    anchors.top: parent.top
                    anchors.topMargin: parent.height * 0.2
                    lineColor: "yellow"
                    width: parent.width
                    height: 2
                    Text {
                        text: yellowMax //qsTr("170")
                        font.family: "arial"
                        color: "white"
                        font.pointSize: 12
                        anchors.right: parent.left
                        anchors.verticalCenter: parent.verticalCenter
                        opacity: 0.5
                    }
                }
                Line {
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: parent.height * 0.2
                    lineColor: "yellow"
                    width: parent.width
                    height: 2
                    Text {
                        text: yellowMin //qsTr("170")
                        font.family: "arial"
                        color: "white"
                        font.pointSize: 12
                        anchors.right: parent.left
                        anchors.verticalCenter: parent.verticalCenter
                        opacity: 0.5
                    }
                }
                Line {
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: parent.height * 0.1
                    lineColor: "red"
                    width: parent.width
                    height: 2
                    Text {
                        text: redMin //qsTr("170")
                        font.family: "arial"
                        color: "white"
                        font.pointSize: 12
                        anchors.right: parent.left
                        anchors.verticalCenter: parent.verticalCenter
                        opacity: 0.5
                    }
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
                            bottomText.text = qsTr("TIME")
                        else if (index == 1)
                            bottomText.text = qsTr("POWER")
                        else if (index == 2)
                            bottomText.text = qsTr("PRE-HEIGHT")
                        else if (index == 3)
                            bottomText.text = qsTr("POST-HEIGHT")
                    }
                }
                Item {
                    id: bottomItem
                    width: parent.width
                    anchors.top: bottomText.bottom
                    visible: radioButton.checked
                    Rectangle {
                        id: bottomItem1
                        width: parent.width
                        height: 3
                        color: "#f79428"
                    }
                    Rectangle {
                        color: "#6d6e71"
                        anchors.top: bottomItem1.bottom
                        anchors.topMargin: 10
                        anchors.horizontalCenter: parent.horizontalCenter
                        width: 40
                        height: 40
                        rotation: 45
                    }
                    RadioButton {
                        id: radioButton
                        visible: false
                        exclusiveGroup: bottomGroup
                    }
                }
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    radioButton.checked = true
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
//        anchors.fill: qualityListViewTwo
        color: "#6d6e71"
        visible: qualityListViewTwo.visible
        width: qualityParent.width //Screen.width * 0.35
        height: Screen.height *0.25
        anchors.top: qualityListView.bottom
        anchors.topMargin: 45
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
        width: qualityParent.width - 20 //Screen.width * 0.35
        height: Screen.height *0.25
        orientation: Qt.Horizontal
        interactive: false
        anchors.top: qualityListView.bottom
        anchors.topMargin: 40
        delegate: qualityListViewTwoDelegate
        model: 100
        layoutDirection: Qt.RightToLeft
        anchors.right: parent.right
        anchors.rightMargin: 20
    }
    Component {
        id: qualityListViewTwoDelegate
        Item {
            width: index == 0 ? 40 : 8
            height: Screen.height * 0.25
            Rectangle {
                width: 15
                height: parent.height
                color: Qt.rgba(0,0,0,0)
                border.width: 1
                border.color: "#33FFCC"
                visible: index == 0 ? true : false
                anchors.horizontalCenter: parent.horizontalCenter
            }
            Rectangle {
                id: point
                radius: 100
                width: index == 0 ? 30 : 4
                height: index == 0 ? 30 : 4
                anchors.top: parent.top
                anchors.horizontalCenter: parent.horizontalCenter
                color: index == 0 ? "#33FFCC" : "white" //* 8 >= qualityListViewTwo.width ? "red" : "white"
                Component.onCompleted: {
                    point.anchors.topMargin = hmiAdaptor.randPoint() + 80 //index + clickType
                }
                Text {
                    text: index == 0 ? "68" : ""
                    font.family: "arial"
                    font.pixelSize: 20
                    color: "white"
                    anchors.centerIn: parent
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
