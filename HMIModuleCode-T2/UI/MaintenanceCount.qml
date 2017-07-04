/*******************************************************************
Copyright:http://www.sinux.com.cn
Date:2016/12/26
Author:zhangjiyong&lilongfei
Description: main interface,load the welcome screen and menu interface
The function interface:
    checkNeedPassWd()
    showDialog()
*******************************************************************/
import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import QtQuick.Window 2.2
import QtQuick.Controls 1.1
import QtQuick.Dialogs 1.2
Item {
    id: toolChange
    property int select: -1
//    property bool myfocus: true
    property bool bIsEditLimit1: false
    property bool editing: false
    signal focusChanged()
    width: Screen.width*0.7
    height: Screen.height*0.6
    signal clickDone(var value)
    Component.onCompleted: {
        hmiAdaptor.maintenanceStart(3);
    }
    Component.onDestruction: {
        hmiAdaptor.maintenanceStop(3);
    }

    function initPage()
    {
        editing = true
        listModel.clear()
        listModel.append({mytitle:qsTr("Horn")})
        listModel.append({mytitle:qsTr("Anvil")})
        listModel.append({mytitle:qsTr("Gather")})
        listModel.append({mytitle:qsTr("Guide")})
        listModel.append({mytitle:qsTr("System")})
//        listModel.append({mytitle:qsTr("Actuator")})

        for (var i = 0; i < 5; i++)
        {
            listModel.set(i,{
                "imageSourece"  :hmiAdaptor.maintenanceCountGetImage(i),
                "mynum"         :hmiAdaptor.maintenanceCountGetValue(i,1),
                "mycurrent"     :hmiAdaptor.maintenanceCountGetValue(i,2),
                "mycurrent1"    :hmiAdaptor.maintenanceCountGetValue(i,3),
                "mylimit"       :hmiAdaptor.maintenanceCountGetValue(i,4),
                "mylimit1"      :hmiAdaptor.maintenanceCountGetValue(i,5),

                "createDate"    :hmiAdaptor.maintenanceCountGetValue(i,6),
                "maxLimit"      :hmiAdaptor.maintenanceCountGetValue(i,7),
                "minLimit"      :hmiAdaptor.maintenanceCountGetValue(i,8),
                "maxLimit1"     :hmiAdaptor.maintenanceCountGetValue(i,9),
                "minLimit1"     :hmiAdaptor.maintenanceCountGetValue(i,10),
                "myreset"       :qsTr("Reset"),
                "mystate1"      :hmiAdaptor.maintenanceCountGetValue(i,11),
                "mystate2"      :hmiAdaptor.maintenanceCountGetValue(i,12),
                "mystate3"      :hmiAdaptor.maintenanceCountGetValue(i,13),
                "mystate4"      :hmiAdaptor.maintenanceCountGetValue(i,14)})
        }
        listView.model = null
        listView.model = listModel
        editing = false

    }

    ListModel {
        id: listModel
        Component.onCompleted: {
            initPage()
        }
    }

    Row {
        id: title
        spacing: 12
        anchors.left: listView.left
        anchors.top: parent.top
        anchors.topMargin: 15
        Item {
            width: 330
            height: 10
        }

        Text {
            width: 150
            text: qsTr("Counter")
            color: "white"
            font.family: "arial"
            font.pixelSize: 25
            verticalAlignment: Qt.AlignVCenter
            horizontalAlignment: Qt.AlignHCenter
        }
        Text {
            width: 150
            text: qsTr("Limit")
            color: "white"
            font.family: "arial"
            font.pixelSize: 25
            verticalAlignment: Qt.AlignVCenter
            horizontalAlignment: Qt.AlignHCenter
        }
        Text {
            width: 150
            text: qsTr("Date Started")
            color: "white"
            font.family: "arial"
            font.pixelSize: 25
            verticalAlignment: Qt.AlignVCenter
            horizontalAlignment: Qt.AlignHCenter
        }
        Text {
            width: 150
            text: qsTr("Reset")
            color: "white"
            font.family: "arial"
            font.pixelSize: 25
            verticalAlignment: Qt.AlignVCenter
            horizontalAlignment: Qt.AlignHCenter
        }
        Text {
            width: 150
            text: qsTr("80% Alarm")
            color: "white"
            font.family: "arial"
            font.pixelSize: 25
            verticalAlignment: Qt.AlignVCenter
            horizontalAlignment: Qt.AlignHCenter
        }
        Text {
            width: 150
            text: qsTr("100% Lock")
            color: "white"
            font.family: "arial"
            font.pixelSize: 25
            verticalAlignment: Qt.AlignVCenter
            horizontalAlignment: Qt.AlignHCenter
        }
    }
    Line {
        id: line
        width: listView.width
        height: 2
        lineColor: "white"
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.leftMargin: 20
        anchors.rightMargin: 30
        anchors.top: title.bottom
        anchors.topMargin: 10
    }

    ListView {
        id: listView
        width: line.width
//        height: parent.height * 0.7
        anchors.bottom: parent.bottom
        model: listModel
        delegate: listLine
        interactive: false
        anchors.top: line.bottom
        anchors.topMargin: 5
        anchors.left: parent.left
        anchors.leftMargin: 20
    }

    Component {
        id: listLine
        Item {
            id: lineItem
            property int listIndex: 0
            width: listView.width
            height:  listView.height / 5
            Component.onCompleted: {
                listIndex = index
            }
            Row {
                spacing: 12
                anchors.verticalCenter: parent.verticalCenter
                Text {
                    width: 160
                    height: 79
                    text: mytitle
                    color: "white"
                    font.family: "arial"
                    font.pointSize: 14
                    verticalAlignment: Qt.AlignVCenter
                    horizontalAlignment: Qt.AlignHCenter
                    anchors.verticalCenter: image.verticalCenter
                    anchors.verticalCenterOffset: 22
                }
                Image {
                    id: image
                    width: 160
                    height: 60
                    source:  imageSourece //"file:///c:/ToolChangeImage/group2/wiredemo.jpg"
                    Text {
                        text: mynum
                        anchors.top: parent.bottom
                        font.pointSize: 14
                        font.family: "arial"
                        color: "white"
                        height: 45
                        anchors.horizontalCenter: parent.horizontalCenter
                    }
                }

                Text {
                    width: 150
                    height: 50
                    text: mycurrent
                    color: "white"
                    font.family: "arial"
                    font.pointSize: 14
                    verticalAlignment: Qt.AlignVCenter
                    horizontalAlignment: Qt.AlignHCenter
                    anchors.verticalCenter: resetButton.verticalCenter
                    visible: lineItem.listIndex == 4 ? true : false
                }
                Column {
                    width: 150
                    height: parent.height
                    spacing: 5
                    visible: lineItem.listIndex == 4 ? false : true
                    Text {
                        id: currentCount
                        width: 150
                        height: 50
                        text: mycurrent
                        color: "white"
                        font.family: "arial"
                        font.pointSize: 14
                        verticalAlignment: Qt.AlignVCenter
                        horizontalAlignment: Qt.AlignHCenter
                        Text {
                            width: 5
                            height: 50
                            text: "/"
                            color: "white"
                            font.family: "arial"
                            font.pointSize: 14
                            verticalAlignment: Qt.AlignVCenter
                            horizontalAlignment: Qt.AlignHCenter
                            anchors.right: parent.right
                        }
                    }
                    Text {
                        id: currentCount2
                        width: 150
                        height: 50
                        text: mycurrent1
                        color: "white"
                        font.family: "arial"
                        font.pointSize: 14
                        verticalAlignment: Qt.AlignVCenter
                        horizontalAlignment: Qt.AlignHCenter
                        visible: lineItem.listIndex == 4 ? false : true
                        Text {
                            width: 5
                            height: 50
                            text: "/"
                            color: "white"
                            font.family: "arial"
                            font.pointSize: 14
                            verticalAlignment: Qt.AlignVCenter
                            horizontalAlignment: Qt.AlignHCenter
                            anchors.right: parent.right
                        }
                    }
                }

                Column {
                    id: keyColumn
                    width: 150
                    height: parent.height
                    spacing: 5
                    Connections {
                        target: toolChange
                        onFocusChanged: {
                            input.inputFocus = false
                            input2.inputFocus = false
                        }

                    }

                    MiniKeyNumInput {
                        id: input
                        width: 150
                        height: 50
                        inputWidth: 150
                        inputText: mylimit
                        visible: lineItem.listIndex == 4 ? false : true
//                        inputFocus: toolChange.myfocus
                        onInputFocusChanged: {
                            if (input.inputFocus) {
                                bIsEditLimit1 = true
                                toolChange.select = index
                                backGround.visible = true
                                backGround.opacity = 0.5
                                keyNum.visible = true
                                keyNum.titleText = qsTr("Counter Limit")
                                keyNum.currentValue = input.inputText
                                keyNum.minvalue = minLimit //"0"
                                keyNum.maxvalue = maxLimit //"10000"

                            }
                        }
                    }
                    MiniKeyNumInput {
                        id: input2
                        width: 150
                        height: 50
    //                    inputHeight: 79
                        inputWidth: 150
                        inputText: mylimit1
                        visible: lineItem.listIndex == 4 ? false : true
//                        inputFocus: toolChange.myfocus
                        onInputFocusChanged: {
                            if (input2.inputFocus) {
                                bIsEditLimit1 = false
                                toolChange.select = index
                                backGround.visible = true
                                backGround.opacity = 0.5
                                keyNum.visible = true
                                keyNum.titleText = qsTr("Counter Limit")
                                keyNum.currentValue = input2.inputText
                                keyNum.minvalue = minLimit1 //"0"
                                keyNum.maxvalue = maxLimit1 //"10000"

                            }
                        }
                    }
                }

                Text {
                    width: 150
                    height: 79
                    text: createDate
                    color: "white"
                    font.family: "arial"
                    font.pointSize: 14
                    verticalAlignment: Qt.AlignVCenter
                    horizontalAlignment: Qt.AlignHCenter
                    anchors.verticalCenter: resetButton.verticalCenter
                }
                CButton {
                    id: resetButton
                    width: 150
                    height: 50
                    text: myreset
                    visible: lineItem.listIndex == 4 ? false : true
                    anchors.verticalCenter: keyColumn.verticalCenter
                    anchors.verticalCenterOffset: 15
                    onClicked: {
                        hmiAdaptor.maintenanceCountReset(mytitle)
                        hmiAdaptor.maintenanceCountExecute("_Recall")
                        initPage()
                        //                        currentCount.text = hmiAdaptor.maintenanceCountGetValue(listIndex,3)
                    }
                }
//                Column {
//                    width: 150
//                    height: parent.height
//                    spacing: 5
//                    CButton {
//                        width: 150
//                        height: 50
//                        text: myreset
//                        visible: lineItem.listIndex == 4 ? false : true
//                        onClicked: {
//                            hmiAdaptor.maintenanceCountReset(mytitle)
//                            hmiAdaptor.maintenanceCountExecute("_Recall")
//                            initPage()
//                            //                        currentCount.text = hmiAdaptor.maintenanceCountGetValue(listIndex,3)
//                        }
//                    }
//                    Item {
//                        width: 150
//                        height: 50
////                        text: myreset
//                        visible: lineItem.listIndex == 4 ? false : true
////                        onClicked: {
////                            hmiAdaptor.maintenanceCountReset(mytitle)
////                            hmiAdaptor.maintenanceCountExecute("_Recall")
////                            initPage()
////    //                        currentCount.text = hmiAdaptor.maintenanceCountGetValue(listIndex,3)
////                        }
//                    }
//                }
                Text {
                    width: 150
                    height: 79
                    text: "-"
                    color: "white"
                    font.family: "arial"
                    font.pointSize: 14
                    verticalAlignment: Qt.AlignVCenter
                    horizontalAlignment: Qt.AlignHCenter
                    visible: index == 5 ? true : false
                }
                Column {
                    width: 150
                    height: parent.height
                    spacing: 5
                    Switch2 {
                        id: myswitch
                        width: 150
                        textLeft: qsTr("On")
                        textRight: qsTr("Off")
                        clip: true
                        state: mystate1
                        visible: lineItem.listIndex == 4 ? false : true
                        onStateChanged: {
                            if (!editing)
                                hmiAdaptor.maintenanceCount80PercentAlarm(mytitle, "switch1")
                        }
                    }
                    Switch2 {
                        id: myswitch2
                        width: 150
                        textLeft: qsTr("On")
                        textRight: qsTr("Off")
                        clip: true
                        state: mystate2
                        visible: lineItem.listIndex == 4 ? false : true
                        onStateChanged: {
                            if (!editing)
                                hmiAdaptor.maintenanceCount80PercentAlarm(mytitle, "switch2")
                        }
                    }
                }
                Column {
                    width: 150
                    height: parent.height
                    spacing: 5
                    Switch2 {
                        id: myswitch100
                        width: 150
                        textLeft: qsTr("On")
                        textRight: qsTr("Off")
                        clip: true
                        state: mystate3
                        visible: lineItem.listIndex == 4 ? false : true
                        onStateChanged: {
                            if (!editing)
                                hmiAdaptor.maintenanceCount80PercentAlarm(mytitle, "switch3")
                        }
                    }
                    Switch2 {
                        id: myswitch1002
                        width: 150
                        textLeft: qsTr("On")
                        textRight: qsTr("Off")
                        clip: true
                        state: mystate4
                        visible: lineItem.listIndex == 4 ? false : true
                        onStateChanged: {
                            if (!editing)
                                hmiAdaptor.maintenanceCount80PercentAlarm(mytitle, "switch4")
                        }
                    }
                }
            }
        }
    }
//    Row {
//        id: row1
//        anchors.bottom: parent.bottom
//        anchors.horizontalCenter: parent.horizontalCenter
//        anchors.bottomMargin: 20
//        spacing: 50
//        Text {
//            text: qsTr("Actuator Part Number: ") + hmiAdaptor.getMaintenanceVerson(0)
//            color: "white"
//            font.family: "arial"
//            font.pointSize: 14
//        }
//        Text {
//            text: qsTr("Actuator Software Verson: ") + hmiAdaptor.getMaintenanceVerson(1)
//            color: "white"
//            font.family: "arial"
//            font.pointSize: 14
//        }
//    }
//    Row {
//        id: row2
//        anchors.bottom: row1.top
//        anchors.horizontalCenter: parent.horizontalCenter
//        anchors.bottomMargin: 20
//        spacing: 50
//        Text {
//            text: qsTr("Actuator Serial Number: ")+hmiAdaptor.getMaintenanceVerson(2)
//            color: "white"
//            font.family: "arial"
//            font.pointSize: 14
//        }
//        Text {
//            text: qsTr("Actuator Module: ")+hmiAdaptor.getMaintenanceVerson(3)
//            color: "white"
//            font.family: "arial"
//            font.pointSize: 14
//        }
//    }
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
                var tempString
                clickDone(keyNum.inputText)
                hmiAdaptor.maintenanceCountSetLimit(listModel.get(toolChange.select).mytitle, keyNum.inputText)
                if (bIsEditLimit1) {
                    if (toolChange.select == 0)
                        tempString = hmiAdaptor.dataProcessing("HornCountLimit", keyNum.inputText)
                    else if (toolChange.select == 1)
                        tempString = hmiAdaptor.dataProcessing("AnvilCountLimit", keyNum.inputText)
                    else if (toolChange.select == 2)
                        tempString = hmiAdaptor.dataProcessing("GatherCountLimit", keyNum.inputText)
                    else if (toolChange.select == 3)
                        tempString = hmiAdaptor.dataProcessing("GuideCountLimit", keyNum.inputText)

                    listModel.set(toolChange.select,{"mylimit":tempString})
                }
                else {
                    if (toolChange.select == 0)
                        tempString = hmiAdaptor.dataProcessing("HornEnergyLimit", keyNum.inputText)
                    else if (toolChange.select == 1)
                        tempString = hmiAdaptor.dataProcessing("AnvilEnergyLimit", keyNum.inputText)
                    else if (toolChange.select == 2)
                        tempString = hmiAdaptor.dataProcessing("GatherEnergyLimit", keyNum.inputText)
                    else if (toolChange.select == 3)
                        tempString = hmiAdaptor.dataProcessing("GuideEnergyLimit", keyNum.inputText)

                    listModel.set(toolChange.select,{"mylimit1":tempString})
                }

                toolChange.focusChanged()
//                toolChange.myfocus = false
                backGround.visible = false
                backGround.opacity = 0
                keyNum.visible = false
                keyNum.inputText = ""
                keyNum.tempValue = ""
            } else if (index == 11) {
                backGround.visible = false
//                toolChange.myfocus = false
                toolChange.focusChanged()
                backGround.opacity = 0
                keyNum.visible = false
                keyNum.inputText = ""
                keyNum.tempValue = ""
            }
        }
        onInputTextChanged: {
            if (keyNum.inputText != "") {
                listModel.set(toolChange.select,{"key3":keyNum.inputText})
            }
        }
    }
}
