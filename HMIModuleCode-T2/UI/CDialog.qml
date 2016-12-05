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
        anchors.centerIn: parent
        width: 700
        height: 525
        source: "qrc:/images/images/dialogbg.png"
        Text {
            id: title
            anchors.centerIn: parent
            font.family: "arial"
            font.pixelSize: 25
            color: "white"
            text: qsTr("aaaaaaaaaaaaaaaaaa")
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