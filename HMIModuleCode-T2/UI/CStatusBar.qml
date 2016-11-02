import QtQuick 2.7
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.0
import QtQuick.Window 2.2

Item {
    width: Screen.width
    height: Screen.height * 0.03
    Rectangle {
        anchors.fill: parent
//        color: "#fac834"
        color: "#004b8d"
        Text {
            id: time
            font.family: "arial"
            font.pointSize: 12
            color: "white"
            anchors.right: parent.right
            anchors.rightMargin: Screen.width * 0.05
            text: Qt.formatDateTime(new Date(),"hh:mm dd MMMM yyyy")
            //QDate::longMonthName
        }
        Timer {
            interval: 1000
            repeat: true
            running: true
            onTriggered: {
                //QDate::longMonthName()
                time.text = Qt.formatDateTime(new Date(),"hh:mm dd MMMM yyyy")
            }
        }
    }
}
