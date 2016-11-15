import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2

Item {
    id: addExistSpliceOrWire
//    width: Screen.width*0.7
//    height: Screen.height*0.6
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
        width: parent.width //Screen.width*0.7
        height: parent.height //Screen.height*0.6
        color: "#6d6e71"
        Text {
            id: title
            anchors.top: parent.top
            anchors.topMargin: 10
            anchors.left: parent.left
            anchors.leftMargin: 10
            width: parent.width/4
            color: "white"
            clip: true
            font.pointSize: 16
            font.family: "arial"
            text: qsTr(titleName)
        }
        Text {
            id: head1
            anchors.top: title.bottom
            anchors.topMargin: 10
            anchors.left: parent.left
            anchors.leftMargin: 10
            width: parent.width/4
            color: "white"
            font.pointSize: 10
            horizontalAlignment: Qt.AlignHCenter
            clip: true
            font.family: "arial"
            text: qsTr(componentName)
        }
        Text {
            id: head2
            anchors.top: title.bottom
            anchors.topMargin: 10
            anchors.left: head1.right
            anchors.leftMargin: 10
            width: parent.width/4
            color: "white"
            font.pointSize: 10
            horizontalAlignment: Qt.AlignHCenter
            clip: true
            font.family: "arial"
            text: qsTr(componentData)
        }
        Text {
            id: head3
            anchors.top: title.bottom
            anchors.topMargin: 10
            anchors.left: head2.right
            anchors.leftMargin: 10
            width: parent.width/7
            horizontalAlignment: Qt.AlignHCenter
            color: "white"
            font.pointSize: 10
            clip: true
            font.family: "arial"
            text: qsTr(componentMiddle)
        }
        Text {
            id: head4
            anchors.top: title.bottom
            anchors.topMargin: 10
            anchors.left: head3.right
            anchors.leftMargin: 10
            width: parent.width/7
            color: "white"
            horizontalAlignment: Qt.AlignHCenter
            font.pointSize: 10
            font.family: "arial"
            clip: true
            text: qsTr(componenttype)
        }
        Text {
            id: head5
            anchors.top: title.bottom
            anchors.topMargin: 10
            anchors.left: head4.right
            anchors.leftMargin: 10
            width: parent.width/7
            color: "white"
            horizontalAlignment: Qt.AlignHCenter
            clip: true
            font.pointSize: 10
            font.family: "arial"
            text: componentCount
        }
        Rectangle {
            id: tipsRec
            anchors.top: head5.bottom
            anchors.topMargin: 4
            width: parent.width
            height: 10
            color: "#585858"
        }
        ExclusiveGroup{
            id: mos
        }
        ListView {
            id: listView
            anchors.top: tipsRec.bottom
            anchors.topMargin: 10
            anchors.left: parent.left
            anchors.leftMargin: 24
            anchors.right: parent.right
            anchors.rightMargin: 24
//            width: parent.width - 48
            height: parent.height- 170
            clip: true
            delegate: listDelegate
        }
//        list << "PartId" << "PartName" << "DateCreated" << "OperatorName" << "TotalSplices" << "ProcessMode" << "#ofWorkstation" << "#ofSplicesperWorkstation" << "Rows" << "Columns" << "MaxSplicesPerZone";

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
                    anchors.leftMargin: 10
                    horizontalAlignment: Qt.AlignLeft
                    width: parent.width/4
                    elide: Text.ElideRight
                    text: PartName
                    clip: true
                    color: "white"
                    font.pointSize: 10
                    font.family: "arial"
                    Component.onCompleted: {
                        console.log("headData width== ", headData.width)
                    }
                }
                Text {
                    id: headData
                    anchors.top: parent.top
                    anchors.topMargin: 10
                    anchors.left: headName.right
                    anchors.leftMargin: 6
                    horizontalAlignment: Qt.AlignCenter
                    width: parent.width/4
                    text: DateCreated
                    clip: true
                    color: "white"
                    font.pointSize: 10
                    font.family: "arial"
                }
                Text {
                    id: headMiddle
                    anchors.top: parent.top
                    anchors.topMargin: 10
                    anchors.left: headData.right
                    anchors.leftMargin: 14
                    horizontalAlignment: Qt.AlignCenter
                    width: parent.width/7
                    text: TotalSplices
                    clip: true
                    color: "white"
                    font.pointSize: 10
                    font.family: "arial"
                }
                Text {
                    id: headType
                    anchors.top: parent.top
                    anchors.topMargin: 10
                    anchors.left: headMiddle.right
                    anchors.leftMargin: 14
                    horizontalAlignment: Qt.AlignCenter
                    width: parent.width/7
                    text: ProcessMode
                    color: "white"
                    clip: true
                    font.pointSize: 10
                    font.family: "arial"
                }
                Text {
                    id: headCount
                    anchors.top: parent.top
                    anchors.topMargin: 10
                    anchors.left: headType.right
                    anchors.leftMargin: 18
                    horizontalAlignment: Qt.AlignCenter
                    width: parent.width/7
                    text: ProcessMode
                    color: "white"
                    clip: true
                    font.pointSize: 10
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
        Rectangle {
            id: bottomTip
            anchors.top: listView.bottom
            anchors.topMargin: 4
            width: parent.width
            clip: true
            height: 10
            color: "#585858"
        }
        CButton {
            id: select
            anchors.top: bottomTip.bottom
            anchors.topMargin: 10
            anchors.right: parent.right
            anchors.rightMargin: 24
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
            anchors.top: bottomTip.bottom
            anchors.topMargin: 10
            anchors.right: select.left
            anchors.rightMargin: 24
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
