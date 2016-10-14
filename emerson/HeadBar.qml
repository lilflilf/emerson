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

    Item {
        id: btn
        height: parent.height
        width: parent.width * 0.05
        anchors.left: parent.left
        anchors.leftMargin: parent.width * 0.02
        Image {
            id: backGround
            anchors.top: parent.top
            anchors.topMargin: 6
            height: parent.height-30
            width: parent.width*0.68
            anchors.left: parent.left
            source: "qrc:/Images/images/menu.png"
        }
        Text {
            id: menu
            anchors.top: backGround.bottom
            anchors.left: parent.left
            anchors.leftMargin: parent.width * 0.02
            text: qsTr("MENU")
            color: "white"
            font.pointSize: 12
            font.family: "arial"
        }
        MouseArea {
            anchors.fill: parent
        }
    }

//    Button {
//        id: btn
//        height: parent.height
//        width: parent.width * 0.05
//        anchors.left: parent.left
//        anchors.leftMargin: parent.width * 0.02
//        text: "Menu Button"
//        checkable: true
//    }
    Item {
        id: mainMenu
        width: 150
        height: 240
        anchors.top: btn.bottom
        anchors.left: btn.left
        visible: btn.checked ? true : false
        z: 10
        Rectangle {
            anchors.fill: parent
            color: "#58585a"
        }
        ListModel {
            id: listMainMenu
            Component.onCompleted: {
                listMainMenu.append({"menuName":"Creat/Edit"})
                listMainMenu.append({"menuName":"Operate"})
                listMainMenu.append({"menuName":"Test"})
                listMainMenu.append({"menuName":"Maintenance"})
                listMainMenu.append({"menuName":"View Data"})
                listMainMenu.append({"menuName":"Settings"})
            }
        }
        ExclusiveGroup {
            id: wirePositionGroup;
        }

        Column {
            anchors.fill: parent
            Repeater {
                model: listMainMenu
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
                            RadioButton {
                                id: mainMenuCheck
                                visible: false
                                exclusiveGroup: wirePositionGroup
                                onCheckedChanged: {
                                    if (mainMenuCheck.checked) {
                                        item.background = 0.5
                                        console.log("index == ",index)
                                        if (index == 0) {
                                            creatMenu.visible = true
                                            creatMenu.childModel = creatMenuList
                                            creatMenu.height = creatMenuList.count * 40
                                        }
                                        else if (index == 3) {
                                            creatMenu.visible = true
                                            creatMenu.childModel = maintenanceList
                                            creatMenu.height = maintenanceList.count * 40

                                        }
                                        else if (index == 4) {
                                            creatMenu.visible = true
                                            creatMenu.childModel = viewDataList
                                            creatMenu.height = viewDataList.count * 40
                                        }
                                        else if (index == 5) {
                                            creatMenu.visible = true
                                            creatMenu.childModel = settingList
                                            creatMenu.height = settingList.count * 40
                                        }
                                        else if (index == 1 || index == 2)
                                            creatMenu.visible = false

                                    }
                                    else {
                                        console.log("index ==== ",index)
                                        item.background = 0
                                        //creatMenu.visible = false
                                    }
                                }
                            }
                        }
                        Text {
                            anchors.centerIn: parent
                            text: qsTr(menuName)//qsTr("Creat/Edit")
                            color: "white"
                            font.pointSize: 14
                            font.family: "arial"
                        }
                        MouseArea {
                            anchors.fill: parent
                            onClicked: {
                                mainMenuCheck.checked = !mainMenuCheck.checked
                            }
                        }
                    }
                }
            }
        }
    }

    ListModel {
        id: creatMenuList
        ListElement {menuKey:"Create New"}
        ListElement {menuKey:"Edit Existing"}
    }
    ListModel {
        id: maintenanceList
        ListElement {menuKey:"Calibration"}
        ListElement {menuKey:"Advanced Maintenance"}
        ListElement {menuKey:"Maintenance counter"}
        ListElement {menuKey:"Maintenance log"}
    }
    ListModel {
        id: viewDataList
        ListElement {menuKey:"Word Order History"}
        ListElement {menuKey:"Statistical Trend"}
        ListElement {menuKey:"Error/Alarm Log"}
        ListElement {menuKey:"Library"}
        ListElement {menuKey:"Version Information"}

    }
    ListModel {
        id: settingList
        ListElement {menuKey:"Admin"}
        ListElement {menuKey:"Weld Defaults"}
        ListElement {menuKey:"Sequence Defaults"}
        ListElement {menuKey:"Data/Communication"}
    }

    Item {
        id: creatMenu
        width: 200
        height: 80
        anchors.top: btn.bottom
        anchors.left: mainMenu.right
        anchors.leftMargin: 5
        visible: false
        z: 10
        property alias childModel: childMenu.model
        Rectangle {
            anchors.fill: parent
            color: "#58585a"
        }
        ExclusiveGroup {
            id: childPositionGroup;
        }
        Column {
            anchors.fill: parent
            Repeater {
                id: childMenu
                model: creatMenuList

                Item {
                    id: itemChild
                    width: parent.width
                    height: 40
                    property bool check: false
                    property alias background: childRec.opacity
                    Item {
                        anchors.fill: parent
                        Rectangle {
                            id: childRec
                            anchors.fill: parent
                            color: "black"
                            opacity: 0
                        }
                        Text {
                            anchors.centerIn: parent
                            text: menuKey //qsTr("Creat New")//qsTr("Creat/Edit")
                            color: "white"
                            font.pointSize: 14
                            font.family: "arial"
                        }
                        MouseArea {
                            anchors.fill: parent
                            onClicked: {
                                childMenuCheck.checked = !childMenuCheck.checked
                            }
                        }
                        RadioButton {
                            id: childMenuCheck
                            visible: false
                            exclusiveGroup: childPositionGroup
                            onCheckedChanged: {
                                if (childMenuCheck.checked)
                                    childRec.opacity = 0.5
                                else
                                    childRec.opacity = 0
                            }
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
