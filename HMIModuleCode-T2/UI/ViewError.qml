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

    ListView {
        id: listView
        anchors.top: headTitle.bottom
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 150
        anchors.left: headTitle.left
        anchors.leftMargin: 20
        width: headTitle.width
        clip: true
        model: alarmModel
        delegate: listDelegate
    }
    CButton {
        width: 300
        height: 79
        anchors.right: parent.right
        anchors.top: listView.bottom
        text: qsTr("Export Data")
        anchors.topMargin: 50
        anchors.rightMargin: 30
    }

    Image {
        id: back
        width: 300 //parent.width * 0.3
        height: parent.height
        source: "qrc:/images/images/bg.png"
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

        ListModel {
            id: testModel
            Component.onCompleted: {
                testModel.append({"name":"test name A"})
                testModel.append({"name":"test name A"})
                testModel.append({"name":"test name A"})
                testModel.append({"name":"test name A"})
                testModel.append({"name":"test name A"})
                testModel.append({"name":"test name A"})
                testModel.append({"name":"test name A"})
                testModel.append({"name":"test name A"})
                testModel.append({"name":"test name A"})
                testModel.append({"name":"test name A"})
                testModel.append({"name":"test name A"})
                testModel.append({"name":"test name A"})
                testModel.append({"name":"test name A"})
                testModel.append({"name":"test name A"})
                testModel.append({"name":"test name A"})
                testModel.append({"name":"test name A"})
                testModel.append({"name":"test name A"})
                testModel.append({"name":"test name A"})
                testModel.append({"name":"test name A"})
            }
        }
        Item {
            id: searchArea
            property int selectNum: -1
            anchors.left: seach.left
            width: 280
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
            ListView {
                id: searchList
                anchors.top: parent.top
                anchors.left: parent.left
                width: parent.width
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 100
                clip: true
                model: testModel
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
                            text: qsTr(name)
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
                width: parent.width
                height: 79
                text: qsTr("OK")
                iconSource: "qrc:/images/images/OK.png"
                onClicked: {
                    if (searchArea.selectNum != -1) {
                        searchArea.visible = false
                        switch(searchButton.buttonIndex) {
                        case 1:
                            workOrderName.text = testModel.get(searchArea.selectNum).name
                            break;
                        case 2:
                            partName.text = testModel.get(searchArea.selectNum).name
                            break;
                        case 3:
                            spliceName.text = testModel.get(searchArea.selectNum).name
                            break;
                        default:
                            break;
                        }
                    }
                }
            }
        }

        Column {
            id: searchButton
            property int buttonIndex: -1
            anchors.left: parent.left
            anchors.leftMargin: 20
            anchors.top: seach.bottom
            anchors.bottomMargin: 10
            spacing: 10
            clip: true
            CButton {
                id: workOrderName
                width: 250
                height: 60
                text: qsTr("Work Order Name")
                clip: true
                onClicked: {
                    searchButton.buttonIndex = 1
                    searchArea.visible = true
                }
            }
            CButton {
                id: partName
                width: 250
                height: 60
                text: qsTr("Part Name")
                clip: true
                onClicked: {
                    searchButton.buttonIndex = 2
                    searchArea.visible = true
                }
            }
            CButton {
                id: spliceName
                width: 250
                height: 60
                text: qsTr("Splice Number")
                clip: true
                onClicked: {
                    searchButton.buttonIndex = 3
                    searchArea.visible = true
                }
            }
        }
        Text {
            id: title2
            text: qsTr("Maintenance type")
            font.family: "arial"
            color: "white"
            font.pointSize: 16
            anchors.top: searchButton.bottom
            anchors.topMargin: 15
            anchors.left: seach.left
        }

        ComboBox {
            id: nameComboBox
            width: 200
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
            anchors.left: to.left
            anchors.topMargin: 15
        }
        ComboBox {
            id: spliceComboBox
            width: 250
            height: 30
            anchors.left: title3.left
            anchors.top: title3.bottom
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
                height: 70
                text: qsTr("APPLY")
            }
            CButton {
                id: backButton
                width: 250
                height: 70
                text: qsTr("Back")
            }
        }

    }
    //    list << "CreatedDate" << "Alarm/ErrorType" << "Alarm/ErrorLevel" << "Message" << "SpliceName";
    Image {
        id: scrollLeft
        anchors.verticalCenter:scrollbar2.verticalCenter
        anchors.right: scrollbar2.left
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
        anchors.left: back.right
        anchors.leftMargin: 11
        anchors.top: listView.bottom
        anchors.right: parent.right
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
                listView.anchors.leftMargin = -button2.x*1.1
                headTitle.anchors.leftMargin = -button2.x*1.1
            }
        }
    }


    ListModel {
        id: alarmTitleModel
        ListElement {title:"CreatedDate"}
        ListElement {title:"Alarm/ErrorType"}
        ListElement {title:"Alarm/ErrorLevel"}
        ListElement {title:"Message"}
        ListElement {title:"SpliceName"}
    }

    Row {
        id: headTitle
        anchors.top: parent.top
        anchors.topMargin: 30
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
                font.pixelSize: 20
                color: "white"
                clip: true
                text: qsTr(title)
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

