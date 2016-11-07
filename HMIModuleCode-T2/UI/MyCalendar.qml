import QtQuick 2.0
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.4

Button
{
    id: timeSelect
    property string dateValue
    onClicked: calendar.visible = !calendar.visible

    Calendar{
        id: calendar
        width: 500
        height: 500
        anchors.topMargin: 0
        anchors.top: parent.bottom
        visible: false
        activeFocusOnTab: true
        onReleased: {
            timeSelect.text = date;
            timeSelect.text = timeSelect.text.substr(0, 10);
            timeSelect.dateValue = timeSelect.text;
            visible = false;
        }
        style: CalendarStyle {
            gridVisible: false
            dayDelegate: Rectangle {
                gradient: Gradient {
                    GradientStop {
                        position: 0.00
                        color: styleData.selected ? "#111" : (styleData.visibleMonth && styleData.valid ? "#444" : "#666");
                    }
                    GradientStop {
                        position: 1.00
                        color: styleData.selected ? "#444" : (styleData.visibleMonth && styleData.valid ? "#111" : "#666");
                    }
                    GradientStop {
                        position: 1.00
                        color: styleData.selected ? "#777" : (styleData.visibleMonth && styleData.valid ? "#111" : "#666");
                    }
                }

                Label {
                    text: styleData.date.getDate()
                    anchors.centerIn: parent
                    color: styleData.valid ? "white" : "grey"
                }

                Rectangle {
                    width: parent.width
                    height: 1
                    color: "#555"
                    anchors.bottom: parent.bottom
                }

                Rectangle {
                    width: 1
                    height: parent.height
                    color: "#555"
                    anchors.right: parent.right
                }
            }
//            dayOfWeekDelegate: Rectangle {
//                anchors.fill: parent
//                color: "black"
//                Label {
//                    text: styleData.date.getDate()
//                    anchors.centerIn: parent
//                    color: styleData.valid ? "white" : "grey"
//                }
//            }
        }
    }
    onDateValueChanged: {
        timeSelect.text = dateValue;
        calendar.selectedDate = dateValue;
    }

}


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
