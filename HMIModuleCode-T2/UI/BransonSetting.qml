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
            listModel.append({"titleHead":"Power Supply","value":"4000W"})
            listModel.append({"titleHead":"Calibrated Amplitude","value":"72μm"})
            listModel.append({"titleHead":"Tune Point","value":"40%"})
            listModel.append({"titleHead":"Frequency Offset","value":"50%"})
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
                headTitle: qsTr(titleHead)
                centervalue: qsTr(value)
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
        height: 79
    }
    CButton {
        id: test2
        anchors.left: test1.right
        anchors.leftMargin: 20
        anchors.top: testSetting.bottom
        anchors.topMargin: 20
        text: qsTr("Run Sonics 100%")
        width: testSetting.width/2-10
        height: 79
    }
    Text {
        id: powerText
        anchors.left: testSetting.left
        anchors.top: test2.bottom
        anchors.topMargin: 80
        verticalAlignment: Qt.AlignVCenter
        height: 40
        font.family: "arial"
        font.pixelSize: 20
        color: "white"
        text: qsTr("power")
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
        height: 60
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
        height: 60
    }
    CButton {
        id: pingButton
        anchors.top: ipsetButton.bottom
        anchors.topMargin: 20
        anchors.right: parent.right
        anchors.rightMargin: 20
        text: qsTr("Ping Test")
        width: parent.width*0.3
        height: 60
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
        height: 60
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
        height: 60
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
        height: 60
    }
}