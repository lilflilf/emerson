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
    Switch2 {
        width: Screen.desktopAvailableWidth * 0.12
        height: Screen.desktopAvailableHeight * 0.04
        anchors.right: spliceDetailsItem.right
        anchors.top: operateTitle.top
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

    Text {
        id: spliceTips
        anchors.top: spliceDetailsItem.bottom
        anchors.topMargin: 10
        anchors.left: operateTitle.left
        font.pointSize: 16
        font.family: "arial"
        text: qsTr("Splice Locations and Status")
        color: "white"
    }
    Text {
        id: totalcross
        anchors.top: spliceDetailsItem.bottom
        anchors.topMargin: 10
        anchors.right: spliceDetailsItem.right
        font.pointSize: 16
        font.family: "arial"
        text: qsTr("TOTAL CROSS SECTION: 2.3mm")
        color: "white"
    }

    ListModel {
        id: treeModel
        Component.onCompleted: {
            treeModel.append({"id":"A","level":0,"subNode":[]})
            treeModel.append({"id":"B","level":0,"subNode":[]})
            treeModel.append({"id":"C","level":0,"subNode":[]})
            treeModel.append({"id":"D","level":0,"subNode":[]})
            treeModel.append({"id":"E","level":0,"subNode":[]})
            treeModel.append({"id":"F","level":0,"subNode":[]})
            treeModel.append({"id":"G","level":0,"subNode":[]})
            treeModel.append({"id":"H","level":0,"subNode":[]})
            treeModel.append({"id":"I","level":0,"subNode":[]})
            treeModel.append({"id":"J","level":0,"subNode":[]})
            treeModel.append({"id":"K","level":0,"subNode":[]})
            treeModel.append({"id":"L","level":0,"subNode":[]})
            treeModel.append({"id":"M","level":0,"subNode":[]})
            treeModel.append({"id":"N","level":0,"subNode":[]})
            treeModel.append({"id":"O","level":0,"subNode":[]})
            treeModel.append({"id":"P","level":0,"subNode":[]})
            treeModel.get(0).subNode.append({"spliceNo":"1","spliceColor":"white","level":1,"subNode":[]})
            treeModel.get(0).subNode.append({"spliceNo":"56","spliceColor":"white","level":1,"subNode":[]})
            treeModel.get(0).subNode.append({"spliceNo":"55","spliceColor":"white","level":1,"subNode":[]})
            treeModel.get(0).subNode.append({"spliceNo":"54","spliceColor":"white","level":1,"subNode":[]})
            treeModel.get(0).subNode.append({"spliceNo":"53","spliceColor":"white","level":1,"subNode":[]})
            treeModel.get(1).subNode.append({"spliceNo":"52","spliceColor":"white","level":1,"subNode":[]})
            treeModel.get(2).subNode.append({"spliceNo":"51","spliceColor":"white","level":1,"subNode":[]})
            treeModel.get(3).subNode.append({"spliceNo":"7","spliceColor":"white","level":1,"subNode":[]})
            treeModel.get(4).subNode.append({"spliceNo":"9","spliceColor":"white","level":1,"subNode":[]})
            treeModel.get(5).subNode.append({"spliceNo":"11","spliceColor":"white","level":1,"subNode":[]})
            treeModel.get(6).subNode.append({"spliceNo":"13","spliceColor":"white","level":1,"subNode":[]})
            treeModel.get(7).subNode.append({"spliceNo":"14","spliceColor":"white","level":1,"subNode":[]})
            treeModel.get(8).subNode.append({"spliceNo":"15","spliceColor":"white","level":1,"subNode":[]})
            treeModel.get(9).subNode.append({"spliceNo":"88","spliceColor":"white","level":1,"subNode":[]})
            treeModel.get(10).subNode.append({"spliceNo":"16","spliceColor":"white","level":1,"subNode":[]})
            treeModel.get(11).subNode.append({"spliceNo":"17","spliceColor":"white","level":1,"subNode":[]})
            treeModel.get(12).subNode.append({"spliceNo":"18","spliceColor":"white","level":1,"subNode":[]})
            treeModel.get(13).subNode.append({"spliceNo":"19","spliceColor":"white","level":1,"subNode":[]})
            treeModel.get(14).subNode.append({"spliceNo":"20","spliceColor":"white","level":1,"subNode":[]})
            treeModel.get(15).subNode.append({"spliceNo":"22","spliceColor":"white","level":1,"subNode":[]})
        }
    }
    SpliceLocation {
        id: spliceLocation
        anchors.top: spliceTips.bottom
        anchors.topMargin: 10
        anchors.left: operateTitle.left
        width: Screen.desktopAvailableWidth * 0.37
        height: Screen.desktopAvailableHeight *0.35
        columns: 4
        rows: 4
        listModel: treeModel
    }
}
