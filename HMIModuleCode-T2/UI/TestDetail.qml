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
        anchors.top: parent.top
        anchors.leftMargin: 25
        anchors.topMargin: 15
    }

    CButton {
        width: Screen.desktopAvailableWidth * 0.17
        height: Screen.desktopAvailableHeight * 0.07
        anchors.right: spliceDetailsItem.right
        anchors.top: operateTitle.top
        text: qsTr("FINISH SAMPLE")
    }

    QualityWindow {
        id: qualityWindow
        anchors.right: parent.right
        anchors.rightMargin: 30
        anchors.top: operateTitle.top

    }
    SpliceDetails {
        id: spliceDetailsItem
        width: Screen.desktopAvailableWidth * 0.5
        height: Screen.desktopAvailableHeight *0.4
        anchors.top: operateTitle.bottom
        anchors.left: operateTitle.left
        anchors.topMargin: 15
        centerVisable: false
        Component.onCompleted: {
            spliceDetailsItem.leftModel.append({"myLineLength":200,"mycolor":"red","isCheck":false,"linetext":"0"})
            spliceDetailsItem.leftModel.append({"myLineLength":200,"mycolor":"black","isCheck":false,"linetext":"0"})
            spliceDetailsItem.leftModel.append({"myLineLength":200,"mycolor":"blue","isCheck":false,"linetext":"0"})
        }
    }
}
