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
    Rectangle {
        id: headBack
        anchors.fill: parent
        color: (title.text == "Test" || title.text == "Create Assembly" || title.text == "Edit Existing") ? "#f79428" : "#0079c1"
    }
    //    Image {
    //        id: headBack
    //        anchors.fill: parent
    //        source: "qrc:/images/images/headbg.png"
    //    }

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
        width: 232
        height: 300
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
                listMainMenu.append({"menuName":"Create/Edit"})
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
                    height: 50
                    property bool check: false
                    property alias background: rec.opacity
                    Image {
                        anchors.fill: parent
                        source: "qrc:/images/images/menubg1.png"
                    }
                    Item {
                        anchors.fill: parent
                        Rectangle {
                            id: rec
                            anchors.fill: parent
                            opacity: 0
                            color: "#12648d"
                            RadioButton {
                                id: mainMenuCheck
                                visible: false
                                exclusiveGroup: wirePositionGroup
                                onCheckedChanged: {
                                    if (mainMenuCheck.checked) {
                                        if (index == 0) {
                                            creatMenu.visible = true
                                            creatMenu.childModel = null
                                            creatMenu.childModel = creatMenuList
                                            creatMenu.height = creatMenuList.count * 50
                                        }
                                        else if (index == 3) {
                                            creatMenu.visible = true
                                            creatMenu.childModel = null
                                            creatMenu.childModel = maintenanceList
                                            creatMenu.height = maintenanceList.count * 50

                                        }
                                        else if (index == 4) {
                                            creatMenu.visible = true
                                            creatMenu.childModel = null
                                            creatMenu.childModel = viewDataList
                                            creatMenu.height = viewDataList.count * 50
                                        }
                                        else if (index == 5) {
                                            creatMenu.visible = true
                                            creatMenu.childModel = null
                                            creatMenu.childModel = settingList
                                            creatMenu.height = settingList.count * 50
                                        }
                                        headBar.selectIndex = index
                                        creatMenu.anchors.topMargin = index * 50

                                    }
                                    else {
                                        rec.opacity = 0
                                        if (headBar.selectIndex == index)
                                            creatMenu.visible = false
                                    }
                                }
                            }
                        }
                        Text {
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.left: parent.left
                            anchors.leftMargin: 5
                            text: qsTr(menuName)//qsTr("Creat/Edit")
                            color: "white"
                            font.pointSize: 20
                            font.family: "arial"
                        }
                        MouseArea {
                            anchors.fill: parent
                            onPressed:  {
                                mainMenuCheck.checked = !mainMenuCheck.checked
                                rec.opacity = 1
                            }
                            onReleased: {
                                if (index == 1 || index == 2 ) {
                                    rec.opacity = 0
                                }
                            }
                            onClicked: {
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
                    Image {
                        source: "qrc:/images/images/right.png"
                        anchors.right: parent.right
                        anchors.rightMargin: 20
                        anchors.verticalCenter: parent.verticalCenter
                        visible: index == 1 || index == 2 ? false : true
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
        width: 310
        height: 100
        anchors.top: btn.bottom
        anchors.left: mainMenu.right
        anchors.leftMargin: 5
        visible: false
        z: 11
        property alias childModel: childMenu.model
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
                    property bool check: false
                    width: parent.width
                    height: 50
                    Image {
                        anchors.fill: parent
                        source: "qrc:/images/images/menubg1.png"
                        Rectangle {
                            id: rec2
                            anchors.fill: parent
                            color: "#12648d"
                            opacity: 0
                            RadioButton {
                                id: childMenuCheck
                                visible: false
                                exclusiveGroup: childPositionGroup
                            }
                        }
                        Text {
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.left: parent.left
                            anchors.leftMargin: 5
                            text: menuKey
                            color: "white"
                            font.pointSize: 20
                            font.family: "arial"
                        }
                        MouseArea {
                            anchors.fill: parent
                            onPressed: {
                                rec2.opacity = 1
                            }
                            onReleased: {
                                rec2.opacity = 0
                            }
                            onClicked: {
                                childMenuCheck.checked = !childMenuCheck.checked
                                btn.isCheck = false
                                creatMenu.visible = false
                                btnBack.visible = false
                                if (menuKey == "Create New"){
                                    root.menuInit(0)
                                    title.text = qsTr("Create Assembly")
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
                                else if (menuKey == "Maintenance log"){
                                    root.menuInit(8)
                                    title.text = qsTr("Maintenance log")
                                }
                                else if (menuKey == "Library") {
                                    root.menuInit(12)
                                    title.text = qsTr("Library")
                                }
                                else if (menuKey == "Version Information") {
                                    root.menuInit(13)
                                    title.text = qsTr("Version Information")
                                }
                                else if (menuKey == "Word Order History"){
                                    root.menuInit(9)
                                    title.text = qsTr("Word Order History")
                                }
                                else if (menuKey == "Statistical Trend"){
                                    root.menuInit(10)
                                    title.text = qsTr("Statistical Trend")
                                }
                                else if (menuKey == "Error/Alarm Log"){
                                    root.menuInit(11)
                                    title.text = qsTr("Error/Alarm Log")
                                }
                                else if (menuKey == "Permission Setting"){
                                    root.menuInit(14)
                                    title.text = qsTr("Permission Setting")
                                }
                                else if (menuKey == "Weld Defaults") {
                                    root.menuInit(15)
                                    title.text = qsTr("Weld Defaults")
                                }
                                else if (menuKey == "Operator Library"){
                                    root.menuInit(16)
                                    title.text = qsTr("Operator Library")
                                }
                                else if (menuKey == "Data/Communication") {
                                    root.menuInit(17)
                                    title.text = qsTr("Data Communication")
                                }
                                else if (menuKey == "Branson Setting") {
                                    root.menuInit(18)
                                    title.text = qsTr("Branson Setting")
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    //    CButton {
    //        anchors.right: btn.left
    //        width: 40
    //        height: parent.height
    //        onClicked: {
    //            Qt.quit()
    //        }
    //    }


    Text {
        id: title
        anchors.leftMargin: 20
        font.family: "arial"
        font.pointSize: 36
        color: "white"
        text: qsTr("Create Assembly")
        anchors.left: btn.right
        anchors.verticalCenter: parent.verticalCenter
    }
    Image {
        id: personButton
        anchors.top: parent.top
        anchors.topMargin: 6
        anchors.right: parent.right
        anchors.rightMargin: 20
        width: 70
        height: parent.height-16
        z: 14
        source: "qrc:/images/images/user.png"
        MouseArea {
            anchors.fill: parent
            onClicked: {
                background.visible = true
                dialog.visible = true
                okButton.visible = false
                helpTitle.visible = true
                helpTitle.text = "Current Operator: Jerry Wang"
                personColumn.visible = true
                background.opacity = 0.5
            }
            onPressed: {
                personButton.opacity = 0.5
            }
            onReleased: {
                personButton.opacity = 1
            }
        }
    }
    Image {
        id: helpButton
        anchors.top: parent.top
        anchors.topMargin: 6
        anchors.right: personButton.left
        anchors.rightMargin: 20
        width: 70
        height: parent.height-16
        z: 14
        source: "qrc:/images/images/help.png"
        MouseArea {
            anchors.fill: parent
            onClicked: {
                background.visible = true
                dialog.visible = true
                helpTitle.visible = true
                helpTitle.text = "Create Part:"
                helpValue.visible = true
                okButton.visible = true
                background.opacity = 0.5
            }
            onPressed: {
                helpButton.opacity = 0.5
            }
            onReleased: {
                helpButton.opacity = 1
            }
        }
    }
    Image {
        id: languageButton
        anchors.top: parent.top
        anchors.topMargin: 6
        anchors.right: helpButton.left
        anchors.rightMargin: 20
        width: 70
        height: parent.height-16
        z: 14
        source: "qrc:/images/images/guo1.png"
        MouseArea {
            anchors.fill: parent
            onClicked: {
                background.visible = true
                dialog.visible = true
                language.visible = true
                okButton.visible = true
                background.opacity = 0.5
            }
            onPressed: {
                languageButton.opacity = 0.5
            }
            onReleased: {
                languageButton.opacity = 1
            }
        }
    }
    Rectangle {
        id: background
        z: 18
        visible: false
        width: Screen.width
        height: Screen.height
        color: "black"
        opacity: 0
        MouseArea {
            anchors.fill: parent
        }
    }
    Rectangle {
        id: dialog
        visible: false
        anchors.top: parent.top
        anchors.topMargin: Screen.height/4
        anchors.left: parent.left
        anchors.leftMargin: Screen.width/3
        width: Screen.width/3
        height: Screen.height/2+30
        color: "#404041"
        z: background.z+1
        Grid {
            id: language
            property int selectIndex: -1
            visible: false
            anchors.top: parent.top
            anchors.topMargin: 10
            anchors.left: parent.left
            anchors.leftMargin: 8
            spacing: 10
            columns: 6
            rows: 5
            Repeater {
                id: languageRep
                model: 26
                delegate: Rectangle {
                    property string borderColor: "#404041"
                    width: 65
                    height: 55
                    color: "#404041"
                    border.width: 1
                    border.color: borderColor
                    Image {
                        anchors.centerIn: parent
                        width: 59
                        height: 49
                        source: "qrc:/images/images/guo2.png"
                        MouseArea {
                            anchors.fill: parent
                            onClicked: {
                                if (language.selectIndex == -1) {
                                    languageRep.itemAt(index).borderColor = "yellow"
                                    language.selectIndex = index
                                } else {
                                    languageRep.itemAt(language.selectIndex).borderColor = "#404041"
                                    language.selectIndex = index
                                    languageRep.itemAt(index).borderColor = "yellow"
                                }
                            }
                        }
                    }
                }
            }
        }
        Text {
            id: helpTitle
            visible: false
            anchors.top: parent.top
            anchors.topMargin: 20
            anchors.left: parent.left
            anchors.leftMargin: 20
            font.pixelSize: 20
            font.family: "arial"
            color: "white"
            text: qsTr("Create Part:")
        }
        Text {
            id: helpValue
            visible: false
            anchors.top: helpTitle.bottom
            anchors.topMargin: 30
            anchors.left: helpTitle.left
            width: parent.width - 40
            font.pixelSize: 20
            font.family: "arial"
            color: "white"
            wrapMode: Text.WordWrap
            text: qsTr("-Add New Splice: add new splice\n-Add Existing Splice: add existing splice from the splice library")
        }
        Column {
            id: personColumn
            visible: false
            anchors.top: helpTitle.bottom
            anchors.topMargin: 50
            anchors.left: parent.left
            anchors.leftMargin: 40
            width: parent.width-80
            spacing: 30
            CButton {
                width: parent.width
                textColor: "white"
                text: qsTr("Switch User")
                onClicked: {
                    root.logoff()

                    personColumn.visible = false
                    background.visible = false
                    helpTitle.visible = false
                    background.opacity = 0
                    dialog.visible = false
                }
            }
            //            CButton {
            //                width: parent.width
            //                textColor: "white"
            //                text: qsTr("Log Off")
            //                onClicked: {
            //                    root.logoff()

            //                    personColumn.visible = false
            //                    background.visible = false
            //                    helpTitle.visible = false
            //                    background.opacity = 0
            //                    dialog.visible = false
            //                }
            //            }
            CButton {
                width: parent.width
                textColor: "white"
                text: qsTr("Shut Down")
                onClicked: {
                    Qt.quit()
                }
            }
            CButton {
                width: parent.width
                textColor: "white"
                text: qsTr("Cancel")
                onClicked: {
                    personColumn.visible = false
                    background.visible = false
                    helpTitle.visible = false
                    background.opacity = 0
                    dialog.visible = false
                }
            }
        }

        CButton {
            id: okButton
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 12
            anchors.right: parent.right
            anchors.rightMargin: 20
            width: 200
            height: 60
            iconSource: "qrc:/images/images/OK.png"
            text: qsTr("OK")
            onClicked: {
                dialog.visible = false
                background.visible = false
                language.visible = false
                helpTitle.visible = false
                helpValue.visible = false
                background.opacity = 0
            }
        }
    }
}
