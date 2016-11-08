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
        spacing: 10
        Text {
            anchors.verticalCenter: parent.verticalCenter
            horizontalAlignment: Qt.AlignHCenter
            width: (parent.width-40)/5
            color: "white"
            clip: true
            font.pointSize: 25
            font.family: "arial"
            text: qsTr("Function Name")
        }
        TextEdit {
            anchors.verticalCenter: parent.verticalCenter
            horizontalAlignment: Qt.AlignHCenter
            width: (parent.width-40)/5
            color: "white"
            clip: true
            font.pointSize: 25
            font.family: "arial"
            text: qsTr("1.Administrator")
        }
        TextEdit {
            anchors.verticalCenter: parent.verticalCenter
            horizontalAlignment: Qt.AlignHCenter
            width: (parent.width-40)/5
            color: "white"
            clip: true
            font.pointSize: 25
            font.family: "arial"
            text: qsTr("2.Technician")
        }
        TextEdit {
            anchors.verticalCenter: parent.verticalCenter
            horizontalAlignment: Qt.AlignHCenter
            width: (parent.width-40)/5
            color: "white"
            clip: true
            font.pointSize: 25
            font.family: "arial"
            text: qsTr("3.Quality Control")
        }
        TextEdit {
            anchors.verticalCenter: parent.verticalCenter
            horizontalAlignment: Qt.AlignHCenter
            width: (parent.width-40)/5
            color: "white"
            clip: true
            font.pointSize: 25
            font.family: "arial"
            text: qsTr("4.Open")
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
            listModel.append({name:"Create New"})
            listModel.append({name:"Edit Existing"})
            listModel.append({name:"Manage Libraries"})
            listModel.append({name:"Edit Splice"})
            listModel.append({name:"Teach Mode"})
            listModel.append({name:"Maintenance"})
            listModel.append({name:"View Data"})
            listModel.append({name:"Weld Default"})
            listModel.append({name:"Data Communication"})
            listModel.append({name:"Lock On Alarm"})
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
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 150
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
        anchors.bottomMargin: 40
        width: 300
        height: 79
        text: qsTr("Initial Fram")
        textColor: "white"
    }
    CButton {
        id: okButton
        anchors.right: parent.right
        anchors.rightMargin: 20
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 40
        width: 300
        height: 79
        text: qsTr("OK")
        iconSource: "qrc:/images/images/OK.png"
        textColor: "white"
    }
    CButton {
        id: cancelButton
        anchors.right: okButton.left
        anchors.rightMargin: 43
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 40
        width: 300
        height: 79
        text: qsTr("Cancel")
        textColor: "white"
        iconSource: "qrc:/images/images/cancel.png"
        onClicked: {
        }
    }
}
