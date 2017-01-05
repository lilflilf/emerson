import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2

Item {
    id: progressBar
    property int total: 0
    property int current: 1

    property int finishNo: 1
    property int missNo: 0
//    property bool bIsMiss: missProgress.visible
//    width: parent.width
//    height: parent.height

    signal cycleDone()
    function jumpToNext()
    {

        finishedProgress.anchors.leftMargin = (current - 1) * (progressBar.width/progressBar.total)
        if (current < 2)
            return
        repeater.itemAt(current-2).color = "#ED1C24"
    }
    function jumpToAbove()
    {
        finishedProgress.anchors.leftMargin = (current - 1) * (progressBar.width/progressBar.total)
        repeater.itemAt(current).color = Qt.rgba(0,0,0,0)
    }

    function moveToNext()
    {
        finishedProgress.anchors.leftMargin = (current - 1) * (progressBar.width/progressBar.total)
        if (current < 2)
            return
        repeater.itemAt(current-2).color = "#60BB46"
    }
    onCurrentChanged: {
        if (current > total) {
            current = 1
            for (var i = 0; i < repeater.count; i++)
            {
                repeater.itemAt(i).color = Qt.rgba(0,0,0,0)
            }
            cycleDone()
        }

        if (current == total)
            nextprogress.visible = false
        else
            nextprogress.visible = true
    }

    Rectangle {
        id: totalprogress
        anchors.top: parent.top
        anchors.topMargin: 16
        width: parent.width
        height: parent.height/2
        color: "#9FA1A4"
    }

    Row {
        id: column
        anchors.fill: totalprogress
        Repeater {
            id: repeater
            model: total
            delegate: Rectangle {
                width: finishedProgress.width
                height: finishedProgress.height
                color: Qt.rgba(0,0,0,0) //"#60BB46"
            }
        }
    }

    Rectangle {
        id: finishedProgress
        anchors.top: totalprogress.top
        anchors.left: parent.left
        width: parent.width/progressBar.total
        height: parent.height/2
        anchors.leftMargin: 0
        color: "#60BB46"
    }
    Rectangle {
        id: currentRec
        anchors.top: parent.top
        anchors.topMargin: 2
        anchors.horizontalCenter: finishedProgress.horizontalCenter
        radius: 14
        width: 14
        height: 14
        color: "#00A651"
    }
    Text {
        id: currentText
        anchors.top: parent.top
        anchors.right: currentRec.left
        font.family: "arial"
        font.pointSize: 13
        color: "white"
        text: current
    }
    Rectangle {
        id: nextprogress
        anchors.top: totalprogress.top
        anchors.left: finishedProgress.right
        width: finishedProgress.width
        height: parent.height/2
        color: "#00AFE9"
        visible: current == total ? false : true
    }

    Text {
        id: startNo
        anchors.left: parent.left
        anchors.top: totalprogress.bottom
        anchors.topMargin: 2
        font.family: "arial"
        font.pointSize: 14
        color: "white"
        text: "1"
    }
    Text {
        id: endNo
        anchors.right: parent.right
        anchors.top: totalprogress.bottom
        anchors.topMargin: 2
        font.family: "arial"
        font.pointSize: 14
        color: "white"
        text: total
    }
    Rectangle {
        anchors.top: totalprogress.top
        anchors.left: totalprogress.right
        color: "#626465"
        width: nextprogress.width
        height: parent.height/2
        z: 10
    }
}
