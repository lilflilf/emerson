import QtQuick 2.7
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.0
import QtQuick.Window 2.2

Item {
    property int selectIndx: -1
    width: parent.width
    height: parent.height
    property var shrinkLimit: "" //   MaxmmTemp MinmmTemp MaxmmTime MinmmTime;

    Component.onCompleted: {
        initPage()
        titleModel.append({title:"Shrink Tube Id"})
        titleModel.append({title:"Temp(℃)"})
        titleModel.append({title:"Time(S)"})
    }

    function initPage()
    {
        networkSwitch.state = hmiAdaptor.dataCommunicationGetSwitch("Network(Ethernet)") ? "right" : "left";
        remoteSwitch.state = hmiAdaptor.dataCommunicationGetSwitch("Remote Data Logging") ? "right" : "left";
        graphSwitch.state = hmiAdaptor.dataCommunicationGetSwitch("Graph Data") ? "right" : "left";
        modularSwitch.state = hmiAdaptor.dataCommunicationGetSwitch("Modular Producation Mode") ? "right" : "left";
        serverPortEdit.inputText = hmiAdaptor.dataCommunicationGetValue("IpPort")[2];
        ipConfig.text = hmiAdaptor.dataCommunicationGetValue("IpPort")[0];
        var list = new Array()
        list = hmiAdaptor.dataCommunicationGetValue("shrinkLimit");
        shrinkLimit = list;

        testModel.clear()
        list = hmiAdaptor.dataCommunicationGetValue("shrinkData")
        {
            if (list.length % 3 == 0)
            {
                for (var i = 0 ;i < list.length / 3; i++)
                {
                    testModel.append({shrinkid:list[i*3],temperature:list[i*3+1],times:list[i*3+2]})
                }
            }
        }
    }

    Image {
        anchors.fill: parent
        source: "qrc:/images/images/bg.png"
    }

    Item {
        id: leftArea
        anchors.top: parent.top
        width: Screen.width*0.3
        height: parent.height
        Text {
            id: networkText
            anchors.top: parent.top
            anchors.topMargin: 24
            anchors.left: parent.left
            anchors.leftMargin: 10
            verticalAlignment: Qt.AlignVCenter
            font.family: "arial"
            font.pixelSize: 20
            color: "white"
            text: qsTr("Network(Ethernet)")
        }
        Switch2 {
            id: networkSwitch
            anchors.verticalCenter: networkText.verticalCenter
            anchors.right: parent.right
            anchors.rightMargin: 10
            width: parent.width*0.5
//            state: "right"
            textLeft: qsTr("off")
            textRight: qsTr("on")
            clip: true
        }
        Text {
            id: serverPort
            anchors.left: networkText.left
            anchors.top: networkText.bottom
            anchors.topMargin: 35
            verticalAlignment: Qt.AlignVCenter
            font.family: "arial"
            font.pixelSize: 20
            color: "white"
            text: qsTr("Server Port")
        }
        MyLineEdit {
            id: serverPortEdit
            anchors.verticalCenter: serverPort.verticalCenter
            anchors.left: networkSwitch.left
            width: parent.width*0.5
            height: 50
            inputWidth: parent.width*0.5
            inputHeight: 48
            horizontalAlignment: Qt.AlignHCenter
            inputText: qsTr("4000")
//            regExp: RegExpValidator{regExp: /^[1-4000]$/}
        }

        CButton {
            id: ipConfig
            anchors.top: serverPort.bottom
            anchors.topMargin: 24
            anchors.left: networkText.left
            anchors.right: networkSwitch.right
            width: parent.width-20
            textColor: "white"
            text: qsTr("IP Configuration")
        }
        Text {
            id: remoteText
            anchors.top: ipConfig.bottom
            anchors.topMargin: 14
            anchors.left: networkText.left
            verticalAlignment: Qt.AlignVCenter
            font.family: "arial"
            font.pixelSize: 20
            color: "white"
            text: qsTr("Remote Data\nLogging")
        }
        Switch2 {
            id: remoteSwitch
            anchors.left: networkSwitch.left
            anchors.verticalCenter: remoteText.verticalCenter
            width: parent.width*0.5
//            state: "left"
            textLeft: qsTr("off")
            textRight: qsTr("on")
            clip: true
        }
        Text {
            id: graphText
            anchors.top: remoteText.bottom
            anchors.topMargin: 34
            anchors.right: remoteText.right
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
            width: parent.width*0.5
//            state: "left"
            textLeft: qsTr("off")
            textRight: qsTr("on")
            visible: remoteSwitch.on
            clip: true
        }
        Text {
            id: modularText
            anchors.top: graphText.bottom
            anchors.topMargin: 24
            anchors.left: networkText.left
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
            width: parent.width*0.5
//            state: "right"
            textLeft: qsTr("off")
            textRight: qsTr("on")
            clip: true
        }
        Column {
            id: columnButton
            anchors.left: networkText.left
            anchors.right: parent.right
            anchors.rightMargin: 10
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 10
            spacing: 10
            CButton {
                text: qsTr("Defalut Setting")
                textColor: "white"
                clip: true
                width: columnButton.width
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
                width: columnButton.width
            }
            CButton {
                iconSource: "qrc:/images/images/OK.png"
                text: qsTr("OK")
                textColor: "white"
                clip: true
                width: columnButton.width
                onClicked: {

                    var boolList = new Array()
                    boolList.push(networkSwitch.state == "right")
                    boolList.push(remoteSwitch.state == "right")
                    boolList.push(graphSwitch.state == "right")
                    boolList.push(modularSwitch.state == "right")
                    var strList = new Array()
                    for (var i = 0 ; i < testModel.count; i++)
                    {
                        strList.push(testModel.get(i).shrinkid)
                        strList.push(testModel.get(i).temperature)
                        strList.push(testModel.get(i).times)
                    }
                    hmiAdaptor.dataCommunicationSetValue(boolList,strList,ipConfig.text,serverPortEdit.inputText)
                    hmiAdaptor.dataCommunicationExecute("_Set")
                }
            }
        }
    }

    ListModel {
        id: listModel
    }
    Item {
        id: rightArea
        anchors.left: leftArea.right
        anchors.top: parent.top
        width: Screen.width*0.7
        height: parent.height
        ListModel {
            id: testModel
        }
        ListModel {
            id: titleModel
        }

        Row {
            id: headTitle
            anchors.top: parent.top
            anchors.topMargin: 24
            anchors.left: parent.left
            anchors.leftMargin: 40
            anchors.right: parent.right
            anchors.rightMargin: 40
            height: 50
            spacing: 40
            clip: true
            Repeater {
                model: titleModel
                delegate:  Text {
                    verticalAlignment: Qt.AlignVCenter
                    width: (headTitle.width-80)/3
                    font.family: "arial"
                    font.pixelSize: 25
                    color: "white"
                    clip: true
                    text: qsTr(title)
                }
            }
        }
        Line {
            id: line1
            anchors.top: headTitle.bottom
            anchors.topMargin: 6
            anchors.left: parent.left
            anchors.leftMargin: 20
            width: parent.width-20
            height: 1
            lineColor: "#ffffff"
        }
        Line {
            id: line2
            anchors.top: line1.bottom
            anchors.left: parent.left
            anchors.leftMargin: 20
            width: parent.width-20
            height: 1
            lineColor: "#0d0f11"
        }
        ExclusiveGroup {
            id: listviewPositionGroup
        }

        ListView {
            id: listView
            anchors.top: line2.bottom
            anchors.left: parent.left
            anchors.leftMargin: 40
            anchors.right: parent.right
            anchors.rightMargin: 40
            anchors.bottom: bottomTip.top
            clip: true
            model: testModel
            delegate: Component {
                id: shrinkDelegate
                Item {
                    width: listView.width
                    height: 50
                    Text {
                        id: shrinkId
                        anchors.left: parent.left
                        anchors.verticalCenter: parent.verticalCenter
                        verticalAlignment: Qt.AlignVCenter
                        width: (listView.width-80)/3
                        font.family: "arial"
                        font.pixelSize: 20
                        elide: Text.ElideRight
                        color: "white"
                        text: qsTr(shrinkid)
                    }
                    Text {
                        id: temp
                        anchors.left: shrinkId.right
                        anchors.leftMargin: 40
                        anchors.verticalCenter: parent.verticalCenter
                        verticalAlignment: Qt.AlignVCenter
                        width: (listView.width-80)/3
                        font.family: "arial"
                        font.pixelSize: 20
                        color: "white"
                        elide: Text.ElideRight
                        text: qsTr(temperature)
                    }
                    Text {
                        id: time
                        anchors.left: temp.right
                        anchors.leftMargin: 40
                        anchors.verticalCenter: parent.verticalCenter
                        verticalAlignment: Qt.AlignVCenter
                        width: (listView.width-80)/3
                        font.family: "arial"
                        font.pixelSize: 20
                        color: "white"
                        elide: Text.ElideRight
                        text: qsTr(times)
                    }
                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            selectIndx = index
                            selectCheck.checked = !selectCheck.checked
                        }
                    }
                    Rectangle {
                        id: backGround
                        anchors.fill: parent
                        color: "black"
                        opacity: 0//opacityValue
                        RadioButton {
                            id: selectCheck
                            exclusiveGroup: listviewPositionGroup
                            visible: false
                            onCheckedChanged: {
                                if (checked)
                                    backGround.opacity = 0.3
                                else
                                    backGround.opacity = 0
                            }
                        }
                    }
                }
            }
        }
        Image {
            id: scrollUp
            anchors.top: line2.bottom
            anchors.topMargin: 2
            anchors.left: listView.right
            width: 17
            height: 10
            visible: listView.contentHeight > listView.height ? true : false
            source: "qrc:/images/images/up.png"
        }
        Image {
            id: scrollDown
            anchors.bottom: bottomTip.top
            anchors.bottomMargin: 2
            anchors.left: listView.right
            width: 17
            height: 10
            visible: listView.contentHeight > listView.height ? true : false
            source: "qrc:/images/images/down.png"
        }
        Rectangle {
            id: scrollbar
            width: 10
            height: listView.height-24
            anchors.top: scrollUp.bottom
            anchors.left: listView.right
            anchors.leftMargin: 4
            color: "#585858"
            radius: 10
            visible: listView.contentHeight > listView.height ? true : false
            Rectangle {
                id: button
                anchors.left: parent.left
                y: (listView.visibleArea.yPosition < 0 ) ? 0 : (listView.contentY+listView.height>listView.contentHeight) ?
                    scrollbar.height - button.height : listView.visibleArea.yPosition * scrollbar.height
                width: 10
                height: listView.visibleArea.heightRatio * scrollbar.height;
                color: "#ccbfbf"
                radius: 10
                // 鼠标区域
                MouseArea {
                    id: mouseArea
                    anchors.fill: button
                    drag.target: button
                    drag.axis: Drag.YAxis
                    drag.minimumY: 0
                    drag.maximumY: scrollbar.height - button.height
                    // 拖动
                    onMouseYChanged: {
                        listView.contentY = button.y / scrollbar.height * listView.contentHeight
                    }
                }
            }
        }
        Rectangle {
            id: bottomTip
            anchors.bottom: bottomTip2.top
            anchors.left: parent.left
            anchors.leftMargin: 20
            width: parent.width - 20
            clip: true
            height: 1
            color: "#ffffff"
        }
        Rectangle {
            id: bottomTip2
            anchors.bottom: addnew.top
            anchors.bottomMargin: 24
            anchors.left: parent.left
            anchors.leftMargin: 20
            width: parent.width - 20
            clip: true
            height: 1
            color: "#0d0f11"
        }
        CButton {
            id: addnew
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 10
            anchors.left: parent.left
            anchors.leftMargin: 20
            width: (bottomTip2.width-72)/3
            spacing: 10
            iconSource: "qrc:/images/images/Add.png"
            text: qsTr("ADD NEW SHRINK")
            pointSize: 20
            clip: true
            textColor: "white"
            onClicked: {
//                backGround.visible = true
//                backGround.opacity = 0.5
//                dialog.bIsEdit = false
//                dialog.visible = true
            }
        }
        CButton {
            id: edit
            anchors.bottom: addnew.bottom
            anchors.left: addnew.right
            anchors.leftMargin: 24
            width: (bottomTip2.width-72)/3
            iconSource: "qrc:/images/images/stting.png"
            text: qsTr("EDIT SHRINK")
            pointSize: 20
            clip: true
            textColor: "white"
            onClicked: {
//                backGround.visible = true
//                backGround.opacity = 0.5
            }
        }
        CButton {
            id: dele
            anchors.bottom: addnew.bottom
            anchors.left: edit.right
            anchors.leftMargin: 24
            width: (bottomTip2.width-72)/3
            text: qsTr("DELETE SHRINK")
            pointSize: 20
            clip: true
            textColor: "white"
            onClicked: {
            }
        }
    }
}
