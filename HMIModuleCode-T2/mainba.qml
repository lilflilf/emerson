import QtQuick 2.5
import QtQuick.Window 2.2
import UI.Utility 1.0

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    MainForm {
        anchors.fill: parent
        Utility{
            id:utility
        }
        Text{
            id:timeLabel
            anchors.right:parent.right
            anchors.rightMargin: 10
            color: "white"
            font.family: "Arial"
            font.bold: true
            font.pixelSize: 15
        }

        Connections{
            target: utility
            onCurrentTime:{
                console.log("Call CurrentTime")
                timeLabel.text = strTime;
            }
        }
    }

}
