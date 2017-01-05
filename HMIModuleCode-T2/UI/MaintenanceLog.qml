import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import QtQuick.Dialogs 1.2

Item {
    id: toolChange
    width: Screen.width*0.7
    height: Screen.height*0.6

    MyTimeSelect {
        id: newCalendar
        anchors.centerIn: parent
        z: 12
        visible: false
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
            font.pointSize: 18
            anchors.top: parent.top
            anchors.topMargin: 20
            anchors.left: parent.left
            anchors.leftMargin: 20
        }
        Line {
            id: line1
            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.top: seach.bottom
            anchors.topMargin: 20
            width: parent.width-58
            lineColor: "#375566"
            height: 1
        }
        Item {
            id: searchArea
            property int selectNum: -2
            property int buttonIndex: -1
            anchors.left: parent.left
            anchors.leftMargin: 10
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

            ListModel {
                id: mySearchMode
                ListElement {Type:qsTr("Calibration")}
                ListElement {Type:qsTr("Tooling Change")}
                ListElement {Type:qsTr("Advanced Maintenance")}
                ListElement {Type:qsTr("Maintenance Counter")}
            }

            ListView {
                id: searchList
                anchors.top: allText.bottom
                anchors.left: parent.left
                width: parent.width
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 100
                clip: true
                model: mySearchMode //testModel
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
                            text: Type
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
                text: qsTr("OK")
                iconSource: "qrc:/images/images/OK.png"

                onClicked: {
                    if (searchArea.selectNum != -2) {
                        searchArea.visible = false
                        workOrderName.text = searchList.model.get(searchArea.selectNum).Type
                    } else {
                        searchArea.visible = false
                        workOrderName.text = qsTr("All")
                    }
                }
            }
        }

        Text {
            id: title2
            text: qsTr("Maintenance Type")
            font.family: "arial"
            color: "white"
            font.pointSize: 16
            anchors.top: line1.bottom
            anchors.topMargin: 10
            anchors.left: seach.left
        }
        CButton {
            id: workOrderName
            anchors.left: title2.left
            anchors.leftMargin: 10
            anchors.top: title2.bottom
            anchors.right: parent.right
            anchors.rightMargin: 48
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

        Line {
            id: line3
            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.top: mytimeSelect2.bottom
            anchors.topMargin: 10
            width: parent.width-58
            lineColor: "#375566"
            height: 1
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
                    if (newCalendar.visible) {
                        newCalendar.visible = false
                    }
                    var fromtime = hmiAdaptor.timeChangeToInt(mycalendar1.text + " " + mytimeSelect1.text)
                    var totime = hmiAdaptor.timeChangeToInt(mycalendar2.text + " " + mytimeSelect2.text)
                    maintenanceLogModel.searchMaintenanceLog(workOrderName.text,fromtime,totime)
                }
            }
//            CButton {
//                id: backButton
//                width: parent.width
//                text: qsTr("Back")
//            }
        }
    }

    ListModel {
        id: headModel
        ListElement {key:qsTr("CreatedDate")}
        ListElement {key:qsTr("OperatorName")}
        ListElement {key:qsTr("Type")}
        ListElement {key:qsTr("Message")}
    }

    Row {
        id: headRows
        anchors.left: back.right
        anchors.leftMargin: 15
        spacing: 30
        anchors.top: parent.top
        anchors.topMargin: 20
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
                font.pixelSize: 25
                font.family: "arial"
            }
            model: headModel
        }
    }
    Line {
        width: headRows.width
        anchors.left: headRows.left
        anchors.top: headRows.bottom
        anchors.topMargin: 10
        height: 2
        lineColor: "white"
    }

    ListView {
        id: listView
        anchors.left: headRows.left
        anchors.top: headRows.bottom
        anchors.topMargin: 5
        anchors.bottom: line2.top
        anchors.bottomMargin: 20
        model: maintenanceLogModel
        delegate: listDelegate
        width: headRows.width // headModel.count * 200 + (headModel.count - 1) * 30
        clip: true
    }

    Line {
        id: line2
        width: headRows.width
        anchors.left: headRows.left
        anchors.bottom: exportButton.top
        anchors.bottomMargin: 10
        height: 2
        lineColor: "white"
    }

    CButton {
        id: exportButton
        width: 200
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 20
        anchors.right: parent.right
        anchors.rightMargin: 20
        text: qsTr("Export Data")
        iconSource: "qrc:/images/images/export.png"
    }

    ExclusiveGroup {
        id: positionGroup
    }

    Component {
        id: listDelegate
        Item {
            id: listItem
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
                    model: headModel.count
                    delegate:  Text {
                        id: tempText
                        property var newObject: null
                        anchors.verticalCenter: parent.verticalCenter
                        width: 200
                        font.family: "arial"
                        font.pixelSize: 20
                        color: "white"
                        clip: true
                        elide: Text.ElideRight
                        text: maintenanceLogModel.getValue(listItem.listIndex,headModel.get(index).key)
                        MouseArea {
                            anchors.fill: parent
//                            z:10
                            hoverEnabled: true
                            onEntered: {
//                                tempText.color = "red"
                                tempText.newObject = Qt.createQmlObject('import QtQuick 2.0;Rectangle {color: "#052a40";property alias mytext: tempText.text;height: tempText.height;width:tempText.width;z:11; Text {id: tempText;anchors.verticalCenter: parent.verticalCenter;text: qsTr("")
;font.family: "arial";font.pixelSize: 20;color: "white";wrapMode: Text.WordWrap; maximumLineCount: 10}}',listView,"");
                                tempText.newObject.mytext = tempText.text
//                                if (tempText.width > 600)
//                                    tempText.width = 600
                                tempText.newObject.x = tempText.x
                                tempText.newObject.y = tempText.y + listIndex * 50
//                                tempText.newObject.width = tempText.width
//                                tempText.newObject.height = tempText.height

                            }
                            onExited: {
                                tempText.color = "white"
                                tempText.newObject.destroy()
                            }
                        }
                    }
                }
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
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
                    visible: false
                    exclusiveGroup: positionGroup
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
