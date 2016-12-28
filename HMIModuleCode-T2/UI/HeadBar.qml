/*******************************************************************
Copyright:http://www.sinux.com.cn
Date:2016/12/26
Author:zhangjiyong&lilongfei
Description:title bar component,contains help&waring&language info,
menu is from listMainMenu&creatMenuList&maintenanceList&viewDataList&
settingList,language is from listModel
The function interface:
    root.checkNeedPassWd()
    hmiAdaptor.getCurrentOperatorId()
*******************************************************************/
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
                                    root.checkNeedPassWd(2)
//                                    title.text = qsTr("Operate")
                                } else if (index == 1) {
                                    btn.isCheck = false
                                    creatMenu.visible = false
                                    btnBack.visible = false
                                    root.checkNeedPassWd(3)
//                                    title.text = qsTr("Test")
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
                                    root.checkNeedPassWd(0)
//                                    title.text = qsTr("Create New")
                                }
                                else if (menuKey == qsTr("Edit Existing")){
                                    root.checkNeedPassWd(1)
//                                    title.text = qsTr("Edit Existing")
                                }
                                else if (menuKey == qsTr("Calibration")){
                                    root.checkNeedPassWd(4)
//                                    title.text = qsTr("Calibration")
                                }
                                else if (menuKey == qsTr("Tool Change")){
                                    root.checkNeedPassWd(5)
//                                    title.text = qsTr("Tool Change")
                                }
                                else if (menuKey == qsTr("Advanced Maintenance")){
                                    root.checkNeedPassWd(6)
//                                    title.text = qsTr("Advanced Maintenance")
                                }
                                else if (menuKey == qsTr("Maintenance Counter")){
                                    root.checkNeedPassWd(7)
//                                    title.text = qsTr("Maintenance Counter")
                                }
                                else if (menuKey == qsTr("Maintenance log")){
                                    root.checkNeedPassWd(8)
//                                    title.text = qsTr("Maintenance log")
                                }
                                else if (menuKey == qsTr("Library")) {
                                    root.checkNeedPassWd(12)
//                                    title.text = qsTr("Library")
                                }
                                else if (menuKey == qsTr("Version Information")) {
                                    root.checkNeedPassWd(13)
//                                    title.text = qsTr("Version Information")
                                }
                                else if (menuKey == qsTr("Work Order History")){
                                    root.checkNeedPassWd(9)
//                                    title.text = qsTr("Work Order History")
                                }
                                else if (menuKey == qsTr("Statistical Trend")){
                                    root.checkNeedPassWd(10)
//                                    title.text = qsTr("Statistical Trend")
                                }
                                else if (menuKey == qsTr("Error/Alarm Log")){
                                    root.checkNeedPassWd(11)
//                                    title.text = qsTr("Error/Alarm Log")
                                }
                                else if (menuKey == qsTr("Permission Setting")){
                                    root.checkNeedPassWd(14)
//                                    title.text = qsTr("Permission Setting")
                                }
                                else if (menuKey == qsTr("Weld Defaults")) {
                                    root.checkNeedPassWd(15)
//                                    title.text = qsTr("Weld Defaults")
                                }
                                else if (menuKey == qsTr("Operator Library")){
                                    root.checkNeedPassWd(16)
//                                    title.text = qsTr("Operator Library")
                                }
                                else if (menuKey == qsTr("Data/Communication")) {
                                    root.checkNeedPassWd(17)
//                                    title.text = qsTr("Data Communication")
                                }
