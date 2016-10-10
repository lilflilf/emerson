import QtQuick 2.4
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2
import QtQuick.Controls 1.4

Item {
    width: Screen.desktopAvailableWidth * 0.8
    height: Screen.desktopAvailableHeight *0.5

    Rectangle {
        id: lineLeft
        width: 2
        height: parent.height
        anchors.left: parent.left
        anchors.leftMargin: parent.width / 2 - 40
    }
    Rectangle {
        id: lineRight
        width: 2
        height: parent.height
        anchors.left: parent.left
        anchors.leftMargin: parent.width / 2 + 40
    }

    Item {
        id: top
        width: parent.width
        height: parent.height * 0.1
        Rectangle {
            anchors.fill: parent
        }
        opacity: 0.1
    }
    Item {
        id: bottom
        width: parent.width
        height: parent.height * 0.1
        anchors.bottom: parent.bottom
        Rectangle {
            anchors.fill: parent
        }
        opacity: 0.1
    }
    Item {
        id: middle
        width: parent.width
        height: parent.height * 0.7
        anchors.top: top.bottom
        anchors.topMargin: parent.height * 0.1 / 2
        Rectangle {
            anchors.fill: parent
            color: "black"
            opacity: 0.2
        }

        CButton {
            anchors.centerIn: parent
            width: 60
            height: 40
            onClicked: {
//                adaptor.openFileDialog();
                fileDialog.open()
                //loadder.source = "qrc:/MyFileDialog.qml"
            }
        }
        FileDialog {
               id: fileDialog
               title: "Please choose a file"
               onAccepted: {
                   //path = fileDialog.fileUrls[0].toString();
                   console.log("You chose: ",fileDialog.fileUrls)
               }
               onRejected: {
                   console.log("Canceled")
               }
           }
        Loader {
            id: loadder
            anchors.fill: parent
        }
    }
}
