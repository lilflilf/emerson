/*******************************************************************
Copyright:http://www.sinux.com.cn
Date:2016/12/26
Author:zhangjiyong&lilongfei
Description: maintenance calibration interface
The function interface:
    hmiAdaptor.maintenanceStart()
    hmiAdaptor.calibrationMaintenanceExecute()
*******************************************************************/
import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import QtQuick.Window 2.2
import QtQuick.Controls 1.1
import QtQuick.Dialogs 1.2
Item {
    id: calibration
    width: Screen.width*0.7
    height: Screen.height*0.6
    property var currentIndex: 1

    Component.onCompleted: {
        hmiAdaptor.maintenanceStart(0);
    }
    Component.onDestruction: {
        hmiAdaptor.maintenanceStop(0);
    }

    Connections {
        target: hmiAdaptor
        onWidthCalibrationFinish: {
            if (_Result && calibration.currentIndex == 1)
            {
                hmiAdaptor.calibrationMaintenanceExecute(1)
            }

        }
        onHeightCalibrationFinish: {
            if (_Result && calibration.currentIndex == 1)
            {
                calibration.currentIndex++
                button1.enabled = true
                animated.visible = false
            }
        }
    }

    Image {
        anchors.fill: parent
        source: "qrc:/images/images/bg.png"
    }
    Rectangle {
        id: back
        anchors.fill: parent
        color: "black"
        opacity: 0.5
    }
    Rectangle {
        Image {
            anchors.fill: parent
            source: "qrc:/images/images/bg.png"
        }
        width: parent.width * 0.5
        height: parent.height * 0.8
        anchors.centerIn: parent
        Text {
            id: title
            text: qsTr("Calibration-Width and Height")
            color: "white"
            font.family: "arial"
            font.pointSize: 20
            anchors.left: parent.left
            anchors.leftMargin: 15
            anchors.top: parent.top
            anchors.topMargin: 15
        }
        Text {
            id: content
            text: qsTr("This process calibrates and adjusts the Width and Height control system.Please press and hold the start button on this sereen or the start switch on the actuator.")
            color: "white"
            font.family: "arial"
            font.pointSize: 20
            anchors.left: parent.left
            anchors.leftMargin: 15
            anchors.right: parent.right
            anchors.rightMargin: 15
            anchors.top: title.bottom
            anchors.topMargin: 15
            wrapMode: Text.WordWrap
        }

        Image {
            id: image
            source: "qrc:/images/images/maintenance-1.png"
            width: parent.width * 0.4
            height: parent.height * 0.5
            anchors.top: content.bottom
            anchors.topMargin: 30
            anchors.left: parent.left
            anchors.leftMargin: 20
        }
        AnimatedImage {
            id: animated
            source: "qrc:/images/images/loading.gif";
            anchors.bottom: column.top
            anchors.bottomMargin: 20
            anchors.horizontalCenter: column.horizontalCenter
            visible: false
        }

        CButton {
            id: button3
            width: 200
            text: qsTr("Sonics")
            anchors.left: column.left
            anchors.bottom: column.top
            anchors.bottomMargin: 20
            visible: line1.visible
            onPressed: {
                if (calibration.currentIndex == 4)
                    hmiAdaptor.calibrationMaintenanceExecute(2)
            }
            onReleased: {
                if (calibration.currentIndex == 4) {
                    hmiAdaptor.calibrationMaintenanceExecute(3)
                }
            }
        }

        Column {
            id: column
            spacing: 20
            anchors.verticalCenter: image.verticalCenter
            anchors.left: image.right
            anchors.leftMargin: 100
            CButton {
                id: button1
                width: 200
                text: qsTr("Start")
                onClicked: {
                    if (calibration.currentIndex == 1) {
                        button1.enabled = false
                        animated.visible = true
                        hmiAdaptor.calibrationMaintenanceExecute(0)
                    }
                    else if (calibration.currentIndex == 2)
                        calibration.currentIndex++
                }
                onPressed: {
                    if (calibration.currentIndex == 3)
                        hmiAdaptor.calibrationMaintenanceExecute(2)
                }
                onReleased: {
                    if (calibration.currentIndex == 3) {
                        hmiAdaptor.calibrationMaintenanceExecute(3)
                        calibration.currentIndex++
                    }

                }

            }
            MiniKeyNumInput{
                id: line1
                height: button2.height
                width: 200
                inputWidth: 200
                visible: false
                inputText: qsTr("enter value here")
                onInputFocusChanged: {
                    if (line1.inputFocus) {
                        backGround.visible = true
                        keyNum.visible = true
                        if (line1.inputText == qsTr("enter value here")) {
                            keyNum.currentValue = hmiAdaptor.getDefaultAmplitudeToString(0, 0)
                            keyNum.minvalue = hmiAdaptor.getDefaultAmplitudeToString(0, 1)
                            keyNum.maxvalue = hmiAdaptor.getDefaultAmplitudeToString(0, 2)
                        } else {
                            keyNum.currentValue = line1.inputText
                            keyNum.minvalue = hmiAdaptor.getDefaultAmplitudeToString(line1.inputText, 1)
                            keyNum.maxvalue = hmiAdaptor.getDefaultAmplitudeToString(line1.inputText, 2)
                        }
                    }
                }
            }
            CButton {
                id: button2
                width: 200
                text: qsTr("Cancel")
                onClicked: {
                    if (button2.text == qsTr("Back"))
                        calibration.currentIndex--
                    else if (button2.text == qsTr("Save")) {
                        if (line1.inputText != qsTr("enter value here"))
                            hmiAdaptor.hornCalibrationComplete(line1.inputText)
                        mainRoot.checkNeedPassWd(0)
                    }
                    else if (button2.text == qsTr("Cancel"))
                        calibration.currentIndex = 1
                }
            }
            Connections {
                target: calibration
                onCurrentIndexChanged: {
                    if (calibration.currentIndex == 1)
                    {
                        button1.text = qsTr("Start")
                        button2.text = qsTr("Cancel")
                    }
                    else if (calibration.currentIndex == 2)
                    {
                        button1.text = qsTr("Next")
                        button2.text = qsTr("Back")
                    }
                    else if (calibration.currentIndex == 3)
                    {
                        title.text = qsTr("Calibration - Amplitude")
                        content.text = qsTr("This process calibrates the Amplitude. Please set an Amplitude measuring instrument and press and hold the start button on this screen to run Ultrasonic. Then, please enter the Amplitude value.")
                        button1.text = qsTr("Start")
                        button2.text = qsTr("Cancel")
                        image.source = "qrc:/images/images/maintenance-2.png"

                    }
                    else if (calibration.currentIndex == 4)
                    {
                        button1.visible = false
                        line1.visible = true
                        button2.text = qsTr("Save")
                    }
                }
            }
        }
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
                    if (line1.inputFocus) {
                        line1.inputText = keyNum.inputText
                        line1.inputFocus = false
                    }
                    keyNum.visible = false
                    keyNum.inputText = ""
                    keyNum.tempValue = ""
                    backGround.visible = false
                } else {
                    keyNum.timeRun = true
                }
            } else if (index == 11) {
                if (line1.inputFocus) {
                    line1.inputFocus = false
                }
                keyNum.visible = false
                keyNum.inputText = ""
                keyNum.tempValue = ""
                backGround.visible = false
            }
        }
        onInputTextChanged: {
            if (keyNum.inputText != "") {
                if (line1.inputFocus) {
                    line1.inputText = keyNum.inputText
                }
            }
        }
    }

}
