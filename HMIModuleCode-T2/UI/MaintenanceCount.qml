import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import QtQuick.Dialogs 1.2
Item {
    id: toolChange
    width: Screen.width*0.7
    height: Screen.height*0.6

    ListModel {
        id: listModel
        ListElement {key1:"Home";     key2:"3"; key3:"200,000"; key4:"105009"; key5:"10/20/2016"; key6:"Reset"}
        ListElement {key1:"AnvilTip"; key2:"3"; key3:"400,000"; key4:"15001"; key5:"10/20/2016"; key6:"Reset"}
        ListElement {key1:"Gather";   key2:"3"; key3:"400,000"; key4:"25111"; key5:"10/20/2016"; key6:"Reset"}
        ListElement {key1:"AnvilGuide"; key2:"3"; key3:"400,000"; key4:"35222"; key5:"10/20/2016"; key6:"Reset"}
        ListElement {key1:"Converter";  key2:"3"; key3:"400,000"; key4:"35224"; key5:"10/20/2016"; key6:"Reset"}
        ListElement {key1:"Converter";  key2:"-"; key3:"-"; key4:"35224"; key5:"10/20/2016"; key6:"-"}

    }

    Row {
        id: title
        spacing: 70
        anchors.left: listView.left
        Item {
            width: 370
            height: 10
        }

        Text {
            width: 150
            height: 79
            text: qsTr("Counter Limit")
            color: "white"
            font.family: "arial"
            font.pointSize: 14
            verticalAlignment: Qt.AlignVCenter
            horizontalAlignment: Qt.AlignHCenter
        }
        Text {
            width: 150
            height: 79
            text: qsTr("Current Counter")
            color: "white"
            font.family: "arial"
            font.pointSize: 14
            verticalAlignment: Qt.AlignVCenter
            horizontalAlignment: Qt.AlignHCenter
        }
        Text {
            width: 150
            height: 79
            text: qsTr("Data Started")
            color: "white"
            font.family: "arial"
            font.pointSize: 14
            verticalAlignment: Qt.AlignVCenter
            horizontalAlignment: Qt.AlignHCenter
        }
        Text {
            width: 150
            height: 79
            text: qsTr("Reset")
            color: "white"
            font.family: "arial"
            font.pointSize: 14
            verticalAlignment: Qt.AlignVCenter
            horizontalAlignment: Qt.AlignHCenter
        }
    }
    Line {
        id: line
        width: listView.width
        height: 2
        lineColor: "blue"
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.leftMargin: 30
        anchors.rightMargin: 30
        anchors.top: title.bottom
    }

    ListView {
        id: listView
        width: line.width
        height: parent.height * 0.7
        model: listModel
        delegate: listLine
        interactive: false
        anchors.top: line.bottom
        anchors.topMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 30
    }
    Component {
        id: listLine
        Item {
            id: line
            width: listView.width
            height: 80
            Row {
                spacing: 70
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
                    source: "file:///c:/ToolChangeImage/group2/wiredemo.jpg"
                }
                MyLineEdit {
                    width: 150
                    height: 60
                    inputHeight: 79
                    inputWidth: 150
                    defaultText: key3
                    visible: index == 5 ? false : true
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
                    height: 79
                    text: key6
                    visible: index == 5 ? false : true

                }
            }
        }
    }
    Row {
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottomMargin: 10
        spacing: 50
        Text {
            text: qsTr("ActuatorPart Number: xxx-xxx\nActuatorSerial Number:xxx-xxx")
            color: "white"
            font.family: "arial"
            font.pointSize: 14
        }
        Text {
            text: qsTr("Software Verson Number: xxx-xxx\nActuatorModule:xxx-xxx")
            color: "white"
            font.family: "arial"
            font.pointSize: 14
        }
    }


}
