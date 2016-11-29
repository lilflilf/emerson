import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import QtQuick.Dialogs 1.2
Item {
    id: toolChange
    property int select: -1
    property bool myfocus: false
    width: Screen.width*0.7
    height: Screen.height*0.6

//    Component.onCompleted: {
//        hmiAdaptor.maintenanceStart(3);
//    }
//    Component.onDestruction: {
//        hmiAdaptor.maintenanceStop(3);
//    }

    ListModel {
        id: listModel
        ListElement {key1:"Horn";     key2:"3"; key3:"200,000"; key4:"105009"; key5:"10/20/2016"; key6:"Reset"}
        ListElement {key1:"AnvilTip"; key2:"3"; key3:"400,000"; key4:"15001"; key5:"10/20/2016"; key6:"Reset"}
        ListElement {key1:"Gather";   key2:"3"; key3:"400,000"; key4:"25111"; key5:"10/20/2016"; key6:"Reset"}
        ListElement {key1:"AnvilGuide"; key2:"3"; key3:"400,000"; key4:"35222"; key5:"10/20/2016"; key6:"Reset"}
        ListElement {key1:"Converter";  key2:"3"; key3:"400,000"; key4:"35224"; key5:"10/20/2016"; key6:"Reset"}
        ListElement {key1:"Actuator";  key2:"-"; key3:"-"; key4:"35224"; key5:"10/20/2016"; key6:"-"}

    }

    Row {
        id: title
        spacing: 70
        anchors.left: listView.left
        anchors.top: parent.top
        anchors.topMargin: 15
        Item {
            width: 370
            height: 10
        }

        Text {
            width: 150
            text: qsTr("Counter Limit")
            color: "white"
            font.family: "arial"
            font.pixelSize: 25
            verticalAlignment: Qt.AlignVCenter
            horizontalAlignment: Qt.AlignHCenter
        }
        Text {
            width: 150
            text: qsTr("Current Counter")
            color: "white"
            font.family: "arial"
            font.pixelSize: 25
            verticalAlignment: Qt.AlignVCenter
            horizontalAlignment: Qt.AlignHCenter
        }
        Text {
            width: 150
            text: qsTr("Data Started")
            color: "white"
            font.family: "arial"
            font.pixelSize: 25
            verticalAlignment: Qt.AlignVCenter
            horizontalAlignment: Qt.AlignHCenter
        }
        Text {
            width: 150
            text: qsTr("Reset")
            color: "white"
            font.family: "arial"
            font.pixelSize: 25
            verticalAlignment: Qt.AlignVCenter
            horizontalAlignment: Qt.AlignHCenter
        }
    }
    Line {
        id: line
        width: listView.width
        height: 2
        lineColor: "white"
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.leftMargin: 20
        anchors.rightMargin: 30
        anchors.top: title.bottom
        anchors.topMargin: 10
    }

    ListView {
        id: listView
        width: line.width
        height: parent.height * 0.7
        model: listModel
        delegate: listLine
        interactive: false
        anchors.top: line.bottom
        anchors.topMargin: 5
        anchors.left: parent.left
        anchors.leftMargin: 20
    }
    Component {
        id: listLine
        Item {
            width: listView.width
            height: index == 5 ? 100 : 80
            Row {
                spacing: 70
                anchors.verticalCenter: parent.verticalCenter
                Text {
                    width: 150
                    height: 79
                    text: qsTr(key1)
                    color: "white"
                    font.family: "arial"
                    font.pointSize: 14
                    verticalAlignment: Qt.AlignVCenter
                    horizontalAlignment: Qt.AlignHCenter
                }
                Image {
                    width: 150
                    height: 60
                    //source: "file:///c:/ToolChangeImage/group2/wiredemo.jpg"
                }
                MiniKeyNumInput {
                    id: input
                    width: 150
                    height: 60
//                    inputHeight: 79
                    inputWidth: 150
                    inputText: key3
                    visible: index == 5 ? false : true
                    inputFocus: toolChange.myfocus
                    onInputFocusChanged: {
                        if (input.inputFocus) {
                            toolChange.select = index
                            backGround.visible = true
                            backGround.opacity = 0.5
                            keyNum.visible = true
                            keyNum.titleText = qsTr("Counter Limit")
                            keyNum.currentValue = input.inputText
                            keyNum.minvalue = "0"
                            keyNum.maxvalue = "10000"
                        }
                    }
                }
                Text {
                    width: 150
                    height: 79
                    text: qsTr("-")
                    color: "white"
                    font.family: "arial"
                    font.pointSize: 14
                    verticalAlignment: Qt.AlignVCenter
                    horizontalAlignment: Qt.AlignHCenter
                    visible: index == 5 ? true : false
                }
                Text {
                    width: 150
                    height: 79
                    text: qsTr(key4)
                    color: "white"
                    font.family: "arial"
                    font.pointSize: 14
                    verticalAlignment: Qt.AlignVCenter
                    horizontalAlignment: Qt.AlignHCenter
                }
                Text {
                    width: 150
                    height: 79
                    text: qsTr(key5)
                    color: "white"
                    font.family: "arial"
                    font.pointSize: 14
                    verticalAlignment: Qt.AlignVCenter
                    horizontalAlignment: Qt.AlignHCenter
                }

                CButton {
                    width: 150
                    text: key6
                    visible: index == 5 ? false : true

                }
            }
        }
    }
    Row {
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottomMargin: 20
        spacing: 50
        Text {
            text: qsTr("Actuator Part Number: xxx-xxx\n\nActuator Serial Number:xxx-xxx")
            color: "white"
            font.family: "arial"
            font.pointSize: 14
        }
        Text {
            text: qsTr("Actuator Software Verson Number: xxx-xxx\n\nActuator Module:xxx-xxx")
            color: "white"
            font.family: "arial"
            font.pointSize: 14
        }
    }
    Rectangle {
        id: backGround
        anchors.fill: parent
        color: "black"
        opacity: 0.5
        visible: false
        MouseArea {
            anchors.fill: parent
            onClicked: {

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
                listModel.set(toolChange.select,{"key3":keyNum.inputText})
                toolChange.myfocus = false
                backGround.visible = false
                backGround.opacity = 0
                keyNum.visible = false
                keyNum.inputText = ""
                keyNum.tempValue = ""
            } else if (index == 11) {
                backGround.visible = false
                toolChange.myfocus = false
                backGround.opacity = 0
                keyNum.visible = false
                keyNum.inputText = ""
                keyNum.tempValue = ""
            }
        }
        onInputTextChanged: {
            if (keyNum.inputText != "") {
                listModel.set(toolChange.select,{"key3":keyNum.inputText})
            }
        }
    }
}
