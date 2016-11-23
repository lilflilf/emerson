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
        width: Screen.width * 0.3
        height: parent.height
        color: "black"
        opacity: 0.3
    }

    MyTimeSelect {
        id: newCalendar
        anchors.centerIn: parent
        z: 12
        visible: false
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
        property int selectNum: -2
        anchors.left: seach.left
        width: Screen.width * 0.3 - 20
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
            width: Screen.width * 0.3 - 20
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
            text: qsTr("OK")
            iconSource: "qrc:/images/images/OK.png"
            onClicked: {
                if (searchArea.selectNum == -2) {
                    searchArea.visible = false
                    searchInfo.text = "All"
                } else {
                    searchArea.visible = false
                    searchInfo.text = testModel.get(searchArea.selectNum).name
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
        anchors.top: seach.bottom
        anchors.topMargin: 15
        anchors.left: seach.left
    }

    CButton {
        id: searchInfo
//        width: 250
        anchors.left: title2.left
        anchors.top: title2.bottom
        clip: true
        text: qsTr("All")
        height: mytimeSelect.height
        anchors.right: mytimeSelect.right
        backgroundComponent: Rectangle {
            anchors.fill: parent
            color: "black"
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
        anchors.top: searchInfo.bottom
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

    CButton {
        id: mycalendar
        anchors.left: from.left
        anchors.top: from.bottom
        width: 170
        z: 10
        height: 40
        text: Qt.formatDateTime(new Date(), "yyyy-MM-dd")
        backgroundComponent: Rectangle {
            anchors.fill: parent
            color: "black"
            border.color: "#1987ab"
            border.width: 2
        }
        onClicked: {
            newCalendar.visible = !newCalendar.visible
        }
    }

    CButton {
        id: mytimeSelect
        width: 170
        anchors.top: mycalendar.top
        anchors.left: mycalendar.right
        anchors.leftMargin: 20
        z: 11
        text: Qt.formatDateTime(new Date(), "hh:mm:ss")
        height: 40
        backgroundComponent: Rectangle {
            anchors.fill: parent
            color: "black"
            border.color: "#1987ab"
            border.width: 2
        }
        onClicked: {
            newCalendar.visible = !newCalendar.visible
        }
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
    CButton {
        id: mycalendar2
        anchors.left: from.left
        anchors.top: to.bottom
        width: 170
        z: 10
        text: Qt.formatDateTime(new Date(), "yyyy-MM-dd")
        height: 40
        backgroundComponent: Rectangle {
            anchors.fill: parent
            color: "black"
            border.color: "#1987ab"
            border.width: 2
        }
        onClicked: {
            newCalendar.visible = !newCalendar.visible
        }
    }
    CButton {
        width: 170
        anchors.top: mycalendar2.top
        anchors.left: mycalendar2.right
        anchors.leftMargin: 20
        z: 10
        text: Qt.formatDateTime(new Date(), "hh:mm:ss")
        height: 40
        backgroundComponent: Rectangle {
            anchors.fill: parent
            color: "black"
            border.color: "#1987ab"
            border.width: 2
        }
        onClicked: {
            newCalendar.visible = !newCalendar.visible
        }
    }
    Column {
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 20
        spacing: 10
        CButton {
            id: applyButton
            width: searchInfo.width
            text: qsTr("APPLY")
        }
        CButton {
            id: backButton
            width: searchInfo.width
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


}
