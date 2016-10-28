import QtQuick 2.7
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.0
import QtQuick.Window 2.2

Item {
    id: operateDetail
    width: Screen.desktopAvailableWidth
    height: Screen.desktopAvailableHeight * 0.8
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
        width: Screen.desktopAvailableWidth * 0.12
        height: Screen.desktopAvailableHeight * 0.04
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
        width: Screen.desktopAvailableWidth * 0.5
        height: Screen.desktopAvailableHeight *0.45
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

    CProgressBar {
        width: 300
        height: 10
        anchors.top: spliceDetailsItem.bottom
        anchors.topMargin: 20
        anchors.left: parent.left
        value: 0.5
    }

    CButton {
        id: finish
        width: 300//Screen.desktopAvailableWidth * 0.17
        height: 79//Screen.desktopAvailableHeight * 0.07
        anchors.right: qualityWindow.right
        anchors.bottom: parent.bottom
        text: qsTr("FINISH SAMPLE")
    }
}
