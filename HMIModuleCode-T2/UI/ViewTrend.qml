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
        text: qsTr("Splice Number")
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
}
