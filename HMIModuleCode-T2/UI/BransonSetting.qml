/*******************************************************************
Copyright:http://www.sinux.com.cn
Date:2016/12/26
Author:zhangjiyong&lilongfei
Description:
The function interface:
*******************************************************************/
import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2

Item {
    width: parent.width
    height: parent.height
    Image {
        anchors.fill: parent
        source: "qrc:/images/images/bg.png"
    }
    ListModel {
        id: listModel
        Component.onCompleted: {
            listModel.append({"titleHead":qsTr("Power Supply"),"value":"4000W"})
            listModel.append({"titleHead":qsTr("Calibrated Amplitude"),"value":"72μm"})
            listModel.append({"titleHead":qsTr("Tune Point"),"value":"40%"})
            listModel.append({"titleHead":qsTr("Frequency Offset"),"value":"50%"})
        }
    }

    Text {
        id: title
        anchors.top: parent.top
        anchors.topMargin: 20
        anchors.left: parent.left
        anchors.leftMargin: 20
        font.family: "arial"
        font.pixelSize: 20
        color: "white"
        text: qsTr("Sonics Test")
    }
    Grid {
        id: testSetting
        anchors.top: title.bottom
        anchors.topMargin: 20
        anchors.left: title.left
        width: (parent.width-40)/2
        height: 154*2+20
        spacing: 20
        columns: 2
        rows: 2
        Repeater {
            model: listModel
            delegate: Recsetting {
                width: (testSetting.width-20)/2
                height: (testSetting.height-20)/2
                headTitle: titleHead
                centervalue: value
            }
        }
    }
    CButton {
        id: test1
        anchors.left: testSetting.left
        anchors.top: testSetting.bottom
        anchors.topMargin: 20
        text: qsTr("Run Sonics")
        width: testSetting.width/2-10
    }
    CButton {
        id: test2
        anchors.left: test1.right
        anchors.leftMargin: 20
        anchors.top: testSetting.bottom
        anchors.topMargin: 20
        text: qsTr("Run Sonics 100%")
        width: testSetting.width/2-10
    }
    Text {
        id: powerText
        anchors.left: testSetting.left
        anchors.top: test2.bottom
        anchors.topMargin: 50
        verticalAlignment: Qt.AlignVCenter
        height: 40
        font.family: "arial"
        font.pixelSize: 20
        color: "white"
        text: qsTr("power")
    }
    Row {
        anchors.bottom: progressBar.top
        anchors.bottomMargin: 2
        spacing: (progressBar.width-2*14)/13
        anchors.left: progressBar.left
        Repeater {
            model: 14
            delegate: Item {
                width: 2
                height: 30
                Text {
                    id: num
                    anchors.top: parent.top
                    anchors.horizontalCenter:line.horizontalCenter
                    font.pixelSize: 10
                    font.family: "arial"
                    color: "white"
                    text: index*10
                }
                Rectangle {
                    id: line
                    anchors.top: num.bottom
                    width: 2
                    height: 10
                    color: "blue"
                }
            }
        }
    }

    CProgressBar {
        id: progressBar
        anchors.verticalCenter: powerText.verticalCenter
        anchors.left: powerText.right
        anchors.leftMargin: 10
        maximum: 100
        value: 50
        minimum: 1
    }
    Text {
        id: shrinkText
        anchors.right: shrinkButton.left
        anchors.rightMargin: 10
        anchors.verticalCenter: shrinkButton.verticalCenter
        font.family: "arial"
        font.pixelSize: 20
        color: "white"
        text: qsTr("Shrink Tube")
    }
    CButton {
        id: shrinkButton
        anchors.top: parent.top
        anchors.topMargin: 20
        anchors.right: parent.right
        anchors.rightMargin: 20
        text: qsTr("Shrink Tube Test")
        width: parent.width*0.3
    }
    Text {
        id: ipsetText
        anchors.right: ipsetButton.left
        anchors.rightMargin: 10
        anchors.verticalCenter: ipsetButton.verticalCenter
        font.family: "arial"
        font.pixelSize: 20
        color: "white"
        text: qsTr("Network(Ethernet)")
    }
    CButton {
        id: ipsetButton
        anchors.top: shrinkButton.bottom
        anchors.topMargin: 20
        anchors.right: parent.right
        anchors.rightMargin: 20
        text: qsTr("Client IP Setting")
        width: parent.width*0.3
    }
    CButton {
        id: pingButton
        anchors.top: ipsetButton.bottom
        anchors.topMargin: 20
        anchors.right: parent.right
        anchors.rightMargin: 20
        text: qsTr("Ping Test")
        width: parent.width*0.3
    }
    CButton {
        id: reset
        anchors.top: pingButton.bottom
        anchors.topMargin: 20
        anchors.right: parent.right
        anchors.rightMargin: 20
        text: qsTr("Reset")
        width: parent.width*0.3
        height: 60
    }
    CButton {
        id: defalutButton
        anchors.top: reset.bottom
        anchors.topMargin: 20
        anchors.right: parent.right
        anchors.rightMargin: 20
        text: qsTr("Default Setting")
        width: parent.width*0.3
    }
    CButton {
        id: cancelButton
        anchors.top: defalutButton.bottom
        anchors.topMargin: 20
        anchors.right: parent.right
        anchors.rightMargin: 20
        iconSource: "qrc:/images/images/cancel.png"
        text: qsTr("Cancel")
        width: parent.width*0.3
    }
    CButton {
        id: okButton
        anchors.top: cancelButton.bottom
        anchors.topMargin: 20
        anchors.right: parent.right
        anchors.rightMargin: 20
        iconSource: "qrc:/images/images/OK.png"
        text: qsTr("OK")
        width: parent.width*0.3
    }
}
