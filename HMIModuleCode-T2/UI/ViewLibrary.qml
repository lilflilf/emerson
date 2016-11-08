import QtQuick 2.0
import QtQuick.Controls 1.2

Item {
    Image {
        anchors.fill: parent
        source: "qrc:/images/images/bg.png"
    }
    Column {
        id: column
        anchors.top: parent.top
        anchors.topMargin: 30
        anchors.left: parent.left
        anchors.leftMargin: 30
        height: 79*3+20
        width: 250
        spacing: 10
        CButton {
            width: column.width
            height: 79
            textColor: "white"
            text: qsTr("Part")
        }
        CButton {
            width: column.width
            height: 79
            textColor: "white"
            text: qsTr("Splice")
        }
        CButton {
            width: column.width
            height: 79
            textColor: "white"
            text: qsTr("Wire")
        }
    }


    Row {
        id: rowButton
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 30
        anchors.right: parent.right
        anchors.rightMargin: 20
        spacing: 20
        height: 79
        CButton {
            width: 250
            height: 79
            textColor: "white"
            text: qsTr("View Details")
        }
        CButton {
            width: 250
            height: 79
            textColor: "white"
            text: qsTr("Export")
        }
        CButton {
            width: 250
            height: 79
            textColor: "white"
            text: qsTr("Back")
        }
    }
}
