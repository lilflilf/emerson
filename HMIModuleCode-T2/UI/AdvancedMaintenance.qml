import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import QtQuick.Dialogs 1.2
import Qt.labs.folderlistmodel 2.1

Item {
    id: toolChange
    width: Screen.width*0.7
    height: Screen.height*0.6

    Column {
        id: column1
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.leftMargin: 250
        anchors.topMargin: 30
        spacing: 20
        Image {
            width: 280
            height: 280
            source: "qrc:/images/images/maintenance-5.png"
//            source: "file:///c:/ToolChangeImage/group2/wiredemo.jpg"
        }
        Image {
            width: 280
            height: 280
            source: "qrc:/images/images/maintenance-6.png"
//            source: "file:///c:/ToolChangeImage/group2/wiredemo.jpg"
        }
    }

    Column {
        anchors.left:column1.right
        anchors.top: column1.top
        anchors.leftMargin: 60
        spacing: 10
        CButton {
            height: 79
            width: 250
            text: qsTr("1-Anvil Arm")
        }
        CButton {
            height: 79
            width: 250
            text: qsTr("2-Gather")
        }
        CButton {
            height: 79
            width: 250
            text: qsTr("3-Safety")
        }
    }
    Column {
        anchors.left:column1.right
        anchors.top: column1.top
        anchors.topMargin: 330
        anchors.leftMargin: 60
        spacing: 10
        CButton {
            height: 79
            width: 250
            text: qsTr("4-Cutter")
        }
        CButton {
            height: 79
            width: 250
            text: qsTr("5-Cooling Tooling")
        }
        CButton {
            height: 79
            width: 250
            text: qsTr("6-Cooling Converter")
        }

    }
}
