/*******************************************************************
Copyright:http://www.sinux.com.cn
Date:2016/12/26
Author:zhangjiyong&lilongfei
Description:set menu bar DataCommunication interface
The function interface:
    hmiAdaptor.dataCommunicationGetSwitch()
*******************************************************************/
import QtQuick 2.2
import QtQuick.Controls 1.1
import QtQuick.Controls.Styles 1.1
import QtQuick.Layouts 1.0
import QtQuick.Window 2.2

Item {
    property int selectIndx: -1
    width: parent.width
    height: parent.height

    Component.onCompleted: {
        initPage()
    }

    function initPage()
    {
        networkSwitch.state = hmiAdaptor.dataCommunicationGetSwitch("Network(Ethernet)") ? "right" : "left";
        remoteSwitch.state = hmiAdaptor.dataCommunicationGetSwitch("Remote Data Logging") ? "right" : "left";
        graphSwitch.state = hmiAdaptor.dataCommunicationGetSwitch("Graph Data") ? "right" : "left";
        modularSwitch.state = hmiAdaptor.dataCommunicationGetSwitch("Modular Producation Mode") ? "right" : "left";
        serverPortEdit.inputText = hmiAdaptor.dataCommunicationGetValue("IpPort")[2];
        ipConfig.text = hmiAdaptor.dataCommunicationGetValue("IpPort")[0];
//        var list = new Array()
//        list = hmiAdaptor.dataCommunicationGetValue("shrinkLimit");
//        shrinkLimit = list;

//        testModel.clear()
//        list = hmiAdaptor.dataCommunicationGetValue("shrinkData")

//        if (list.length % 3 == 0)
//        {
//            for (var i = 0 ;i < list.length / 3; i++)
//            {
//                testModel.append({shrinkid:list[i*3],temperature:list[i*3+1],times:list[i*3+2]})
//            }
//        }
    }

    Image {
        anchors.fill: parent
        source: "qrc:/images/images/bg.png"
    }


    Text {
        id: networkText
        anchors.top: parent.top
        anchors.topMargin: 48
        anchors.left: parent.left
        anchors.leftMargin: 24
        verticalAlignment: Qt.AlignVCenter
        font.family: "arial"
        font.pixelSize: 20
        height: 70
        color: "white"
        text: qsTr("Network(Ethernet)")
    }
    Switch2 {
        id: networkSwitch
        anchors.verticalCenter: networkText.verticalCenter
        anchors.left: modularText.right
        anchors.leftMargin: 6
        width: parent.width*0.26
        //            state: "right"
        textLeft: qsTr("off")
        textRight: qsTr("on")
        clip: true
    }
    Text {
        id: remoteText
        anchors.top: networkSwitch.bottom
        anchors.topMargin: 24
        anchors.left: networkText.left
        verticalAlignment: Qt.AlignVCenter
        font.family: "arial"
        font.pixelSize: 20
        color: "white"
        height: 70
        text: qsTr("Remote Data\nLogging")
    }
    Switch2 {
        id: remoteSwitch
        anchors.left: modularText.right
        anchors.leftMargin: 6
        anchors.verticalCenter: remoteText.verticalCenter
        width: parent.width*0.26
        //            state: "left"
        textLeft: qsTr("off")
        textRight: qsTr("on")
        clip: true
    }
    Text {
        id: graphText
        anchors.top: remoteSwitch.bottom
        anchors.topMargin: 24
        anchors.right: remoteText.right
        verticalAlignment: Qt.AlignVCenter
        font.family: "arial"
        font.pixelSize: 20
        color: "white"
        height: 70
        visible: remoteSwitch.on
        text: qsTr("Graph Data")
    }
    Switch2 {
        id: graphSwitch
        anchors.left: modularText.right
        anchors.leftMargin: 6
        anchors.verticalCenter: graphText.verticalCenter
        width: parent.width*0.26
        //            state: "left"
        textLeft: qsTr("off")
        textRight: qsTr("on")
        visible: remoteSwitch.on
        clip: true
    }
    Text {
        id: modularText
        anchors.top: graphSwitch.bottom
        anchors.topMargin: 24
        anchors.left: networkText.left
        verticalAlignment: Qt.AlignVCenter
        font.family: "arial"
        font.pixelSize: 20
        color: "white"
        height: 70
        text: qsTr("Modular Production\nMode")
    }
    Switch2 {
        id: modularSwitch
        anchors.left: modularText.right
        anchors.leftMargin: 6
        anchors.verticalCenter: modularText.verticalCenter
        width: parent.width*0.26
        //            state: "right"
        textLeft: qsTr("off")
        textRight: qsTr("on")
        clip: true
    }

    Row {
        id: rownButton
        anchors.left: parent.left
        anchors.leftMargin: 24
        anchors.right: parent.right
        anchors.rightMargin: 24
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        spacing: 48
        CButton {
            text: qsTr("Defalut Setting")
            textColor: "white"
            clip: true
            width: (rownButton.width-96)/3
            onClicked: {
                hmiAdaptor.dataCommunicationExecute("_Recall")
                initPage()
            }
        }
        CButton {
            iconSource: "qrc:/images/images/cancel.png"
            text: qsTr("Cancel")
            textColor: "white"
            clip: true
            width: (rownButton.width-96)/3
        }
        CButton {
            iconSource: "qrc:/images/images/OK.png"
            text: qsTr("OK")
            textColor: "white"
            clip: true
            width: (rownButton.width-96)/3
            onClicked: {

                var boolList = new Array()
                boolList.push(networkSwitch.state == "right")
                boolList.push(remoteSwitch.state == "right")
                boolList.push(graphSwitch.state == "right")
                boolList.push(modularSwitch.state == "right")
                var strList = new Array();
//                for (var i = 0 ; i < testModel.count; i++)
//                {
//                    strList.push(testModel.get(i).shrinkid)
//                    strList.push(testModel.get(i).temperature)
//                    strList.push(testModel.get(i).times)
//                }
                hmiAdaptor.dataCommunicationSetValue(boolList,strList,ipConfig.text,serverPortEdit.inputText)
                hmiAdaptor.dataCommunicationExecute("_Set")
            }
        }
    }
    Text {
        id: shrinkText
        anchors.right: shrinkButton.left
        anchors.rightMargin: 10
        anchors.top: parent.top
        anchors.topMargin: 48
        font.family: "arial"
        font.pixelSize: 20
        verticalAlignment: Qt.AlignVCenter
        height: 70
        color: "white"
        text: qsTr("Shrink Tube")
    }
    CButton {
        id: shrinkButton
        anchors.right: parent.right
        anchors.rightMargin: 24
        anchors.verticalCenter: shrinkText.verticalCenter
        text: qsTr("Shrink Tube Test")
        width: parent.width*0.3
    }
    Text {
        id: ipsetText
        anchors.top: shrinkButton.bottom
        anchors.topMargin: 24
        anchors.right: ipsetButton.left
        anchors.rightMargin: 10
        font.family: "arial"
        font.pixelSize: 20
        height: 70
        verticalAlignment: Qt.AlignVCenter
        color: "white"
        text: qsTr("Network(Ethernet)")
    }
    CButton {
        id: ipsetButton
        anchors.verticalCenter: ipsetText.verticalCenter
        anchors.right: parent.right
        anchors.rightMargin: 24
        text: qsTr("Client IP Setting")
        width: parent.width*0.3
    }
    Text {
        id: serverPort
        anchors.top: ipsetButton.bottom
        anchors.topMargin: 24
        anchors.right: serverPortEdit.left
        anchors.rightMargin: 10
        height: 70
        verticalAlignment: Qt.AlignVCenter
        font.family: "arial"
        font.pixelSize: 20
        color: "white"
        text: qsTr("Server Port")
    }
    MiniKeyNumInput {
        id: serverPortEdit
        anchors.verticalCenter: serverPort.verticalCenter
        anchors.right: parent.right
        anchors.rightMargin: 24
        width: parent.width*0.3
        height: 50
        inputWidth: parent.width*0.3
        inputText: "0"
        onInputFocusChanged: {
            if (serverPortEdit.inputFocus) {
                backGround.visible = true
                keyNum.visible = true
                keyNum.titleText = serverPort.text
                keyNum.currentValue = serverPortEdit.inputText
                keyNum.minvalue = "0"
                keyNum.maxvalue = "65535"
            }
        }
    }

    CButton {
        id: ipConfig
        anchors.top: serverPortEdit.bottom
        anchors.topMargin: 24
        anchors.right: parent.right
        anchors.rightMargin: 24
        width: parent.width*0.3
        textColor: "white"
        text: qsTr("IP Configuration")
    }

    CButton {
        id: pingButton
        anchors.top: ipConfig.bottom
        anchors.topMargin: 24
        anchors.right: parent.right
        anchors.rightMargin: 24
        text: qsTr("Ping Test")
        width: parent.width*0.3
    }
    Rectangle {
        id: backGround
        anchors.fill: parent
        color: "black"
        opacity: 0.5
        visible: false
        MouseArea {
            anchors.fill: parent
            onClicked: {
            }
        }

    }
    KeyBoardNum {
        id: keyNum
        anchors.centerIn: parent
        width: 962
        height: 526
        visible: false
        titleText: ""
        maxvalue: "4"
        minvalue: "1"
        currentValue: "4"
        onCurrentClickIndex: {
            if (index == 15) {
                if (hmiAdaptor.comepareCurrentValue(keyNum.minvalue,keyNum.maxvalue,keyNum.inputText)) {
                    if (serverPortEdit.inputFocus) {
                        serverPortEdit.inputText = keyNum.inputText
                        serverPortEdit.inputFocus = false
                    } else if (serverPortEdit.inputFocus) {
                        serverPortEdit.inputText = keyNum.inputText
                        serverPortEdit.inputFocus = false
                    }
                    backGround.visible = false
                    keyNum.visible = false
                    keyNum.inputText = ""
                    keyNum.tempValue = ""
                } else {
                    keyNum.timeRun = true
                }
            } else if (index == 11) {
                if (serverPortEdit.inputFocus) {
                    serverPortEdit.inputFocus = false
                } else if (serverPortEdit.inputFocus) {
                    serverPortEdit.inputFocus = false
                }
                backGround.visible = false
                keyNum.visible = false
                keyNum.inputText = ""
                keyNum.tempValue = ""
            }
        }
        onInputTextChanged: {
            if (keyNum.inputText != "") {
                if (serverPortEdit.inputFocus) {
                    serverPortEdit.inputText = keyNum.inputText
                } else if (serverPortEdit.inputFocus) {
                    serverPortEdit.inputText = keyNum.inputText
                }
            }
        }
    }
}
