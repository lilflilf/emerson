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
    Image {
        anchors.fill: parent
        source: "qrc:/images/images/keyBoardbg.png"
    }

    Text {
        id: title
        anchors.top: parent.top
        anchors.topMargin: 20
        anchors.left: parent.left
        anchors.leftMargin: 20
        font.family: "arial"
        font.pixelSize: 27
        color: "white"
        text: qsTr("text")
    }
    Text {
        id: currentText
        anchors.top: title.bottom
        anchors.topMargin: 44
        anchors.left: title.left
        font.family: "arial"
        font.pixelSize: 24
        color: "#aeb4b9"
        text: qsTr("Current Value")
    }
    Rectangle {
        id: rec1
        anchors.top: currentText.bottom
        anchors.topMargin: 24
        anchors.left: title.left
        width: 300
        height: 50
        border.width: 1
        border.color: "#0079C1"
        color: Qt.rgba(0,0,0,0)
        Text {
            id: currenvalue
            anchors.centerIn: parent
            horizontalAlignment: Qt.AlignHCenter
            font.family: "arial"
            font.pixelSize: 21
            color: "white"
            elide: Text.ElideRight
            text: qsTr("Current Value")
        }
    }
    Text {
        id: newText
        anchors.top: rec1.bottom
        anchors.topMargin: 20
        anchors.left: title.left
        font.family: "arial"
        font.pixelSize: 24
        color: "white"
        text: qsTr("New Value")
    }
    Rectangle {
        id: rec2
        anchors.top: newText.bottom
        anchors.topMargin: 24
        anchors.left: title.left
        width: 300
        height: 50
        border.width: 1
        border.color: "#0079C1"
        color: Qt.rgba(0,0,0,0)
        Text {
            id: newvalue
            anchors.centerIn: parent
            horizontalAlignment: Qt.AlignHCenter
            font.family: "arial"
            font.pixelSize: 21
            elide: Text.ElideRight
            color: "white"
            text: qsTr(inputText)
        }
    }
    Text {
        id: minValue
        anchors.top: rec2.bottom
        anchors.topMargin: 34
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
    Image {
        id: close
        anchors.top: parent.top
        anchors.right: parent.right
        source: "qrc:/images/images/keyboardclose.png"
        MouseArea {
            anchors.fill: parent
            onClicked: {
                keyBoardnum.visible = false
                currentClickIndex(15)
            }
        }
    }
    ListModel {
        id: listModel
        Component.onCompleted: {
            listModel.append({"iconsource":"qrc:/images/images/keyboard1.png","value":"1"})
            listModel.append({"iconsource":"qrc:/images/images/keyboard2.png","value":"2"})
            listModel.append({"iconsource":"qrc:/images/images/keyboard3.png","value":"3"})
            listModel.append({"iconsource":"qrc:/images/images/keyboarddel.png","value":""})
            listModel.append({"iconsource":"qrc:/images/images/keyboard4.png","value":"4"})
            listModel.append({"iconsource":"qrc:/images/images/keyboard5.png","value":"5"})
            listModel.append({"iconsource":"qrc:/images/images/keyboard6.png","value":"6"})
            listModel.append({"iconsource":"qrc:/images/images/keyboardclear.png","value":""})
            listModel.append({"iconsource":"qrc:/images/images/keyboard7.png","value":"7"})
            listModel.append({"iconsource":"qrc:/images/images/keyboard8.png","value":"8"})
            listModel.append({"iconsource":"qrc:/images/images/keyboard9.png","value":"9"})
            listModel.append({"iconsource":"qrc:/images/images/keyboardcancel.png","value":""})
            listModel.append({"iconsource":"qrc:/images/images/keyBoardxing.png","value":"*"})
            listModel.append({"iconsource":"qrc:/images/images/keyboard0.png","value":"0"})
            listModel.append({"iconsource":"qrc:/images/images/keyboarddian.png","value":"."})
            listModel.append({"iconsource":"qrc:/images/images/keyboarddone.png","value":""})
        }
    }
    Grid {
        anchors.top: close.bottom
        anchors.topMargin: 34
        anchors.left: rec2.right
        anchors.leftMargin: 40
        anchors.right: parent.right
        anchors.rightMargin: 17
        columnSpacing: 34
        rowSpacing: 5
        columns: 4
        rows: 4
        Repeater {
            model: listModel
            delegate: Image {
                id: num
                source: iconsource
                MouseArea {
                    anchors.fill: parent
                    onPressed: {
                        num.opacity = 0.5
                    }
                    onReleased: {
                        num.opacity = 1
                    }
                    onClicked: {
                        if (index == 3) {
                            var TempSTring = ""
                            for (var i = 0; i < inputText.length-1;i++) {
                                TempSTring += inputText.charAt(i)
                            }
                            inputText = TempSTring
                        } else if (index == 7) {
                            inputText = ""
                        } else if (index == 11) {
                            currentClickIndex(index)
                        } else if (index == 15) {
                            currentClickIndex(index)
                        } else {
                            inputText += listModel.get(index).value
                        }
                    }
                }
            }
        }
    }
}

