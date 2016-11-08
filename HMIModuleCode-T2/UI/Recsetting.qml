import QtQuick 2.7
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.0
import QtQuick.Window 2.2

Item {
    property string localbordercolor: "#0079c1"
    property string recBackGround: "qrc:/images/images/advancesetting-bg1.png"
    property string headTitle: ""
    property string centervalue: ""
    signal mouseAreaClick()
    width: parent.width
    height: parent.height
    Image {
        anchors.fill: parent
        source: recBackGround
    }
    Rectangle {
        id: backGround
        width: parent.width
        height: parent.height-9
        border.color: localbordercolor
        border.width: 2
        color: Qt.rgba(0,0,0,0)
    }
    Text {
        id: headName
        anchors.top: parent.top
        anchors.topMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 10
        font.family: "arial"
        font.pixelSize: 20
        color: "white"
        text: qsTr(headTitle)
    }
    Text {
        id: centerValue
        anchors.centerIn: parent
        font.family: "arial"
        font.pixelSize: 25
        color: "white"
        text: qsTr(centervalue)
    }
    MouseArea {
        anchors.fill: parent
        onClicked: {
            localbordercolor = "#05f91c"
            mouseAreaClick()
        }
    }
}
