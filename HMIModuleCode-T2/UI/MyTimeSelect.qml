import QtQuick 2.0
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.0
import QtQuick.Window 2.2

Item {
    id: timeSelect
    property string timeValue: ""
    property string dateValue: ""
    width: 691
    height: 396
    onVisibleChanged: {
        var temp = Qt.formatDateTime(new Date(), "hh")
        time.currentIndex = temp
        temp = Qt.formatDateTime(new Date(), "mm")
        mint.currentIndex = temp
        temp = Qt.formatDateTime(new Date(), "ss")
        second.currentIndex = temp
    }

    Image {
        id: bg
        anchors.fill: parent
        source: "qrc:/images/images/timeSelectbg.png"
        MouseArea {
            anchors.fill: parent
        }
    }
    Calendar{
        id: calendar
        width: 434
        height: 396
        anchors.left: parent.left
        anchors.leftMargin: 13
        activeFocusOnTab: true
        onReleased: {
            timeSelect.dateValue = date
            timeSelect.dateValue = timeSelect.dateValue.substr(0, 10)
        }

        style: CalendarStyle {
            gridColor: Qt.rgba(0,0,0,0)
            gridVisible: false
            dayDelegate: Rectangle {
                gradient: Gradient {
                    GradientStop {
                        position: 0.00
                        color: styleData.selected ? Qt.rgba(0,0,0,0) : (styleData.visibleMonth && styleData.valid ? Qt.rgba(0,0,0,0) : Qt.rgba(0,0,0,0));
                    }
                    GradientStop {
                        position: 1.00
                        color: styleData.selected ? Qt.rgba(0,0,0,0) : (styleData.visibleMonth && styleData.valid ? Qt.rgba(0,0,0,0) : Qt.rgba(0,0,0,0));
                    }
                    GradientStop {
                        position: 1.00
                        color: styleData.selected ? Qt.rgba(0,0,0,0) : (styleData.visibleMonth && styleData.valid ? Qt.rgba(0,0,0,0) : Qt.rgba(0,0,0,0));
                    }
                }
                Rectangle {
                    anchors.fill: parent
                    color: "blue"
                    visible: styleData.selected
                }

                Label {
                    text: styleData.date.getDate()
                    anchors.centerIn: parent
                    color: styleData.visibleMonth && styleData.valid ? "white" : "#3d515d"
                    font.pointSize: 20
                    font.family: "arial"
                }
            }
            background: Item {
                anchors.fill: parent
            }

            dayOfWeekDelegate: Item {
                width: 50
                height: 30
                Item {
                    anchors.fill: parent
                }

                Label {
                    text: control.__locale.dayName(styleData.dayOfWeek, control.dayOfWeekFormat) //styleData.dayOfWeek.getDate() //styleData.date.getDate()
                    anchors.centerIn: parent
                    color: "blue"
                    font.family: "arial"
                    font.pointSize: 16
                }
            }
            navigationBar: Item {
                height: 33//Math.round(TextSingleton.implicitHeight * 2.73)
                CButton {
                    id: previousMonth
                    width: 100 //parent.height
                    height: 33 //width
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    text: "<"
                    onClicked: control.showPreviousMonth()
                    backgroundEnabled: false
                    textColor: "blue"
                    pixelSize: 30
                    labelHorizontalOffset: -30
                }
                Label {
                    id: dateText
                    text: styleData.title
                    elide: Text.ElideRight
                    horizontalAlignment: Text.AlignHCenter
                    font.pixelSize: 20
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: previousMonth.right
                    anchors.leftMargin: 2
                    anchors.right: nextMonth.left
                    anchors.rightMargin: 2
                    color: "white"
                    font.family: "arial"
                }
                CButton {
                    id: nextMonth
                    width: 100 //parent.height
                    height: 33 //width
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.right: parent.right
                    text: ">"
                    onClicked: control.showNextMonth()
                    backgroundEnabled: false
                    textColor: "blue"
                    pixelSize: 30
                    labelHorizontalOffset: 30

                }
            }
        }
    }

    Row {
        anchors.left: calendar.right
        spacing: 15
        anchors.top: parent.top
        anchors.topMargin: 35
        Text {
            width: 59
            horizontalAlignment: Qt.AlignHCenter
            verticalAlignment: Qt.AlignVCenter
            text: qsTr("hour")
            font.family: "arial"
            font.pointSize: 16
            color: "blue"

        }
        Text {
            width: 59
            horizontalAlignment: Qt.AlignHCenter
            verticalAlignment: Qt.AlignVCenter
            text: qsTr("minute")
            font.family: "arial"
            font.pointSize: 16
            color: "blue"

        }
        Text {
            width: 59
            horizontalAlignment: Qt.AlignHCenter
            verticalAlignment: Qt.AlignVCenter
            text: qsTr("second")
            font.family: "arial"
            font.pointSize: 16
            color: "blue"
        }
    }

    Image {
        anchors.fill: time
        source: "qrc:/images/images/timeSlidDown.png"
    }
    MyLineEdit {
        id: hourText
        width: 59
        height: 59
        inputWidth: 59
        inputHeight: 59
        anchors.bottom: time.top
        anchors.right: time.right
        anchors.bottomMargin: 15
        horizontalAlignment: Qt.AlignHCenter
    }
    PathView {
        id: time
        model: 24
        width: 59
        height: 232
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 20
        anchors.left: calendar.right
        highlightRangeMode: ListView.StrictlyEnforceRange;
        preferredHighlightBegin: 0.5;
        preferredHighlightEnd: 0.5;
        clip: true;
        pathItemCount: 7;
        path: Path {
            startY: 0
            startX: 30
            PathLine { y: second.height; x: 30 }
        }
        delegate: Item {
            height: 33
            width: time.width
            Text {
                id: modelRect
                anchors.centerIn: parent
                text: index
                font.family: "arial"
                color: time.currentIndex == index ? "blue" : "white";
                font.pointSize: 20
                onColorChanged: {
                    if (modelRect.color == "#0000ff") {
                        if (index < 10) {
                            hourText.inputText = "0"+index
                        } else {
                            hourText.inputText = index
                        }
                        timeSelect.timeValue = hourText.inputText + ":" + minuteText.inputText + ":" + secondText.inputText
                    }
                }
            }
        }

    }
    Image {
        anchors.fill: time
        source: "qrc:/images/images/timeSlidUp.png"
        opacity: 0.5
    }
    Image {
        anchors.fill: mint
        source: "qrc:/images/images/timeSlidDown.png"
    }
    Text {
        text: ":"
        color: "white"
        anchors.right: minuteText.left
        anchors.verticalCenter: minuteText.verticalCenter
        font.pointSize: 20
    }
    MyLineEdit {
        id: minuteText
        width: 59
        height: 59
        inputWidth: 59
        inputHeight: 59
        anchors.bottom: mint.top
        anchors.right: mint.right
        anchors.bottomMargin: 15
        horizontalAlignment: Qt.AlignHCenter
    }
    PathView {
        id: mint
        model: 60
        width: 59
        height: 232
        anchors.bottom: time.bottom
        anchors.left: time.right
        anchors.leftMargin: 15
        highlightRangeMode: ListView.StrictlyEnforceRange;
        preferredHighlightBegin: 0.5;
        preferredHighlightEnd: 0.5;
        clip: true;
        pathItemCount: 7;
        path: Path {
            startY: 0
            startX: 30
            PathLine { y: second.height; x: 30 }
        }
        delegate: Item {
            height: 33
            width: time.width
            Text {
                id: modelRect2
                anchors.centerIn: parent
                text: index
                font.family: "arial"
                color: mint.currentIndex == index ? "blue" : "white";
                font.pointSize: 20
                onColorChanged: {
                    if (modelRect2.color == "#0000ff") {
                        if (index < 10) {
                            minuteText.inputText = "0"+index
                        } else {
                            minuteText.inputText = index
                        }
                        timeSelect.timeValue = hourText.inputText + ":" + minuteText.inputText + ":" + secondText.inputText

                    }
                }
            }
        }
    }
    Image {
        anchors.fill: mint
        source: "qrc:/images/images/timeSlidUp.png"
        opacity: 0.5
    }
    Image {
        anchors.fill: second
        source: "qrc:/images/images/timeSlidDown.png"
    }
    Text {
        text: ":"
        color: "white"
        anchors.right: secondText.left
        anchors.verticalCenter: secondText.verticalCenter
        font.pointSize: 20
    }
    MyLineEdit {
        id: secondText
        width: 59
        height: 59
        inputWidth: 59
        inputHeight: 59
        anchors.bottom: second.top
        anchors.right: second.right
        anchors.bottomMargin: 15
        horizontalAlignment: Qt.AlignHCenter

    }
    PathView {
        id: second
        model: 60
        width: 59
        height: 232
        anchors.bottom: mint.bottom
        anchors.left: mint.right
        anchors.leftMargin: 15
        highlightRangeMode: ListView.StrictlyEnforceRange;
        preferredHighlightBegin: 0.5 //height / 2.5;
        preferredHighlightEnd: 0.5 //height / 2.5;
        clip: true;
        pathItemCount: 7;
        path: Path {
            startY: 0
            startX: 30 //0//pathMargin
            PathLine { y: second.height; x: 30 }
        }
        delegate: Item {
            height: 33
            width: time.width
            Text {
                id: modelRect3
                anchors.centerIn: parent
                text: index
                font.family: "arial"
                color: second.currentIndex == index ? "blue" : "white";
                font.pointSize: 20
                onColorChanged: {
                    if (modelRect3.color == "#0000ff") {
                        if (index < 10) {
                            secondText.inputText = "0"+index
                        } else {
                            secondText.inputText = index
                        }
                        timeSelect.timeValue = hourText.inputText + ":" + minuteText.inputText + ":" + secondText.inputText

                    }
                }
            }
        }
    }
    Image {
        anchors.fill: second
        source: "qrc:/images/images/timeSlidUp.png"
        opacity: 0.5
    }
}

//CButton {
//    id: timeSelect
//    text: "00:00:00"
//    height: 40
//    backgroundComponent: Rectangle {
//        anchors.fill: parent
//        color: "black"
//        border.color: "#1987ab"
//        border.width: 2
//    }
//    onClicked: {
//        time.visible = !time.visible
//        mint.visible = !mint.visible
//    }

//    ListView {
//        id: time
//        visible: false
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
//        visible: false
//        model: 60
//        width: parent.width / 3
//        height: 150
//        anchors.top: parent.bottom
//        anchors.left: time.right
//        highlightRangeMode: ListView.StrictlyEnforceRange;
//        preferredHighlightBegin: height / 3;
//        preferredHighlightEnd: height / 3;
//        clip: true;
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
