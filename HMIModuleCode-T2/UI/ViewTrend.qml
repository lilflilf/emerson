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
    Rectangle {
        id: back
        width: 300
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
        width: 250
        height: 30
        anchors.left: title2.left
        anchors.top: title2.bottom
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
        anchors.topMargin: 15
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
        anchors.left: seach.left
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
            height: 60
            text: qsTr("APPLY")
        }
        CButton {
            id: backButton
            width: 250
            height: 60
            text: qsTr("Back")
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
//        width: 700
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
            height: 79
            text: "Time"
        }
        CButton {
            width: (qualityListViewTwo.width - 90) / 4
            height: 79
            text: "Pre-Height"
        }
        CButton {
            width: (qualityListViewTwo.width - 90) / 4
            height: 79
            text: "Post-Hight"
        }
        CButton {
            width: (qualityListViewTwo.width - 90) / 4
            height: 79
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


}
