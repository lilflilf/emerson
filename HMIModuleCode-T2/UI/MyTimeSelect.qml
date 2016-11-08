import QtQuick 2.0
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.4

Button {
    id: timeSelect
    text: "00:00:00"

    onClicked: {
        time.visible = !time.visible
        mint.visible = !mint.visible
    }

    ListView {
        id: time
        visible: false
        model: 24
        width: parent.width / 3
        height: 150
        anchors.top: parent.bottom
        highlightRangeMode: ListView.StrictlyEnforceRange;
        preferredHighlightBegin: height / 3;
        preferredHighlightEnd: height / 3;
        clip: true;

        delegate: Text {
            id: modelRect
            height: 30
            width: time.width
            text: index//qsTr("index")
            font.family: "arial"
            color: modelRect.ListView.isCurrentItem ? "blue" : "white";
            font.pointSize: 14
            horizontalAlignment: Qt.AlignHCenter
            onColorChanged: {
                if (modelRect.color == "#0000ff") {
                    var str = timeSelect.text
                    var myList = new Array();
                    myList = str.split(":")
                    myList[0] = index
                    timeSelect.text = myList[0] + ":" + myList[1] + ":" + myList[2]
            }
            }


        }

    }
    ListView {
        id: mint
        visible: false
        model: 60
        width: parent.width / 3
        height: 150
        anchors.top: parent.bottom
        anchors.left: time.right
        highlightRangeMode: ListView.StrictlyEnforceRange;
        preferredHighlightBegin: height / 3;
        preferredHighlightEnd: height / 3;
        delegate: Text {
            id: modelRect2
            height: 30
            width: time.width
            text: index//qsTr("index")
            font.family: "arial"
            color: modelRect2.ListView.isCurrentItem ? "blue" : "white";
            font.pointSize: 14
            horizontalAlignment: Qt.AlignHCenter
            onColorChanged: {
                if (modelRect2.color == "#0000ff") {
                    var str = timeSelect.text
                    var myList = new Array();
                    myList = str.split(":")
                    myList[1] = index
                    timeSelect.text = myList[0] + ":" + myList[1] + ":" + myList[2]
                }
            }
        }
    }
}
