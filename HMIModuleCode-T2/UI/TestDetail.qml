import QtQuick 2.7
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.0
import QtQuick.Window 2.2

Item {
    id: operateDetail
    signal signalSaveSplice()
    width: Screen.width
    height: Screen.height * 0.8
    Rectangle {
        anchors.fill: parent
        color: "#626465"
    }

    Text {
        id: operateTitle
        text: qsTr("Splice:mod_70742305_proc_1")
        font.pointSize: 16
        font.family: "arial"
        color: "white"
        anchors.left: parent.left
        anchors.leftMargin: 25
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
            spliceDetailsItem.leftModel.append({"myLineLength":200,"mycolor":"red","isCheck":false,"linetext":"0"})
            spliceDetailsItem.leftModel.append({"myLineLength":200,"mycolor":"black","isCheck":false,"linetext":"0"})
            spliceDetailsItem.leftModel.append({"myLineLength":200,"mycolor":"blue","isCheck":false,"linetext":"0"})
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
            width: 300//Screen.width * 0.17
            height: 79//Screen.height * 0.07
            text: qsTr("EDITE SPLICE")
        }
        CButton {
            width: 300//Screen.width * 0.17
            height: 79//Screen.height * 0.07
            text: qsTr("SAVE SPLICE")
            onClicked: {
                signalSaveSplice()
            }
        }
    }
}
