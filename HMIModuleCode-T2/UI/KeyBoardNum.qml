import QtQuick 2.7
import QtQuick.Layouts 1.0
import QtQuick.Window 2.2
import QtQuick.Controls 1.4

Item {
    id: keyBoardnum
    property alias titleText: title.text
    property alias currentValue: currenvalue.text
    property int minvalue: 0
    property string inputText: ""
    property int maxvalue: 0
    signal currentClickIndex(int index)
    width: parent.width
    height: parent.height
    Rectangle {
        anchors.fill: parent
        color: "#6d6e71"
    }

    Text {
        id: title
        anchors.top: parent.top
        anchors.topMargin: 24
        anchors.left: parent.left
        anchors.leftMargin: 24
        font.family: "arial"
        font.pointSize: 24
        color: "white"
        text: qsTr("text")
    }
    Text {
        id: currentText
        anchors.top: title.bottom
        anchors.topMargin: 24
        anchors.left: title.left
        font.family: "arial"
        font.pixelSize: 24
        color: "white"
        text: qsTr("Current Value")
    }
    Text {
        id: currenvalue
        anchors.top: currentText.bottom
        anchors.topMargin: 24
        anchors.left: title.left
        font.family: "arial"
        font.pixelSize: 24
        color: "white"
        text: qsTr("Current Value")
    }
    Text {
        id: newText
        anchors.top: currenvalue.bottom
        anchors.topMargin: 24
        anchors.left: title.left
        font.family: "arial"
        font.pixelSize: 24
        color: "white"
        text: qsTr("New Value")
    }
    Rectangle {
        id: newvalueBack
        anchors.top: newText.bottom
        anchors.topMargin: 24
        anchors.left: title.left
        width: parent.width/3
        height: 30
        border.color: "#1987ab"
        border.width: 2
        color: "black"
    }
    Text {
        id: newvalue
        anchors.fill: newvalueBack
        font.family: "arial"
        font.pixelSize: 22
        horizontalAlignment: Qt.AlignHCenter
        verticalAlignment: Qt.AlignVCenter
        color: "white"
        elide: Text.ElideRight
        text: qsTr(inputText)
    }
    Text {
        id: minValue
        anchors.top: newvalue.bottom
        anchors.topMargin: 24
        anchors.left: title.left
        font.family: "arial"
        font.pixelSize: 24
        color: "white"
        text: qsTr("Min Value ")+minvalue
    }
    Text {
        id: maxValue
        anchors.top: minValue.bottom
        anchors.topMargin: 24
        anchors.left: title.left
        font.family: "arial"
        font.pixelSize: 24
        color: "white"
        text: qsTr("Max Value ")+maxvalue
    }
    Grid {
        anchors.top: title.bottom
        anchors.right: parent.right
        width: parent.width/2
        height: parent.height
        spacing: 30
        columns: 3
        Repeater {
            model: ["1","2","3","4","5","6","7","8","9","INC","0","C","ESC",".","OK"]
            delegate: CButton {
                width: 50
                height: 50
                text: modelData
                textColor: "white"
                onClicked: {
                    if (index < 11 && index != 9) {
                        inputText += modelData
                    }
                    currentClickIndex(index)
                }
            }
        }
    }
}

