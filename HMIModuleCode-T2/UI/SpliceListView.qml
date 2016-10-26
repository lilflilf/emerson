import QtQuick 2.7
import QtQuick.Layouts 1.0
import QtQuick.Window 2.2
import QtQuick.Controls 1.4

Item {
    id: spliceList
    property alias listModel: splice.model
    property bool bIsWorkShow: false
    width: Screen.desktopAvailableWidth * 0.3
    height: Screen.desktopAvailableHeight*0.53
    signal currentSelecte(int index)
    signal currentWorkStation(int index)
    ListView {
        id: splice
        width: spliceList.width
        height: spliceList.height
        clip: true
        delegate: spliceDelegate
    }
    Rectangle {
        id: scrollbar
        width: 10
        height: splice.height
        anchors.left: splice.right
        anchors.leftMargin: -14
        color: "#ccbfbf"
        radius: 10
        z: 10
        visible: splice.contentHeight > splice.height ? true : false
        Rectangle {
            id: button
            anchors.left: parent.left
            y: (splice.visibleArea.yPosition < 0 ) ? 0 : (splice.contentY+splice.height>splice.contentHeight) ?
                scrollbar.height - button.height : splice.visibleArea.yPosition * scrollbar.height
            width: 10
            height: splice.visibleArea.heightRatio * scrollbar.height;
            color: "#717275"
            radius: 10
            // 鼠标区域
            MouseArea {
                id: mouseArea
                anchors.fill: button
                drag.target: button
                drag.axis: Drag.YAxis
                drag.minimumY: 0
                drag.maximumY: scrollbar.height - button.height
                // 拖动
                onMouseYChanged: {
                    splice.contentY = button.y / scrollbar.height * splice.contentHeight
                }
            }
        }
    }
    Component {
        id: spliceDelegate
        Item {
            width: splice.width
            height: 48
            Text {
                id: numIndex
                anchors.top: parent.top
                anchors.topMargin: 10
                anchors.left: parent.left
                anchors.leftMargin: 10
                width: 25
                height: 28
                clip: true
                font.family: "arial"
                font.pointSize: 16
                text: index+1
                color: "white"
            }
            MouseArea {
                id: mouse
                anchors.fill: parent
                onPressed: {
                    timer.running = true
                    background.opacity = 0.5
                }
                onReleased: {
                    background.opacity = 0
                }
                onClicked: {
                    currentSelecte(index)
                }
            }
            Rectangle {
                id: background
                anchors.left: numIndex.right
                anchors.leftMargin: 2
                width: parent.width - 55
                height: parent.height
                color: "black"
                opacity: 0
                clip: true
            }
            Text {
                id: spliceName
                anchors.top: parent.top
                anchors.topMargin: 10
                anchors.left: numIndex.right
                anchors.leftMargin: 6
                width: bIsWorkShow ? parent.width*0.65 : parent.width*0.75
                height: 28
                font.pointSize: 14
                font.family: "arial"
                text: qsTr(nameValue)
                elide: Text.ElideRight
                color: "white"
                clip: true
            }
            CButton {
                id: workStation
                anchors.top: parent.top
                anchors.topMargin: 10
                anchors.left: spliceName.right
                anchors.leftMargin: 10
                clip: true
                visible: bIsWorkShow
                width: 28
                height: 28
                backgroundComponent: Rectangle {
                    anchors.fill: parent
                    color: stationColor
                }
                text: station
                textColor: "white"

                pixelSize: 20
                onClicked: {
                    currentWorkStation(index)
                }
                onTextChanged: {
                    if (station == "?")
                        workStation.textColor = "black"
                    else
                        workStation.textColor = "white"
                }

            }
            CButton {
                id: deleteButton
                anchors.top: parent.top
                anchors.topMargin: 10
                anchors.left: bIsWorkShow ? workStation.right : spliceName.right
                anchors.leftMargin: 10
                clip: true
                width: 28
                height: 28
                backgroundComponent: Rectangle {
                    anchors.fill: parent
                    color: "red"
                }
                text: "X"
                textColor: "black"
                onClicked: {

                }
            }
            Timer {
                id: timer
                running: false
                interval: 100
                onTriggered: {
                    background.opacity = 0
                }
            }
        }
    }
}
