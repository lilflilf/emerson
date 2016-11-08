import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import QtQuick.Dialogs 1.2

Item {
    id: toolChange
    property int selectIndx: -1
    width: Screen.width*0.7
    height: Screen.height*0.6

    Item {
        id: rightItem
        anchors.left: back.right
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.leftMargin: 10
        anchors.rightMargin: 10
        anchors.bottomMargin: 150

        ListView {
            id: listView
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.leftMargin: 10
            model: workOrderModel
            delegate: listDelegate
            width: 3000
            clip: true

        }
    }

    Image {
        width: parent.width * 0.3
        height: parent.height
        source: "qrc:/images/images/bg.png"
    }

    Rectangle {
        id: back
        width: parent.width * 0.3
        height: parent.height
        color: "black"
        opacity: 0.3
    }
    Text {
        id: seach
        text: qsTr("Seach")
        font.family: "arial"
        color: "white"
        font.pointSize: 16
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.topMargin: 10
    }
    Text {
        id: title2
        text: qsTr("Maintenance type")
        font.family: "arial"
        color: "white"
        font.pointSize: 16
        anchors.top: seach.bottom
        anchors.left: seach.left
        anchors.topMargin: 10
    }

    ExclusiveGroup {
        id: checkGroup1
    }
    Item {
        id: item1
        anchors.top: title2.bottom
        anchors.topMargin: 10
        anchors.left: title2.left
        CheckBox {
            id: check1
            scale: 2
            exclusiveGroup: checkGroup1
            anchors.verticalCenter: parent.verticalCenter
        }
        Text {
            text: qsTr("All")
            font.family: "arial"
            color: "white"
            font.pointSize: 14
            anchors.left: parent.right
            anchors.leftMargin: 20
            anchors.verticalCenter: parent.verticalCenter
        }
    }

    Item {
        id: item2
        anchors.top: item1.bottom
        anchors.topMargin: 30
        anchors.left: item1.left
        CheckBox {
            id: check2
            scale: 2
            exclusiveGroup: checkGroup1
            anchors.verticalCenter: parent.verticalCenter
        }
        Text {
            text: qsTr("Select")
            font.family: "arial"
            color: "white"
            font.pointSize: 14
            anchors.left: parent.right
            anchors.leftMargin: 20
            anchors.verticalCenter: parent.verticalCenter
        }
    }

    ComboBox {
        id: nameComboBox
        width: 300
        height: 30
        anchors.left: title2.left
        anchors.top: item2.bottom
        anchors.topMargin: 20
        model: ["First", "Second", "Third"]
    }

    Text {
        id: date
        text: qsTr("Date and Time")
        font.family: "arial"
        color: "white"
        font.pointSize: 16
        anchors.top: nameComboBox.bottom
        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.topMargin: 10
    }

    ExclusiveGroup {
        id: checkGroup2
    }
    Item {
        id: item3
        anchors.top: date.bottom
        anchors.topMargin: 10
        anchors.left: title2.left
        CheckBox {
            id: check3
            scale: 2
            exclusiveGroup: checkGroup2
            anchors.verticalCenter: parent.verticalCenter
        }
        Text {
            text: qsTr("All")
            font.family: "arial"
            color: "white"
            font.pointSize: 14
            anchors.left: parent.right
            anchors.leftMargin: 20
            anchors.verticalCenter: parent.verticalCenter
        }
    }

    Item {
        id: item4
        anchors.top: item3.bottom
        anchors.topMargin: 30
        anchors.left: item1.left
        CheckBox {
            id: check4
            scale: 2
            exclusiveGroup: checkGroup2
            anchors.verticalCenter: parent.verticalCenter
        }
        Text {
            text: qsTr("Select")
            font.family: "arial"
            color: "white"
            font.pointSize: 14
            anchors.left: parent.right
            anchors.leftMargin: 20
            anchors.verticalCenter: parent.verticalCenter
        }
    }
    Text {
        id: from
        text: qsTr("From:")
        font.family: "arial"
        color: "white"
        font.pointSize: 16
        anchors.top: item4.bottom
        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.topMargin: 10
    }
    MyCalendar {
        id: mycalendar
        anchors.left: item1.left
        anchors.top: from.bottom
        width: 150
    }
    MyTimeSelect {
        width: 150
        anchors.top: mycalendar.top
        anchors.left: mycalendar.right
        anchors.leftMargin: 20
    }
    Text {
        id: to
        text: qsTr("To:")
        font.family: "arial"
        color: "white"
        font.pointSize: 16
        anchors.top: mycalendar.bottom
        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.topMargin: 10
    }
    MyCalendar {
        id: mycalendar2
        anchors.left: item1.left
        anchors.top: to.bottom
        width: 150
    }
    MyTimeSelect {
        width: 150
        anchors.top: mycalendar2.top
        anchors.left: mycalendar2.right
        anchors.leftMargin: 20
    }

    Text {
        id: title3
        text: qsTr("Splice Part Number")
        font.family: "arial"
        color: "white"
        font.pointSize: 16
        anchors.top: mycalendar2.bottom
        anchors.left: seach.left
        anchors.topMargin: 10
    }

    ExclusiveGroup {
        id: checkGroup3
    }
    Item {
        id: item5
        anchors.top: title3.bottom
        anchors.topMargin: 10
        anchors.left: title3.left
        CheckBox {
            id: check5
            scale: 2
            exclusiveGroup: checkGroup3
            anchors.verticalCenter: parent.verticalCenter
        }
        Text {
            text: qsTr("All")
            font.family: "arial"
            color: "white"
            font.pointSize: 14
            anchors.left: parent.right
            anchors.leftMargin: 20
            anchors.verticalCenter: parent.verticalCenter
        }
    }

    Item {
        id: item6
        anchors.top: item5.bottom
        anchors.topMargin: 30
        anchors.left: item5.left
        CheckBox {
            id: check6
            scale: 2
            exclusiveGroup: checkGroup3
            anchors.verticalCenter: parent.verticalCenter
        }
        Text {
            text: qsTr("Select")
            font.family: "arial"
            color: "white"
            font.pointSize: 14
            anchors.left: parent.right
            anchors.leftMargin: 20
            anchors.verticalCenter: parent.verticalCenter
        }
    }

    ComboBox {
        id: spliceComboBox
        width: 300
        height: 30
        anchors.left: title3.left
        anchors.top: item6.bottom
        anchors.topMargin: 20
        model: ["First", "Second", "Third"]
    }

    Column {
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.leftMargin: 20
        spacing: 10
        CButton {
            id: applyButton
            width: 300
            height: 70
            text: qsTr("APPLY")
        }
        CButton {
            id: backButton
            width: 300
            height: 70
            text: qsTr("Back")
        }
    }


//    ListView {
//        id: listView
//        anchors.left: back.right
////        anchors.right: parent.right
//        anchors.top: parent.top
//        anchors.bottom: parent.bottom
//        anchors.leftMargin: 10
////        anchors.rightMargin: 10
//        anchors.bottomMargin: 150
//        model: workOrderModel
//        delegate: listDelegate
//    }

    Image {
        id: scrollUp
        anchors.top: rightItem.top
        anchors.topMargin: 2
        anchors.left: rightItem.right
        width: 17
        height: 10
        visible: listView.contentHeight > listView.height ? true : false
        source: "qrc:/images/images/up.png"
    }
    Image {
        id: scrollDown
        anchors.bottom: rightItem.bottom
        anchors.bottomMargin: 2
        anchors.left: rightItem.right
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
        anchors.left: rightItem.right
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


    Image {
        id: scrollLeft
        anchors.bottom: rightItem.bottom
        anchors.right: scrollbar2.left
        width: 11
        height: 17
        visible: true //listView.contentHeight > listView.height ? true : false
        source: "qrc:/images/images/left.png"
        z: 10
    }
    Image {
        id: scrollRight
        anchors.bottom: rightItem.bottom
        anchors.left: scrollbar2.right
        width: 11
        height: 17
        visible: true //listView.contentHeight > listView.height ? true : false
        source: "qrc:/images/images/right.png"
        z: 10
    }
    Rectangle {
        id: scrollbar2
        width: rightItem.width
        height: 17
        anchors.bottom: rightItem.bottom
        anchors.left: rightItem.left
        anchors.right: rightItem.right
        color: "#585858"
        radius: 10
        visible: true //listView.contentHeight > listView.height ? true : false
        Rectangle {
            id: button2
            anchors.top: parent.top
            x: 0
//            y: (listView.visibleArea.yPosition < 0 ) ? 0 : (listView.contentY+listView.height>listView.contentHeight) ?
//                scrollbar2.height - button2.height : listView.visibleArea.yPosition * scrollbar2.height
            width: scrollbar2.width / listView.width * scrollbar2.width //50
            height: 17 //listView.visibleArea.heightRatio * scrollbar2.height;
            color: "#ccbfbf"
            radius: 10
            // 鼠标区域
            MouseArea {
                id: mouseArea2
                anchors.fill: button2
                drag.target: button2
                drag.axis: Drag.XAxis
                drag.minimumX: 0
                drag.maximumX: scrollbar2.width - button2.width
            }
            onXChanged: {
                listView.anchors.leftMargin = -button2.x
                console.log(button2.x)
            }
        }
    }



    ExclusiveGroup {
        id: listviewPositionGroup
    }

    Component {
        id: listDelegate
        Item {
            width: listView.width
            height: 50
            clip: true
            Text {
                id: headName
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                anchors.leftMargin: 48
                width: (parent.width-96)/4
                horizontalAlignment: Qt.AlignLeft
                elide: Text.ElideRight
                text: name
                clip: true
                color: "white"
                font.pointSize: 14
                font.family: "arial"
            }
            Text {
                id: headData
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: headName.right
                width: (parent.width-96)/4
                horizontalAlignment: Qt.AlignCenter
                text: date
                clip: true
                color: "white"
                font.pointSize: 14
                font.family: "arial"
            }
            Text {
                id: headMiddle
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: headData.right
                width: (parent.width-96)/4
                horizontalAlignment: Qt.AlignLeft
                text: middle
                elide: Text.ElideRight
                clip: true
                color: "white"
                font.pointSize: 14
                font.family: "arial"
            }
            Text {
                id: headCount
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: headMiddle.right
                anchors.leftMargin: (parent.width-96)/12
                horizontalAlignment: Qt.AlignLeft
                width: (parent.width-96)/12
                text: count
                elide: Text.ElideRight
                color: "white"
                clip: true
                font.pointSize: 14
                font.family: "arial"
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    selectIndx = index
                    selectCheck.checked = !selectCheck.checked
                }
            }
            Rectangle {
                id: backGround
                anchors.fill: parent
                color: "black"
                opacity: 0//opacityValue
                RadioButton {
                    id: selectCheck
                    exclusiveGroup: listviewPositionGroup
                    visible: false
                    onCheckedChanged: {
                        if (checked)
                            backGround.opacity = 0.3
                        else
                            backGround.opacity = 0
                    }
                }
            }
        }
    }
}
