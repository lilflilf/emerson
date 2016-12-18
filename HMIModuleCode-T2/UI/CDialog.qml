import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2

Item {
    id: dialog
    width: Screen.width
    height: Screen.height
    property alias okvisible: okButton.visible
    property alias okText: okButton.text
    property alias cancelvisible: cancelButton.visible
    property alias cancelText: cancelButton.text
    property alias centerText: title.text
    property alias msgTypeIco: msgType.source
    property alias titleText: headText.text
    signal cliceTo(bool reb)
    Rectangle {
        id: backGround
        anchors.fill: parent
        color: "black"
        opacity: 0.5
        MouseArea {
            anchors.fill: parent
            onClicked: {

            }
        }
    }
    Image {
        anchors.top: parent.top
        anchors.topMargin: (parent.height-525)/2+25
        anchors.left: parent.left
        anchors.leftMargin: (parent.width - 700)/2
        width: 700
        height: 525
        source: "qrc:/images/images/dialogbg.png"
        Image {
            id: msgType
            width: 80
            height: 80
        }
        Text {
            id: headText
            font.family: "arial"
            font.pixelSize: 25
            wrapMode: Text.WordWrap
            color: "white"
        }
        Text {
            id: title
            anchors.centerIn: parent
            anchors.left: parent.left
            anchors.leftMargin: 10
            width: parent.width - 20
            font.family: "arial"
            font.pixelSize: 25
            wrapMode: Text.WordWrap
            color: "white"
            horizontalAlignment: Qt.AlignHCenter
            text: qsTr("")
        }
        CButton {
            id: okButton
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 24
            anchors.right: parent.right
            anchors.rightMargin: 30
            width: 180
            visible: false
            pointSize: 16
            text: qsTr("")
            onClicked: {
                dialog.visible = false
                cliceTo(true)
            }
        }
        CButton {
            id: cancelButton
            anchors.right: okButton.left
            anchors.bottom: okButton.bottom
            anchors.rightMargin: 20
            width: 180
            pointSize: 16
            visible: false
            text: qsTr("")
            onClicked: {
                dialog.visible = false
                cliceTo(false)
            }
        }
    }
}
