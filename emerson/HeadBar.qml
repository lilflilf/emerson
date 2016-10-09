import QtQuick 2.7
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.0
import QtQuick.Window 2.2

Item {
    width: Screen.desktopAvailableWidth
    height: Screen.desktopAvailableHeight * 0.07
    Rectangle {
        anchors.fill: parent
        color: "#f79428"
    }

//    CButton {
//        width: 40
//        height: parent.height
//        onClicked: {
//            root.close()
//        }
//    }
    Button {
        id: btn
        height: parent.height
        width: parent.width * 0.1
        anchors.left: parent.left
        anchors.leftMargin: parent.width * 0.02
        text: "Menu Button"
        menu: Menu {
            id: menu

            MenuItem {text: "Button1";onTriggered: root.menuInit(3)}
            MenuItem {text: "Button2";onTriggered: btn.text=text}
            MenuItem {text: "Button3";onTriggered: btn.text=text}
            MenuItem {text: "Button4";onTriggered: btn.text=text}

        }
    }
//    CButton {
//        anchors.left: btn.right
//        width: 40
//        height: parent.height
//        onClicked: {
//            root.menuInit(3)
//        }
//    }

    Text {
        id: title
        anchors.leftMargin: 20
        font.family: "arial"
        font.pointSize: 36
        color: "white"
        text: qsTr("Creat Assembly")
        anchors.left: btn.right
        anchors.verticalCenter: parent.verticalCenter
    }
}
