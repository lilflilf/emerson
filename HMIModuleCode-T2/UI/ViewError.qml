import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import QtQuick.Dialogs 1.2

Item {
    id: viewError
    width: Screen.width*0.7
    height: Screen.height*0.6

    MyTimeSelect {
        id: newCalendar
        anchors.centerIn: parent
        z: 12
        visible: false
    }
    ListView {
        id: listView
        anchors.top: tipsRec.bottom
        anchors.topMargin: 5
        anchors.bottom: scrollbar2.top
        anchors.left: headTitle.left
        anchors.leftMargin: 20
        width: headTitle.width
        clip: true
        model: alarmModel
        delegate: listDelegate
    }

    CButton {
        id: exportdata
        width: 300
        anchors.right: parent.right
        anchors.bottom:  parent.bottom
        text: qsTr("Export Data")
        anchors.bottomMargin: 10
        anchors.rightMargin: 20
    }

    Rectangle {
        id: back
        width: parent.width * 0.3
        height: parent.height
        color: "#052a40"
        z: 10

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
        Line {
            id: line
            anchors.top: seach.bottom
            anchors.topMargin: 10
            anchors.left: parent.left
            anchors.leftMargin: 10
            width: parent.width-58
            height: 1
            lineColor: "#375566"
        }

        Item {
            id: searchArea
            property int selectNum: -2
            property int buttonIndex: -1
            anchors.left: seach.left
            anchors.right: parent.right
            anchors.rightMargin: 48
            anchors.top: seach.bottom
            anchors.bottom: parent.bottom
            z: 12
            visible: false
            Image {
                anchors.fill: parent
                source: "qrc:/images/images/bg.png"
            }
            ExclusiveGroup {
                id: searchMos
            }
            Text {
                id: allText
                anchors.top: parent.top
                anchors.left: parent.left
                anchors.leftMargin: 6
                font.family: "arial"
                font.pixelSize: 16
                verticalAlignment: Qt.AlignVCenter
                width: parent.width
                height: 40
                color: "white"
                text: qsTr("All")
                MouseArea {
                    anchors.top: parent.top
                    anchors.left: parent.left
                    anchors.leftMargin: -6
                    width: parent.width
                    height: parent.height
                    onClicked: {
                        searchArea.selectNum = -2
                        selectCheck.checked = !selectCheck.checked
                    }
                }
                Rectangle {
                    id: backGround
                    anchors.top: parent.top
                    anchors.left: parent.left
                    anchors.leftMargin: -6
                    width: parent.width
                    height: parent.height
                    color: "black"
                    opacity: 0.3//opacityValue
                    RadioButton {
                        id: selectCheck
                        exclusiveGroup: searchMos
                        visible: false
                        checked: true
                        onCheckedChanged: {
                            if (checked)
                                backGround.opacity = 0.3
                            else
                                backGround.opacity = 0
                        }
                    }
                }
            }

            ListView {
                id: searchList
                anchors.top: allText.bottom
                anchors.left: parent.left
                width: parent.width
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 20 + exportdata.height
                clip: true
                model: alarmModel
                delegate: Component {
                    id: seachComponent
                    Item {
                        width: searchList.width
                        height: 40
                        Text {
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.left: parent.left
                            anchors.leftMargin: 6
                            font.family: "arial"
                            font.pixelSize: 16
                            color: "white"
                            elide: Text.ElideRight
                            text: Alarm/ErrorType
                        }
                        MouseArea {
                            anchors.fill: parent
                            onClicked: {
                                searchArea.selectNum = index
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
                                exclusiveGroup: searchMos
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
            CButton {
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 10
                anchors.left: parent.left
                width: parent.width
                text: qsTr("OK")
                iconSource: "qrc:/images/images/OK.png"
                onClicked: {
                    if (searchArea.selectNum != -2) {
                        searchArea.visible = false
                        workOrderName.text = searchList.model.getAlarmValue(searchArea.selectNum,"Alarm/ErrorType")
                    } else {
                        searchArea.visible = false
                        workOrderName.text = qsTr("All")
                    }
                }
            }
        }

        Text {
            id: title2
            text: qsTr("Alarm/ErrorType")
            font.family: "arial"
            color: "white"
            font.pointSize: 16
            anchors.top: line.bottom
            anchors.topMargin: 10
            anchors.left: seach.left
        }
        CButton {
            id: workOrderName
            anchors.left: title2.left
            anchors.leftMargin: 10
            anchors.right: parent.right
            anchors.rightMargin: 48
            anchors.top: title2.bottom
            text: qsTr("All")
            clip: true
            height: mytimeSelect1.height
            backgroundComponent: Rectangle {
                anchors.fill: parent
                color: "#052a40"
                border.color: "#1987ab"
                border.width: 2
            }
            onClicked: {
                searchArea.visible = true
            }
        }
        Text {
            id: date
            text: qsTr("Date and Time")
            font.family: "arial"
            color: "white"
            font.pointSize: 16
            anchors.top: workOrderName.bottom
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
        }
        ExclusiveGroup {
            id: timeSelectGroup
        }

        MyCalendar {
            id: mycalendar1
            anchors.left: from.left
            anchors.leftMargin: 10
            anchors.top: from.bottom
            width: (parent.width-98)/2
            bIsdate: true
            selecter: newCalendar
            exclusiveGroup: timeSelectGroup
        }

        MyCalendar {
            id: mytimeSelect1
            width: (parent.width-98)/2
            anchors.top: mycalendar1.top
            anchors.left: mycalendar1.right
            anchors.leftMargin: 20
            bIsdate: false
            selecter: newCalendar
            exclusiveGroup: timeSelectGroup
        }

        Text {
            id: to
            text: qsTr("To:")
            font.family: "arial"
            color: "white"
            font.pointSize: 16
            anchors.top: mycalendar1.bottom
            anchors.left: parent.left
            anchors.leftMargin: 20
        }

        MyCalendar {
            id: mycalendar2
            anchors.left: from.left
            anchors.leftMargin: 10
            anchors.top: to.bottom
            width: (parent.width-98)/2
            bIsdate: true
            selecter: newCalendar
            exclusiveGroup: timeSelectGroup
        }

        MyCalendar {
            id: mytimeSelect2
            width: (parent.width-98)/2
            anchors.top: mycalendar2.top
            anchors.left: mycalendar2.right
            anchors.leftMargin: 20
            bIsdate: false
            selecter: newCalendar
            exclusiveGroup: timeSelectGroup
        }

        Column {
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 10
            anchors.left: parent.left
            anchors.leftMargin: 30
            anchors.right: parent.right
            anchors.rightMargin: 48
            spacing: 10
            CButton {
                id: applyButton
                width: parent.width
                text: qsTr("APPLY")
                onClicked: {
                    if (newCalendar.visible)
                        newCalendar.visible = false
                    var fromtime = hmiAdaptor.timeChangeToInt(mycalendar1.text + " " + mytimeSelect1.text)
                    var totime = hmiAdaptor.timeChangeToInt(mycalendar2.text + " " + mytimeSelect2.text)
                    alarmModel.searchAlarmLog(workOrderName.text,fromtime,totime)
                }
            }
//            CButton {
//                id: backButton
//                width: parent.width
//                text: qsTr("Back")
//            }
        }

    }
    //    list << "CreatedDate" << "Alarm/ErrorType" << "Alarm/ErrorLevel" << "Message" << "SpliceName";
    Image {
        id: scrollUp
        anchors.top: tipsRec.bottom
        anchors.topMargin: 2
        anchors.right: parent.right
        anchors.rightMargin: 6
        width: 17
        height: 10
        visible: listView.contentHeight > listView.height ? true : false
        source: "qrc:/images/images/up.png"
    }
    Image {
        id: scrollDown
        anchors.bottom: scrollbar2.top
        anchors.bottomMargin: 2
        anchors.right: parent.right
        anchors.rightMargin: 6
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
        anchors.right: parent.right
        anchors.rightMargin: 8
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
        anchors.verticalCenter:scrollbar2.verticalCenter
        anchors.left: back.right
        anchors.leftMargin: 11
        width: 11
        height: 17
        visible: true
        source: "qrc:/images/images/left.png"
    }
    Image {
        id: scrollRight
        anchors.verticalCenter:scrollbar2.verticalCenter
        anchors.left: scrollbar2.right
        width: 11
        height: 17
        visible: true
        source: "qrc:/images/images/right.png"
    }

    Rectangle {
        id: scrollbar2
        anchors.left: scrollLeft.right
        anchors.bottom: exportdata.top
        anchors.bottomMargin: 20
        anchors.right: parent.right
        anchors.rightMargin: 22
        height: 17
        color: "#585858"
        radius: 10
        visible: true
        Rectangle {
            id: button2
            anchors.top: parent.top
            x: 0
            width: scrollbar2.width / listView.width * scrollbar2.width
            height: 17
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
                listView.anchors.leftMargin = -button2.x*1.1 + 20
                headTitle.anchors.leftMargin = -button2.x*1.1 +20
            }
        }
    }


    ListModel {
        id: alarmTitleModel
        ListElement {title:qsTr("CreatedDate")}
        ListElement {title:qsTr("Alarm/ErrorType")}
        ListElement {title:qsTr("Alarm/ErrorLevel")}
        ListElement {title:qsTr("Message")}
        ListElement {title:qsTr("SpliceName")}
    }
    Row {
        id: headTitle
        anchors.top: parent.top
        anchors.topMargin: 15
        anchors.left: back.right
        anchors.leftMargin: 20
        spacing: 30
        clip: true
        Repeater {
            id: headRepeater
            model: alarmTitleModel
            delegate:  Text {
                verticalAlignment: Qt.AlignVCenter
                width: 200
                font.family: "arial"
                font.pixelSize: 25
                color: "white"
                clip: true
                text: title
            }
        }
    }
    Rectangle {
        id: tipsRec
        anchors.top: headTitle.bottom
        anchors.topMargin: 10
        anchors.left: back.right
        anchors.leftMargin: 20
        anchors.right: parent.right
        anchors.rightMargin: 20
        clip: true
        height: 1
        color: "#ffffff"
    }
    Rectangle {
        id: tipsRec2
        anchors.top: tipsRec.bottom
        anchors.left: back.right
        anchors.leftMargin: 20
        anchors.right: parent.right
        anchors.rightMargin: 20
        clip: true
        height: 1
        color: "#0d0f11"
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
                    model: viewLib.count
                    delegate:  Text {
                        anchors.verticalCenter: parent.verticalCenter
                        width: 200
                        font.family: "arial"
                        font.pixelSize: 20
                        color: "white"
                        clip: true
                        elide: Text.ElideRight
                        text: listView.model.getValue(listIndex,headRepeater.model.get(index).title)
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

