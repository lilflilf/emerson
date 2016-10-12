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
//    Button {
//        id: btn
//        height: parent.height
//        width: parent.width * 0.1
//        anchors.left: parent.left
//        anchors.leftMargin: parent.width * 0.02
//        text: "Menu Button"
//        menu: Menu {
//            id: menu
//            MenuItem {text: "Button1";onTriggered: root.menuInit(3)}
//            MenuItem {text: "Button2";onTriggered: btn.text=text}
//            MenuItem {text: "Button3";onTriggered: btn.text=text}
//            MenuItem {text: "Button4";onTriggered: btn.text=text}

//        }
//    }
    Button {
        id: btn
        height: parent.height
        width: parent.width * 0.05
        anchors.left: parent.left
        anchors.leftMargin: parent.width * 0.02
        text: "Menu Button"
        checkable: true
    }
    Item {
        width: 150
        height: 200
        anchors.top: btn.bottom
        anchors.left: btn.left
        visible: btn.checked ? true : false
        Rectangle {
            anchors.fill: parent
            color: "black"
            opacity: 0.5
        }
        Column {
            anchors.fill: parent
            Item {
                id: item
                width: parent.width
                height: 40
                property bool check: false
                property alias background: rec.opacity
                Item {
                    anchors.fill: parent
                    Rectangle {
                        id: rec
                        anchors.fill: parent
                        color: "black"
                        opacity: 0
                    }
                    Text {
                        anchors.centerIn: parent
                        text: qsTr("Creat/Edit")
                        color: "white"
                        font.pointSize: 14
                        font.family: "arial"
                    }
                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            item.check = !item.check
                            if (item.check)
                                item.background = 0.5
                            else
                                item.background = 0
                        }
                    }
                }
            }
        }
    }

    CButton {
        anchors.left: btn.right
        width: 40
        height: parent.height
        onClicked: {
            root.menuInit(3)
        }
    }

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
