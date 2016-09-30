import QtQuick 2.7
import QtQuick.Layouts 1.0
import QtQuick.Window 2.2
import QtQuick.Controls 1.4

Item {
    id: spliceList
    property alias listModel: splice.model
    width: Screen.desktopAvailableWidth*0.2
    height: Screen.desktopAvailableHeight*0.5
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
        height: spliceList.height
        anchors.left: splice.right
        anchors.leftMargin: -14
        color: "#ccbfbf"
        radius: 10
        z: 10
        visible: splice.contentHeight > spliceList.height ? true : false
        Rectangle {
            id: button
            anchors.left: parent.left
            y: splice.visibleArea.yPosition * scrollbar.height
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
                anchors.leftMargin: 10
                width: parent.width - 40
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
                anchors.leftMargin: 16
                width: parent.width*0.55
                height: 28
                font.pointSize: 16
                font.family: "arial"
                text: nameValue
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
                width: 28
                height: 28
                backgroundComponent: Rectangle {
                    anchors.fill: parent
                    color: stationColor
                }
                text: station
                textColor: "white"
                pointSize: 20
                onClicked: {
                    currentWorkStation(index)
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
