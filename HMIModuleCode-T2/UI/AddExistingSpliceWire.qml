import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2

Item {
    id: addExistSpliceOrWire
    property string titleName: ""
    property string componentName: ""
    property string componentData: ""
    property string componentMiddle: ""
    property string componenttype: ""
    property string componentCount: ""
    property int selectCount: 0
    property int selectIndex: -1
    property alias listModel: listView.model
    property bool bIsOnlyOne: false
    signal signalAddExistSelectClick(var partId, var name)
    signal signalAddExistCancel()
    Rectangle {
        width: parent.width
        height: parent.height
        color: "#6d6e71"
        Text {
            id: title
            anchors.top: parent.top
            anchors.topMargin: 10
            anchors.left: parent.left
            anchors.leftMargin: 50
            width: parent.width/4
            color: "white"
            clip: true
            font.pixelSize: 27
            font.family: "arial"
            text: qsTr(titleName)
        }
        Text {
            id: head1
            anchors.top: title.bottom
            anchors.topMargin: 20
            anchors.left: parent.left
            anchors.leftMargin: 50
            width: (parent.width-120)/5
            color: "white"
            font.pixelSize: 18
            clip: true
            elide: Text.ElideRight
            font.family: "arial"
            text: qsTr(componentName)
        }
        Text {
            id: head2
            anchors.top: title.bottom
            anchors.topMargin: 20
            anchors.left: head1.right
            anchors.leftMargin: 10
            width: (parent.width-120)/5
            color: "white"
            font.pixelSize: 18
            elide: Text.ElideRight
            clip: true
            font.family: "arial"
            text: qsTr(componentData)
        }
        Text {
            id: head3
            anchors.top: title.bottom
            anchors.topMargin: 20
            anchors.left: head2.right
            anchors.leftMargin: 10
            width: (parent.width-120)/5
            color: "white"
            elide: Text.ElideRight
            font.pixelSize: 18
            clip: true
            font.family: "arial"
            text: qsTr(componentMiddle)
        }
        Text {
            id: head4
            anchors.top: title.bottom
            anchors.topMargin: 20
            anchors.left: head3.right
            anchors.leftMargin: 10
            width: (parent.width-120)/5
            color: "white"
            font.pixelSize: 18
            elide: Text.ElideRight
            font.family: "arial"
            clip: true
            text: qsTr(componenttype)
        }
        Text {
            id: head5
            anchors.top: title.bottom
            anchors.topMargin: 20
            anchors.left: head4.right
            anchors.leftMargin: 10
            width: (parent.width-120)/5
            color: "white"
            clip: true
            elide: Text.ElideRight
            font.pixelSize: 18
            font.family: "arial"
            text: componentCount
        }
        Rectangle {
            id: tipsRec1
            anchors.top: head5.bottom
            anchors.topMargin: 4
            width: parent.width
            height: 1
            color: "white"
        }
        Rectangle {
            id: tipsRec2
            anchors.top: tipsRec1.bottom
            width: parent.width
            height: 1
            color: "#0d0f11"
        }
        ExclusiveGroup{
            id: mos
        }
        ListView {
            id: listView
            anchors.top: tipsRec2.bottom
            anchors.topMargin: 10
            anchors.left: parent.left
            anchors.leftMargin: 50
            anchors.right: parent.right
            anchors.rightMargin: 30
            anchors.bottom: bottomTip1.top
            clip: true
            delegate: listDelegate
        }
//        list << "PartId" << "PartName" << "DateCreated" << "OperatorName" << "TotalSplices" << "ProcessMode" << "#ofWorkstation" << "#ofSplicesperWorkstation" << "Rows" << "Columns" << "MaxSplicesPerZone";
//        list << "SpliceId" << "SpliceName" << "DateCreated" << "OperatorName" << "CrossSection" << "TotalWires" << "Verified" << "WeldMode" << "Energy" << "Amplitude"
//             << "Width" << "TriggerPressure" << "WeldPressure" << "Time+" << "Time-" << "Power+" << "Power-" << "Pre-Height+" << "Pre-Height-" << "Height+" << "Height-" << "count";

        Component {
            id: listDelegate
            Item {
                width: listView.width
                height: 40
                Text {
                    id: headName
                    anchors.top: parent.top
                    anchors.topMargin: 10
                    anchors.left: parent.left
                    width: (parent.width-40)/5
                    elide: Text.ElideRight
                    text: PartName
                    clip: true
                    color: "white"
                    font.pixelSize: 14
                    font.family: "arial"
                }
                Text {
                    id: headData
                    anchors.top: parent.top
                    anchors.topMargin: 10
                    anchors.left: headName.right
                    anchors.leftMargin: 10
                    elide: Text.ElideRight
                    width: (parent.width-40)/5
                    text: DateCreated
                    clip: true
                    color: "white"
                    font.pixelSize: 14
                    font.family: "arial"
                }
                Text {
                    id: headMiddle
                    anchors.top: parent.top
                    anchors.topMargin: 10
                    anchors.left: headData.right
                    anchors.leftMargin: 10
                    width: (parent.width-40)/5
                    elide: Text.ElideRight
                    text: TotalSplices
                    clip: true
                    color: "white"
                    font.pixelSize: 14
                    font.family: "arial"
                }
                Text {
                    id: headType
                    anchors.top: parent.top
                    anchors.topMargin: 10
                    anchors.left: headMiddle.right
                    anchors.leftMargin: 10
                    elide: Text.ElideRight
                    width: (parent.width-40)/5
                    text: ProcessMode
                    color: "white"
                    clip: true
                    font.pixelSize: 14
                    font.family: "arial"
                }
                Text {
                    id: headCount
                    anchors.top: parent.top
                    anchors.topMargin: 10
                    anchors.left: headType.right
                    anchors.leftMargin: 10
                    width: (parent.width-40)/5
                    elide: Text.ElideRight
                    text: ProcessMode
                    color: "white"
                    clip: true
                    font.pixelSize: 14
                    visible: componentCount != "" ? true : false
                    font.family: "arial"
                }
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        if (bIsOnlyOne) {
                            selectIndex = index
                            selectCheck.checked = !selectCheck.checked
                        } else {
                            if (!backGround.visible) {
                                selectCount++
                                backGround.opacity = 0.3
                                backGround.visible = true
                            } else {
                                selectCount--
                                backGround.opacity = 0
                                backGround.visible = false
                            }
                        }
                    }
                }
                Rectangle {
                    id: backGround
                    anchors.fill: parent
                    color: "black"
                    visible: bIsOnlyOne
                    opacity: 0
                    RadioButton {
                        id: selectCheck
                        visible: false
                        exclusiveGroup: mos
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
        Image {
            id: scrollUp
            anchors.top: tipsRec2.bottom
            anchors.topMargin: 2
            anchors.left: listView.right
            anchors.leftMargin: 4
            width: 17
            height: 10
            visible: listView.contentHeight > listView.height ? true : false
            source: "qrc:/images/images/up.png"
        }
        Image {
            id: scrollDown
            anchors.bottom: bottomTip1.top
            anchors.bottomMargin: 2
            anchors.left: listView.right
            anchors.leftMargin: 4
            width: 17
            height: 10
            visible: listView.contentHeight > listView.height ? true : false
            source: "qrc:/images/images/down.png"
        }
        Rectangle {
            id: scrollbar
            width: 10
            height: listView.height-24
            anchors.top: scrollUp.bottom
            anchors.left: listView.right
            anchors.leftMargin: 4
            color: "#585858"
            radius: 10
            visible: listView.contentHeight > listView.height ? true : false
            Rectangle {
                id: button
                anchors.left: parent.left
                y: (listView.visibleArea.yPosition < 0 ) ? 0 : (listView.contentY+listView.height>listView.contentHeight) ?
                    scrollbar.height - button.height : listView.visibleArea.yPosition * scrollbar.height
                width: 10
                height: listView.visibleArea.heightRatio * scrollbar.height;
                color: "#ccbfbf"
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
                        listView.contentY = button.y / scrollbar.height * listView.contentHeight
                    }
                }
            }
        }

        Rectangle {
            id: bottomTip1
            anchors.bottom: bottomTip2.top
            width: parent.width
            clip: true
            height: 1
            color: "white"
        }
        Rectangle {
            id: bottomTip2
            anchors.bottom: select.top
            anchors.bottomMargin: 20
            width: parent.width
            clip: true
            height: 1
            color: "#0d0f11"
        }
        CButton {
            id: select
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 10
            anchors.right: parent.right
            anchors.rightMargin: 20
            width: 200
            height: 50
            clip: true
            text: bIsOnlyOne ? qsTr("Select") : qsTr("Select(" + selectCount + ")")
            textColor: "white"
            onClicked: {
                if (selectIndex != -1)
                    signalAddExistSelectClick(listModel.getValue(selectIndex,"PartId"),listModel.getValue(selectIndex,"PartName"))
            }
        }

        CButton {
            id: cancel
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 10
            anchors.right: select.left
            anchors.rightMargin: 25
            width: 200
            height: 50
            text: qsTr("Cancel")
            textColor: "white"
            onClicked: {
                signalAddExistCancel()
            }
        }
    }
}
