/*******************************************************************
Copyright:http://www.sinux.com.cn
Date:2016/12/26
Author:zhangjiyong&lilongfei
Description:AdvancedMaintenance set interface
The function interface:
    hmiAdaptor.maintenanceStart()
    hmiAdaptor.advancedMaintenanceExecute()
*******************************************************************/
import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import QtQuick.Window 2.2
import QtQuick.Controls 1.1
import QtQuick.Dialogs 1.2
import Qt.labs.folderlistmodel 2.1

Item {
    id: toolChange
    property bool bIsList: false
    property var listIndex: -1
    width: Screen.width*0.7
    height: Screen.height*0.6

    Component.onCompleted: {
        hmiAdaptor.maintenanceStart(2);
    }
    Component.onDestruction: {
        hmiAdaptor.maintenanceStop(2);
    }

    Connections {
        target: hmiAdaptor
        onSignalButtonStateChanged: {
            if (buttonName == "AnvilArm") {
                if (state)
                    button1.backgroundComponent = buttonBackTrue
                else
                    button1.backgroundComponent = buttonBackFalse
            }
            else if (buttonName == "Gather") {
                if (state)
                    button2.backgroundComponent = buttonBackTrue
                else
                    button2.backgroundComponent = buttonBackFalse
            }
            else if (buttonName == "Safety") {
                if (state)
                    button3.backgroundComponent = buttonBackTrue
                else
                    button3.backgroundComponent = buttonBackFalse
            }
            else if (buttonName == "Cutter") {
                if (state)
                    button4.backgroundComponent = buttonBackTrue
                else
                    button4.backgroundComponent = buttonBackFalse
            }
            else if (buttonName == "Cooling Tooling") {
                if (state)
                    button5.backgroundComponent = buttonBackTrue
                else
                    button5.backgroundComponent = buttonBackFalse
            }
            else if (buttonName == "Cooling Converter") {
                if (state)
                    button6.backgroundComponent = buttonBackTrue
                else
                    button6.backgroundComponent = buttonBackFalse
            }
            else if (buttonName == "Crash") {
                if (state)
                    button7.backgroundComponent = buttonBackTrue
                else
                    button7.backgroundComponent = buttonBackFalse
            }
        }
    }

    Column {
        id: column1
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.leftMargin: 50
        anchors.topMargin: 30
        spacing: 20
        Image {
            width: 280
            height: 280
            source: "qrc:/images/images/maintenance-5.png"
//            source: "file:///c:/ToolChangeImage/group2/wiredemo.jpg"
        }
        Image {
            width: 280
            height: 280
            source: "qrc:/images/images/maintenance-6.png"
//            source: "file:///c:/ToolChangeImage/group2/wiredemo.jpg"
        }
    }


//    ANVILARMCLICK,
//    ANVILCLICK,
//    GATHERCLICK,
//    CUTTERCLICK,
//    CRASHCLICK,
//    SAFETYCLICK,
//    CONVERTERCOOLINGCLICK,
//    TOOLINGCOOLINGCLICK,

    Component {
        id: buttonBackTrue
        Rectangle {
            anchors.fill: parent
            color: "green"
        }
    }
    Component {
        id: buttonBackFalse
        Image {
            anchors.fill: parent
            source: "qrc:/images/images/icon-bg.png"
        }
    }

    Column {
        id: buttonColumn1
        anchors.left:column1.right
        anchors.top: column1.top
        anchors.leftMargin: 60
        spacing: 10
        CButton {
            id: button1
            width: 250
            text: qsTr("1-Anvil Arm")
            onClicked: {
                hmiAdaptor.advancedMaintenanceExecute(0)
            }
        }
        CButton {
            id: button2
            width: 250
            text: qsTr("2-Gather")
            onClicked: {
                hmiAdaptor.advancedMaintenanceExecute(2)
            }
        }
        CButton {
            id: button3
            width: 250
            text: qsTr("3-Safety")
            onClicked: {
                hmiAdaptor.advancedMaintenanceExecute(5)
            }
        }
    }
    Column {
        id: buttonCoumn
        anchors.left:column1.right
        anchors.top: column1.top
        anchors.topMargin: 280
        anchors.leftMargin: 60
        spacing: 10
        CButton {
            id: button4
            width: 250
            text: qsTr("4-Cutter")
            onClicked: {
                hmiAdaptor.advancedMaintenanceExecute(3)
            }
        }
        CButton {
            id: button5
            width: 250
            text: qsTr("5-Cooling Tooling")
            onClicked: {
                hmiAdaptor.advancedMaintenanceExecute(7)
            }
        }
        CButton {
            id: button6
            width: 250
            text: qsTr("6-Cooling Converter")
            onClicked: {
                hmiAdaptor.advancedMaintenanceExecute(6)
            }
        }
        CButton {
            id: button7
            width: 250
            text: qsTr("7-Crash")
            onClicked: {
                hmiAdaptor.advancedMaintenanceExecute(4)
            }
        }

    }

    Rectangle {
        id: tempLine
        width: 1
        color: "white"
        anchors.left: buttonCoumn.right
        anchors.leftMargin: 10
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.topMargin: 15
        anchors.bottomMargin: 15
    }

    ListModel {
        id: listModel
        Component.onCompleted: {
            listModel.append({"titleHead":qsTr("Power Supply"),"value":hmiAdaptor.getAdvancedMaintenanceValue(1,"current"),
                             "maxValue":hmiAdaptor.getAdvancedMaintenanceValue(1,"max"),
                             "minValue":hmiAdaptor.getAdvancedMaintenanceValue(1,"min")})
            listModel.append({"titleHead":qsTr("Calibrated Amplitude"),"value":"72μm"})
            listModel.append({"titleHead":qsTr("Tune Point"),"value":hmiAdaptor.getAdvancedMaintenanceValue(2,"current"),
                                 "maxValue":hmiAdaptor.getAdvancedMaintenanceValue(2,"max"),
                                 "minValue":hmiAdaptor.getAdvancedMaintenanceValue(2,"min")})
            listModel.append({"titleHead":qsTr("Frequency Offset"),"value":hmiAdaptor.getAdvancedMaintenanceValue(3,"current"),
                                 "maxValue":hmiAdaptor.getAdvancedMaintenanceValue(3,"max"),
                                 "minValue":hmiAdaptor.getAdvancedMaintenanceValue(3,"min")})
        }
    }

    Text {
        id: title
        anchors.top: parent.top
        anchors.topMargin: 30
        anchors.left: buttonCoumn.right
        anchors.leftMargin: 20
        font.family: "arial"
        font.pixelSize: 20
        color: "white"
        text: qsTr("Sonics and Power Test")
    }
    Text {
        id: powerText
        anchors.top: title.bottom
        anchors.topMargin: 20
        anchors.left: title.left
        verticalAlignment: Qt.AlignVCenter
        height: 40
        font.family: "arial"
        font.pixelSize: 20
        color: "white"
        text: qsTr("Power")
    }
    Row {
        id: progressBar2
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
        anchors.right: parent.right
        anchors.rightMargin: 20
        maximum: 100
        value: 50
        minimum: 1
    }

    Row {
        id: rowButton3
        anchors.top: progressBar.bottom
        anchors.topMargin: 20
        anchors.right: progressBar.right
//        anchors.rightMargin: 50
        anchors.left: progressBar.left
//        anchors.leftMargin: 50
        spacing: 20
        CButton {
            id: test1
            text: qsTr("Run Sonics")
            width: (rowButton3.width -20)/2
        }
        CButton {
            id: test2
            text: qsTr("Run Sonics 100%")
            width: (rowButton3.width -20)/2
        }
    }

    Row {
        id: rowButton2
        anchors.top: rowButton3.bottom
        anchors.topMargin: 20
        anchors.right: rowButton3.right
        anchors.left: rowButton3.left

        spacing: 20
        Item {
            width: (rowButton2.width-20)/2
            height: Screen.height * 0.08

            Text {
                id: amplitude
                text: qsTr("Amplitude")
                font.family: "arial"
                font.pixelSize: 20
                color: "white"
                anchors.verticalCenter: parent.verticalCenter
            }
            Recsetting {
                id: recsetting1
                anchors.right: parent.right
                width: (rowButton2.width-20)/4
                height: Screen.height * 0.08
                centervalue: hmiAdaptor.getAdvancedMaintenanceValue(0,"current")
                onMouseAreaClick: {
                    bIsList = false
                    backGround.visible = true
                    backGround.opacity = 0.5
                    keyNum.visible = true
                    keyNum.titleText = amplitude.text
                    keyNum.currentValue = recsetting1.centervalue
                    keyNum.minvalue = hmiAdaptor.getAdvancedMaintenanceValue(0,"min")
                    keyNum.maxvalue = hmiAdaptor.getAdvancedMaintenanceValue(0,"max")
                    console.log("Amplitude")
                }

            }
        }

        CButton {
            text: qsTr("Reset")
            width: (rowButton2.width-20)/2
            onClicked: {
                hmiAdaptor.maintenanceReset()
            }
        }
    }
    Text {
        id: tipText
        text: qsTr("Power Supply and Frequency Setting")
        font.family: "arial"
        font.pixelSize: 20
        color: "white"
        anchors.bottom: testSetting.top
        anchors.bottomMargin: 30
        anchors.left: powerText.left
        visible: hmiAdaptor.getCurrentOperatorName() == "BRANSON" ? true : false
    }

    Grid {
        id: testSetting
//        anchors.horizontalCenter: rowButton3.horizontalCenter
        anchors.bottom: buttonCoumn.bottom
        rowSpacing: 10
        columnSpacing: 60
        columns: 2
        rows: 2
        anchors.left: powerText.left
        anchors.right: progressBar2.right
        visible: tipText.visible
        Repeater {
            anchors.right: parent.right
            model: listModel
            delegate: Item {
                width: testSetting.width / 2 - 30
                height: 60
                Text {
                    text: titleHead
                    font.family: "arial"
                    font.pixelSize: 20
                    color: "white"
                    anchors.verticalCenter: parent.verticalCenter
                    visible: index == 1 ? false : true
                }
                Recsetting {
                    width: (rowButton2.width-20)/4
                    height: 60
                    centervalue: value
                    anchors.right: parent.right
                    visible: index == 1 ? false : true
                    onMouseAreaClick: {
                        bIsList = true
                        listIndex = index
                        backGround.visible = true
                        backGround.opacity = 0.5
                        keyNum.titleText = titleHead
                        keyNum.visible = true
                        keyNum.currentValue = value
                        keyNum.minvalue = minValue
                        keyNum.maxvalue = maxValue

                    }
                }
            }
        }
    }

    Rectangle {
        id: backGround
        anchors.fill: parent
        color: "black"
        opacity: 0.7
        visible: false //content.bIsEdit ? true : false
        MouseArea {
            anchors.fill: parent
            onClicked: {
//                if (templateModel.count == 0 && template2.visible && temPlateDialog.visible == false) {
//                    backGround.visible = false
//                    backGround.opacity = 0
//                    template2.visible = false
//                }
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
                    if (bIsList) {
                        listModel.set(listIndex,{"value":keyNum.inputText})
                        if (listIndex == 0)
                            hmiAdaptor.setAdvancedMaintenanceValue(1,keyNum.inputText)
                        else
                            hmiAdaptor.setAdvancedMaintenanceValue(listIndex,keyNum.inputText)
                    }
                    else {
                        recsetting1.centervalue = keyNum.inputText
                        hmiAdaptor.setAdvancedMaintenanceValue(0,keyNum.inputText)
                    }
                    backGround.visible = false
                    backGround.opacity = 0
                    keyNum.visible = false
                    keyNum.inputText = ""
                    keyNum.tempValue = ""
                }
            } else if (index == 11) {
                backGround.visible = false
                backGround.opacity = 0
                keyNum.visible = false
                keyNum.inputText = ""
                keyNum.tempValue = ""
            }
        }
        onInputTextChanged: {
            if (keyNum.inputText != "") {
            }
        }
    }

//    Row {
//        id: rowButton
//        anchors.bottom: parent.bottom
//        anchors.bottomMargin: 20
//        anchors.left: buttonCoumn.right
//        anchors.leftMargin: 20
//        anchors.right: parent.right
//        anchors.rightMargin: 20
//        spacing: 20
//        CButton {
//            iconSource: "qrc:/images/images/cancel.png"
//            text: qsTr("Cancel")
//            width: (rowButton.width-20)/2
//        }
//        CButton {
//            iconSource: "qrc:/images/images/OK.png"
//            text: qsTr("OK")
//            width: (rowButton.width-20)/2
//        }
//    }
}
