/*******************************************************************
Copyright:http://www.sinux.com.cn
Date:2016/12/26
Author:zhangjiyong&lilongfei
Description: keyBoardnum component,By setting the exposed properties,
change the maximum minimunm value,the data Model is listModel
The function interface:
    currentClickIndex()
    hmiAdaptor.getStringUnit()
*******************************************************************/
import QtQuick 2.2
import QtQuick.Layouts 1.0
import QtQuick.Window 2.2
import QtQuick.Controls 1.1

Item {
    id: keyBoardnum
    property alias titleText: title.text
    property alias currentValue: currenvalue.text
    property string minvalue: "0"
    property string inputText: ""
    property string maxvalue: "0"
    property string tempValue: ""
    property alias timeRun: timer.running
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
        text: ""
        visible: keyBoardnum.visible

    }
    Text {
        id: waring
        anchors.top: title.top
        anchors.left: title.right
        anchors.leftMargin: 20
        anchors.right: parent.right
        horizontalAlignment: Qt.AlignHCenter
        font.family: "arial"
        font.pixelSize: 27
        color: "red"
        visible: timer.running
        text: qsTr("Please type again. \nThe value is out of the range.")
    }
    Timer {
        id: timer
        interval: 3000
        running: false
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
            text: inputText
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
        id: grid
        anchors.top: parent.top
        anchors.topMargin: 94
        anchors.left: rec2.right
        anchors.leftMargin: 40
        anchors.right: parent.right
        anchors.rightMargin: 17
        columnSpacing: 34
        rowSpacing: 5
        columns: 4
        rows: 4
        visible: keyBoardnum.visible
        onVisibleChanged: {
            if (grid.visible)
                forceActiveFocus()
        }

        Keys.enabled: true
        Keys.onPressed: {
            console.log("ffffffffffffffffffffffffffffffff",event.key)

            if (event.key == Qt.Key_Backspace) {
                var TempSTring = ""
                for (var i = 0; i < tempValue.length-1;i++) {
                    TempSTring += tempValue.charAt(i)
                }
                tempValue = TempSTring
                inputText = TempSTring + hmiAdaptor.getStringUnit(keyBoardnum.minvalue)
            }
            else if (event.key >= Qt.Key_0 && event.key <= Qt.Key_9)
            {
                tempValue += event.key - 48
                if (hmiAdaptor.keyNumStringMatch(keyBoardnum.minvalue,keyBoardnum.maxvalue,keyBoardnum.tempValue)) {
                    inputText = tempValue + hmiAdaptor.getStringUnit(keyBoardnum.minvalue)
                } else {
                    timer.running = true
                    var Temp = ""
                    for (var j = 0; j < tempValue.length-1;j++) {
                        Temp += tempValue.charAt(j)
                    }
                    tempValue = Temp
                }
            }
            else if (event.key == Qt.Key_Return)
            {
                currentClickIndex(15)
            }
            else if (event.key == Qt.Key_Escape)
            {
                inputText = keyBoardnum.currentValue
                keyBoardnum.visible = false
                tempValue = ""
                currentClickIndex(11)
            }
        }

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
                            for (var i = 0; i < tempValue.length-1;i++) {
                                TempSTring += tempValue.charAt(i)
                            }
                            tempValue = TempSTring
                            inputText = TempSTring + hmiAdaptor.getStringUnit(keyBoardnum.minvalue)
                        } else if (index == 7) {
                            inputText = ""
                            tempValue = ""
                        } else if (index == 11) {
                            inputText = keyBoardnum.currentValue
                            keyBoardnum.visible = false
                            tempValue = ""
                            currentClickIndex(11)
                        } else if (index == 15) {
                            currentClickIndex(index)
                        } else {
                            tempValue += listModel.get(index).value
                            if (hmiAdaptor.keyNumStringMatch(keyBoardnum.minvalue,keyBoardnum.maxvalue,keyBoardnum.tempValue)) {
                                inputText = tempValue + hmiAdaptor.getStringUnit(keyBoardnum.minvalue)
                            } else {
                                timer.running = true
                                var Temp = ""
                                for (var j = 0; j < tempValue.length-1;j++) {
                                    Temp += tempValue.charAt(j)
                                }
                                tempValue = Temp
                            }
                        }
                    }
                }
            }
        }
    }
}

