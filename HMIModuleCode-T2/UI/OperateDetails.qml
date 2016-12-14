import QtQuick 2.7
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.0
import QtQuick.Window 2.2

Item {
    id: operateDetail
    property var spliceList: null
    Rectangle {
        anchors.fill: parent
        color: "#626465"
        MouseArea {
            anchors.fill: parent
        }
    }

    function selectSplice(spliceId)
    {
        spliceModel.editNew(spliceId)
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
    }

    Text {
        id: operateTitle
        text: qsTr("Splice:")
        font.pointSize: 16
        font.family: "arial"
        color: "white"
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.leftMargin: 25
        anchors.topMargin: 15
    }
    Text {
        id: spliceName
        font.pointSize: 16
        font.family: "arial"
        color: "white"
        anchors.left: operateTitle.right
        anchors.top: parent.top
        anchors.topMargin: 15
    }
    Switch2 {
        width: Screen.width * 0.12
        height: Screen.height * 0.04
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
        source: "qrc:/images/images/wiredemo.jpg"
    }
    QualityWindow {
        id: qualityWindow
        anchors.right: parent.right
        anchors.rightMargin: 30
        anchors.top: operateTitle.top
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

    Text {
        id: spliceTips
        anchors.top: spliceDetailsItem.bottom
        anchors.topMargin: 10
        anchors.left: operateTitle.left
        font.pointSize: 14
        font.family: "arial"
        //text: qsTr("Splice Locations and Status")
        text: qsTr("Insulation: 1 Temp(℃):260 Time(s):09.0")
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
        id: testModel
        Component.onCompleted: {
            testModel.append({"theNo":1})
            testModel.append({"theNo":2})
            testModel.append({"theNo":3})
            testModel.append({"theNo":4})
            testModel.append({"theNo":5})
            testModel.append({"theNo":6})
            testModel.append({"theNo":7})
            testModel.append({"theNo":8})
        }
    }

    ListModel {
        id: treeModel
        Component.onCompleted: {
            var array = ["A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P"]
            for (var i = 0; i < spliceLocation.rows*spliceLocation.columns; i++) {
                treeModel.append({"id":array[i],"level":0,"subNode":[]})
            }
            var zoneList = new Array();
            zoneList = partModel.geteWorkStationZone()
            var j = 0
            for ( j = 0; j < zoneList.length; j++) {
                if (j == 0) {
                    treeModel.get(zoneList[j]).subNode.append({"spliceNo":j+1,"spliceColor":"#00aa7e","level":1,"subNode":[]})
                } else if (j == 1) {
                    treeModel.get(zoneList[j]).subNode.append({"spliceNo":j+1,"spliceColor":"#00afe9","level":1,"subNode":[]})
                } else {
                    treeModel.get(zoneList[j]).subNode.append({"spliceNo":j+1,"spliceColor":"white","level":1,"subNode":[]})
                }
            }
        }
    }

    SpliceLocation {
        id: spliceLocation
        anchors.top: spliceTips.bottom
        anchors.topMargin: 10
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        anchors.left: operateTitle.left
        width: Screen.width * 0.37
        columns: partModel.getWorkStationColumns()
        rows: partModel.getWorkStationRows()
        visible: partModel.getPartOnlineOrOffLine()
        listModel: treeModel
    }
    SpliceStatusOffLine {
        id: offline
        anchors.top: spliceTips.bottom
        anchors.topMargin: 10
        anchors.left: operateTitle.left
        width: Screen.width * 0.37
        height: Screen.height *0.2
        listModel: testModel
        visible: false
    }

    Rectangle {
        id: currentSplice
        anchors.top:  spliceTips.bottom
        anchors.topMargin: 12
        anchors.left: spliceLocation.right
        anchors.leftMargin: 10
        radius: 15
        width: 15
        height: 15
        color: "#00aa7e"
    }
    Text {
        id: currentspliceTips
        anchors.top: spliceTips.bottom
        anchors.topMargin: 10
        anchors.left: currentSplice.right
        anchors.leftMargin: 6
        font.pointSize: 13
        font.family: "arial"
        color: "white"
        text: qsTr("CURRENT SPLICE")
    }
    Rectangle {
        id: nextSPlice
        anchors.top:  currentspliceTips.bottom
        anchors.topMargin: 26
        anchors.left: spliceLocation.right
        anchors.leftMargin: 10
        radius: 15
        width: 15
        height: 15
        color: "#00afe9"
    }
    Text {
        id: nextSPliceTips
        anchors.top: currentspliceTips.bottom
        anchors.topMargin: 24
        anchors.left: nextSPlice.right
        anchors.leftMargin: 6
        font.pointSize: 13
        font.family: "arial"
        color: "white"
        text: qsTr("NEXT SPLICE")
    }
    Rectangle {
        id: missSplice
        anchors.top:  nextSPliceTips.bottom
        anchors.topMargin: 26
        anchors.left: spliceLocation.right
        anchors.leftMargin: 10
        radius: 15
        width: 15
        height: 15
        color: "#d31145"
    }
    Text {
        id: missSpliceTips
        anchors.top: nextSPliceTips.bottom
        anchors.topMargin: 24
        anchors.left: missSplice.right
        anchors.leftMargin: 6
        font.pointSize: 13
        font.family: "arial"
        color: "white"
        text: qsTr("MISSED SPLICE")
    }
    Rectangle {
        id: completeMiss
        anchors.top: missSpliceTips.bottom
        anchors.topMargin: 24
        anchors.left: spliceLocation.right
        anchors.leftMargin: 10
        width: spliceDetailsItem.width-spliceLocation.width-10
        height: spliceDetailsItem.height/ 4.3
        color: "#6d6e71"
        opacity: 1
        Rectangle {
            id: tipsRec
            anchors.left: parent.left
            width: 17
            height: parent.height
            color: "#d31145"
        }
        Text {
            id: tipsText
            anchors.left: tipsRec.right
            anchors.leftMargin: 10
            width: parent.width-tipsRec.width-10
            height: parent.height
            verticalAlignment: Qt.AlignVCenter
            text: qsTr("Complete\nMissed\nSplie")
            color: "white"
            font.pointSize: 16
            font.family: "arial"
        }
        MouseArea {
            anchors.fill: parent
            onPressed: {
                completeMiss.opacity = 0.5
            }
            onReleased: {
                completeMiss.opacity = 1
            }
        }
    }
    Text {
        id: partCount2
        anchors.left: offline.left
        anchors.top: offline.bottom
        anchors.topMargin: 10
        font.pointSize: 13
        font.family: "arial"
        text: qsTr("PART COUNTER 68/125")
        color: "white"
        visible: false
    }
    CProgressBar {
        id: progressBar2
        visible: false
        anchors.top: partCount2.bottom
        anchors.topMargin: 10
        anchors.left: offline.left
        width: 200
        height: 10
        maximum: 125
        minimum: 1
        value: 60
    }

    Text {
        id: progresstracking
        anchors.bottom: workStation.top
        anchors.bottomMargin: 4
        anchors.left: qualityWindow.left
        font.pointSize: 16
        font.family: "arial"
        text: qsTr("Progress and Tracking")
        color: "white"
    }
    Text {
        id: workStation
        anchors.bottom: progressBar.top
        anchors.bottomMargin: 6
        anchors.left: qualityWindow.left
        font.pointSize: 13
        font.family: "arial"
        text: qsTr("Work Station: B")
        color: "white"
    }
    Text {
        id: partTask
        anchors.right: parent.right
        anchors.rightMargin: 30
        anchors.bottom: progressBar.top
        anchors.bottomMargin: 6
        font.pointSize: 13
        font.family: "arial"
        text: qsTr("PART TASKS: 68-72")
        color: "white"
    }
    CButton {
        id: leftButton
        anchors.bottom: partCount.top
        anchors.bottomMargin: 20
        anchors.left: qualityWindow.left
        width: 50
        height: 32
        iconSource: "qrc:/images/images/you.png"
        backgroundEnabled: false
        clip: true
    }
    Progressbar {
        id: progressBar
        anchors.left: leftButton.right
        anchors.leftMargin: 25
        anchors.right: rightButton.left
        anchors.rightMargin: 25
        anchors.bottom: partCount.top
        anchors.bottomMargin: 4
        width: Screen.width*0.4-150
        height: 64
        total: 125
    }
    CButton {
        id: rightButton
        anchors.bottom: partCount.top
        anchors.bottomMargin: 20
        anchors.right: qualityWindow.right
        width: 50
        height: 32
        iconSource: "qrc:/images/images/zuo.png"
        backgroundEnabled: false
        clip: true
        onClicked: {
            progressBar.finishNo++
            progressBar.current++
            offline.setSatusOffLineNum(testModel.get(testModel.count-1).theNo+1)
        }
    }
    Text {
        id: partCount
        anchors.left: qualityWindow.left
        anchors.bottom: progressBar4.top
        anchors.bottomMargin: 6
        font.pointSize: 13
        font.family: "arial"
        text: qsTr("PART COUNTER 68/125")
        color: "white"
    }
    CProgressBar {
        id: progressBar4
        anchors.left: qualityWindow.left
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 20
        width: Screen.width*0.2
        height: 10
        maximum: 125
        minimum: 1
        value: 60
    }
    Text {
        id: maintenance
        anchors.right: qualityWindow.right
        anchors.bottom: progressBar3.top
        anchors.bottomMargin: 6
        font.pointSize: 13
        font.family: "arial"
        text: qsTr("MAINTENANCE COUNTER 68K/125K")
        color: "white"
    }
    CProgressBar {
        id: progressBar3
        anchors.right: qualityWindow.right
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 20
        width: Screen.width*0.2
        height: 10
        maximum: 125
        minimum: 1
        value: 60
    }
}
