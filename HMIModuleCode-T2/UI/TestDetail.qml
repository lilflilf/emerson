import QtQuick 2.7
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.0
import QtQuick.Window 2.2

Item {
    id: testDetail
    signal signalSaveSplice()
    width: Screen.width
    height: Screen.height * 0.8
    property var teachCount: 0
    property int quantity: 0
    property bool bIsLimite: false
    Component.onCompleted: {
        hmiAdaptor.operateProcessExec("Start")
    }

    Connections {
        target: hmiAdaptor
        onSignalWeldCycleCompleted: {
            teachCount++
            if (spliceModel.getStructValue("TestModel","") == 1)
            {
                if (teachCount >= spliceModel.getStructValue("TestCount","")) {
                    cdialog2.visible = true
                    hmiAdaptor.operateProcessExec("Stop")
                    return
                }
            }
            progressBar.value = teachCount
            if (spliceModel.getStructValue("TeachMode","") == 0)
            {
                cdialog.visible = true
                return
            }
            if (spliceModel.getStructValue("TeachMode","") != 3)
            {
                hmiAdaptor.teachModeProcess()
            }
            setData()
            hmiAdaptor.operateProcessExec("Execute")

        }
    }

    function setData()
    {
        qualityWindow.timeModel = alarmModel.getPointList("Time",spliceModel.getStructValue("SpliceName",""),spliceModel.getHashCode())
        qualityWindow.powerModel = alarmModel.getPointList("Power",spliceModel.getStructValue("SpliceName",""),spliceModel.getHashCode())
        qualityWindow.preModel = alarmModel.getPointList("Pre-Height",spliceModel.getStructValue("SpliceName",""),spliceModel.getHashCode())
        qualityWindow.postModel = alarmModel.getPointList("Post-Height",spliceModel.getStructValue("SpliceName",""),spliceModel.getHashCode())

//        qualityWindow.qualityModel.clear()
//        if (qualityWindow.timeModel.length > 0) {
//            qualityWindow.qualityModel.append({"redMax":spliceModel.getRawData("Time+"),"redMin":spliceModel.getRawData("Time-"),"yellowMax":4,"yellowMin":1,"current":qualityWindow.timeModel[qualityWindow.timeModel.length - 1],"currentText":"23"})
//            qualityWindow.qualityModel.append({"redMax":spliceModel.getRawData("Power+"),"redMin":spliceModel.getRawData("Power-"),"yellowMax":4,"yellowMin":1,"current":qualityWindow.powerModel[qualityWindow.powerModel.length - 1],"currentText":"123"})
//            qualityWindow.qualityModel.append({"redMax":spliceModel.getRawData("Pre-Height+"),"redMin":spliceModel.getRawData("Pre-Height-"),"yellowMax":4,"yellowMin":1,"current":qualityWindow.preModel[qualityWindow.preModel.length - 1],"currentText":"2512"})
//            qualityWindow.qualityModel.append({"redMax":spliceModel.getRawData("Post-Height+"),"redMin":spliceModel.getRawData("Post-Height-"),"yellowMax":4,"yellowMin":1,"current":qualityWindow.postModel[qualityWindow.postModel.length - 1],"currentText":"43"})
//        }
//        else {
//            qualityWindow.qualityModel.append({"redMax":spliceModel.getRawData("Time+"),"redMin":spliceModel.getRawData("Time-"),"yellowMax":4,"yellowMin":1,"current":-1,"currentText":"23"})
//            qualityWindow.qualityModel.append({"redMax":spliceModel.getRawData("Power+"),"redMin":spliceModel.getRawData("Power-"),"yellowMax":4,"yellowMin":1,"current":-1,"currentText":"123"})
//            qualityWindow.qualityModel.append({"redMax":spliceModel.getRawData("Pre-Height+"),"redMin":spliceModel.getRawData("Pre-Height-"),"yellowMax":4,"yellowMin":1,"current":-1,"currentText":"2512"})
//            qualityWindow.qualityModel.append({"redMax":spliceModel.getRawData("Post-Height+"),"redMin":spliceModel.getRawData("Post-Height-"),"yellowMax":4,"yellowMin":1,"current":-1,"currentText":"43"})

//        }
        qualityWindow.qualityModel.clear()
        if (qualityWindow.timeModel.length > 0) {
            qualityWindow.qualityModel.append({"redMax":spliceModel.getRawData("Time+"),"redMin":spliceModel.getRawData("Time-"),"yellowMax":hmiAdaptor.controlLimitProcess("Time+",qualityWindow.timeModel,spliceModel.getRawData("Time+"),spliceModel.getRawData("Time-")),"yellowMin":hmiAdaptor.controlLimitProcess("Time-",qualityWindow.timeModel,spliceModel.getRawData("Time+"),spliceModel.getRawData("Time-")),"current":qualityWindow.timeModel[qualityWindow.timeModel.length - 1],"currentText":"23"})
            qualityWindow.qualityModel.append({"redMax":spliceModel.getRawData("Power+"),"redMin":spliceModel.getRawData("Power-"),"yellowMax":hmiAdaptor.controlLimitProcess("Power+",qualityWindow.powerModel,spliceModel.getRawData("Power+"),spliceModel.getRawData("Power-")),"yellowMin":hmiAdaptor.controlLimitProcess("Power-",qualityWindow.powerModel,spliceModel.getRawData("Power+"),spliceModel.getRawData("Power-")),"current":qualityWindow.powerModel[qualityWindow.powerModel.length - 1],"currentText":"123"})
            qualityWindow.qualityModel.append({"redMax":spliceModel.getRawData("Pre-Height+"),"redMin":spliceModel.getRawData("Pre-Height-"),"yellowMax":hmiAdaptor.controlLimitProcess("Time+",qualityWindow.preModel,spliceModel.getRawData("Pre-Height+"),spliceModel.getRawData("Pre-Height-")),"yellowMin":hmiAdaptor.controlLimitProcess("Pre-Height-",qualityWindow.preModel,spliceModel.getRawData("Pre-Height+"),spliceModel.getRawData("Pre-Height-")),"current":qualityWindow.preModel[qualityWindow.preModel.length - 1],"currentText":"2512"})
            qualityWindow.qualityModel.append({"redMax":spliceModel.getRawData("Post-Height+"),"redMin":spliceModel.getRawData("Post-Height-"),"yellowMax":hmiAdaptor.controlLimitProcess("Time+",qualityWindow.postModel,spliceModel.getRawData("Post-Height+"),spliceModel.getRawData("Post-Height-")),"yellowMin":hmiAdaptor.controlLimitProcess("Post-Height-",qualityWindow.postModel,spliceModel.getRawData("Post-Height+"),spliceModel.getRawData("Post-Height-")),"current":qualityWindow.postModel[qualityWindow.postModel.length - 1],"currentText":"43"})
        }
        else {
            qualityWindow.qualityModel.append({"redMax":spliceModel.getRawData("Time+"),"redMin":spliceModel.getRawData("Time-"),"yellowMax":-1,"yellowMin":-1,"current":-1,"currentText":"23"})
            qualityWindow.qualityModel.append({"redMax":spliceModel.getRawData("Power+"),"redMin":spliceModel.getRawData("Power-"),"yellowMax":-1,"yellowMin":-1,"current":-1,"currentText":"123"})
            qualityWindow.qualityModel.append({"redMax":spliceModel.getRawData("Pre-Height+"),"redMin":spliceModel.getRawData("Pre-Height-"),"yellowMax":-1,"yellowMin":-1,"current":-1,"currentText":"2512"})
            qualityWindow.qualityModel.append({"redMax":spliceModel.getRawData("Post-Height+"),"redMin":spliceModel.getRawData("Post-Height-"),"yellowMax":-1,"yellowMin":-1,"current":-1,"currentText":"43"})
        }
        qualityWindow.setData()
    }

    function selectSplice(spliceId)
    {
        spliceModel.editNew(spliceId)
        setData()
        var list = new Array
        list = spliceModel.getWireIdList()
        spliceDetailsItem.clear()
        spliceName.text = spliceModel.getStructValue("SpliceName","")
        spliceDetailsImage.source = spliceModel.getStructValue("PicPath","")
        for (var i = 0; i < list.length;i++)
        {
            wireModel.addFromLibrary(list[i])
            spliceDetailsItem.addWireFromSplice()
        }
        hmiAdaptor.setOperateProcess(spliceId,true)
        hmiAdaptor.operateProcessExec("Execute")

    }

    Rectangle {
        anchors.fill: parent
        color: "#626465"
    }

    Text {
        id: operateTitle
        text: qsTr("Splice:")
        font.pointSize: 16
        font.family: "arial"
        color: "white"
        anchors.left: parent.left
        anchors.leftMargin: 25
    }
    Text {
        id: spliceName
        font.pointSize: 16
        font.family: "arial"
        color: "white"
        anchors.left: operateTitle.right
    }

    Switch2 {
        width: Screen.width * 0.12
        height: Screen.height * 0.04
        anchors.right: spliceDetailsItem.right
        anchors.leftMargin: 22
        anchors.top: parent.top
        textLeft: qsTr("Diagram")
        textRight: qsTr("Image")
        state: "left"
        onStateChanged: {
            if (state == "left") {
                spliceDetailsItem.visible = true
                spliceDetailsImage.visible = false
            }
            else
            {
                spliceDetailsItem.visible = false
                spliceDetailsImage.visible = true
            }
        }
    }
    Image {
        id: spliceDetailsImage
        anchors.fill: spliceDetailsItem
        source: "qrc:/images/images/wiredemo.jpg"
    }

    Line {
        id: line
        height: parent.height
        width: 1
        lineColor: "white"
        anchors.left: spliceDetailsItem.right
        anchors.leftMargin: 10
        visible: false
    }

    QualityWindow {
        id: qualityWindow
        anchors.top: operateTitle.top
        anchors.right: parent.right
        anchors.rightMargin: 30
        bisTest: true
    }
    SpliceDetails {
        id: spliceDetailsItem
        width: Screen.width * 0.5
        height: Screen.height *0.45
        anchors.top: operateTitle.bottom
        anchors.left: operateTitle.left
        anchors.topMargin: 15
        centerVisable: false
        Component.onCompleted: {
        }
    }
    Item {
        id: leftBottomItem
        visible: true
        anchors.top: spliceDetailsItem.bottom
        anchors.topMargin: 20
        anchors.left: spliceDetailsItem.left
        anchors.right: spliceDetailsItem.right
        anchors.bottom: parent.bottom
        Text {
            id: partCount
            text: qsTr("PART COUNT")
            color: "white"
            font.pointSize: 14
            font.family: "arial"
        }
        CProgressBar {
            id: progressBar
            width: spliceDetailsItem.width
            height: 10
            anchors.top: partCount.bottom
            anchors.topMargin: 20
            anchors.left: parent.left
            minimum: 0
            maximum: bIsLimite ? 1 : quantity
            value:  bIsLimite ? 0.5 : 0
        }
        Text {
            id: present
            anchors.right: progressBar.right
            anchors.bottom: progressBar.top
            color: "white"
            font.pointSize: 14
            font.family: "arial"
            anchors.bottomMargin: 10
            text: testDetail.teachCount + "/" + (spliceModel.getStructValue("TestModel","") == 0 ? "--" : testDetail.quantity)
        }

        Text {
            id: weld
            text: qsTr("Weld Parameters - Actual")
            color: "white"
            font.pointSize: 14
            anchors.top: progressBar.bottom
            anchors.topMargin: 20
            anchors.left: parent.left
            font.family: "arial"
        }
        Item {
            id: leftBottomBack
            width: spliceDetailsItem.width
            anchors.left: parent.left
            anchors.top: weld.bottom
            anchors.topMargin: 20
            anchors.bottom: parent.bottom
            anchors.bottomMargin:  30
            anchors.right: parent.right
            ListModel {
                id: leftBottomModel
                Component.onCompleted: {
                    leftBottomModel.append({ name: qsTr("ENERGY(J)"),myvalue: spliceModel.getStructValue("Energy","current")})
                    leftBottomModel.append({ name: qsTr("T.P.(PSI)"),myvalue: spliceModel.getStructValue("Trigger Pressure","current")})
                    leftBottomModel.append({ name: qsTr("W.P.(PSI)"),myvalue: spliceModel.getStructValue("Weld Pressure","current")})
                    leftBottomModel.append({ name: qsTr("AMP(um)"),myvalue: spliceModel.getStructValue("Amplitude","current")})
                    leftBottomModel.append({ name: qsTr("WIDTH(mm)"),myvalue: spliceModel.getStructValue("Width","current")})
                }
            }

            ListView {
                anchors.fill: parent
                anchors.topMargin: 10
                orientation: Qt.Horizontal
                interactive: false
                model: leftBottomModel
                delegate: Item {
                    width: leftBottomBack.width / 5
                    height: leftBottomBack.height
                    Text {
                        id: title
                        font.family: "arial"
                        text:  name
                        font.pointSize: 16
                        color: "white"
                        anchors.horizontalCenter: parent.horizontalCenter
                    }
                    Text {
                        anchors.top: title.bottom
                        anchors.topMargin: 20
                        font.family: "arial"
                        text: myvalue
                        font.pointSize: 16
                        color: "white"
                        anchors.horizontalCenter: parent.horizontalCenter
                    }
                }
            }
        }
    }

    Item {
        id: leftBottomItem2
        visible: false
        anchors.top: spliceDetailsItem.bottom
        anchors.topMargin: 20
        anchors.left: spliceDetailsItem.left
        anchors.right: spliceDetailsItem.right
        anchors.bottom: parent.bottom
        Text {
            id: testTracking
            text: qsTr("Test Tracking")
            color: "white"
            font.pointSize: 14
            font.family: "arial"
        }
        Row {
            id: row1
            anchors.top: testTracking.bottom
            anchors.topMargin: 10
            spacing: 10
            CButton {
                width: 170
                height: 50
                text: qsTr("SPLICE 1")
                backgroundComponent: Rectangle {
                    anchors.fill: parent
                    color: "#4E5051"
                }
            }
            CButton {
                width: 170
                height: 50
                text: qsTr("+ NEW SAMPLE")

            }
        }
        Text {
            id: sampDetail
            text: qsTr("SAMPLE DETAILS:")
            anchors.left: parent.left
            anchors.top: row1.bottom
            color: "white"
            font.pointSize: 14
            font.family: "arial"
            anchors.topMargin: 20
        }
        Text {
            id: sampDetail2
            text: qsTr("35 Splices\n\nTeach Mode:Standard\n\n6/24/2016")
            anchors.left: sampDetail.right
            anchors.top: row1.bottom
            color: "white"
            font.pointSize: 14
            font.family: "arial"
            anchors.topMargin: 20
            anchors.leftMargin: 10
        }
    }

    CButton {
        id: finish
        width: 300
        height: 79
        anchors.right: qualityWindow.right
        anchors.bottom: parent.bottom
        text: qsTr("FINISH SAMPLE")
        onClicked: {
            if (spliceModel.getStructValue("TeachMode","") != 3)
            {
                hmiAdaptor.stopTeachMode()
            }
            finish.visible = false
            rightBottom.visible = true
            leftBottomItem.visible = false
            leftBottomItem2.visible = true
        }
    }

    Column {
        id: rightBottom
        visible: false
        anchors.right: qualityWindow.right
        anchors.bottom: parent.bottom
        spacing: 20
        CButton {
            width: 300
            height: 79
            text: qsTr("EDITE SPLICE")
        }
        CButton {
            width: 300
            height: 79
            text: qsTr("SAVE SPLICE")
            onClicked: {
                signalSaveSplice()
            }
        }
    }
    CDialog {
        id: cdialog
        anchors.centerIn: parent
        okvisible: true
        okText: "Accept"
        cancelvisible: true
        cancelText: "Reject"
        titleText: "Teach Mode - Standard"
        centerText: "Please hit the button to start next"
        visible: false
        onCliceTo: {
            if (reb)
                hmiAdaptor.teachModeProcess()
            setData()
            hmiAdaptor.operateProcessExec("Execute")
        }

    }
    CDialog {
        id: cdialog2
        anchors.centerIn: parent
        okvisible: true
        okText: "OK"
        cancelvisible: true
        cancelText: "CANCEL"
        centerText: "Test Complete"
        visible: false
        onCliceTo: {
            if (spliceModel.getStructValue("TeachMode","") != 3)
            {
                hmiAdaptor.stopTeachMode()
            }
            root.checkNeedPassWd(3)
        }

    }
}
