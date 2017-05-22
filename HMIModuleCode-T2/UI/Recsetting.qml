import QtQuick 2.2
import QtQuick.Controls 1.1
import QtQuick.Layouts 1.0
import QtQuick.Window 2.2

Item {
    id: recsetting
    property string localbordercolor: "#0079c1"
    property alias recBackGround: bg.source
    property string headTitle: ""
    property string centervalue: ""
    property alias bgvisable: bg.visible
    property bool myFocus: false
    signal mouseAreaClick()
    width: parent.width
    height: parent.height
    Image {
        id: bg
        anchors.fill: parent
        source: "qrc:/images/images/advancesetting-bg1.png"
    }
    Rectangle {
        id: backGround
        width: parent.width
        height: parent.height
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
        text: headTitle
    }
    Text {
        id: centerValue
        anchors.centerIn: parent
        font.family: "arial"
        font.pixelSize: 25
        color: "white"
        text: centervalue
    }
    MouseArea {
        anchors.fill: parent
        onClicked: {
            myFocus = true
            mouseAreaClick()
        }
    }
}
