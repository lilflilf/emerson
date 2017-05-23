import QtQuick 2.7
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.1
import QtQuick.Layouts 1.0
import QtQuick.Window 2.2

CButton {
    id: mycalendar
    property var selecter: null
    property bool bIsdate: false
    property alias exclusiveGroup: mycalendarRadio.exclusiveGroup
    width: 170
    z: 10
    height: 40
    text: mycalendar.bIsdate == true ? Qt.formatDateTime(new Date(), "yyyy-MM-dd") : Qt.formatDateTime(new Date(), "hh:mm:ss")
    backgroundComponent: Rectangle {
        id: backColor
        anchors.fill: parent
        color: "black"
        border.color: mycalendarRadio.checked ? "#05f91c" : "#1987ab"
        border.width: 2
    }
    RadioButton {
        id: mycalendarRadio
        visible: false
//        exclusiveGroup: timeSelectGroup
    }
    onClicked: {
        if (mycalendarRadio.checked == false) {
            mycalendarRadio.checked = true
            selecter.visible = true
        }
        else
        {
            mycalendarRadio.checked = false
            newCalendar.visible = false
        }
    }
    Connections {
        target: mycalendar.selecter
        onDateValueChanged: {
            if (mycalendarRadio.checked == true && mycalendar.bIsdate == true)
                mycalendar.text = selecter.dateValue
        }
        onTimeValueChanged: {
            if (mycalendarRadio.checked == true && mycalendar.bIsdate == false && selecter.visible)
                mycalendar.text = selecter.timeValue
        }
        onVisibleChanged: {
            if (selecter.visible == false) {
                mycalendarRadio.checked = false
            }
        }
    }
}

//CButton
//{
//    id: timeSelect
//    property string dateValue
//    onClicked: calendar.visible = !calendar.visible
//    height: 40

//    backgroundComponent: Rectangle {
//        anchors.fill: parent
//        color: "black"
//        border.color: "#1987ab"
//        border.width: 2
//    }
//    Calendar{
//        id: calendar
//        width: 500
//        height: 500
//        x: (Screen.width - 500) / 2
//        y: 0
////        anchors.topMargin: 0
////        anchors.top: parent.bottom
//        visible: false
//        activeFocusOnTab: true
//        z: 10
//        onReleased: {
//            timeSelect.text = date;
//            timeSelect.text = timeSelect.text.substr(0, 10);
//            timeSelect.dateValue = timeSelect.text;
//            visible = false;
//        }
//        style: CalendarStyle {
//            gridVisible: false
//            dayDelegate: Rectangle {
//                gradient: Gradient {
//                    GradientStop {
//                        position: 0.00
//                        color: styleData.selected ? "#111" : (styleData.visibleMonth && styleData.valid ? "#444" : "#666");
//                    }
//                    GradientStop {
//                        position: 1.00
//                        color: styleData.selected ? "#444" : (styleData.visibleMonth && styleData.valid ? "#111" : "#666");
//                    }
//                    GradientStop {
//                        position: 1.00
//                        color: styleData.selected ? "#777" : (styleData.visibleMonth && styleData.valid ? "#111" : "#666");
//                    }
//                }

//                Label {
//                    text: styleData.date.getDate()
//                    anchors.centerIn: parent
//                    color: styleData.valid ? "white" : "grey"
//                }

//                Rectangle {
//                    width: parent.width
//                    height: 1
//                    color: "#555"
//                    anchors.bottom: parent.bottom
//                }

//                Rectangle {
//                    width: 1
//                    height: parent.height
//                    color: "#555"
//                    anchors.right: parent.right
//                }
//            }
////            background: Rectangle {
////                color: "#555"
////                anchors.fill: parent
////            }

//            dayOfWeekDelegate: Item {
//                width: 50
//                height: 30
//                Rectangle {
//                    anchors.fill: parent
//                    color: "#555"
//                }

