import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import QtQuick.Dialogs 1.2
Item {
    id: calibration
    width: Screen.width*0.7
    height: Screen.height*0.6
    property var currentIndex: 1
    Image {
        anchors.fill: parent
        source: "qrc:/images/images/bg.png"
    }
    Rectangle {
        id: back
        anchors.fill: parent
        color: "black"
        opacity: 0.5
    }
    Rectangle {
        color: "#6d6e71"
        width: parent.width * 0.5
        height: parent.height * 0.8
        anchors.centerIn: parent
        Text {
            id: title
            text: qsTr("Calibration-Width and Height")
            color: "white"
            font.family: "arial"
            font.pointSize: 14
            anchors.left: parent.left
            anchors.leftMargin: 15
            anchors.top: parent.top
            anchors.topMargin: 15
        }
        Text {
            id: content
            text: qsTr("This process calibrates and adjusts the Width and Height control system.Please press and hold the start button on this sereen or the start switch on the actuarot.")
            color: "white"
            font.family: "arial"
            font.pointSize: 14
            anchors.left: parent.left
            anchors.leftMargin: 15
            width: parent.width * 0.8
            anchors.top: title.bottom
            anchors.topMargin: 15
            wrapMode: Text.WordWrap
        }

        Image {
            id: image
            source: "qrc:/images/images/wiredemo.jpg"
            width: parent.width * 0.4
            height: parent.height * 0.5
            anchors.top: content.bottom
            anchors.topMargin: 50
            anchors.left: parent.left
            anchors.leftMargin: 20
        }

        Column {
            spacing: 20
            anchors.verticalCenter: image.verticalCenter
            anchors.left: image.right
            anchors.leftMargin: 100
            CButton {
                id: button1
                height: 79
                width: 200
                text: qsTr("Start")
                onClicked: {
                    calibration.currentIndex++
                }
            }
            MyLineEdit {
                id: line1
                height: 79
                width: 200
                inputWidth: 200
                inputHeight: 79
                visible: false
                defaultText: qsTr("enter value here")
            }

            CButton {
                id: button2
                height: 79
                width: 200
                text: qsTr("Cancel")
                onClicked: {
                    if (button2.text == "Back")
                        calibration.currentIndex--
                }
            }
            Connections {
                target: calibration
                onCurrentIndexChanged: {
                    if (calibration.currentIndex == 1)
                    {
                        button1.text = qsTr("Start")
                        button2.text = qsTr("Cancel")
                    }
                    else if (calibration.currentIndex == 2)
                    {
                        button1.text = qsTr("Next")
                        button2.text = qsTr("Back")
                    }
                    else if (calibration.currentIndex == 3)
                    {
                        button1.text = qsTr("Start")
                        button2.text = qsTr("Cancel")
                    }
                    else if (calibration.currentIndex == 4)
                    {
                        button1.visible = false
                        line1.visible = true
                        button2.text = qsTr("Save")
                    }
                }
            }
        }

    }

}
