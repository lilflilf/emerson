import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2

Item {
    id: workStation
    width: Screen.desktopAvailableWidth * 0.65
    height: Screen.desktopAvailableHeight*0.18
    property alias listModel: color.model
    property variant array: ["#ff6699","#ff0033","#33FFCC","#cc99ff","#cc0099","#930202","#99ccff","#f79428",
        "#0000cc","Olive","#ffff33","#ffcc00","#cc9909","#66ff00","#009900","#00cc66","#3366ff","#cc33cc","#cc9966","#9400D3"]
    property int currentIndex : 6
    property int allWorkTotal: 0
    property int clickCount: 0
    property int maxSpliceNum: 0

    onAllWorkTotalChanged: {
        if (allWorkTotal < 8)
            rightButton.visible = false
        else
            rightButton.visible = true
        leftButton.visible = false
    }

    CButton {
        id: leftButton
        anchors.top: parent.top
        anchors.left: parent.left
        width: 50
        height: 50
        iconSource: "qrc:/images/images/you.png"
        backgroundEnabled: false
        clip: true
        visible: false
        onClicked: {
            listModel.remove(0)
            clickCount--
//            listModel.insert(6,{"workcolor":array[currentIndex-clickCount]})
            if (clickCount < 7) {
                listModel.insert(6,{"workcolor":array[currentIndex-clickCount]})
            } else {
                listModel.insert(6,{"workcolor":array[clickCount]})
            }
            if (clickCount == 0) {
                leftButton.visible = false
            }
            rightButton.visible = true
        }
    }
    CButton {
        id: rightButton
        anchors.top: parent.top
        anchors.left: allworkStation.right
        anchors.leftMargin: 8
        clip: true
        width: 50
        height: 50
        iconSource: "qrc:/images/images/zuo.png"
        backgroundEnabled: false
        visible: allWorkTotal > 7 ? true : false
        onClicked: {
            leftButton.visible = true
            clickCount++
            listModel.remove(6)
            listModel.insert(0,{"workcolor":array[currentIndex+clickCount]})
            if ((currentIndex+clickCount+1) == allWorkTotal) {
                rightButton.visible = false
            }
        }
    }
    Row {
        id: allworkStation
        anchors.top: parent.top
        anchors.topMargin: 8
        anchors.left: leftButton.right
        anchors.leftMargin: 8
        clip: true
        spacing: 10
        Repeater {
            id: color
            model: allWorkTotal > 7 ? 7 : allWorkTotal
            delegate: Item {
                id: station
                width: 55
                height: workStation.height
                Rectangle {
                    id: colorStation
                    anchors.top: parent.top
                    anchors.horizontalCenter: parent.horizontalCenter
                    width: 35
                    height: 35
                    radius: 35
                    color: listModel.get(index).workcolor
                    border.color: "white"
                    border.width: 1
                    Drag.active: dragArea.drag.active;
                    Drag.supportedActions: Qt.CopyAction;
                    Drag.dragType: Drag.Automatic;
                    Drag.mimeData: {"color": color, "width": width, "height": height};
                    MouseArea {
                        id: dragArea;
                        anchors.fill: parent;
                        drag.target: parent;
                    }
                }
                Rectangle {
                    id: tips
                    anchors.top: colorStation.bottom
                    anchors.topMargin: 8
                    anchors.horizontalCenter: parent.horizontalCenter
                    width: 50
                    height: 10
                    color: "#7b7c7e"
                    radius: 2
                }
                Text {
                    id: maxSplice
                    anchors.top: tips.bottom
                    anchors.topMargin: 8
                    anchors.horizontalCenter: parent.horizontalCenter
                    horizontalAlignment: Qt.AlignHCenter
                    color: "white"
                    opacity: 0.8
                    clip: true
                    visible: maxSpliceNum == 0 ? false : true
                    font.pointSize: 15
                    font.family: "arial"
                    text: qsTr("3/" + numToString(maxSpliceNum))
                }
                Text {
                    id: stationText
                    anchors.top: maxSplice.bottom
                    anchors.topMargin: 8
                    anchors.horizontalCenter: parent.horizontalCenter
                    horizontalAlignment: Qt.AlignHCenter
                    color: "white"
                    opacity: 0.8
                    clip: true
                    visible: maxSpliceNum == 0 ? false : true
                    font.pointSize: 10
                    font.family: "arial"
                    text: qsTr("Station" + numToString(index+1+clickCount))
                }
            }
        }
    }
    function numToString(num)
    {
        var name = "1"
        name = num
        return name
    }
}
