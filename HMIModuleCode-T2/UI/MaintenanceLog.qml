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
            property int selectNum: -2
            property int buttonIndex: -1
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
            Text {
                id: allText
                anchors.top: parent.top
                anchors.left: parent.left
                anchors.leftMargin: 6
                font.family: "arial"
                font.pixelSize: 16
                verticalAlignment: Qt.AlignVCenter
                width: 280
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
                    if (searchArea.selectNum != -2) {
                        searchArea.visible = false
                        workOrderName.text = testModel.get(searchArea.selectNum).name
                    } else {
                        searchArea.visible = false
                        workOrderName.text = "All"
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
            anchors.top: seach.bottom
            anchors.topMargin: 15
            anchors.left: seach.left
        }
        CButton {
            id: workOrderName
            anchors.left: title2.left
            anchors.top: title2.bottom
            width: 250
            height: 50
            text: qsTr("All")
            clip: true
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
        Column {
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 10
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
    }



    ListModel {
        id: headModel
        ListElement {key:"CreatedDate"}
        ListElement {key:"OperatorName"}
        ListElement {key:"Type"}
        ListElement {key:"Message"}
    }

    Row {
        id: headRows
        anchors.left: back.right
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
                font.pointSize: 20
                font.family: "arial"
            }
            model: headModel
        }
    }
    Line {
        width: headRows.width
        anchors.left: headRows.left
        anchors.top: headRows.bottom
        height: 2
        lineColor: "white"
    }
}
