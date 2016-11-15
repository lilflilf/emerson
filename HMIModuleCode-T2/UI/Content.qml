import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import QtQuick.Window 2.2

Item {
    id: content
    property bool bIsBasic: true
    property bool bIsDrag: false
    property bool bIsEdit: false
    property string draColor: ""
    signal titleTextChanged(var myTitleText)
    width: Screen.width
    height: Screen.height
    Image {
        anchors.fill: parent
        source: "qrc:/images/images/bg.png"
    }
    Connections {
        target: loader.item
        onSignalSaveSplice: {
            loader.source = ""
            titleTextChanged("Creat Assembly")
        }
    }

    Loader {
        id: loader
        z: 10
        anchors.fill: parent
    }
    ListModel{
        id: listModel
    }
    ListModel {
        id: testModel
    }
    ListModel{
        id: listModel2
    }
    Component.onCompleted: {
        listModel.append({"nameValue":"Splice1 test title hellow word! welcome ","stationColor":"white","station":"?"})
        listModel.append({"nameValue":"Splice2 test title hellow word! welcome ","stationColor":"white","station":"?"})
        listModel.append({"nameValue":"Splice2 test title hellow word! welcome ","stationColor":"white","station":"?"})
        listModel.append({"nameValue":"Splice3 test title hellow word! welcome ","stationColor":"white","station":"?"})
        listModel.append({"nameValue":"Splice4 test title hellow word! welcome ","stationColor":"white","station":"?"})
        listModel.append({"nameValue":"Splice5 test title hellow word! welcome ","stationColor":"white","station":"?"})
        listModel.append({"nameValue":"Splice6 test title hellow word! welcome ","stationColor":"white","station":"?"})
        listModel.append({"nameValue":"Splice7 test title hellow word! welcome ","stationColor":"white","station":"?"})
        listModel.append({"nameValue":"Splice8 test title hellow word! welcome ","stationColor":"white","station":"?"})
        listModel.append({"nameValue":"Splice9 test title hellow word! welcome ","stationColor":"white","station":"?"})
        listModel.append({"nameValue":"Splice10 test title hellow word! welcome ","stationColor":"white","station":"?"})
        listModel.append({"nameValue":"Splice11 test title hellow word! welcome ","stationColor":"white","station":"?"})
        listModel.append({"nameValue":"Splice12 test title hellow word! welcome ","stationColor":"white","station":"?"})
        listModel.append({"nameValue":"Splice13 test title hellow word! welcome ","stationColor":"white","station":"?"})
        listModel.append({"nameValue":"Splice14 test title hellow word! welcome ","stationColor":"white","station":"?"})
        listModel.append({"nameValue":"Splice15 test title hellow word! welcome ","stationColor":"white","station":"?"})
        listModel.append({"nameValue":"Splice16 test title hellow word! welcome ","stationColor":"white","station":"?"})
        listModel.append({"nameValue":"Splice17 test title hellow word! welcome ","stationColor":"white","station":"?"})
        listModel.append({"nameValue":"Splice18 test title hellow word! welcome ","stationColor":"white","station":"?"})
        testModel.append({"name":"splice test title 11111111111222","date":"2016/10/13","middle":"VW","type":"YES","count":"3"})
        testModel.append({"name":"splice test title 1111111111122","date":"2016/10/13","middle":"VW","type":"YES","count":"3"})
        testModel.append({"name":"splice test title 11111111111","date":"2016/10/13","middle":"VW","type":"YES","count":"3"})
        testModel.append({"name":"splice test title 11111111111","date":"2016/10/13","middle":"VW","type":"YES","count":"311"})
        testModel.append({"name":"splice test title 1111111111133333333333333","date":"2016/10/13","middle":"VW","type":"YES","count":"3"})
    }

    function getAllWorkstationColor(count)
    {
        var array = ["#ff6699","#ff0033","#33FFCC","#cc99ff","#cc0099","#930202","#99ccff","#f79428","#0000cc","Olive"]
        colorModel.clear()
        if (count > 7)
            count = 7
        for (var i = 0; i < count; i++) {
            colorModel.append({"workcolor":array[i]});
        }
    }
    SwipeView {
        width: Screen.width * 0.3
        height: parent.height
        id: swipeView
        currentIndex: tabBar.currentIndex
        Page {
            id: splice
            Rectangle {
                anchors.fill: parent
                color: "#052a40"
            }
            Label {
                id: listname
                anchors.top: parent.top
                anchors.topMargin: tabBar.height+10
                anchors.left: parent.left
                horizontalAlignment: Qt.AlignHCenter
                height: 20
                width: parent.width/2
                clip: true
                font.pointSize: 13
                font.family: "arial"
                text: qsTr("Splice")
                color: "white"
            }
            Label {
                id: workname
                anchors.top: parent.top
                anchors.topMargin: tabBar.height+10
                anchors.left: listname.right
                horizontalAlignment: Qt.AlignHCenter
                height: 20
                width: parent.width/2
                clip: true
                font.pointSize: 13
                font.family: "arial"
                text: qsTr("Zone/Workstation")
                color: "white"
            }
            Rectangle {
                id: tipsRec
                anchors.top: workname.bottom
                anchors.topMargin: 4
                width: parent.width
                height: 2
                color: "#585858"
            }
            SpliceListView {
                id: spliceList
                listModel: bIsEdit ? listModel : listModel2
                anchors.top: tipsRec.bottom
                anchors.topMargin: 6
                anchors.bottom: tipsRec2.top
                bIsWorkShow: !bIsBasic
                onCurrentSelecte: {
                    listModel.set(index,{"nameValue":"gggggggg"})
                }
                onCurrentWorkStation: {
                    stationSet.index = index
                    stationSet.visible = true
                    backGround2.visible = true
                    backGround2.opacity = 0.5
                }
            }
            Rectangle {
                id: tipsRec2
//                anchors.top: spliceList.bottom
//                anchors.topMargin: 4
                anchors.bottom: addNewSplice.top
                anchors.bottomMargin: 5
                width: parent.width
                height: 2
                color: "#585858"
            }
            CButton {
                id: addNewSplice
//                anchors.top: tipsRec2.bottom
//                anchors.topMargin: 10
                anchors.bottom: addExitSplice.top
//                anchors.bottomMargin: 5
                anchors.left: parent.left
                anchors.leftMargin: 6
                text: "+ ADD NEW SPLICE"
                textColor: "white"
                width: parent.width - 12
                height: 79
                pointSize: 16
                onClicked: {
                    loader.source = "qrc:/UI/CreatWire.qml"
                    titleTextChanged("Creat Splice")
                }
            }

            CButton {
                id: addExitSplice
//                anchors.top: addNewSplice.bottom
//                anchors.topMargin: 10
                anchors.bottom: upload.top
//                anchors.bottomMargin: 5
                anchors.left: parent.left
                anchors.leftMargin: 6
                text: "+ ADD EXITING SPLICE"
                textColor: "white"
                width: parent.width - 12
                height: 79
                pointSize: 16
                onClicked: {
                    backGround.visible = true
                    backGround.opacity = 0.7
                    addExit.visible = true
                }
            }
            CButton {
                id: upload
//                anchors.top: addExitSplice.bottom
//                anchors.topMargin: 10
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 5
                anchors.left: parent.left
                anchors.leftMargin: 6
                text: "IMPORT SPLICE"
                textColor: "white"
                width: parent.width / 2 - 12
                height: 79
                pointSize: 16
                onClicked: {
                }
            }
            CButton {
                id: save
//                anchors.top: upload.bottom
//                anchors.topMargin: 10
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 5
                anchors.right: parent.right
                anchors.rightMargin: 6
                text: "SAVE PART"
                textColor: "white"
                width: parent.width / 2 - 12
                height: 79
                pointSize: 16
                onClicked: {
                }
            }
        }

        Page {
            id: settting
            Rectangle {
                anchors.fill: parent
                color: "#052a40"
            }
            Label {
                id: processMode
                anchors.top: parent.top
                anchors.topMargin: tabBar.height+12
                anchors.left: parent.left
                anchors.leftMargin: 6
                color: "white"
                opacity: 0.5
                text: qsTr("PROCESS MODE")
                //                height: parent.height * 0.1
                //                width: parent.width * 0.5
                font.family: "arial"
                font.pointSize: 16
            }
            // default right is on, left is off
            Switch2 {
                id: basicSwitch
                anchors.top: processMode.bottom
                anchors.topMargin: 12
                anchors.left: parent.left
                anchors.leftMargin: 6
                height: parent.height * 0.04
                width: parent.width * 0.6
                textLeft: qsTr("Basic")
                textRight: qsTr("Adv")
                state: "left"
                opacity: 0.8
                clip: true
                onOnChanged: {
                    if (basicSwitch.state == "left") {
                        bIsBasic = true
                    } else {
                        bIsBasic = false
                    }
                }
            }
            Label {
                id: lab1
                color: "white"
                visible: !bIsBasic
                anchors.top: basicSwitch.bottom
                anchors.topMargin: 24
                anchors.left: parent.left
                anchors.leftMargin: 6
                opacity: 0.5
                text: qsTr("WORKSTATIONS")
                font.family: "arial"
                font.pointSize: 16
            }
            MyLineEdit {
                id: edit1
                visible: !bIsBasic
                anchors.top: lab1.bottom
                anchors.topMargin: 12
                anchors.left: parent.left
                anchors.leftMargin: 6
                width: 300
                height: 50
                inputWidth: parent.width * 0.3
                inputHeight: parent.height * 0.05
                horizontalAlignment: Qt.AlignHCenter
                tipsText: qsTr("#of Workstations")
                maxSize: 20
                regExp: RegExpValidator{regExp: /([1-9]|1[0-9]|20)/}
                opacity: 0.7
                tipsSize: 14
                onTextChange: {
                    getAllWorkstationColor(text)
                    workStationcolor.allWorkTotal = text
                }
            }
            MyLineEdit {
                id: edit2
                visible: !bIsBasic
                anchors.top: edit1.bottom
                anchors.topMargin: 12
                anchors.left: parent.left
                anchors.leftMargin: 6
                width: 300
                height: 50
                inputWidth: parent.width * 0.3
                inputHeight: parent.height * 0.05
                horizontalAlignment: Qt.AlignHCenter
                tipsText: qsTr("#of Splices per Workstations")
                maxSize: 20
                regExp: RegExpValidator{regExp: /([1-9]|1[0-9]|20)/}
                opacity: 0.7
                tipsSize: 14
                onTextChange: {
                    workStationcolor.maxSpliceNum = text
                }
            }
            Label {
                id: lab2
                visible: !bIsBasic
                anchors.top: edit2.bottom
                anchors.topMargin: 6
                anchors.left: parent.left
                anchors.leftMargin: 6
                color: "white"
                text: qsTr("BOARD LAYOUT")
                font.family: "arial"
                font.pointSize: 16
                opacity: 0.5
            }
            MyLineEdit {
                id: edit3
                visible: !bIsBasic
                anchors.top: lab2.bottom
                anchors.topMargin: 12
                anchors.left: parent.left
                anchors.leftMargin: 6
                width: parent.width*0.5
                height: 50
                horizontalAlignment: Qt.AlignHCenter
                inputWidth: parent.width * 0.3
                inputHeight: parent.height * 0.05
                tipsText: qsTr("Rows")
                regExp: RegExpValidator{regExp: /^[1-4]{1}$/}
                maxSize: 20
                opacity: 0.7
                tipsSize: 14
                onTextChange: {
                    boardlayout.rows = text
                    for (var i = 0; i< workModel.count; i++) {
                        workModel.get(i).workStation.destroy()
                    }
                    workModel.clear()
                }
            }
            MyLineEdit {
                id: edit4
                visible: !bIsBasic
                anchors.top: lab2.bottom
                anchors.topMargin: 12
                anchors.left: edit3.right
                anchors.leftMargin: -10
                horizontalAlignment: Qt.AlignHCenter
                width: 300
                height: 50
                inputWidth: parent.width * 0.3
                inputHeight: parent.height * 0.05
                tipsText: qsTr("Columns")
                regExp: RegExpValidator{regExp: /^[1-4]{1}$/}
                maxSize: 20
                opacity: 0.7
                tipsSize: 14
                onTextChange: {
                    boardlayout.columns = text
                    for (var i = 0; i< workModel.count; i++) {
                        workModel.get(i).workStation.destroy()
                    }
                    workModel.clear()
                }
            }
            MyLineEdit {
                id: edit5
                visible: !bIsBasic
                anchors.top: edit4.bottom
                anchors.topMargin: 12
                anchors.left: parent.left
                anchors.leftMargin: 6
                width: 300
                height: 50
                inputWidth: parent.width * 0.3
                inputHeight: parent.height * 0.05
                horizontalAlignment: Qt.AlignHCenter
                tipsText: qsTr("Max Splice Per Zone")
                regExp: RegExpValidator{regExp: /([1-9]|1[0-2])/}
                maxSize: 20
                opacity: 0.7
                tipsSize: 14
                onTextChange: {
                }
            }
//            Label {
//                id: lab3
//                color: "white"
//                anchors.top: edit5.bottom
//                anchors.topMargin: 6
//                anchors.left: parent.left
//                anchors.leftMargin: 6
//                text: qsTr("UNITS")
//                font.family: "arial"
//                font.pointSize: 16
//                opacity: 0.5
//            }
//            Switch2 {
//                id: unitSwitch
//                anchors.top: lab3.bottom
//                anchors.topMargin: 12
//                anchors.left: parent.left
//                anchors.leftMargin: 6
//                height: parent.height * 0.04
//                width: parent.width * 0.6
//                textLeft: qsTr("Imperial")
//                textRight: qsTr("Metric")
//                state: "left"
//                opacity: 0.8
//            }
        }
    }
    TabBar {
        width: Screen.width * 0.3
        id: tabBar
        currentIndex: swipeView.currentIndex
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.leftMargin: 10
        height: 64
        TabButton {
            height: parent.height
            Rectangle {
                anchors.fill: parent
                color:  "#052a40"  //tabBar.currentIndex == 0 ? "black" : "#48484a"
            }
            Text {
                anchors.centerIn: parent
                font.family: "arial"
                font.pointSize: 17.5
                text: qsTr("SPLICE")
                color: tabBar.currentIndex == 0 ? "white" : "#969ea5"
            }
            Rectangle {
                width: parent.width
                height: 6
                color:  "#F79428"
                anchors.bottom: parent.bottom
                visible: tabBar.currentIndex == 0 ? true : false
            }
        }
        TabButton {
            height: parent.height
            Rectangle {
                anchors.fill: parent
                color:  "#052a40"
            }
            Text {
                anchors.centerIn: parent
                font.family: "arial"
                font.pointSize: 17.5
                text: qsTr("SETTINGS")
                color: tabBar.currentIndex == 1 ? "white" : "#969ea5"
            }
            Rectangle {
                width: parent.width
                height: 6
                color:  "#F79428"
                anchors.bottom: parent.bottom
                visible: tabBar.currentIndex == 1 ? true : false
            }
        }
    }

    Item {
        id: rightArea
        anchors.left: swipeView.right
        width: Screen.width * 0.7
        height: parent.height
        MouseArea {
            anchors.fill: parent
        }
        ListModel {
            id: colorModel
        }
        ListModel {
            id: workModel
        }
        Image {
            anchors.fill: parent
            source: "qrc:/images/images/bg.png"
        }
        MyLineEdit {
            id: edit6
            anchors.top: parent.top
            anchors.topMargin: 4
            anchors.left: parent.left
            anchors.leftMargin: 50
            width: parent.width * 0.62
            height: 45
            inputWidth: parent.width * 0.62
            inputHeight: parent.height * 0.05
            horizontalAlignment: Qt.AlignHCenter
            defaultText: qsTr("PART NAME")
            //regExp: RegExpValidator{regExp: /^[1-9]{1,2}$/}
            maxSize: 60
            clip: true
            onTextChange: {
            }
        }
        CButton {
            id: template
            anchors.top: parent.top
            anchors.topMargin: 4
            anchors.right: boardlayout.right
            text: qsTr("Template")
            textColor: "white"
            backgroundComponent: Rectangle {
                anchors.fill: parent
                color: "black"
            }
            width: 200
            height: 45
            pointSize: 16
            onClicked: {
            }
        }
//        MyLineEdit {
//            id: edit7
//            anchors.top: edit6.bottom
//            anchors.topMargin: 2
//            anchors.left: parent.left
//            anchors.leftMargin: 50
//            width: parent.width * 0.62
//            height: 45
//            inputWidth: parent.width * 0.62
//            inputHeight: parent.height * 0.05
//            horizontalAlignment: Qt.AlignHCenter
//            defaultText: qsTr("WORK ORDER ID")
//            //regExp: RegExpValidator{regExp: /^[1-9]{1,2}$/}
//            maxSize: 60
//            clip: true
//            onTextChange: {
//            }
//        }
        Text {
            id: boardText
            anchors.top: edit6.bottom
            anchors.topMargin: 24
            anchors.left: parent.left
            anchors.leftMargin: 50
            color: "white"
            opacity: 0.5
            width: 100
            font.family: "arial"
            font.pointSize: 16
            visible: !bIsBasic
            text: qsTr("Board Layout")
        }
        Text {
            id: tempText
            anchors.top:  edit6.bottom
            anchors.topMargin: 24
            anchors.right: boardlayout.right
            color: "white"
            opacity: 0.5
            font.family: "arial"
            font.pointSize: 16
            text: qsTr("Temp(℃):260 Time(s):09.0 ENABLED")
        }
        BoardLayOut {
            id: boardlayout
            anchors.top: boardText.bottom
            anchors.topMargin: 10
            anchors.left: parent.left
            anchors.leftMargin: 50
            visible: !bIsBasic
            columns: 0
            rows: 0
            onColumnsChanged: {
                followArea.visible = false
            }
            onRowsChanged: {
                followArea.visible = false
            }
        }

        Component {
            id: dragColor
            Rectangle {
                id: dragItem
                width: 35
                height: 35
                radius: 35
                border.color: "white"
                border.width: 1
                Drag.active: dragArea.drag.active
                Drag.supportedActions: Qt.MoveAction
                Drag.dragType: Drag.Internal
                Drag.mimeData: {"color": color, "width": width, "height": height};
                MouseArea {
                    id: dragArea;
                    anchors.fill: parent
                    drag.target: parent
                    drag.minimumX: 0
                    drag.maximumX: boardlayout.width-35
                    drag.minimumY: 0
                    drag.maximumY: boardlayout.height-35
                    onPositionChanged: {
                        draColor = dragItem.color
                        bIsDrag = true
                    }
                    onReleased: {
                        bIsDrag = false
                    }
                }
            }
        }

        DropArea {
            id: dropContainer;
            property bool bFollow: followArea.visible
            anchors.top: boardText.bottom
            anchors.topMargin: 6
            anchors.left: parent.left
            anchors.leftMargin: 50
            width: boardlayout.width-35
            height: boardlayout.height-35
            onEntered: {
                drag.accepted = true;
                if (!bIsDrag) {
                    followArea.visible = false
                    followArea.color = drag.getDataAsString("color");
                } else {
                    followArea.color = draColor
                }
            }
            onPositionChanged: {
                drag.accepted = true;
                followArea.visible = true
                followArea.x = drag.x
                followArea.y = drag.y
            }
            onDropped: {
                if(drop.supportedActions == Qt.CopyAction){
                    var component =  dragColor.createObject(boardlayout,{
                                                          "x": drop.x,
                                                          "y": drop.y,
                                                          "width": parseInt(drop.getDataAsString("width")),
                                                          "height": parseInt(drop.getDataAsString("height")),
                                                          "color": drop.getDataAsString("color"),
                                                          "Drag.supportedActions": Qt.MoveAction,
                                                          "Drag.dragType": Drag.Internal
                                                      });
                    workModel.append({"workStation":component})
                    followArea.visible = false
                }
                drop.acceptProposedAction();
                drop.accepted = true;
            }
            Rectangle {
                id: followArea
                radius: 35
                width: 35
                height: 35
                border.color: "white"
                border.width: 1
                visible: parent.containsDrag
                onVisibleChanged: {
//                    console.log("aaaaaaaaa",followArea.visible)
                }
            }
        }
        CButton {
            id: editSplice
            anchors.top: boardlayout.bottom
            anchors.topMargin: parent.height/10-64
            anchors.right: boardlayout.right
            text: "EDIT SPLICE"
            textColor: "white"
            width: 200
            height: 79
            pointSize: 16
            onClicked: {
            }
        }
        CButton {
            id: testSplice
            anchors.top: editSplice.bottom
            anchors.topMargin: 5
            anchors.right: boardlayout.right
            text: "TEST SPLICE"
            textColor: "white"
            width: 200
            height: 79
            pointSize: 16
            onClicked: {
            }
        }
        Text {
            id: workStation
            anchors.top: boardlayout.bottom
            anchors.topMargin: 10
            anchors.left: boardlayout.left
            visible: !bIsBasic
            text: qsTr("WORKSTATIONS")
            color: "white"
            opacity: 0.5
            font.family: "arial"
            font.pointSize: 16
        }

        WorkStationColor {
            id: workStationcolor
            visible: !bIsBasic
            anchors.top: workStation.bottom
            anchors.topMargin: 4
            anchors.left: boardlayout.left
            listModel: colorModel
            allWorkTotal: 0
            maxSpliceNum: 0
        }
    }
    Rectangle {
        id: backGround
        anchors.fill: parent
        color: "black"
        opacity: 0
        visible: false
        MouseArea {
            anchors.fill: parent
            onClicked: {

            }
        }
    }
    Rectangle {
        id: backGround2
        anchors.fill: parent
        color: "black"
        visible: false
        opacity: 0
        MouseArea {
            anchors.fill: parent
            onClicked: {
                backGround2.visible = false
                backGround2.opacity = 0
                stationSet.visible = false
                stationSet.selecteColor = ""
                stationSet.selecteZone = ""
                var station = listModel.get(stationSet.index).station
                var stationColor = listModel.get(stationSet.index).stationColor
                if (station == "?" && stationColor != "white") {
                    listModel.set(stationSet.index,{"stationColor":"white"})
                } else if (station != "?" && stationColor == "white") {
                    listModel.set(stationSet.index,{"station":"?"})
                }
            }
        }
    }
    WorkStationSet {
        id: stationSet
        anchors.centerIn: parent
        width: 560
        height: 280
        allWorkTotal: workStationcolor.allWorkTotal
        allZoneTotal: boardlayout.columns*boardlayout.rows
        visible: false
        onSelecteZoneChanged: {
            if (stationSet.selecteZone == "") {
                return
            }
            listModel.set(stationSet.index,{"station":stationSet.selecteZone})
            if (stationSet.selecteColor != "") {
                boardlayout.setBoardLayoutColor(stationSet.selecteIndex,stationSet.selecteColor,stationSet.index+1)
                stationSet.visible = false
                stationSet.selecteColor = ""
                stationSet.selecteZone = ""
                backGround2.visible = false
                backGround2.opacity = 0
            }
        }
        onSelecteColorChanged: {
            if (stationSet.selecteColor == "") {
                return
            }
            listModel.set(stationSet.index,{"stationColor":stationSet.selecteColor})
            if (stationSet.selecteZone != "") {
                boardlayout.setBoardLayoutColor(stationSet.selecteIndex,stationSet.selecteColor,stationSet.index+1)
                stationSet.visible = false
                stationSet.selecteColor = ""
                stationSet.selecteZone = ""
                backGround2.visible = false
                backGround2.opacity = 0
            }
        }
    }
    AddExistingSpliceWire {
        id: addExit
        anchors.centerIn: parent
        width: Screen.width*0.7
        height: Screen.height*0.6
        visible: false
        listModel: testModel
        titleName: qsTr("Add Existing Splice")
        componentName: qsTr("SPLICE NAME")
        componentData: qsTr("DATE CREATED")
        componentMiddle: qsTr("# OF WIRES")
        componenttype: qsTr("CROSS SECTION")
        componentCount: qsTr("COUNT")
        onSignalAddExistCancel: {
            backGround.visible = false
            backGround.opacity = 0
            addExit.visible = false
        }
        onSignalAddExistSelectClick: {
            backGround.visible = false
            backGround.opacity = 0
            addExit.visible = false
        }
    }
}
