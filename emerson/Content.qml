import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import QtQuick.Window 2.2

Item {
    id: content
    property bool bIsBasic: true
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
        listModel.append({"nameValue":"111111111","stationColor":"yellow","station":"A"})
        listModel.append({"nameValue":"222222222","stationColor":"yellow","station":"C"})
        listModel.append({"nameValue":"111111111","stationColor":"yellow","station":"D"})
        listModel.append({"nameValue":"333333333","stationColor":"yellow","station":"B"})
        listModel.append({"nameValue":"111111111","stationColor":"yellow","station":"E"})
        listModel.append({"nameValue":"444444444","stationColor":"yellow","station":"G"})
        listModel.append({"nameValue":"111111111","stationColor":"yellow","station":"P"})
        listModel.append({"nameValue":"111111111","stationColor":"yellow","station":"P"})
        listModel.append({"nameValue":"111111111","stationColor":"yellow","station":"P"})
        listModel.append({"nameValue":"111111111","stationColor":"yellow","station":"P"})
        listModel.append({"nameValue":"111111111","stationColor":"yellow","station":"P"})
        listModel.append({"nameValue":"111111111","stationColor":"yellow","station":"P"})
        listModel.append({"nameValue":"111111111","stationColor":"yellow","station":"P"})
        listModel.append({"nameValue":"111111111","stationColor":"yellow","station":"P"})
        listModel.append({"nameValue":"111111111","stationColor":"yellow","station":"P"})
        listModel.append({"nameValue":"111111111","stationColor":"yellow","station":"P"})
        listModel.append({"nameValue":"111111111","stationColor":"yellow","station":"P"})
        listModel.append({"nameValue":"111111111","stationColor":"yellow","station":"P"})

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
                    listModel.set(index,{"station":"D"})
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
                opacity: 0.7
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
                opacity: 0.7
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
                maxSize: 20
                opacity: 0.7
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
                maxSize: 20
                opacity: 0.7
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
                maxSize: 20
                opacity: 0.7
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
            id: roundModel
            Component.onCompleted: {
                roundModel.append({"listNum":"1","count":"2","color1":"red","color2":"yellow"})
                roundModel.append({"listNum":"2","count":"2","color1":"blue","color2":"blue"})
                roundModel.append({"listNum":"3","count":"2","color1":"green","color2":"green"})
                roundModel.append({"listNum":"4","count":"3","color1":"red","color2":"blue"})
                roundModel.append({"listNum":"5","count":"4","color1":"red","color2":"green"})
                roundModel.append({"listNum":"6","count":"5","color1":"red","color2":"yellow"})
                roundModel.append({"listNum":"7","count":"0","color1":"red","color2":"yellow"})
                roundModel.append({"listNum":"8","count":"2","color1":"red","color2":"yellow"})
                roundModel.append({"listNum":"9","count":"2","color1":"red","color2":"yellow"})
                roundModel.append({"listNum":"10","count":"2","color1":"red","color2":"yellow"})
                roundModel.append({"listNum":"11","count":"2","color1":"red","color2":"yellow"})
                roundModel.append({"listNum":"12","count":"2","color1":"red","color2":"yellow"})
                roundModel.append({"listNum":"13","count":"2","color1":"red","color2":"yellow"})
                roundModel.append({"listNum":"14","count":"2","color1":"red","color2":"yellow"})
                roundModel.append({"listNum":"15","count":"2","color1":"red","color2":"yellow"})
                roundModel.append({"listNum":"16","count":"2","color1":"red","color2":"yellow"})
            }
        }

        Rectangle {
            anchors.fill: parent
            color: "#686a6c"
        }
        Text {
            id: boardText
            anchors.top: parent.top
            anchors.topMargin: 60
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
            anchors.topMargin: 10
            anchors.left: parent.left
            anchors.leftMargin: 50
            listModel: roundModel
            columns: 4
            rows: 4
        }
        CButton {
            id: wire
            anchors.top: boardlayout.bottom
            anchors.topMargin: 20
            anchors.left: parent.left
            anchors.leftMargin: 6
            text: "ADD WIRE"
            textColor: "white"
            width: parent.width - 12
            height: 30
            pointSize: 16
            onClicked: {
                loader.source = "qrc:/CreatWire.qml"
            }
        }
    }
}
