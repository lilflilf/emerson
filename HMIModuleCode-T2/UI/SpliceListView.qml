import QtQuick 2.7
import QtQuick.Layouts 1.0
import QtQuick.Window 2.2
import QtQuick.Controls 1.4

Item {
    id: spliceList
    property alias listModel: splice.model
    property bool bIsWorkShow: false
    width: Screen.width * 0.3
    height: Screen.height*0.53
    signal currentSelecte(int index)
    signal currentWorkStation(int index)
    signal currentQty(int count, var name,int index)
    signal changeNumRecVisable(int y, bool isVisable)
    property var selectIndex: -1
    property int tempY: 0
    property bool bIschange: false
    property bool bIsSequence: false
    ExclusiveGroup {
        id: checkGroup
    }

    function deleteSplice()
    {
        listModel.remove(selectIndex)
    }
    function changeUp()
    {
        if (selectIndex <= 0 )
            return
        listModel.move(selectIndex,selectIndex-1,1)
        splice.currentIndex = splice.currentIndex - 1
        selectIndex = selectIndex-1
        currentSelecte(selectIndex)
        changeNumRecVisable(spliceList.y + tempY * 48, true)

    }
    function changeDown()
    {
        if (listModel.count <= selectIndex)
            return
        listModel.move(selectIndex,selectIndex+1,1)
        splice.currentIndex = splice.currentIndex + 1
        selectIndex = selectIndex+1
        currentSelecte(selectIndex)
        changeNumRecVisable(spliceList.y + tempY * 48, true)
    }

    ListView {
        id: splice
        width: spliceList.width
        height: spliceList.height
        clip: true
        delegate: spliceDelegate
        highlightRangeMode: ListView.StrictlyEnforceRange
        onDragStarted: {
            changeNumRecVisable(0, false)
        }
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
                onClicked: {
                    select.checked = !select.checked
                    if (select.checked) {
                        currentSelecte(index)
                        selectIndex = index
                    }
                    else {
                        currentSelecte(-1)
                        changeNumRecVisable(spliceList.y + 48 * index, false)
                    }
                }
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
                text: SpliceName
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
                visible: bIsWorkShow && !bIsSequence
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
                id: qtyButton
                anchors.top: parent.top
                anchors.topMargin: 10
                anchors.right: deleteButton.left
                anchors.rightMargin: 10
                clip: true
                visible: bIsSequence
                width: 28
                height: 28
                backgroundComponent: Rectangle {
                    anchors.fill: parent
                    color: stationColor
                }
                text: qty
                textColor: "black"
                pixelSize: 20
                onClicked: {
                    currentQty(text,spliceName.text,index)
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
                iconSource: "qrc:/images/images/close.png"
                onClicked: {
                    var temp = splice.mapFromItem(deleteButton,mouseX,mouseY)
                    tempY = temp.y / 48
                    select.checked = !select.checked
                    if (select.checked) {
                        currentSelecte(index)
                        selectIndex = index
                        bIschange = true
                        changeNumRecVisable(spliceList.y + tempY * 48, true)

//                        changeNumRecVisable(spliceList.y + 48 * index, true)

                    }
                    else {
                        bIschange = false
                        currentSelecte(-1)
                        changeNumRecVisable(spliceList.y + 48 * index, false)
                    }
                    //                    listModel.remove(index)

                }
            }
//            Rectangle {
//                id: changeNumRec
//                z: 13
//                visible: true
//                width: 90
//                height: 90
//                anchors.left: deleteButton.right
//                anchors.top: deleteButton.top
//                CButton {
//                    id: upbutton
//                    width: 90
//                    height: 40
//                }
//                CButton {
//                    width: 90
//                    height: 40
//                    anchors.top: upbutton.bottom
//                    anchors.topMargin: 10
//                }
//            }

            Rectangle {
                id: background
                anchors.left: numIndex.right
                anchors.leftMargin: 2
                width: parent.width - 55
                height: parent.height
                color: "black"
                opacity: 0
                clip: true
                RadioButton {
                    id: select
                    visible: false
                    exclusiveGroup: checkGroup
                    onCheckedChanged: {
                        if (select.checked) {
                            background.opacity = 0.5
                        } else {
                            background.opacity = 0
                        }
                    }
                }
            }
        }
    }
}
