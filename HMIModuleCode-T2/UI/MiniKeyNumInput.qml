import QtQuick 2.7

Item {
    property alias tipsText: tips.text
    property alias inputText: mytext.text
    property bool inputFocus: false
    property alias inputWidth: miniKey.width
    CButton {
        id: miniKey
        height: parent.height

        Text {
            id: mytext
            anchors.centerIn: parent
            font.family: "arial"
            color: "white"
            font.pointSize: 16
        }

        backgroundComponent: Rectangle {
            anchors.fill: parent
            color: "#052a40"
            border.color: "#1987ab"
            border.width: 2
        }
        onClicked: {
            inputFocus = true
        }
    }

    Text {
        id: tips
        anchors.left: miniKey.right
        anchors.leftMargin: 8
        anchors.verticalCenter: miniKey.verticalCenter
        font.family: "arial"
        color: "white"
        font.pointSize: 16
    }
}