//                                else if (menuKey == "Branson Setting") {
//                                    root.checkNeedPassWd(18)
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
                helpTitle.text = qsTr("Current Operator: ") + hmiAdaptor.getCurrentOperatorName() //Jerry Wang"
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
            onClicked: {
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
    ListModel {
        id: listModel
        Component.onCompleted: {
            listModel.append({"row":"1","subNode":[]})
            listModel.append({"row":"2","subNode":[]})
            listModel.append({"row":"3","subNode":[]})
            listModel.append({"row":"4","subNode":[]})
            listModel.append({"row":"5","subNode":[]})
            listModel.append({"row":"6","subNode":[]})
            listModel.get(0).subNode.append({"iconsource":"qrc:/images/images/Arabic.png","selectlanguage":"Arabic","backColor":"black","theopacity":"1"})
            listModel.get(0).subNode.append({"iconsource":"qrc:/images/images/United-Arab-Emirates.png","selectlanguage":"Arabic","backColor":"black","theopacity":"1"})
            listModel.get(0).subNode.append({"iconsource":"qrc:/images/images/chinese.png","selectlanguage":"Chinese","backColor":"black","theopacity":"1"})
            listModel.get(0).subNode.append({"iconsource":"qrc:/images/images/chinese.png","selectlanguage":"Chinese(TaiWan)","backColor":"black","theopacity":"1"})
            listModel.get(0).subNode.append({"iconsource":"qrc:/images/images/Czech.png","selectlanguage":"Czech","backColor":"black","theopacity":"1"})
            listModel.get(0).subNode.append({"iconsource":"qrc:/images/images/dutch.png","selectlanguage":"Dutch","backColor":"black","theopacity":"1"})
            listModel.get(0).subNode.append({"iconsource":"qrc:/images/images/australia.png","selectlanguage":"EngLish","backColor":"black","theopacity":"1"})
            listModel.get(1).subNode.append({"iconsource":"qrc:/images/images/Canada.png","selectlanguage":"EngLish","backColor":"black","theopacity":"1"})
            listModel.get(1).subNode.append({"iconsource":"qrc:/images/images/Hindi.png","selectlanguage":"EngLish","backColor":"black","theopacity":"1"})
            listModel.get(1).subNode.append({"iconsource":"qrc:/images/images/English.png","selectlanguage":"EngLish","backColor":"black","theopacity":"1"})
            listModel.get(1).subNode.append({"iconsource":"qrc:/images/images/us.png","selectlanguage":"EngLish","backColor":"black","theopacity":"1"})
            listModel.get(1).subNode.append({"iconsource":"qrc:/images/images/us&English.png","selectlanguage":"EngLish","backColor":"black","theopacity":"1"})
            listModel.get(1).subNode.append({"iconsource":"qrc:/images/images/Canada.png","selectlanguage":"French","backColor":"black","theopacity":"1"})
            listModel.get(1).subNode.append({"iconsource":"qrc:/images/images/french.png","selectlanguage":"French","backColor":"black","theopacity":"1"})
            listModel.get(2).subNode.append({"iconsource":"qrc:/images/images/Canada&french.png","selectlanguage":"French","backColor":"black","theopacity":"1"})
            listModel.get(2).subNode.append({"iconsource":"qrc:/images/images/German.png","selectlanguage":"German","backColor":"black","theopacity":"1"})
            listModel.get(2).subNode.append({"iconsource":"qrc:/images/images/Hindi.png","selectlanguage":"Hindi","backColor":"black","theopacity":"1"})
            listModel.get(2).subNode.append({"iconsource":"qrc:/images/images/Hungarian.png","selectlanguage":"Hungarian","backColor":"black","theopacity":"1"})
            listModel.get(2).subNode.append({"iconsource":"qrc:/images/images/Indonesian.png","selectlanguage":"Indonesian","backColor":"black","theopacity":"1"})
            listModel.get(2).subNode.append({"iconsource":"qrc:/images/images/Italian.png","selectlanguage":"Italian","backColor":"black","theopacity":"1"})
            listModel.get(2).subNode.append({"iconsource":"qrc:/images/images/Japanese.png","selectlanguage":"Japanese","backColor":"black","theopacity":"1"})
            listModel.get(3).subNode.append({"iconsource":"qrc:/images/images/Korean.png","selectlanguage":"Korean","backColor":"black","theopacity":"1"})
            listModel.get(3).subNode.append({"iconsource":"qrc:/images/images/Malaysian.png","selectlanguage":"Malaysian","backColor":"black","theopacity":"1"})
            listModel.get(3).subNode.append({"iconsource":"qrc:/images/images/polish.png","selectlanguage":"Polish","backColor":"black","theopacity":"1"})
            listModel.get(3).subNode.append({"iconsource":"qrc:/images/images/Portuguese.png","selectlanguage":"Portuguese","backColor":"black","theopacity":"1"})
            listModel.get(3).subNode.append({"iconsource":"qrc:/images/images/Brazil.png","selectlanguage":"Portuguese","backColor":"black","theopacity":"1"})
            listModel.get(3).subNode.append({"iconsource":"qrc:/images/images/Portuguese&Brazil.png","selectlanguage":"Portuguese","backColor":"black","theopacity":"1"})
            listModel.get(3).subNode.append({"iconsource":"qrc:/images/images/Romanian.png","selectlanguage":"Romanian","backColor":"black","theopacity":"1"})
            listModel.get(4).subNode.append({"iconsource":"qrc:/images/images/russian.png","selectlanguage":"Russian","backColor":"black","theopacity":"1"})
            listModel.get(4).subNode.append({"iconsource":"qrc:/images/images/Slovak.png","selectlanguage":"Slovak","backColor":"black","theopacity":"1"})
            listModel.get(4).subNode.append({"iconsource":"qrc:/images/images/Spanish.png","selectlanguage":"Spanish","backColor":"black","theopacity":"1"})
            listModel.get(4).subNode.append({"iconsource":"qrc:/images/images/Mexcio.png","selectlanguage":"Spanish","backColor":"black","theopacity":"1"})
            listModel.get(4).subNode.append({"iconsource":"qrc:/images/images/Spanish&Mexcio.png","selectlanguage":"Spanish","backColor":"black","theopacity":"1"})
            listModel.get(4).subNode.append({"iconsource":"qrc:/images/images/Thai.png","selectlanguage":"Thai","backColor":"black","theopacity":"1"})
            listModel.get(4).subNode.append({"iconsource":"qrc:/images/images/Turkish.png","selectlanguage":"Turkish","backColor":"black","theopacity":"1"})
            listModel.get(5).subNode.append({"iconsource":"qrc:/images/images/Vietnam.png","selectlanguage":"Vietnam","backColor":"black","theopacity":"1"})
        }
    }

    Image {
        id: dialog
        visible: false
        anchors.top: parent.top
        anchors.topMargin: (Screen.height-dialog.height)/2
        anchors.left: parent.left
        anchors.leftMargin: (Screen.width - dialog.width)/2
        width: language.visible ? 1270 : 700
        height: language.visible ? 659 : 525
        source: "qrc:/images/images/dialogbg.png"
        z: background.z+1
        Image {
            id: scrollUp
            anchors.top: parent.top
            anchors.topMargin: 30
            anchors.right: parent.right
            anchors.rightMargin: 10
            width: 17
            height: 10
            visible: language.visible
            source: "qrc:/images/images/up.png"
        }
        Image {
            id: scrollDown
            anchors.bottom: okButton.top
            anchors.bottomMargin: 20
            anchors.right: parent.right
            anchors.rightMargin: 10
            width: 17
            height: 10
            visible: language.visible
            source: "qrc:/images/images/down.png"
        }
        Rectangle {
            id: scrollbar
            width: 10
            anchors.top: scrollUp.bottom
            anchors.bottom: scrollDown.top
            anchors.right: parent.right
            anchors.rightMargin: 14
            color: "#585858"
            radius: 10
            visible: language.visible
            Rectangle {
                id: button
                anchors.left: parent.left
                y: (language.visibleArea.yPosition < 0 ) ? 0 : (language.contentY+language.height>language.contentHeight) ?
                    scrollbar.height - button.height : language.visibleArea.yPosition * scrollbar.height
                width: 10
                height: language.visibleArea.heightRatio * scrollbar.height;
                color: "#ccbfbf"
                radius: 10
                // 鼠标区域
                MouseArea {
                    id: mouseArea
                    anchors.fill: button
                    drag.target: button
                    drag.axis: Drag.YAxis
                    drag.minimumY: 0
                    drag.maximumY: scrollbar.height - button.height
                    // 拖动
                    onMouseYChanged: {
                        language.contentY = button.y / scrollbar.height * language.contentHeight
                    }
                }
            }
        }
        ListView {
            id: language
            property int selectrow: -1
            property int selectColum: -1
            anchors.top: parent.top
            anchors.topMargin: 30
            anchors.right: scrollbar.left
            anchors.rightMargin: 10
            anchors.left: parent.left
            anchors.leftMargin: 20
            anchors.bottom: okButton.top
            anchors.bottomMargin: 20
            clip: true
            visible: false
            model: listModel
            delegate: Item {
                property int listIndex: -1
                width: language.width
                height: 120
                Component.onCompleted: {
                    listIndex = index
                }
                Row {
                    width: language.width
                    height: 120
                    Repeater {
                        id: languageRep
                        model: subNode
                        delegate: Rectangle {
                            width: language.width/7
                            height: 120
                            color: model.backColor
                            border.width: 1
                            border.color: "#0079C1"
                            opacity: model.theopacity
                            Image {
                                anchors.top: parent.top
                                anchors.topMargin: -20
                                anchors.horizontalCenter: parent.horizontalCenter
                                source: model.iconsource
                                MouseArea {
                                    anchors.fill: parent
                                    onClicked: {
                                        if (language.selectrow == -1) {
                                            listModel.get(listIndex).subNode.set(index,{"backColor":"#29afff","theopacity":"0.5"})
                                            language.selectrow = listIndex
                                            language.selectColum = index
                                        } else {
                                            listModel.get(language.selectrow).subNode.set(language.selectColum,{"backColor":"black","theopacity":"1"})
                                            listModel.get(listIndex).subNode.set(index,{"backColor":"#29afff","theopacity":"0.5"})
                                            language.selectrow = listIndex
                                            language.selectColum = index
                                        }
                                    }
                                }
                            }
                            Text {
                                id: selectText
                                anchors.horizontalCenter: parent.horizontalCenter
                                anchors.bottom: parent.bottom
                                anchors.bottomMargin: 6
                                font.family: "arial"
                                font.pixelSize: 20
                                color: "white"
                                text: model.selectlanguage
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
                if (language.visible ) {
                    languageButton.source = listModel.get(language.selectrow).subNode.get(language.selectColum).iconsource
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
            visible: language.visible
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
