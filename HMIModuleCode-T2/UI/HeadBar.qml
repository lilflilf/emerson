import QtQuick 2.7
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.0
import QtQuick.Window 2.2

Item {
    z: 10
    id: headBar
    property alias titleText: title.text
    property var selectIndex: 0
    width: Screen.width
    height: 97//Screen.height * 0.07
//    Rectangle {
//        id: headBack
//        anchors.fill: parent
//        color: "#f79428"
//    }
    Image {
        id: headBack
        anchors.fill: parent
        source: "qrc:/images/images/headbg.png"
    }

    MouseArea {
        z: 9
        visible: btn.isCheck == true ? true : false
        width: Screen.width
        height: Screen.height
        onClicked: {
            btn.isCheck = false
            creatMenu.visible = false
            btnBack.visible = false
        }
    }

    Item {
        id: btn
        property bool isCheck: false
        height: 60//parent.height
        width: 60//parent.width * 0.05
        anchors.left: parent.left
        anchors.leftMargin: 30//parent.width * 0.02
        anchors.verticalCenter: parent.verticalCenter
        Rectangle {
            id: btnBack
            anchors.fill: parent
            color: "#404041"
            visible: false
        }
        Image {
            id: backGround
            anchors.fill: parent
            height: 60//parent.height-30
            width: 60//parent.width*0.68
            source: "qrc:/images/images/menu.png"
        }
//        Text {
//            id: menu
//            anchors.top: backGround.bottom
//            anchors.horizontalCenter: parent.horizontalCenter
//            text: qsTr("MENU")
//            color: "white"
//            font.pointSize: 12
//            font.family: "arial"
//        }
        MouseArea {
            anchors.fill: parent
            onClicked: {
                btn.isCheck = !btn.isCheck
                if (btn.isCheck){
                    btnBack.visible = true
                    mainMenu.mainModel = null
                    mainMenu.mainModel = listMainMenu
                }
                else
                {
                    btnBack.visible = false
                    creatMenu.visible = false
                }
            }
        }
    }

    Item {
        id: mainMenu
        property alias mainModel: mainModel.model
        width: 150
        height: 240
        anchors.top: btn.bottom
        anchors.left: btn.left
        visible: btn.isCheck ? true : false
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
                id: mainModel
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
                                        if (index == 0) {
                                            creatMenu.visible = true
                                            creatMenu.childModel = null
                                            creatMenu.childModel = creatMenuList
                                            creatMenu.height = creatMenuList.count * 40
                                        }
                                        else if (index == 3) {
                                            creatMenu.visible = true
                                            creatMenu.childModel = null
                                            creatMenu.childModel = maintenanceList
                                            creatMenu.height = maintenanceList.count * 40

                                        }
                                        else if (index == 4) {
                                            creatMenu.visible = true
                                            creatMenu.childModel = null
                                            creatMenu.childModel = viewDataList
                                            creatMenu.height = viewDataList.count * 40
                                        }
                                        else if (index == 5) {
                                            creatMenu.visible = true
                                            creatMenu.childModel = null
                                            creatMenu.childModel = settingList
                                            creatMenu.height = settingList.count * 40
                                        }
//                                        else if (index == 1) {
//                                            btn.isCheck = false
//                                            creatMenu.visible = false
//                                            btnBack.visible = false
//                                            root.menuInit(2)
//                                            console.log("3333333333333333333")
//                                            title.text = qsTr("Operate")
////                                            headBack.color = "blue"
//                                        }
//                                        else if (index == 2) {
//                                            btn.isCheck = false
//                                            creatMenu.visible = false
//                                            btnBack.visible = false
//                                            root.menuInit(3)
//                                            console.log("4444444444444444")
//                                        }
                                        headBar.selectIndex = index
                                        creatMenu.anchors.topMargin = index * 40

                                    }
                                    else {
                                        item.background = 0
                                        if (headBar.selectIndex == index)
                                            creatMenu.visible = false
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
                                if (index == 1) {
                                    btn.isCheck = false
                                    creatMenu.visible = false
                                    btnBack.visible = false
                                    root.menuInit(2)
                                    title.text = qsTr("Operate")
                                } else if (index == 2) {
                                    btn.isCheck = false
                                    creatMenu.visible = false
                                    btnBack.visible = false
                                    root.menuInit(3)
                                    title.text = qsTr("Test")
                                }
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
        ListElement {menuKey:"Tool Change"}
        ListElement {menuKey:"Advanced Maintenance"}
        ListElement {menuKey:"Maintenance Counter"}
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
        ListElement {menuKey:"Permission Setting"}
        ListElement {menuKey:"Weld Defaults"}
        ListElement {menuKey:"Operator Library"}
        ListElement {menuKey:"Data/Communication"}
        ListElement {menuKey:"Branson Setting"}

    }

    Item {
        id: creatMenu
        width: 200
        height: 80
        anchors.top: btn.bottom
        anchors.left: mainMenu.right
        anchors.leftMargin: 5
        visible: false
        z: 11
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
                                //mainMenu.visible = false
                                btn.isCheck = false
                                creatMenu.visible = false
                                btnBack.visible = false
                                if (menuKey == "Create New"){
                                    root.menuInit(0)
                                    title.text = qsTr("Creat Assembly")
                                }
                                else if (menuKey == "Edit Existing"){
                                    root.menuInit(1)
                                    title.text = qsTr("Edit Existing")
                                }
                                else if (menuKey == "Calibration"){
                                    root.menuInit(4)
                                    title.text = qsTr("Calibration")
                                }
                                else if (menuKey == "Tool Change"){
                                    root.menuInit(5)
                                    title.text = qsTr("Tool Change")
                                }
                                else if (menuKey == "Advanced Maintenance"){
                                    root.menuInit(6)
                                    title.text = qsTr("Advanced Maintenance")
                                }
                                else if (menuKey == "Maintenance Counter"){
                                    root.menuInit(7)
                                    title.text = qsTr("Maintenance Counter")
                                }
                                else if (menuKey == "Operator Library"){
                                    root.menuInit(16)
                                    title.text = qsTr("Operator Library")
                                }

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
        anchors.right: btn.left
        width: 40
        height: parent.height
        onClicked: {
            Qt.quit()
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
