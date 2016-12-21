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
        color: "#0079c1" //(title.text == qsTr("Test") || title.text == qsTr("Create New") || title.text == qsTr("Edit Existing")) ? "#f79428" : "#0079c1"
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
            color: "#052a40"
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
                listMainMenu.append({"menuName":qsTr("Create/Edit")})
                listMainMenu.append({"menuName":qsTr("Test")})
                listMainMenu.append({"menuName":qsTr("Operate")})
                listMainMenu.append({"menuName":qsTr("View Data")})
                listMainMenu.append({"menuName":qsTr("Maintenance")})
                listMainMenu.append({"menuName":qsTr("Settings")})
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
                                        else if (index == 4) {
                                            creatMenu.visible = true
                                            creatMenu.childModel = null
                                            creatMenu.childModel = maintenanceList
                                            creatMenu.height = maintenanceList.count * 50

                                        }
                                        else if (index == 3) {
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
                            text: menuName
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
                                if (index == 2) {
                                    btn.isCheck = false
                                    creatMenu.visible = false
                                    btnBack.visible = false
                                    root.menuInit(2)
                                    title.text = qsTr("Operate")
                                } else if (index == 1) {
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
        ListElement {menuKey:qsTr("Create New")}
        ListElement {menuKey:qsTr("Edit Existing")}
    }
    ListModel {
        id: maintenanceList
        ListElement {menuKey:qsTr("Calibration")}
        ListElement {menuKey:qsTr("Tool Change")}
        ListElement {menuKey:qsTr("Advanced Maintenance")}
        ListElement {menuKey:qsTr("Maintenance Counter")}
        ListElement {menuKey:qsTr("Maintenance log")}
    }
    ListModel {
        id: viewDataList
        ListElement {menuKey:qsTr("Work Order History")}
        ListElement {menuKey:qsTr("Statistical Trend")}
        ListElement {menuKey:qsTr("Error/Alarm Log")}
        ListElement {menuKey:qsTr("Library")}
        ListElement {menuKey:qsTr("Version Information")}

    }
    ListModel {
        id: settingList
        ListElement {menuKey:qsTr("Permission Setting")}
        ListElement {menuKey:qsTr("Weld Defaults")}
        ListElement {menuKey:qsTr("Operator Library")}
        ListElement {menuKey:qsTr("Data/Communication")}
//        ListElement {menuKey:"Branson Setting"}

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
                                if (menuKey == qsTr("Create New")){
                                    root.menuInit(0)
                                    title.text = qsTr("Create New")
                                }
                                else if (menuKey == qsTr("Edit Existing")){
                                    root.menuInit(1)
                                    title.text = qsTr("Edit Existing")
                                }
                                else if (menuKey == qsTr("Calibration")){
                                    root.menuInit(4)
                                    title.text = qsTr("Calibration")
                                }
                                else if (menuKey == qsTr("Tool Change")){
                                    root.menuInit(5)
                                    title.text = qsTr("Tool Change")
                                }
                                else if (menuKey == qsTr("Advanced Maintenance")){
                                    root.menuInit(6)
                                    title.text = qsTr("Advanced Maintenance")
                                }
                                else if (menuKey == qsTr("Maintenance Counter")){
                                    root.menuInit(7)
                                    title.text = qsTr("Maintenance Counter")
                                }
                                else if (menuKey == qsTr("Maintenance log")){
                                    root.menuInit(8)
                                    title.text = qsTr("Maintenance log")
                                }
                                else if (menuKey == qsTr("Library")) {
                                    root.menuInit(12)
                                    title.text = qsTr("Library")
                                }
                                else if (menuKey == qsTr("Version Information")) {
                                    root.menuInit(13)
                                    title.text = qsTr("Version Information")
                                }
                                else if (menuKey == qsTr("Work Order History")){
                                    root.menuInit(9)
                                    title.text = qsTr("Work Order History")
                                }
                                else if (menuKey == qsTr("Statistical Trend")){
                                    root.menuInit(10)
                                    title.text = qsTr("Statistical Trend")
                                }
                                else if (menuKey == qsTr("Error/Alarm Log")){
                                    root.menuInit(11)
                                    title.text = qsTr("Error/Alarm Log")
                                }
                                else if (menuKey == qsTr("Permission Setting")){
                                    root.menuInit(14)
                                    title.text = qsTr("Permission Setting")
                                }
                                else if (menuKey == qsTr("Weld Defaults")) {
                                    root.menuInit(15)
                                    title.text = qsTr("Weld Defaults")
                                }
                                else if (menuKey == qsTr("Operator Library")){
                                    root.menuInit(16)
                                    title.text = qsTr("Operator Library")
                                }
                                else if (menuKey == qsTr("Data/Communication")) {
                                    root.menuInit(17)
                                    title.text = qsTr("Data Communication")
                                }
//                                else if (menuKey == "Branson Setting") {
//                                    root.menuInit(18)
//                                    title.text = qsTr("Branson Setting")
//                                }
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
        text: qsTr("Create New")
        anchors.left: btn.right
        anchors.verticalCenter: parent.verticalCenter
    }
    Image {
        id: personButton
        anchors.right: parent.right
        anchors.rightMargin: 20
        height: 60
        width: 60
        z: 14
        source: "qrc:/images/images/person.png"
        anchors.verticalCenter: parent.verticalCenter
        MouseArea {
            anchors.fill: parent
            onClicked: {
                background.visible = true
                dialog.visible = true
                okButton.visible = false
                helpTitle.visible = true
                helpTitle.text = qsTr("Current Operator: ") + hmiAdaptor.getCurrentOperatorId() //Jerry Wang"
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
        anchors.right: personButton.left
        anchors.rightMargin: 20
        z: 14
        height: 60
        width: 60
        source: "qrc:/images/images/help.png"
        anchors.verticalCenter: parent.verticalCenter
        MouseArea {
            anchors.fill: parent
            onClicked: {
                background.visible = true
                dialog.visible = true
                helpTitle.visible = true
                helpTitle.text = qsTr("Create Part:")
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
        anchors.right: helpButton.left
        anchors.rightMargin: 20
        z: 14
        source: "qrc:/images/images/English.png"
        anchors.verticalCenter: parent.verticalCenter
        height: 80
        width: 80
        MouseArea {
            anchors.fill: parent
            onClicked: {
                background.visible = true
                background.opacity = 0.7
                dialog.visible = true
                language.visible = true
                okButton.visible = true
            }
            onPressed: {
                languageButton.opacity = 0.5
            }
            onReleased: {
                languageButton.opacity = 1
            }
        }
    }
    Image {
        id: alarmButton
        anchors.right: languageButton.left
        anchors.rightMargin: 20
        z: 14
        source: "qrc:/images/images/alarm.png"
        anchors.verticalCenter: parent.verticalCenter
        height: 80
        width: 80
        MouseArea {
            anchors.fill: parent

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
    ListModel {
        id: listModel
        Component.onCompleted: {
            listModel.append({"iconsource":"qrc:/images/images/Arabic.png","selectlanguage":"Arabic"})
            listModel.append({"iconsource":"qrc:/images/images/United-Arab-Emirates.png","selectlanguage":"Arabic"})
            listModel.append({"iconsource":"qrc:/images/images/chinese.png","selectlanguage":"Chinese"})
            listModel.append({"iconsource":"qrc:/images/images/chinese.png","selectlanguage":"Chinese(TaiWan)"})
            listModel.append({"iconsource":"qrc:/images/images/Czech.png","selectlanguage":"Czech"})
            listModel.append({"iconsource":"qrc:/images/images/dutch.png","selectlanguage":"Dutch"})
            listModel.append({"iconsource":"qrc:/images/images/australia.png","selectlanguage":"EngLish"})
            listModel.append({"iconsource":"qrc:/images/images/Canada.png","selectlanguage":"EngLish"})
            listModel.append({"iconsource":"qrc:/images/images/Hindi.png","selectlanguage":"EngLish"})
            listModel.append({"iconsource":"qrc:/images/images/English.png","selectlanguage":"EngLish"})
            listModel.append({"iconsource":"qrc:/images/images/us.png","selectlanguage":"EngLish"})
            listModel.append({"iconsource":"qrc:/images/images/Canada.png","selectlanguage":"French"})
            listModel.append({"iconsource":"qrc:/images/images/french.png","selectlanguage":"French"})
            listModel.append({"iconsource":"qrc:/images/images/German.png","selectlanguage":"German"})
            listModel.append({"iconsource":"qrc:/images/images/Hindi.png","selectlanguage":"Hindi"})
            listModel.append({"iconsource":"qrc:/images/images/Hungarian.png","selectlanguage":"Hungarian"})
            listModel.append({"iconsource":"qrc:/images/images/Indonesian.png","selectlanguage":"Indonesian"})
            listModel.append({"iconsource":"qrc:/images/images/Italian.png","selectlanguage":"Italian"})
            listModel.append({"iconsource":"qrc:/images/images/Japanese.png","selectlanguage":"Japanese"})
            listModel.append({"iconsource":"qrc:/images/images/Korean.png","selectlanguage":"Korean"})
            listModel.append({"iconsource":"qrc:/images/images/Malaysian.png","selectlanguage":"Malaysian"})
            listModel.append({"iconsource":"qrc:/images/images/polish.png","selectlanguage":"Polish"})
            listModel.append({"iconsource":"qrc:/images/images/Portuguese.png","selectlanguage":"Portuguese"})
            listModel.append({"iconsource":"qrc:/images/images/Brazil.png","selectlanguage":"Portuguese"})
            listModel.append({"iconsource":"qrc:/images/images/Romanian.png","selectlanguage":"Romanian"})
            listModel.append({"iconsource":"qrc:/images/images/russian.png","selectlanguage":"Russian"})
            listModel.append({"iconsource":"qrc:/images/images/Slovak.png","selectlanguage":"Slovak"})
            listModel.append({"iconsource":"qrc:/images/images/Spanish.png","selectlanguage":"Spanish"})
            listModel.append({"iconsource":"qrc:/images/images/Mexcio.png","selectlanguage":"Spanish"})
            listModel.append({"iconsource":"qrc:/images/images/Thai.png","selectlanguage":"Thai"})
            listModel.append({"iconsource":"qrc:/images/images/Turkish.png","selectlanguage":"Turkish"})
            listModel.append({"iconsource":"qrc:/images/images/Vietnam.png","selectlanguage":"Vietnam"})
        }
    }

    Image {
        id: dialog
        visible: false
        anchors.top: parent.top
        anchors.topMargin: (Screen.height-dialog.height)/2
        anchors.left: parent.left
        anchors.leftMargin: (Screen.width - dialog.width)/2
        width: languageRep.visible ? 1270 : 700
        height: languageRep.visible ? 659 : 525
        source: "qrc:/images/images/dialogbg.png"
        z: background.z+1
        Grid {
            id: language
            property int selectIndex: -1
            visible: false
            anchors.top: parent.top
            anchors.topMargin: 30
            anchors.left: parent.left
            anchors.leftMargin: (parent.width-8*135)/2
            columns: 8
            rows: 4
            Repeater {
                id: languageRep
                model: listModel
                delegate: Rectangle {
                    property string backColor: "black"
                    id: languageRec
                    width: 135
                    height: 135
                    color: backColor
                    border.width: 1
                    border.color: "#0079C1"
                    Image {
                        anchors.centerIn: parent
                        source: iconsource
                        MouseArea {
                            anchors.fill: parent
                            onClicked: {
                                if (language.selectIndex == -1) {
                                    languageRep.itemAt(index).backColor = "#29afff"
                                    languageRep.itemAt(index).opacity = 0.5
                                    language.selectIndex = index
                                } else {
                                    languageRep.itemAt(language.selectIndex).opacity = 1
                                    languageRep.itemAt(language.selectIndex).backColor = "black"
                                    languageRep.itemAt(index).opacity = 0.5
                                    languageRep.itemAt(index).backColor = "#29afff"
                                    language.selectIndex = index
                                }
                            }
                        }
                    }
                    Text {
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.bottom: parent.bottom
                        anchors.bottomMargin: 6
                        font.family: "arial"
                        font.pixelSize: 20
                        color: "white"
                        text: selectlanguage
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
            font.pixelSize: 24
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
            anchors.topMargin: 100
            anchors.left: parent.left
            anchors.leftMargin: 80
            width: parent.width-160
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
            CButton {
                width: parent.width
                textColor: "white"
                text: qsTr("Shut Down")
                onClicked: {
                    hmiAdaptor.quit()
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
            anchors.bottomMargin: 24
            anchors.right: parent.right
            anchors.rightMargin: language.visible ? (parent.width-8*148)/2 : 30
            width: 180
            iconSource: "qrc:/images/images/OK.png"
            text: qsTr("OK")
            onClicked: {
                if (languageRep.visible ) {
                    languageButton.source = listModel.get(language.selectIndex).iconsource
                }
                dialog.visible = false
                background.visible = false
                language.visible = false
                helpTitle.visible = false
                helpValue.visible = false
                background.opacity = 0
            }
        }
        CButton {
            id: cancelButton
            anchors.bottom: okButton.bottom
            anchors.right: okButton.left
            anchors.rightMargin: 20
            width: 180
            visible: languageRep.visible
            iconSource: "qrc:/images/images/cancel.png"
            text: qsTr("Cancel")
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
