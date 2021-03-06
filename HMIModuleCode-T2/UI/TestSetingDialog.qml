import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2

Item {
    width: parent.width
    height: parent.height
    property alias inputNum: defalut.text
    signal signalAdvanceSettingStart(var checkIndex)
    signal signalTestStart(var index) // 0-- off 1--standard 2--auto 3--sigma
    function setData()
    {
        if (spliceModel.getTeachModeValue("TestModel","") == "0") {
            splices.bIsCheck = false
            unButton.bIsCheck = true
        }
        else if (spliceModel.getTeachModeValue("TestModel","") == "1")
        {
            unButton.bIsCheck = false
            splices.bIsCheck = true
            defalut.text = spliceModel.getTeachModeValue("TestCount","")
        }
        if (spliceModel.getTeachModeValue("TeachMode","") == "3") {
            diagram.state = "left"
        }
        else {
            diagram.state = "right"
            standard.bIsCheck = false
            auto.bIsCheck = false
            sigma.bIsCheck = false
            if (spliceModel.getTeachModeValue("TeachMode","") == "0")
                standard.bIsCheck = true
            else if (spliceModel.getTeachModeValue("TeachMode","") == "1")
                auto.bIsCheck = true
            else if (spliceModel.getTeachModeValue("TeachMode","") == "2")
                sigma.bIsCheck = true

        }
    }

    signal signalInputNum(string text)

    Image {
        anchors.fill: parent
        source: "qrc:/images/images/dialogbg.png"
        Text {
            id: testTitle
            anchors.top: parent.top
            anchors.topMargin: 14
            anchors.left: parent.left
            anchors.leftMargin: 14
            text: qsTr("Test Parameters")
            color: "white"
            font.pixelSize: 24
            font.family: "arial"
            clip: true
        }
        Text {
            id: samplesize
            anchors.top: testTitle.bottom
            anchors.topMargin: 46
            anchors.left: parent.left
            anchors.leftMargin: 14
            text: qsTr("Sample Size")
            color: "white"
            font.pixelSize: 20
            font.family: "arial"
            clip: true
        }
        ExclusiveGroup {
            id: mos
        }
        MyRadioButton {
            id: unButton
            anchors.left: samplesize.right
            anchors.leftMargin: 24
            anchors.top: testTitle.bottom
            anchors.topMargin: 32
            height: 57
            width: 217
            clip: true
            buttontext: qsTr("Unconstrained")
            exclusiveGroup: mos
            //            bIsCheck: true
        }
        MyRadioButton {
            id: splices
            anchors.left: samplesize.right
            anchors.leftMargin: 24
            anchors.top: unButton.bottom
            anchors.topMargin: 7
            height: 57
            width: 217
            clip: true
            exclusiveGroup: mos
        }
        Image {
            id: lineEdit
            anchors.left: samplesize.right
            anchors.leftMargin: 78
            anchors.top: unButton.bottom
            anchors.topMargin: 12
            height: 45
            width: 140
            source: "qrc:/images/images/advancesetting-bg1.png"
            Rectangle {
                id: backGround
                width: parent.width
                height: parent.height-2
                border.color: "#0079c1"
                border.width: 2
                color: Qt.rgba(0,0,0,0)
            }
            Text {
                id: defalut
                anchors.fill: parent
                font.pixelSize: 24
                font.family: "arial"
                horizontalAlignment: Qt.AlignHCenter
                verticalAlignment: Qt.AlignVCenter
                color: "white"
                text: qsTr("#of Splices")
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    signalInputNum(defalut.text)
                }
                onPressed: {
                    splices.bIsCheck = true
                }
            }
        }
        Text {
            id: teachMode
            anchors.left: parent.left
            anchors.leftMargin: 14
            anchors.verticalCenter: diagram.verticalCenter
            color: "white"
            font.pixelSize: 20
            font.family: "arial"
            clip: true
            text: qsTr("Teach Mode")
        }
        Switch2 {
            id: diagram
            anchors.top: splices.bottom
            anchors.topMargin: 7
            anchors.left: teachMode.right
            anchors.leftMargin: 24
            anchors.right: parent.right
            anchors.rightMargin: 10
            textLeft: qsTr("OFF")
            textRight: qsTr("ON")
            state: "left"
        }
        ExclusiveGroup {
            id: mos2
        }
        MyRadioButton {
            id: standard
            anchors.left: teachMode.right
            anchors.leftMargin: 24
            anchors.top: diagram.bottom
            anchors.topMargin: 7
            height: 57
            width: 217
            visible: diagram.on
            clip: true
            buttontext: qsTr("Standard")
            exclusiveGroup: mos2
            bIsCheck: true
        }
        MyRadioButton {
            id: auto
            anchors.left: teachMode.right
            anchors.leftMargin: 24
            anchors.top: standard.bottom
            anchors.topMargin: 7
            height: 57
            width: 217
            clip: true
            visible: diagram.on
            buttontext: qsTr("Auto")
            exclusiveGroup: mos2
        }
        MyRadioButton {
            id: sigma
            anchors.left: teachMode.right
            anchors.leftMargin: 24
            anchors.top: auto.bottom
            anchors.topMargin: 7
            height: 57
            width: 217
            clip: true
            visible: diagram.on
            buttontext: qsTr("Sigma")
            exclusiveGroup: mos2
        }
        CButton {
            id: advanceSet
            anchors.top: sigma.bottom
            anchors.topMargin: 7
            anchors.left: parent.left
            anchors.leftMargin: 14
            width: 210
            height: 60
            text: qsTr("Advanced Setting")
            textColor: "white"
            onClicked: {
                if (diagram.state == "right") {
                    headBar.selectsubIndex = 24
                    if (standard.bIsCheck)
                        signalAdvanceSettingStart(0)
                    else if (auto.bIsCheck)
                        signalAdvanceSettingStart(1)
                    else if (sigma.bIsCheck)
                        signalAdvanceSettingStart(1)
                }
                else
                    signalAdvanceSettingStart(3)
            }
        }
        CButton {
            id: start
            anchors.top: sigma.bottom
            anchors.topMargin: 7
            anchors.left: advanceSet.right
            anchors.leftMargin: 15
            width: 180
            height: 60
            text: qsTr("Start")
            textColor: "white"
            onClicked: {
                hmiAdaptor.setWorkFlow(3, 0,"")

                hmiAdaptor.setWorkFlow(0,spliceModel.getStructValue("SpliceId",""),"Test")

                if (unButton.bIsCheck) {
                    spliceModel.setTeachModeValue("TestModel","false","","")
                    hmiAdaptor.setWorkValue("WorkCount",-1)
                }
                else if (splices.bIsCheck) {
                    spliceModel.setTeachModeValue("TestModel","true","","")
                    spliceModel.setTeachModeValue("TestCount",defalut.text,"","")
                    hmiAdaptor.setWorkValue("WorkCount",defalut.text)
                }
                if(diagram.state == "left") {
                    spliceModel.setTeachModeValue("TeachMode","0","","")
                    signalTestStart(0)
                    headBar.selectsubIndex = 25
                }
                else if (diagram.state == "right") {
                    if (standard.bIsCheck)
                        spliceModel.setTeachModeValue("TeachMode","1","","")
                    else if (auto.bIsCheck)
                        spliceModel.setTeachModeValue("TeachMode","2","","")
                    else if (sigma.bIsCheck)
                        spliceModel.setTeachModeValue("TeachMode","3","","")

                    if (standard.bIsCheck)
                        signalTestStart(1)
                    else if (auto.bIsCheck)
                        signalTestStart(2)
                    else if (sigma.bIsCheck)
                        signalTestStart(3)
                }
            }
        }
    }
}

