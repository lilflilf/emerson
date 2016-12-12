import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2

Item {
    id: shrink
    property int selectIndex: -1
    width: parent.width
    height: parent.height
    signal sureClick()
    signal cancelClick()
    property alias shrinkId: inputshrinkId.inputText
    property alias shrinkTemp: inputTemperature.inputText
    property alias shrinkTime: inputtimeText.inputText

    ListModel {
        id: shrinkModel
        Component.onCompleted: {
            hmiAdaptor.dataCommunicationExecute("_Recall");
            var list
            list = hmiAdaptor.dataCommunicationGetValue("shrinkData")
            if (list.length % 3 == 0)
            {
                for (var i = 0 ;i < list.length / 3; i++)
                {
                    shrinkModel.append({shrinkid:list[i*3],temperature:list[i*3+1],times:list[i*3+2]})
                }
            }
        }
    }

    Rectangle {
        id: backGround
        anchors.fill: parent
        color: "#686a6c"
        Text {
            id: title
            anchors.top: parent.top
            anchors.topMargin: 60
            anchors.right: inputshrinkId.left
            anchors.rightMargin: 20
            width: 150
            height: 60
            font.pointSize: 18
            font.family: "arial"
            text: qsTr("Shrink Tube ID")
            verticalAlignment: Qt.AlignVCenter
            horizontalAlignment: Qt.AlignRight
            color: "white"

        }

        MyLineEdit {
            id: inputshrinkId
            anchors.top: parent.top
            anchors.topMargin: 60
            anchors.right: parent.right
            anchors.rightMargin: 72
            horizontalAlignment: Qt.AlignHCenter
            width: 375
            height: 60
            inputWidth: 375
            inputColor: "white"
            inputHeight: 60
            inputText: " " //shrinkModel.get(selectIndx).shrinkid
            Image {
                id: selectImage
                anchors.verticalCenter: parent.verticalCenter
                anchors.right: parent.right
                anchors.rightMargin: 6
                source: "qrc:/images/images/down.png"
            }
            MouseArea {
                anchors.top: parent.top
                anchors.right: parent.right
                width: 80
                height: parent.height
                onClicked: {
                    contArea.visible = true
                }
            }
        }

        Text {
            id: temperatureText
            anchors.top: inputshrinkId.bottom
            anchors.topMargin: 20
            anchors.right: inputTemperature.left
            anchors.rightMargin: 20
            width: 150
            height: 60
            font.pointSize: 18
            font.family: "arial"
            text: qsTr("Temp")
            verticalAlignment: Qt.AlignVCenter
            horizontalAlignment: Qt.AlignRight
            color: "white"
        }
        MyLineEdit {
            id: inputTemperature
            property var partId: 1
            anchors.top: inputshrinkId.bottom
            anchors.topMargin: 20
            anchors.right: parent.right
            anchors.rightMargin: 72
            horizontalAlignment: Qt.AlignHCenter
            width: 375
            height: 60
            inputWidth: 375
            inputColor: "white"
            inputHeight: 60
            inputText: " " //shrinkModel.get(selectIndx).temperature
        }
        Text {
            id: timeText
            anchors.top: temperatureText.bottom
            anchors.topMargin: 20
            anchors.right: inputtimeText.left
            anchors.rightMargin: 20
            width: 150
            height: 60
            font.pointSize: 18
            font.family: "arial"
            text: qsTr("Time")
            verticalAlignment: Qt.AlignVCenter
            horizontalAlignment: Qt.AlignRight
            color: "white"
        }
        MyLineEdit {
            id: inputtimeText
            anchors.top: temperatureText.bottom
            anchors.topMargin: 20
            anchors.right: parent.right
            anchors.rightMargin: 72
            width: 375
            height: 60
            inputWidth: 375
            inputHeight: 60
            inputColor: "white"
            horizontalAlignment: Qt.AlignHCenter
            inputText: " " //shrinkModel.get(selectIndx).times
        }
        CButton {
            anchors.right: sure.left
            anchors.rightMargin: 15
            anchors.top: timeText.bottom
            anchors.topMargin: 16
            width: 180
            text: qsTr("CANCEL")
            textColor: "white"
            iconSource: "qrc:/images/images/cancel.png"
            onClicked: {
                cancelClick()
            }
        }
        CButton {
            id: sure
            anchors.right: parent.right
            anchors.rightMargin: 72
            anchors.top: timeText.bottom
            anchors.topMargin: 16
            width: 180
            text: qsTr("OK")
            textColor: "white"
            iconSource: "qrc:/images/images/OK.png"
            onClicked: {
                sureClick()

            }
        }
        Rectangle {
            id: contArea
            visible: false
            anchors.top: title.bottom
            anchors.right: inputshrinkId.right
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 24
            width: parent.width/4
            border.width: 1
            border.color: "#6d6e71"
            color: "#48484a"
            ListView {
                id: shrinkList
                anchors.fill: parent
                model: shrinkModel
                clip: true
                delegate: Item {
                    property var theopacity: 0.0
                    width: parent.width
                    height: 40 //parent.height
                    Text {
                        anchors.fill: parent
                        text: shrinkid
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
                            inputshrinkId.inputText = shrinkid
                            inputtimeText.inputText = times
                            inputTemperature.inputText = temperature
                            contArea.visible = false
                        }
                    }
                }

            }
        }
    }
}
