import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import QtQuick.Window 2.2

Item {
    id: content
    property bool bIsBasic: true
    property bool bIsDrag: false
    property string draColor: ""
    width: Screen.desktopAvailableWidth
    height: Screen.desktopAvailableHeight
    Loader {
        id: loader
        z: 10
        anchors.fill: parent
    }
    ListModel{
        id: listModel
    }

    Component.onCompleted: {
        listModel.append({"nameValue":"Splice1 test title","stationColor":"white","station":"?"})
        listModel.append({"nameValue":"Splice2 test title","stationColor":"white","station":"?"})
        listModel.append({"nameValue":"Splice2 test title","stationColor":"white","station":"?"})
        listModel.append({"nameValue":"Splice3 test title","stationColor":"white","station":"?"})
        listModel.append({"nameValue":"Splice4 test title2222222222","stationColor":"white","station":"?"})
        listModel.append({"nameValue":"Splice5 test title","stationColor":"white","station":"?"})
        listModel.append({"nameValue":"Splice6 test title","stationColor":"white","station":"?"})
        listModel.append({"nameValue":"Splice7 test title","stationColor":"white","station":"?"})
        listModel.append({"nameValue":"Splice8 test title","stationColor":"white","station":"?"})
        listModel.append({"nameValue":"Splice9 test title","stationColor":"white","station":"?"})
        listModel.append({"nameValue":"Splice10 test title","stationColor":"white","station":"?"})
        listModel.append({"nameValue":"Splice11 test title","stationColor":"white","station":"?"})
        listModel.append({"nameValue":"Splice12 test title","stationColor":"white","station":"?"})
        listModel.append({"nameValue":"Splice13 test title","stationColor":"white","station":"?"})
        listModel.append({"nameValue":"Splice14 test title","stationColor":"white","station":"?"})
        listModel.append({"nameValue":"Splice15 test title","stationColor":"white","station":"?"})
        listModel.append({"nameValue":"Splice16 test title","stationColor":"white","station":"?"})
        listModel.append({"nameValue":"Splice17 test title","stationColor":"white","station":"?"})
        listModel.append({"nameValue":"Splice18 test title","stationColor":"white","station":"?"})

    }
    function getAllWorkstationColor(count)
    {
        var array = ["#ff6699","#ff0033","#33FFCC","#cc99ff","#cc0099","#930202","#99ccff","#f79428","#0000cc","Olive"]
        colorModel.clear()
        if (count > 10)
            count = 10
        for (var i = 0; i < count; i++) {
            colorModel.append({"workcolor":array[i]});
        }
    }
    SwipeView {
        width: Screen.desktopAvailableWidth * 0.2
        height: parent.height
        id: swipeView
        currentIndex: tabBar.currentIndex
        Page {
            id: splice
            Rectangle {
                anchors.fill: parent
                color: "#48484A"
            }
            Label {
                id: listname
                anchors.top: parent.top
                anchors.topMargin: tabBar.height+10
                anchors.left: parent.left
                anchors.leftMargin: 30
                height: 20
                width: 60
                clip: true
                font.pointSize: 12
                font.family: "arial"
                text: qsTr("Splice")
                color: "white"
            }
            Label {
                id: workname
                anchors.top: parent.top
                anchors.topMargin: tabBar.height+10
                anchors.left: listname.right
                anchors.leftMargin: 40
                height: 20
                width: 140
                clip: true
                font.pointSize: 12
                font.family: "arial"
                text: qsTr("Zone/Workstation")
                color: "white"
            }
            Rectangle {
                id: tipsRec
                anchors.top: workname.bottom
                anchors.topMargin: 4
                width: parent.width
                height: 10
                color: "#585858"
            }
            SpliceListView {
                id: spliceList
                listModel: listModel
                anchors.top: tipsRec.bottom
                anchors.topMargin: 6
                onCurrentSelecte: {
                    listModel.set(index,{"nameValue":"gggggggg"})
                }
                onCurrentWorkStation: {
                    stationSet.index = index
                    stationSet.visible = true
                }
            }
        }

        Page {
            id: settting
            Rectangle {
                anchors.fill: parent
                color: "#48484a"
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
                width: parent.width * 0.5
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
                regExp: RegExpValidator{regExp: /^[1-9]{1,2}$/}
                maxSize: 20
                opacity: 0.7
                onTextChange: {
                }
            }
            Label {
                id: lab3
                color: "white"
                anchors.top: edit5.bottom
                anchors.topMargin: 6
                anchors.left: parent.left
                anchors.leftMargin: 6
                text: qsTr("UNITS")
                font.family: "arial"
                font.pointSize: 16
                opacity: 0.5
            }
            Switch2 {
                id: unitSwitch
                anchors.top: lab3.bottom
                anchors.topMargin: 12
                anchors.left: parent.left
                anchors.leftMargin: 6
                height: parent.height * 0.04
                width: parent.width * 0.6
                textLeft: qsTr("Imperial")
                textRight: qsTr("Metric")
                state: "left"
                opacity: 0.8
            }
            CButton {
                id: addNewSplice
                anchors.top: unitSwitch.bottom
                anchors.topMargin: 10
                anchors.left: parent.left
                anchors.leftMargin: 6
                text: "+ ADD NEW SPLICE"
                textColor: "white"
                width: parent.width - 12
                height: 30
                pointSize: 16
                onClicked: {
                    loader.source = "qrc:/CreatWire.qml"
                }
            }
            CButton {
                id: addExitSplice
                anchors.top: addNewSplice.bottom
                anchors.topMargin: 10
                anchors.left: parent.left
                anchors.leftMargin: 6
                text: "+ ADD EXITING SPLICE"
                textColor: "white"
                width: parent.width - 12
                height: 30
                pointSize: 16
                onClicked: {
                }
            }
            CButton {
                id: upload
                anchors.top: addExitSplice.bottom
                anchors.topMargin: 10
                anchors.left: parent.left
                anchors.leftMargin: 6
                text: "UPLOAD SPLICE"
                textColor: "white"
                width: parent.width - 12
                height: 30
                pointSize: 16
                onClicked: {
                }
            }
            CButton {
                id: save
                anchors.top: upload.bottom
                anchors.topMargin: 10
                anchors.left: parent.left
                anchors.leftMargin: 6
                text: "SAVE PART"
                textColor: "white"
                width: parent.width - 12
                height: 30
                pointSize: 16
                onClicked: {
                }
            }
        }
    }
    TabBar {
        width: Screen.desktopAvailableWidth * 0.2
        id: tabBar
        currentIndex: swipeView.currentIndex
        anchors.top: parent.top
        TabButton {
            font.family: "arial"
            font.pointSize: 16
            text: qsTr("SPLICE")
            opacity: 0.33
        }
        TabButton {
            font.family: "arial"
            font.pointSize: 16
            text: qsTr("SETTINGS")
            opacity: 0.33
        }
    }

    Item {
        id: rightArea
        anchors.left: swipeView.right
        width: Screen.desktopAvailableWidth * 0.8
        height: parent.height // * 0.5
        ListModel {
            id: colorModel
        }
        ListModel {
            id: workModel
        }
        Rectangle {
            anchors.fill: parent
            color: "#686a6c"
        }
        MyLineEdit {
            id: edit6
            anchors.top: parent.top
            anchors.topMargin: 4
            anchors.left: parent.left
            anchors.leftMargin: 50
            width: parent.width * 0.67
            height: 50
            inputWidth: parent.width * 0.67
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
            width: 200
            height: 30
            pointSize: 16
            onClicked: {
            }
        }
        MyLineEdit {
            id: edit7
            anchors.top: edit6.bottom
            anchors.topMargin: 2
            anchors.left: parent.left
            anchors.leftMargin: 50
            width: parent.width * 0.67
            height: 50
            inputWidth: parent.width * 0.67
            inputHeight: parent.height * 0.05
            horizontalAlignment: Qt.AlignHCenter
            defaultText: qsTr("WORK ORDER ID")
            //regExp: RegExpValidator{regExp: /^[1-9]{1,2}$/}
            maxSize: 60
            clip: true
            onTextChange: {
            }
        }
        Text {
            id: boardText
            anchors.top: edit7.bottom
            anchors.left: parent.left
            anchors.leftMargin: 50
            color: "white"
            opacity: 0.5
            width: 100
            font.family: "arial"
            font.pointSize: 16
            text: qsTr("Board Layout")
        }

        BoardLayOut {
            id: boardlayout
            anchors.top: boardText.bottom
            anchors.topMargin: 6
            anchors.left: parent.left
            anchors.leftMargin: 50
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
                    console.log("aaaaaaaaa",followArea.visible)
                }
            }
        }
        CButton {
            id: exportSPlice
            anchors.top: boardlayout.bottom
            anchors.topMargin: 30
            anchors.right: boardlayout.right
            text: "EXPORT SPLICE"
            textColor: "white"
            width: 200
            height: 30
            pointSize: 16
            onClicked: {
            }
        }
        CButton {
            id: savePart
            anchors.top: exportSPlice.bottom
            anchors.topMargin: 30
            anchors.right: boardlayout.right
            text: "SAVE PART"
            textColor: "white"
            width: 200
            height: 30
            pointSize: 16
            onClicked: {
            }
        }
        Text {
            id: workStation
            anchors.top: boardlayout.bottom
            anchors.topMargin: 10
            anchors.left: boardlayout.left
            text: qsTr("WORKSTATIONS")
            color: "white"
            opacity: 0.5
            font.family: "arial"
            font.pointSize: 16
        }

        WorkStationColor {
            id: workStationcolor
            anchors.top: workStation.bottom
            anchors.topMargin: 4
            anchors.left: boardlayout.left
            listModel: colorModel
            allWorkTotal: 0
            maxSpliceNum: 0
        }

        WorkStationSet {
            id: stationSet
            anchors.top: boardText.bottom
            anchors.topMargin: 50
            anchors.left: boardlayout.left
            width: 560
            height: 280
            allWorkTotal: workStationcolor.allWorkTotal
            allZoneTotal: boardlayout.columns*boardlayout.rows
            z: 10
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
                }
            }
        }
    }
}
