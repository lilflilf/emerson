import QtQuick 2.7
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.0
import QtQuick.Window 2.2

Item {
    id: operateDetail
    signal signalSaveSplice()
    width: Screen.width
    height: Screen.height * 0.8

    Component.onCompleted: {
//        hmiAdaptor.operateProcessExec("Start")
    }
    Component.onDestruction: {
//        hmiAdaptor.operateProcessExec("Stop")
    }

    function setData()
    {
        qualityWindow.qualityModel.clear()
        qualityWindow.qualityModel.append({"redMax":spliceModel.getRawData("Time+"),"redMin":spliceModel.getRawData("Time-"),"yellowMax":4,"yellowMin":1,"current":-1,"currentText":"23"})
        qualityWindow.qualityModel.append({"redMax":spliceModel.getRawData("Power+"),"redMin":spliceModel.getRawData("Power-"),"yellowMax":4,"yellowMin":1,"current":123,"currentText":"123"})
        qualityWindow.qualityModel.append({"redMax":spliceModel.getRawData("Pre-Height+"),"redMin":spliceModel.getRawData("Pre-Height-"),"yellowMax":4,"yellowMin":1,"current":2512,"currentText":"2512"})
        qualityWindow.qualityModel.append({"redMax":spliceModel.getRawData("Post-Height+"),"redMin":spliceModel.getRawData("Post-Height-"),"yellowMax":4,"yellowMin":1,"current":43,"currentText":"43"})

        qualityWindow.timeModel = alarmModel.getPointList("Time",spliceModel.getStructValue("SpliceName",""),spliceModel.getHashCode())
        qualityWindow.powerModel = alarmModel.getPointList("Power",spliceModel.getStructValue("SpliceName",""),spliceModel.getHashCode())
        qualityWindow.preModel = alarmModel.getPointList("Pre-Height",spliceModel.getStructValue("SpliceName",""),spliceModel.getHashCode())
        qualityWindow.postModel = alarmModel.getPointList("Post-Height",spliceModel.getStructValue("SpliceName",""),spliceModel.getHashCode())

        qualityWindow.qualityListViewTwoModel = 0
        qualityWindow.qualityListViewTwoModel = qualityWindow.timeModel.length
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
//        hmiAdaptor.operateProcessExec("Execute")

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
//        anchors.left: line.right
//        anchors.leftMargin: 36
//        anchors.right: parent.right
//        anchors.rightMargin: 30
////        width: 688
//        height: 543
        anchors.top: operateTitle.top
        anchors.right: parent.right
        anchors.rightMargin: 30

    }
    SpliceDetails {
        id: spliceDetailsItem
        width: Screen.width * 0.5
        height: Screen.height *0.45
        anchors.top: operateTitle.bottom
        anchors.left: operateTitle.left
        //anchors.right: operateTitle.right
        anchors.topMargin: 15
        centerVisable: false
        Component.onCompleted: {
//            spliceDetailsItem.leftModel.append({"myLineLength":200,"mycolor":"#00cc66","isCheck":false,"linetext":"0.75"})
//            spliceDetailsItem.leftModel.append({"myLineLength":200,"mycolor":"#00cc66","isCheck":false,"linetext":"0.75"})
//            spliceDetailsItem.leftModel.append({"myLineLength":200,"mycolor":"#00cc66","isCheck":false,"linetext":"0.75"})
//            spliceDetailsItem.leftModel.append({"myLineLength":200,"mycolor":"#00cc66","isCheck":false,"linetext":"0.75"})

//            spliceDetailsItem.rightModel.append({"myLineLength":200,"mycolor":"#00cc66","isCheck":false,"linetext":"0.75"})
//            spliceDetailsItem.rightModel.append({"myLineLength":200,"mycolor":"#00cc66","isCheck":false,"linetext":"0.75"})
//            spliceDetailsItem.rightModel.append({"myLineLength":200,"mycolor":"#00cc66","isCheck":false,"linetext":"0.75"})
//            spliceDetailsItem.rightModel.append({"myLineLength":200,"mycolor":"#00cc66","isCheck":false,"linetext":"0.75"})
//            spliceDetailsItem.rightModel.append({"myLineLength":200,"mycolor":"#00cc66","isCheck":false,"linetext":"0.75"})
//            spliceDetailsItem.rightModel.append({"myLineLength":200,"mycolor":"#00cc66","isCheck":false,"linetext":"0.75"})
//            spliceDetailsItem.setState("topLeft",200,"0.75","red")
//            spliceDetailsItem.setState("bottomLeft",200,"0.75","red")
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
            value: 0.5
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
                ListElement { name: "ENERGY(J)"; myvalue: "50"}
                ListElement { name: "T.P.(PSI)"; myvalue: "20"}
                ListElement { name: "W.P.(PSI)"; myvalue: "20"}
                ListElement { name: "AMP(um)"; myvalue: "50"}
                ListElement { name: "WIDTH(mm)"; myvalue: "10.00"}
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
                        text:  qsTr(name)
                        font.pointSize: 16
                        color: "white"
                        anchors.horizontalCenter: parent.horizontalCenter
                    }
                    Text {
                        anchors.top: title.bottom
                        anchors.topMargin: 20
                        font.family: "arial"
                        text: myvalue //qsTr(myvalue)
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
        width: 300//Screen.width * 0.17
        height: 79//Screen.height * 0.07
        anchors.right: qualityWindow.right
        anchors.bottom: parent.bottom
        text: qsTr("FINISH SAMPLE")
        onClicked: {
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
}
