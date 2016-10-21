import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2

Item {
    id: progressBar
    property int total: 0
    property int finishNo: 0
    property int current: 0
    property int missNo: 0
    property bool bIsMiss: missProgress.visible
    width: parent.width
    height: parent.height
    Rectangle {
        id: totalprogress
        anchors.top: parent.top
        anchors.topMargin: 16
        width: parent.width
        height: parent.height/2
        color: "#9FA1A4"
    }
    Rectangle {
        id: finishedProgress
        anchors.top: totalprogress.top
        anchors.left: parent.left
        width: progressBar.finishNo/progressBar.total*parent.width
        height: parent.height/2
        color: "#60BB46"
    }
    Rectangle {
        id: currentRec
        anchors.top: parent.top
        anchors.topMargin: 2
        anchors.left: parent.left
        anchors.leftMargin: progressBar.finishNo/progressBar.total*parent.width-5
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
        id: currentprogress
        anchors.top: totalprogress.top
        anchors.left: finishedProgress.right
        width: 3
        height: parent.height/2
        color: "#00A651"
    }
    Rectangle {
        id: nextprogress
        anchors.top: totalprogress.top
        anchors.left: currentprogress.right
        width: 3
        height: parent.height/2
        color: "#00AFE9"
    }
    Rectangle {
        id: missProgress
        anchors.top: totalprogress.top
        anchors.left: parent.left
        anchors.leftMargin: progressBar.current/progressBar.total*parent.width
        width: 3
        height: parent.height/2
        color: "#ED1C24"
        visible: false
    }
    Rectangle {
        id: missRec
        anchors.top: totalprogress.bottom
        anchors.topMargin: 2
        anchors.left: parent.left
        anchors.leftMargin: progressBar.current/progressBar.total*parent.width-5
        radius: 14
        width: 14
        height: 14
        color: "#ED1C24"
        visible: false
    }
    Text {
        id: startNo
        anchors.left: parent.left
        anchors.top: totalprogress.bottom
        anchors.topMargin: 2
        font.family: "arial"
        font.pointSize: 14
        color: "white"
        text: qsTr("0")
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
}
