import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2

Item {
    id: shrink
    property int selectIndex: -1
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
                    id: selected
                    model: 4
                    delegate: Item {
                        property var theopacity: 0.0
                        width: parent.width
                        height: parent.height
                        Text {
                            anchors.fill: parent
                            text: modelData+1
                            color: "white"
                            font.pointSize: 16
                            font.family: "arial"
                            verticalAlignment: Qt.AlignVCenter
                            horizontalAlignment: Qt.AlignHCenter
                        }
                        Rectangle {
                            id: backcolor
                            anchors.fill: parent
                            color: "black"
                            opacity: theopacity
                        }
                        MouseArea {
                            anchors.fill: parent
                            onClicked: {
                                if (selectIndex == -1) {
                                    selectIndex = index
                                    selected.itemAt(index).theopacity = 0.5
                                } else {
                                    selected.itemAt(selectIndex).theopacity = 0.0
                                    selected.itemAt(index).theopacity = 0.5
                                    selectIndex = index
                                }
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
            anchors.leftMargin: parent.width/15
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
        Text {
            id: shrinkTube
            anchors.top: tempSet.bottom
            anchors.topMargin: 24
            anchors.left: contArea.right
            anchors.leftMargin: 24
            text: qsTr("Shrink Tube:")
            color: "white"
            width: parent.width/6
            font.pointSize: 16
            font.family: "arial"
        }
        Switch2 {
            id: onoroff
            anchors.top: tempSet.bottom
            anchors.topMargin: 18
            anchors.left: shrinkTube.right
            anchors.leftMargin: 24
            height: 40
            width: parent.width/6
            textLeft: qsTr("ON")
            textRight: qsTr("OFF")
            state: "right"
            opacity: 0.8
        }
        CButton {
            id: enterButton
            anchors.top: onoroff.bottom
            anchors.topMargin: 24
            anchors.left: contArea.right
            anchors.leftMargin: parent.width/8
            width: parent.width/6
            height: 40
            text: qsTr("Enter")
            onClicked: {
                shrink.visible = false
            }
        }
        CButton {
            id: escButton
            anchors.top: onoroff.bottom
            anchors.topMargin: 24
            anchors.left: enterButton.right
            anchors.leftMargin: 40
            width: parent.width/6
            height: 40
            text: qsTr("Esc")
            onClicked: {
                shrink.visible = false
            }
        }
    }
}
