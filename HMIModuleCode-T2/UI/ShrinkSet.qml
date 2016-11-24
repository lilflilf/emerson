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
            id: title
            anchors.top: parent.top
            anchors.topMargin: 24
            anchors.left: parent.left
            anchors.leftMargin: 48
            height: 50
            clip: true
            color: "white"
            text: qsTr("SHRINK TUBE ID")
            font.pointSize: 16
            font.family: "arial"
        }
        Rectangle {
            id: titleInput
            anchors.verticalCenter: title.verticalCenter
            anchors.left: title.right
            anchors.leftMargin: 4
            width: parent.width*0.6
            height: 50
            border.color: "#1987ab"
            border.width: 2
            color: "#052a40"
            Image {
                id: selectImage
                anchors.verticalCenter: parent.verticalCenter
                anchors.right: parent.right
                anchors.rightMargin: 6
                source: "qrc:/images/images/down.png"
            }
            MouseArea {
                anchors.top: parent.top
                anchors.left: textInput.right
                anchors.right: parent.right
                height: parent.height
                onClicked: {
                    contArea.visible = true
                }
            }
            TextInput {
                id: textInput
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                anchors.right: selectImage.left
                anchors.rightMargin: 20
                height: parent.height
                verticalAlignment: Qt.AlignVCenter
                horizontalAlignment: Qt.AlignHCenter
                clip: true
                font.pointSize: 16
                font.family: "arial"
                color: "white"
            }
        }
        Text {
            id: timeText
            anchors.verticalCenter: timeSet.verticalCenter
            anchors.right: timeSet.left
            anchors.rightMargin: 4
            verticalAlignment: Qt.AlignVCenter
            height: 50
            clip: true
            color: "white"
            text: qsTr("Time(s)")
            font.pointSize: 16
            font.family: "arial"
        }
        MyLineEdit {
            id: timeSet
            anchors.top: title.bottom
            anchors.topMargin: 24
            anchors.right: parent.right
            anchors.rightMargin: parent.width/2+10
            width: parent.width/4
            height: 50
            horizontalAlignment: Qt.AlignHCenter
            inputWidth: parent.width/4
            inputHeight: 50
        }
        Text {
            id: tempText
            anchors.verticalCenter: tempSet.verticalCenter
            anchors.left: parent.left
            anchors.leftMargin: parent.width/2+10
            verticalAlignment: Qt.AlignVCenter
            height: 50
            clip: true
            color: "white"
            text: qsTr("Temp(℃)")
            font.pointSize: 16
            font.family: "arial"
        }
        MyLineEdit {
            id: tempSet
            anchors.top: title.bottom
            anchors.topMargin: 24
            anchors.left: tempText.right
            anchors.leftMargin: 4
            width: parent.width/4
            height: 50
            horizontalAlignment: Qt.AlignHCenter
            inputWidth: parent.width/4
            inputHeight: 50
        }
        CButton {
            id: enterButton
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 24
            anchors.right: escButton.left
            anchors.rightMargin: 48
            width: parent.width/6
            text: qsTr("OK")
            onClicked: {
                shrink.visible = false
            }
        }
        CButton {
            id: escButton
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 24
            anchors.right: parent.right
            anchors.rightMargin: 48
            width: parent.width/6
            text: qsTr("Cancel")
            onClicked: {
                shrink.visible = false
            }
        }
        Rectangle {
            id: contArea
            visible: false
            anchors.top: title.bottom
            anchors.right: titleInput.right
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 24
            width: parent.width/4
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
                                    textInput.text = modelData+1
                                } else {
                                    selected.itemAt(selectIndex).theopacity = 0.0
                                    selected.itemAt(index).theopacity = 0.5
                                    selectIndex = index
                                    textInput.text = modelData+1
                                }
                                contArea.visible = false
                            }
                        }
                    }
                }
            }
        }
    }
}
