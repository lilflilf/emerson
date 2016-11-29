import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import QtQuick.Dialogs 1.2

Item {
    id: viewTrend
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
                visible: false
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
                anchors.top: parent.top
                anchors.left: parent.left
                width: parent.width
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 20
                clip: true
                model: spliceModel
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
                            text: qsTr(SpliceName)
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
                        workOrderName.text = searchList.model.getValue(searchArea.selectNum,"SpliceName")
                    } else {
                        searchArea.visible = false
                        workOrderName.text = "All"
                    }
                }
            }
        }

        Text {
            id: title2
            text: qsTr("Splice Number")
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
            text: qsTr("Click to Select")
            clip: true
            height: mytimeSelect.height
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
        id: mycalendar
        anchors.left: from.left
        anchors.leftMargin: 10
        anchors.top: from.bottom
        width: (parent.width-98)/2
        bIsdate: true
        selecter: newCalendar
        exclusiveGroup: timeSelectGroup
    }

    MyCalendar {
        id: mytimeSelect
        width: (parent.width-98)/2
        anchors.top: mycalendar.top
        anchors.left: mycalendar.right
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
        anchors.top: mycalendar.bottom
        anchors.left: parent.left
        anchors.leftMargin: 20
    }
    MyCalendar {
        id: mycalendar2
        bIsdate: true
        selecter: newCalendar
        exclusiveGroup: timeSelectGroup
        anchors.left: from.left
        anchors.leftMargin: 10
        anchors.top: to.bottom
        width: (parent.width-98)/2
    }

    MyCalendar {
        bIsdate: false
        selecter: newCalendar
        exclusiveGroup: timeSelectGroup
        width: (parent.width-98)/2
        anchors.top: mycalendar2.top
        anchors.left: mycalendar2.right
        anchors.leftMargin: 20
    }
    Column {
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 20
            spacing: 10
            CButton {
                id: applyButton
                width: parent.width
                text: qsTr("APPLY")
            }
            CButton {
                id: backButton
                width: parent.width
                text: qsTr("Back")
            }
        }

    }

    Rectangle {
        anchors.fill: qualityListViewTwo
        color: "#6d6e71"
        visible: qualityListViewTwo.visible
        Line {
            anchors.top: parent.top
            anchors.topMargin: parent.height / 2
            lineColor: "white"
            width: parent.width
            height: 2
        }
        Line {
            anchors.top: parent.top
            anchors.topMargin: parent.height * 0.1
            lineColor: "red"
            width: parent.width
            height: 2
        }
        Line {
            anchors.top: parent.top
            anchors.topMargin: parent.height * 0.2
            lineColor: "yellow"
            width: parent.width
            height: 2
        }
        Line {
            anchors.bottom: parent.bottom
            anchors.bottomMargin: parent.height * 0.2
            lineColor: "yellow"
            width: parent.width
            height: 2
        }
        Line {
            anchors.bottom: parent.bottom
            anchors.bottomMargin: parent.height * 0.1
            lineColor: "red"
            width: parent.width
            height: 2
        }
    }

    ListView {
        id: qualityListViewTwo
        anchors.left: back.right
        anchors.leftMargin: 20
        anchors.right: parent.right
        anchors.rightMargin: 30
        height: Screen.height *0.35
        orientation: Qt.Horizontal
        interactive: false
        anchors.top: parent.top
        anchors.topMargin: 20
        delegate: qualityListViewTwoDelegate
        model: 100
    }
    Component {
        id: qualityListViewTwoDelegate
        Item {
            width: 8
            height: Screen.height * 0.25
            Rectangle {
                id: point
                radius: 100
                width: 4
                height: 4
                anchors.top: parent.top
                anchors.topMargin: 50
                Component.onCompleted: {
                    point.anchors.topMargin = index + 50
                }
            }
        }
    }

    Row {
        id: selectButton
        anchors.left: back.right
        anchors.leftMargin: 20
        anchors.top: qualityListViewTwo.bottom
        anchors.topMargin: 20
        spacing: 30
        CButton {
            width: (qualityListViewTwo.width - 90) / 4
            text: "Time"
        }
        CButton {
            width: (qualityListViewTwo.width - 90) / 4
            text: "Pre-Height"
        }
        CButton {
            width: (qualityListViewTwo.width - 90) / 4
            text: "Post-Hight"
        }
        CButton {
            width: (qualityListViewTwo.width - 90) / 4
            text: "Peak Power"
        }
    }
    Text {
        id: bottomText
        anchors.left: qualityListViewTwo.left
        anchors.top: selectButton.bottom
        anchors.topMargin: 10
        font.family: "arial"
        font.pointSize: 16
        color: "white"
        text: qsTr("Weld Parameter\n\nCross section\nEnergy\nTime\nPressure\nAmplitude\nWidth\nPre-Height\nPost-Height")
    }
    Text {
        id: bottomText2
        anchors.left: qualityListViewTwo.left
        anchors.leftMargin: qualityListViewTwo.width / 2
        anchors.top: selectButton.bottom
        anchors.topMargin: 10
        font.family: "arial"
        font.pointSize: 16
        color: "white"
        text: qsTr("Statistics\n\nSample Size\nMean\nMedian\nSigma\nCPK")
    }
    CButton {
        anchors.bottom: parent.bottom
        anchors.left: bottomText2.left
        width: 200
        text: "Export"
    }


}
