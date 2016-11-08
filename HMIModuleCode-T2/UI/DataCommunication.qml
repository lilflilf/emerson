import QtQuick 2.7
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.0
import QtQuick.Window 2.2

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
            listModel.append({"titleText":"Shrink Tube ID","textvalue":"1"})
            listModel.append({"titleText":"Temp(℃)","textvalue":"260"})
            listModel.append({"titleText":"Time(S)","textvalue":"0.90"})
            listModel.append({"titleText":"Shrink Tube ID","textvalue":"2"})
            listModel.append({"titleText":"Temp(℃)","textvalue":"260"})
            listModel.append({"titleText":"Time(S)","textvalue":"0.90"})
            listModel.append({"titleText":"Shrink Tube ID","textvalue":"3"})
            listModel.append({"titleText":"Temp(℃)","textvalue":"260"})
            listModel.append({"titleText":"Time(S)","textvalue":"0.90"})
            listModel.append({"titleText":"Shrink Tube ID","textvalue":"4"})
            listModel.append({"titleText":"Temp(℃)","textvalue":"260"})
            listModel.append({"titleText":"Time(S)","textvalue":"0.90"})
        }
    }
    Text {
        id: shrinkText
        anchors.top: parent.top
        anchors.topMargin: 24
        anchors.left: parent.left
        anchors.leftMargin: 20
        height: 50
        verticalAlignment: Qt.AlignVCenter
        font.family: "arial"
        font.pixelSize: 20
        color: "white"
        text: qsTr("Shrink Tube")
    }
    Switch2 {
        id: shrinkSwitch
        anchors.left: shrinkText.right
        anchors.leftMargin: 24
        anchors.verticalCenter: shrinkText.verticalCenter
        width: 250
        height: 50
        state: "right"
        textLeft: qsTr("off")
        textRight: qsTr("on")
        clip: true
        onOnChanged: {
            if(shrinkSwitch.on)
                shrinkGrid.visible = true
            else
                shrinkGrid.visible = false
        }
    }
    Text {
        id: networkText
        anchors.top: parent.top
        anchors.topMargin: 24
        anchors.left: shrinkGrid.right
        anchors.leftMargin: 50
        verticalAlignment: Qt.AlignVCenter
        height: 50
        font.family: "arial"
        font.pixelSize: 20
        color: "white"
        text: qsTr("Network(Ethernet)")
    }
    Switch2 {
        id: networkSwitch
        anchors.top: parent.top
        anchors.topMargin: 24
        anchors.right: parent.right
        anchors.rightMargin: 24
        width: 250
        height: 50
        state: "right"
        textLeft: qsTr("off")
        textRight: qsTr("on")
        clip: true
    }
    Text {
        id: serverPort
        anchors.left: networkText.left
        anchors.top: networkText.bottom
        anchors.topMargin: 10
        height: 50
        verticalAlignment: Qt.AlignVCenter
        font.family: "arial"
        font.pixelSize: 20
        color: "white"
        text: qsTr("Server Port")
    }
    MyLineEdit {
        anchors.verticalCenter: serverPort.verticalCenter
        anchors.left: networkSwitch.left
        width: 250
        height: 50
        inputWidth: 250
        inputHeight: 48
        horizontalAlignment: Qt.AlignHCenter
        inputText: qsTr("4000")
        regExp: RegExpValidator{regExp: /^[1-4000]$/}
    }
    CButton {
        id: ipConfig
        anchors.top: serverPort.bottom
        anchors.topMargin: 10
        anchors.left: networkText.left
        anchors.right: networkSwitch.right
        height: 50
        textColor: "white"
        text: qsTr("IP Configuration")
    }
    Text {
        id: remoteText
        anchors.top: ipConfig.bottom
        anchors.topMargin: 10
        anchors.left: networkText.left
        height: 50
        verticalAlignment: Qt.AlignVCenter
        font.family: "arial"
        font.pixelSize: 20
        color: "white"
        text: qsTr("Remote Data Logging")
    }
    Switch2 {
        id: remoteSwitch
        anchors.left: networkSwitch.left
        anchors.verticalCenter: remoteText.verticalCenter
        width: 250
        height: 50
        state: "left"
        textLeft: qsTr("off")
        textRight: qsTr("on")
        clip: true
    }
    Text {
        id: graphText
        anchors.top: remoteText.bottom
        anchors.topMargin: 10
        anchors.right: remoteText.right
        height: 50
        verticalAlignment: Qt.AlignVCenter
        font.family: "arial"
        font.pixelSize: 20
        color: "white"
        visible: remoteSwitch.on
        text: qsTr("Graph Data")
    }
    Switch2 {
        id: graphSwitch
        anchors.left: networkSwitch.left
        anchors.verticalCenter: graphText.verticalCenter
        width: 250
        height: 50
        state: "left"
        textLeft: qsTr("off")
        textRight: qsTr("on")
        visible: remoteSwitch.on
        clip: true
    }
    Text {
        id: modularText
        anchors.top: graphText.bottom
        anchors.topMargin: 10
        anchors.left: networkText.left
        height: 50
        verticalAlignment: Qt.AlignVCenter
        font.family: "arial"
        font.pixelSize: 20
        color: "white"
        text: qsTr("Modular Producation\nMode")
    }
    Switch2 {
        id: modularSwitch
        anchors.left: networkSwitch.left
        anchors.verticalCenter: modularText.verticalCenter
        width: 250
        height: 50
        state: "right"
        textLeft: qsTr("off")
        textRight: qsTr("on")
        clip: true
    }
    Column {
        id: columnButton
        anchors.left: networkText.left
        anchors.right: parent.right
        anchors.rightMargin: 20
        anchors.top: modularText.bottom
        anchors.topMargin: 10
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 24
        spacing: 10
        CButton {
            text: qsTr("Defalut Setting")
            textColor: "white"
            clip: true
            height: (columnButton.height-20)/3
            width: columnButton.width
        }
        CButton {
            iconSource: "qrc:/images/images/cancel.png"
            text: qsTr("Cancel")
            textColor: "white"
            clip: true
            height: (columnButton.height-20)/3
            width: columnButton.width
        }
        CButton {
            iconSource: "qrc:/images/images/OK.png"
            text: qsTr("OK")
            textColor: "white"
            clip: true
            height: (columnButton.height-20)/3
            width: columnButton.width
        }
    }

    Grid {
        id: shrinkGrid
        anchors.top: shrinkText.bottom
        anchors.topMargin: 20
        anchors.left: shrinkText.left
        width: (parent.width-48)*0.6
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 24
        columns: 3
        rows: 4
        spacing: 20
        Repeater {
            model: listModel
            delegate: Recsetting {
                width: (shrinkGrid.width-40)/3
                height: (shrinkGrid.height-60)/4
                centervalue: qsTr(textvalue)
                headTitle: qsTr(titleText)
            }
        }
    }
}
