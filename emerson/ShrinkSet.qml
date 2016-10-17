import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2

Item {
    width: parent.width
    height: parent.height
    Rectangle {
        id: backGround
        anchors.fill: parent
        color: "#686a6c"
        Text {
            id: shrinkText
            anchors.top: parent.top
            anchors.topMargin: 24
            anchors.left: parent.left
            anchors.leftMargin: 20
            width: parent.width/3
            horizontalAlignment: Qt.AlignHCenter
            text: qsTr("Shrink Tube")
            font.pointSize: 16
            font.family: "arial"
            color: "white"
            clip: true
        }
        Rectangle {
            id: contArea
            anchors.top: shrinkText.bottom
            anchors.topMargin: 24
            anchors.left: parent.left
            anchors.leftMargin: 24
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 24
            width: parent.width/3
            border.width: 1
            border.color: "#6d6e71"
            color: "#48484a"
            Column {
                id: shrinkList
                width: parent.width
                height: 40
                Repeater {
                    model: 4
                    delegate: Item {
                        width: parent.width
                        height: parent.height
                        Text {
                            anchors.fill: parent
                            text: modelData+1
                            color: "white"
                            font.pointSize: 16
                            font.family: "arial"
                            horizontalAlignment: Qt.AlignHCenter
                        }
                        Rectangle {
                            id: backcolor
                            anchors.fill: parent
                            color: "black"
                            opacity: 0
                        }

                        MouseArea {
                            anchors.fill: parent
                            onClicked: {
                                backcolor.opacity = 0.7
                            }
                        }
                    }
                }
            }
        }
        Text {
            id: shrinkId
            anchors.top: shrinkText.bottom
            anchors.topMargin: 24
            anchors.left: contArea.right
            anchors.leftMargin: 24
            height: 40
            clip: true
            color: "white"
            text: qsTr("SHRINK TUBE ID")
            font.pointSize: 16
            font.family: "arial"
        }
        MyLineEdit {
            id: idSet
            anchors.top: shrinkText.bottom
            anchors.topMargin: 18
            anchors.left: shrinkId.right
            anchors.leftMargin: 6
            width: parent.width/3
            height: 40
            horizontalAlignment: Qt.AlignHCenter
            inputWidth: parent.width/3
            inputHeight: 38
        }
        Text {
            id: timeText
            anchors.top: shrinkId.bottom
            anchors.topMargin: 24
            anchors.left: contArea.right
            anchors.leftMargin: 24
            height: 40
            clip: true
            color: "white"
            text: qsTr("Time(s)")
            font.pointSize: 16
            font.family: "arial"
        }
        MyLineEdit {
            id: timeSet
            anchors.top: shrinkId.bottom
            anchors.topMargin: 18
            anchors.left: timeText.right
            anchors.leftMargin: 6
            width: parent.width/7
            height: 40
            horizontalAlignment: Qt.AlignHCenter
            inputWidth: parent.width/7
            inputHeight: 38
        }
        Text {
            id: tempText
            anchors.top: shrinkId.bottom
            anchors.topMargin: 24
            anchors.left: timeSet.right
            anchors.leftMargin: parent.width/11
            height: 40
            clip: true
            color: "white"
            text: qsTr("Temp(℃)")
            font.pointSize: 16
            font.family: "arial"
        }
        MyLineEdit {
            id: tempSet
            anchors.top: shrinkId.bottom
            anchors.topMargin: 18
            anchors.left: tempText.right
            anchors.leftMargin: 6
            width: parent.width/7
            height: 40
            horizontalAlignment: Qt.AlignHCenter
            inputWidth: parent.width/7
            inputHeight: 38
        }
        CheckBox {
            id: checkRec
            anchors.top: tempSet.bottom
            anchors.topMargin: 24
            anchors.left: contArea.right
            anchors.leftMargin: 24
            width: 100
            height: 40
            checked: true
            text: qsTr("Shrink Tube")
        }
        CButton {
            id: enterButton
            anchors.top: checkRec.bottom
            anchors.topMargin: 24
            anchors.left: contArea.right
            anchors.leftMargin: 40
            width: 100
            height: 40

        }
        CButton {
            id: escButton
            anchors.top: checkRec.bottom
            anchors.topMargin: 24
            anchors.left: enterButton.right
            anchors.leftMargin: 40
            width: 100
            height: 40
        }
    }
}