//                Label {
//                    text: control.__locale.dayName(styleData.dayOfWeek, control.dayOfWeekFormat) //styleData.dayOfWeek.getDate() //styleData.date.getDate()
//                    anchors.centerIn: parent
//                    color: "white"
//                }
//            }
//            navigationBar: Rectangle {
//                height: 33//Math.round(TextSingleton.implicitHeight * 2.73)
//                color: "#555"

//                Rectangle {
//                    color: Qt.rgba(1,1,1,0.6)
//                    height: 1
//                    width: parent.width
//                }

//                Rectangle {
//                    anchors.bottom: parent.bottom
//                    height: 1
//                    width: parent.width
//                    color: "#ddd"
//                }
//                Button {
//                    id: previousMonth
//                    width: 51 //parent.height
//                    height: 33 //width
//                    anchors.verticalCenter: parent.verticalCenter
//                    anchors.left: parent.left
//                    iconSource: "qrc:/images/images/you.png" //"images/leftanglearrow.png"
//                    onClicked: control.showPreviousMonth()
//                }
//                Label {
//                    id: dateText
//                    text: styleData.title
//                    elide: Text.ElideRight
//                    horizontalAlignment: Text.AlignHCenter
//                    font.pixelSize: 20
//                    anchors.verticalCenter: parent.verticalCenter
//                    anchors.left: previousMonth.right
//                    anchors.leftMargin: 2
//                    anchors.right: nextMonth.left
//                    anchors.rightMargin: 2
//                    color: "white"
//                    font.family: "arial"
//                }
//                Button {
//                    id: nextMonth
//                    width: 51 //parent.height
//                    height: 33 //width
//                    anchors.verticalCenter: parent.verticalCenter
//                    anchors.right: parent.right
//                    iconSource: "qrc:/images/images/zuo.png" //"images/rightanglearrow.png"
//                    onClicked: control.showNextMonth()
//                }
//            }
//        }
//    }
//    onDateValueChanged: {
//        timeSelect.text = dateValue;
//        calendar.selectedDate = dateValue;
//    }

//}


//Button {
//    id: timeSelect
//    text: "00:00:00"
//    ListView {
//        id: time
//        model: 24
//        width: parent.width / 3
//        height: 150
//        anchors.top: parent.bottom
//        highlightRangeMode: ListView.StrictlyEnforceRange;
//        preferredHighlightBegin: height / 3;
//        preferredHighlightEnd: height / 3;
//        clip: true;

//        delegate: Text {
//            id: modelRect
//            height: 30
//            width: time.width
//            text: index//qsTr("index")
//            font.family: "arial"
//            color: modelRect.ListView.isCurrentItem ? "blue" : "white";
//            font.pointSize: 14
//            horizontalAlignment: Qt.AlignHCenter
//            onColorChanged: {
//                if (modelRect.color == "#0000ff") {
//                    var str = timeSelect.text
//                    var myList = new Array();
//                    myList = str.split(":")
//                    myList[0] = index
//                    timeSelect.text = myList[0] + ":" + myList[1] + ":" + myList[2]
//            }
//            }


//        }

//    }
//    ListView {
//        id: mint
//        model: 60
//        width: parent.width / 3
//        height: 150
//        anchors.top: parent.bottom
//        anchors.left: time.right
//        highlightRangeMode: ListView.StrictlyEnforceRange;
//        preferredHighlightBegin: height / 3;
//        preferredHighlightEnd: height / 3;
//        delegate: Text {
//            id: modelRect2
//            height: 30
//            width: time.width
//            text: index//qsTr("index")
//            font.family: "arial"
//            color: modelRect2.ListView.isCurrentItem ? "blue" : "white";
//            font.pointSize: 14
//            horizontalAlignment: Qt.AlignHCenter
//            onColorChanged: {
//                if (modelRect2.color == "#0000ff") {
//                    var str = timeSelect.text
//                    var myList = new Array();
//                    myList = str.split(":")
//                    myList[1] = index
//                    timeSelect.text = myList[0] + ":" + myList[1] + ":" + myList[2]
//                }
//            }
//        }
//    }
//}
