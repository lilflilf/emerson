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
        anchors.leftMargin: 20
        anchors.rightMargin: 10
        anchors.bottomMargin: 150

        ListView {
            id: listView
            anchors.left: parent.left
            anchors.top: headRows.bottom
            anchors.topMargin: 20
            anchors.bottom: parent.bottom
            model: weldHistoryModel
            delegate: listDelegate
            width: headModel.count * 200 + (headModel.count - 1) * 30
            clip: true
        }
        ListModel {
            id: headModel
            ListElement {key:"WorkOrde Name"}
            ListElement {key:"PartName"}
            ListElement {key:"SpliceName"}
            ListElement {key:"OperatorName"}
            ListElement {key:"DateCreated"}
            ListElement {key:"Cross ection"}
            ListElement {key:"WeldMode"}
            ListElement {key:"Energy"}
            ListElement {key:"Amplitude"}
            ListElement {key:"Width"}
            ListElement {key:"TriggerPressure"}
            ListElement {key:"Weld Pressure"}
            ListElement {key:"Time+"}
            ListElement {key:"Timer-"}
            ListElement {key:"Time"}
            ListElement {key:"Power+"}
            ListElement {key:"Power-"}
            ListElement {key:"Power"}
            ListElement {key:"Pre-Height+"}
            ListElement {key:"Pre-Height-"}
            ListElement {key:"Pre-Height"}
            ListElement {key:"Height+"}
            ListElement {key:"Height-"}
            ListElement {key:"Height"}
            ListElement {key:"Alarm"}
            ListElement {key:"SampleRatio"}
            ListElement {key:"GraphData"}

        }

        Row {
            id: headRows
            anchors.left: listView.left
            spacing: 30
            Repeater {
                delegate: Text {
                    id: headName
                    width: 200
                    horizontalAlignment: Qt.AlignLeft
                    verticalAlignment: Qt.AlignVCenter
                    elide: Text.ElideRight
                    text: key
                    clip: true
                    color: "white"
                    font.pointSize: 20
                    font.family: "arial"
                }
                model: headModel
            }
        }
        Line {
            width: listView.width
            anchors.left: headRows.left
            anchors.top: headRows.bottom
            height: 2
            lineColor: "white"
        }
    }

    CButton {
        id: exportData
        width: 250
        height: 79
        anchors.right: rightItem.right
        anchors.top: rightItem.bottom
        anchors.topMargin: 50
        text: qsTr("Export Data")
    }

    Image {
        id: back
        width: 300
        height: parent.height
        source: "qrc:/images/images/bg.png"
    }

//    Rectangle {
//        id: back
//        width: 300//parent.width * 0.25
//        height: parent.height
//        color: "black"
//        opacity: 0.3
//    }
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

    ComboBox {
        id: nameComboBox
        width: 250
        height: 30
        anchors.left: title2.left
        anchors.top: title2.bottom
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
    Text {
        id: from
        text: qsTr("From:")
        font.family: "arial"
        color: "white"
        font.pointSize: 16
        anchors.top: date.bottom
        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.topMargin: 10
    }
    MyCalendar {
        id: mycalendar
        anchors.left: from.left
        anchors.top: from.bottom
        width: 125
        z: 10
    }
    MyTimeSelect {
        width: 125
        anchors.top: mycalendar.top
        anchors.left: mycalendar.right
        anchors.leftMargin: 20
        z: 11

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
        anchors.left: from.left
        anchors.top: to.bottom
        width: 125
        z: 10
    }
    MyTimeSelect {
        width: 125
        anchors.top: mycalendar2.top
        anchors.left: mycalendar2.right
        anchors.leftMargin: 20
        z: 10
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

    ComboBox {
        id: spliceComboBox
        width: 250
        height: 30
        anchors.left: title3.left
        anchors.top: title3.bottom
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
            width: 250
            height: 79
            text: qsTr("APPLY")
        }
        CButton {
            id: backButton
            width: 250
            height: 79
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
        anchors.leftMargin: -10
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
    }
    Image {
        id: scrollRight
        anchors.bottom: rightItem.bottom
        anchors.left: scrollbar2.right
        width: 11
        height: 17
        visible: true //listView.contentHeight > listView.height ? true : false
        source: "qrc:/images/images/right.png"
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

                listView.anchors.leftMargin = -button2.x / scrollbar2.width * listView.width
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
            property var listIndex: 0
            Component.onCompleted: {
                listIndex = index
            }

            Row {
                width: parent.width
                height: parent.height
                spacing: 30
                clip: true
                Repeater {
                    id: listRepeater
                    model: 10
                    delegate:  Text {
                        anchors.verticalCenter: parent.verticalCenter
                        width: 200
                        font.family: "arial"
                        font.pixelSize: 20
                        color: "white"
                        clip: true
                        elide: Text.ElideRight
                        text: listView.model.getValue(listIndex,headModel.get(index).title)
                    }
                }
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
