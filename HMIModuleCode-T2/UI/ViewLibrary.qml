import QtQuick 2.0
import QtQuick.Controls 1.2

Item {
    id: viewLib
    property int selectIndx: -1
    property int count: partTitleModel.count
    Column {
        id: column
        anchors.top: parent.top
        anchors.topMargin: 30
        anchors.left: parent.left
        anchors.leftMargin: 30
        height: 79*3+20
        width: 250
        spacing: 10
        z: 10
        CButton {
            width: column.width
            height: 79
            textColor: "white"
            text: qsTr("Part")
            onClicked: {
                headRepeater.model = partTitleModel
                viewLib.count = partTitleModel.count
            }
        }
        CButton {
            width: column.width
            height: 79
            textColor: "white"
            text: qsTr("Splice")
            onClicked: {
                headRepeater.model = spliceTitleModel
                viewLib.count = spliceTitleModel.count
            }
        }
        CButton {
            width: column.width
            height: 79
            textColor: "white"
            text: qsTr("Wire")
            onClicked: {
                headRepeater.model = wireTitleModel
                viewLib.count = wireTitleModel.count
            }
        }
    }
    ListModel {
        id: partTitleModel
    }
    ListModel {
        id: spliceTitleModel
    }
    ListModel {
        id: wireTitleModel
        Component.onCompleted: {
            partTitleModel.append({"title":"Part Name"})
            partTitleModel.append({"title":"Date Created"})
            partTitleModel.append({"title":"Operator Name"})
            partTitleModel.append({"title":"Total Splices"})
            partTitleModel.append({"title":"Process Mode"})
            partTitleModel.append({"title":"# of Workstation"})
            partTitleModel.append({"title":"# of Splices per Workstation"})
            partTitleModel.append({"title":"Rows"})
            partTitleModel.append({"title":"Columns"})
            partTitleModel.append({"title":"Max Splices Per Zone"})

            spliceTitleModel.append({"title":"Splice Name"})
            spliceTitleModel.append({"title":"Date Created"})
            spliceTitleModel.append({"title":"Operator Name"})
            spliceTitleModel.append({"title":"Cross Section"})
            spliceTitleModel.append({"title":"Total Wires"})
            spliceTitleModel.append({"title":"Verified"})
            spliceTitleModel.append({"title":"Weld Mode"})
            spliceTitleModel.append({"title":"Energy"})
            spliceTitleModel.append({"title":"Amplitude"})
            spliceTitleModel.append({"title":"Width"})
            spliceTitleModel.append({"title":"Trigger Pressure"})
            spliceTitleModel.append({"title":"Weld Pressure"})
            spliceTitleModel.append({"title":"Time+"})
            spliceTitleModel.append({"title":"Time-"})
            spliceTitleModel.append({"title":"Power+"})
            spliceTitleModel.append({"title":"Power-"})
            spliceTitleModel.append({"title":"Pre-Height+"})
            spliceTitleModel.append({"title":"Pre-Height-"})
            spliceTitleModel.append({"title":"Height+"})
            spliceTitleModel.append({"title":"Height-"})

            wireTitleModel.append({"title":"Wire Name"})
            wireTitleModel.append({"title":"Date Created"})
            wireTitleModel.append({"title":"Operator Name"})
            wireTitleModel.append({"title":"Color"})
            wireTitleModel.append({"title":"StripeType"})
            wireTitleModel.append({"title":"Stripe Color"})
            wireTitleModel.append({"title":"Gauge"})
            wireTitleModel.append({"title":"Metal Type"})
            wireTitleModel.append({"title":"Horizontal Location"})
            wireTitleModel.append({"title":"Vertical Location"})
            wireTitleModel.append({"title":"Vertical Position"})
        }
    }

    Row {
        id: headTitle
        anchors.top: parent.top
        anchors.topMargin: 30
        anchors.left: tipsRec.left
        anchors.leftMargin: 20
        spacing: 30
        clip: true
        Repeater {
            id: headRepeater
            model: partTitleModel
            delegate:  Text {
                verticalAlignment: Qt.AlignVCenter
                width: 200
                font.family: "arial"
                font.pixelSize: 20
                color: "white"
                clip: true
                text: qsTr(title)
            }
        }
    }

    Rectangle {
        id: tipsRec
        anchors.top: headTitle.bottom
        anchors.topMargin: 10
        anchors.left: column.right
        anchors.leftMargin: 20
        anchors.right: parent.right
        anchors.rightMargin: 20
        clip: true
        height: 1
        color: "#ffffff"
    }
    Rectangle {
        id: tipsRec2
        anchors.top: tipsRec.bottom
        anchors.left: column.right
        anchors.leftMargin: 20
        anchors.right: parent.right
        anchors.rightMargin: 20
        clip: true
        height: 1
        color: "#0d0f11"
    }

    ListView {
        id: listView
        anchors.top: tipsRec2.bottom
        anchors.bottom: scrollbar2.top
        anchors.left: tipsRec2.left
        anchors.leftMargin: 20
        width: headTitle.width
        clip: true
        model: 20//partModel
        delegate: listDelegate
    }
    Image {
        id: back
        width: column.width+50
        height: parent.height
        source: "qrc:/images/images/bg.png"
    }
    Image {
        id: scrollLeft
        anchors.verticalCenter:scrollbar2.verticalCenter
        anchors.right: scrollbar2.left
        width: 11
        height: 17
        visible: true
        source: "qrc:/images/images/left.png"
    }
    Image {
        id: scrollRight
        anchors.verticalCenter:scrollbar2.verticalCenter
        anchors.left: scrollbar2.right
        width: 11
        height: 17
        visible: true
        source: "qrc:/images/images/right.png"
    }
    Image {
        id: scrollUp
        anchors.top: tipsRec2.bottom
        anchors.topMargin: 2
        anchors.right: parent.right
        anchors.rightMargin: 6
        width: 17
        height: 10
        visible: listView.contentHeight > listView.height ? true : false
        source: "qrc:/images/images/up.png"
    }
    Image {
        id: scrollDown
        anchors.bottom: scrollbar2.top
        anchors.bottomMargin: 2
        anchors.right: parent.right
        anchors.rightMargin: 6
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
        anchors.right: parent.right
        anchors.rightMargin: 8
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
        id: scrollbar2
        anchors.left: tipsRec2.left
        anchors.leftMargin: 11
        anchors.bottom: rowButton.top
        anchors.bottomMargin: 20
        width: tipsRec2.width-22
        height: 17
        color: "#585858"
        radius: 10
        visible: true
        Rectangle {
            id: button2
            anchors.top: parent.top
            x: 0
            width: scrollbar2.width / listView.width * scrollbar2.width
            height: 17
            color: "#ccbfbf"
            radius: 10
            // 鼠标区域
            MouseArea {
                id: mouseArea2
                anchors.fill: button2
                drag.target: button2
                drag.axis: Drag.XAxis
                drag.minimumX: 0
                drag.maximumX: scrollbar2.width - button2.width
            }
            onXChanged: {
                listView.anchors.leftMargin = -button2.x*1.1
                headTitle.anchors.leftMargin = -button2.x*1.1
                console.log(button2.x)
            }
        }
    }
    ExclusiveGroup {
        id: listviewPositionGroup
    }
    Component {
        id: listDelegate
        Item {
            width: listView.width
            height: 50
            clip: true
            Row {
                width: parent.width
                height: parent.height
                spacing: 30
                clip: true
                Repeater {
                    id: listRepeater
                    model: viewLib.count
                    delegate:  Text {
                        anchors.verticalCenter: parent.verticalCenter
                        width: 200
                        font.family: "arial"
                        font.pixelSize: 20
                        color: "white"
                        clip: true
                        elide: Text.ElideRight
                        text: qsTr("11111")
                    }
                }
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    selectIndx = index
                    selectCheck.checked = !selectCheck.checked
                }
            }
            Rectangle {
                id: backGround
                anchors.fill: parent
                color: "black"
                opacity: 0//opacityValue
                RadioButton {
                    id: selectCheck
                    exclusiveGroup: listviewPositionGroup
                    visible: false
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


    Row {
        id: rowButton
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 30
        anchors.right: parent.right
        anchors.rightMargin: 20
        spacing: 20
        height: 79
        CButton {
            width: 250
            height: 79
            textColor: "white"
            text: qsTr("View Details")
        }
        CButton {
            width: 250
            height: 79
            textColor: "white"
            text: qsTr("Export")
        }
        CButton {
            width: 250
            height: 79
            textColor: "white"
            text: qsTr("Back")
        }
    }
}
