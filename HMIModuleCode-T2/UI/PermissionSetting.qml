import QtQuick 2.7
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.0
import QtQuick.Window 2.2

Item {
    Image {
        anchors.fill: parent
        source: "qrc:/images/images/bg.png"
    }
    Row {
        id: headTitle
        anchors.top: parent.top
        anchors.topMargin: 30
        anchors.left: parent.left
        anchors.leftMargin: 55
        width: parent.width - 100
        height: 50
        spacing: 10
        CButton {
            anchors.verticalCenter: parent.verticalCenter
            width: (parent.width-40)/5
            clip: true
            pointSize: 20
//            font.pointSize: 20
//            font.family: "arial"
//            height: 50
            text: qsTr("Function Name")
            onClicked: {
                menuBackGround.visible = true
                menuSelect.visible = true
            }
        }

        MyLineEdit {
            anchors.verticalCenter: parent.verticalCenter
            horizontalAlignment: Qt.AlignHCenter
            width: (parent.width-40)/5
            inputWidth: (parent.width-40)/5
            inputHeight: Screen.height * 0.08
            height: Screen.height * 0.08
            clip: true
            inputSize: 20
            inputColor: "white"
            inputText: qsTr("1.Administrator")
        }
        MyLineEdit {
            anchors.verticalCenter: parent.verticalCenter
            horizontalAlignment: Qt.AlignHCenter
            width: (parent.width-40)/5
            inputWidth: (parent.width-40)/5
            inputHeight: Screen.height * 0.08
            height: Screen.height * 0.08
            clip: true
            inputSize: 20
            inputColor: "white"
            inputText: qsTr("2.Technician")
        }
        MyLineEdit {
            anchors.verticalCenter: parent.verticalCenter
            horizontalAlignment: Qt.AlignHCenter
            width: (parent.width-40)/5
            inputWidth: (parent.width-40)/5
            inputHeight: Screen.height * 0.08
            height: Screen.height * 0.08
            clip: true
            inputSize: 20
            inputColor: "white"
            inputText: qsTr("3.Quality Control")
        }
        MyLineEdit {
            anchors.verticalCenter: parent.verticalCenter
            horizontalAlignment: Qt.AlignHCenter
            width: (parent.width-40)/5
            inputWidth: (parent.width-40)/5
            inputHeight: Screen.height * 0.08
            height: Screen.height * 0.08
            clip: true
            inputSize: 20
            inputColor: "white"
            inputText: qsTr("4.Open")
        }
    }
    Rectangle {
        id: tipsRec
        anchors.top: headTitle.bottom
        anchors.topMargin: 20
        anchors.left: parent.left
        anchors.leftMargin: 20
        width: parent.width - 40
        clip: true
        height: 1
        color: "#ffffff"
    }
    Rectangle {
        id: tipsRec2
        anchors.top: tipsRec.bottom
        anchors.left: parent.left
        anchors.leftMargin: 20
        width: parent.width - 40
        clip: true
        height: 1
        color: "#0d0f11"
    }
    ListModel {
        id: listModel
        Component.onCompleted: {
            listModel.append({name:"Create New",opacityValue:0})
            listModel.append({name:"Edit Existing",opacityValue:0})
            listModel.append({name:"Operate",opacityValue:0})
            listModel.append({name:"Test",opacityValue:0})
            listModel.append({name:"Calibration",opacityValue:0})
            listModel.append({name:"Tool Change",opacityValue:0})
            listModel.append({name:"Advanced Maintenance",opacityValue:0})
            listModel.append({name:"Maintenance Counter",opacityValue:0})
        }
    }

    ListModel {
        id: menuModel
        Component.onCompleted: {
            menuModel.append({name:"Create New",opacityValue:0})
            menuModel.append({name:"Edit Existing",opacityValue:0})
            menuModel.append({name:"Operate",opacityValue:0})
            menuModel.append({name:"Test",opacityValue:0})
            menuModel.append({name:"Calibration",opacityValue:0})
            menuModel.append({name:"Tool Change",opacityValue:0})
            menuModel.append({name:"Advanced Maintenance",opacityValue:0})
            menuModel.append({name:"Maintenance Counter",opacityValue:0})
            menuModel.append({name:"Maintenance log",opacityValue:0})
            menuModel.append({name:"Word Order History",opacityValue:0})
            menuModel.append({name:"Statistical Trend",opacityValue:0})
            menuModel.append({name:"Error/Alarm Log",opacityValue:0})
            menuModel.append({name:"Library",opacityValue:0})
            menuModel.append({name:"Version Information",opacityValue:0})
            menuModel.append({name:"Permission Setting",opacityValue:0})
            menuModel.append({name:"Weld Defaults",opacityValue:0})
            menuModel.append({name:"Operator Library",opacityValue:0})
            menuModel.append({name:"Data/Communication",opacityValue:0})
            menuModel.append({name:"Branson Setting",opacityValue:0})
        }
    }
    Image {
        id: menuSelect
        anchors.top: tipsRec2.bottom
        anchors.left: parent.left
        anchors.leftMargin: 55
        width: 300
        clip: true
        visible: false
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 24
        source: "qrc:/images/images/bg.png"
        z: 10
        Row {
            id: bottomRow
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 16
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: 5
            CButton {
                width: (parent.parent.width-10) / 2
                iconSource: "qrc:/images/images/cancel.png"
                text: qsTr("CANCEL")
                onClicked: {
                    menuBackGround.visible = false
                    menuSelect.visible = false
                    listModel.clear()
                }
            }
            CButton {
                id: sureButton
                width: (parent.parent.width-10) / 2
                iconSource: "qrc:/images/images/OK.png"
                text: qsTr("OK")
                onClicked: {
                    menuBackGround.visible = false
                    menuSelect.visible = false
                    listModel.clear()
                    for (var i = 0; i < menuModel.count; i++) {
                        if (menuModel.get(i).opacityValue == 0.5) {
                            listModel.append({name:menuModel.get(i).name})
                        }
                    }
                }
            }
        }

//        CButton {
//            id: sureButton
//            anchors.bottom: parent.bottom
//            anchors.bottomMargin: 16
//            anchors.horizontalCenter: parent.horizontalAlignment
//            width: parent.width-80
//            iconSource: "qrc:/images/images/OK.png"
//            text: qsTr("OK")
//            onClicked: {
//                menuBackGround.visible = false
//                menuSelect.visible = false
//                listModel.clear()
//                for (var i = 0; i < menuModel.count; i++) {
//                    if (menuModel.get(i).opacityValue == 0.5) {
//                        listModel.append({name:menuModel.get(i).name})
//                    }
//                }
//            }
//        }
        ListView {
            id: menuView
            anchors.top: parent.top
            width: parent.width
            clip: true
            anchors.bottom: bottomRow.top
            anchors.bottomMargin: 20
            model: menuModel
            delegate: Item {
                width: menuView.width
                height: 40
                Text {
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    anchors.leftMargin: 40
                    font.family: "arial"
                    font.pixelSize: 20
                    color: "white"
                    text: qsTr(name)
                }
                Rectangle {
                    id: back
                    anchors.fill: parent
                    color: "black"
                    opacity: opacityValue
                }
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        if (menuModel.get(index).opacityValue == 0) {
                           menuModel.set(index,{opacityValue:0.5})
                        } else {
                            menuModel.set(index,{opacityValue:0})
                        }
                    }
                }
            }
        }
    }


    ListView {
        id: listView
        anchors.top: tipsRec2.bottom
        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.bottom: line3.top
        width: parent.width - 65
        clip: true
        model: listModel
        delegate: listDelegate
    }
    Component {
        id: listDelegate
        Item {
            width: listView.width
            height: 44
            ExclusiveGroup {
                id: listviewPositionGroup;
            }
            Text {
                id: titleName
                anchors.top: parent.top
                anchors.topMargin: 5
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                anchors.leftMargin: 35
                horizontalAlignment: Qt.AlignLeft
                width: (parent.width-100)/5
                font.family: "arial"
                font.pixelSize: 20
                color: "white"
                text: qsTr(name)
            }

            MyCheckBox {
                id: check1
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: titleName.right
                anchors.leftMargin: 10
                width: (parent.width-100)/5
                height: parent.height
                exclusiveGroup: listviewPositionGroup
            }
            MyCheckBox {
                id: check2
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: check1.right
                anchors.leftMargin: 10
                width: (parent.width-100)/5
                height: parent.height
                exclusiveGroup: listviewPositionGroup
            }
            MyCheckBox {
                id: check3
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: check2.right
                anchors.leftMargin: 10
                width: (parent.width-100)/5
                height: parent.height
                exclusiveGroup: listviewPositionGroup
            }
            MyCheckBox {
                id: chec4
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: check3.right
                anchors.leftMargin: 10
                width: (parent.width-100)/5
                height: parent.height
                exclusiveGroup: listviewPositionGroup
            }
        }
    }

    Image {
        id: scrollUp
        anchors.top: tipsRec2.bottom
        anchors.topMargin: 2
        anchors.left: listView.right
        width: 17
        height: 10
        visible: listView.contentHeight > listView.height ? true : false
        source: "qrc:/images/images/up.png"
    }
    Image {
        id: scrollDown
        anchors.bottom: line3.top
        anchors.bottomMargin: 2
        anchors.left: listView.right
        width: 17
        height: 10
        visible: listView.contentHeight > listView.height ? true : false
        source: "qrc:/images/images/down.png"
    }
    Rectangle {
        id: scrollbar
        width: 10
        height: listView.height-24
        anchors.top: scrollUp.bottom
        anchors.left: listView.right
        anchors.leftMargin: 4
        color: "#585858"
        radius: 10
        visible: listView.contentHeight > listView.height ? true : false
        Rectangle {
            id: button
            anchors.left: parent.left
            y: (listView.visibleArea.yPosition < 0 ) ? 0 : (listView.contentY+listView.height>listView.contentHeight) ?
                                                           scrollbar.height - button.height : listView.visibleArea.yPosition * scrollbar.height
            width: 10
            height: listView.visibleArea.heightRatio * scrollbar.height;
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
                    listView.contentY = button.y / scrollbar.height * listView.contentHeight
                }
            }
        }
    }
    Rectangle {
        id: line3
        anchors.bottom: line4.top
        anchors.left: parent.left
        anchors.leftMargin: 20
        width: parent.width-40
        clip: true
        height: 1
        color: "#ffffff"
    }
    Rectangle {
        id: line4
        anchors.bottom: initialButton.top
        anchors.bottomMargin: 20
        anchors.left: parent.left
        anchors.leftMargin: 20
        width: parent.width-40
        clip: true
        height: 1
        color: "#0d0f11"
    }
    CButton {
        id: initialButton
        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 20
        width: 300
        text: qsTr("Initial Fram")
        textColor: "white"
    }
    CButton {
        id: okButton
        anchors.right: parent.right
        anchors.rightMargin: 20
        anchors.bottom: initialButton.bottom
        width: 300
        text: qsTr("OK")
        iconSource: "qrc:/images/images/OK.png"
        textColor: "white"
    }
    CButton {
        id: cancelButton
        anchors.right: okButton.left
        anchors.rightMargin: 43
        anchors.bottom: initialButton.bottom
        width: 300
        text: qsTr("Cancel")
        textColor: "white"
        iconSource: "qrc:/images/images/cancel.png"
        onClicked: {
        }
    }
    Rectangle {
        id: menuBackGround
        anchors.fill: parent
        color: "black"
        visible: false
        opacity: 0.5
        MouseArea {
            anchors.fill: parent
        }
    }
}
