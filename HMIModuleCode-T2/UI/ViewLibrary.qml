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
            id: part
            width: column.width
            height: 79
            textColor: "white"
            text: qsTr("Part")
            opacity: 0.2
            onClicked: {
                if (splice.opacity == 0.2) {
                    splice.opacity = 1
                    part.opacity = 0.2
                } else if (wire.opacity == 0.2) {
                    wire.opacity = 1
                    part.opacity = 0.2
                }
                headRepeater.model = partTitleModel
                viewLib.count = partTitleModel.count
                listView.model = partModel
            }
        }
        CButton {
            id: splice
            width: column.width
            height: 79
            textColor: "white"
            text: qsTr("Splice")
            onClicked: {
                if (part.opacity == 0.2) {
                    part.opacity = 1
                    splice.opacity = 0.2
                } else if (wire.opacity == 0.2) {
                    wire.opacity = 1
                    splice.opacity = 0.2
                }
                headRepeater.model = spliceTitleModel
                viewLib.count = spliceTitleModel.count
                listView.model = spliceModel
            }
        }
        CButton {
            id: wire
            width: column.width
            height: 79
            textColor: "white"
            text: qsTr("Wire")
            onClicked: {
                if (part.opacity == 0.2) {
                    part.opacity = 1
                    wire.opacity = 0.2
                } else if (splice.opacity == 0.2) {
                    splice.opacity = 1
                    wire.opacity = 0.2
                }
                headRepeater.model = wireTitleModel
                viewLib.count = wireTitleModel.count
                listView.model = wireModel
            }
        }
    }
    ListModel {
        id: partKeyModel
    }
    ListModel {
        id: partTitleModel
    }
    ListModel {
        id: spliceTitleModel
    }
    ListModel {
        id: wireTitleModel
//        list << "partId" << "name" << "date" << "totalSplices" << "type" << "operatorName" << "processMode" << "ofWorkstation" << "ofSplicesperWorkstation" << "rows" << "columns" << "maxSplicesPerZone";

        Component.onCompleted: {
            partKeyModel.append({"title":"name"})
            partKeyModel.append({"title":"date"})
            partKeyModel.append({"title":"totalSplices"})
            partKeyModel.append({"title":"type"})
            partKeyModel.append({"title":"operatorName"})
            partKeyModel.append({"title":"processMode"})
            partKeyModel.append({"title":"ofWorkstation"})
            partKeyModel.append({"title":"ofSplicesperWorkstation"})
            partKeyModel.append({"title":"rows"})
            partKeyModel.append({"title":"columns"})
            partKeyModel.append({"title":"maxSplicesPerZone"})

            partTitleModel.append({"title":"PartName"})
            partTitleModel.append({"title":"DateCreated"})
            partTitleModel.append({"title":"OperatorName"})
            partTitleModel.append({"title":"TotalSplices"})
            partTitleModel.append({"title":"ProcessMode"})
            partTitleModel.append({"title":"#ofWorkstation"})
            partTitleModel.append({"title":"#ofSplicesperWorkstation"})
            partTitleModel.append({"title":"Rows"})
            partTitleModel.append({"title":"Columns"})
            partTitleModel.append({"title":"MaxSplicesPerZone"})

            spliceTitleModel.append({"title":"SpliceName"})
            spliceTitleModel.append({"title":"DateCreated"})
            spliceTitleModel.append({"title":"OperatorName"})
            spliceTitleModel.append({"title":"CrossSection"})
            spliceTitleModel.append({"title":"TotalWires"})
            spliceTitleModel.append({"title":"Verified"})
            spliceTitleModel.append({"title":"WeldMode"})
            spliceTitleModel.append({"title":"Energy"})
            spliceTitleModel.append({"title":"Amplitude"})
            spliceTitleModel.append({"title":"Width"})
            spliceTitleModel.append({"title":"TriggerPressure"})
            spliceTitleModel.append({"title":"WeldPressure"})
            spliceTitleModel.append({"title":"Time+"})
            spliceTitleModel.append({"title":"Time-"})
            spliceTitleModel.append({"title":"Power+"})
            spliceTitleModel.append({"title":"Power-"})
            spliceTitleModel.append({"title":"Pre-Height+"})
            spliceTitleModel.append({"title":"Pre-Height-"})
            spliceTitleModel.append({"title":"Height+"})
            spliceTitleModel.append({"title":"Height-"})

//            list <<"WireId"<< "WireName" << "DateCreated" << "OperatorName" << "Color" << "StripeType" << "StripeColor" << "Gauge" << "MetalType" << "HorizontalLocation" << "VerticalLocation" << "VerticalPosition";
            wireTitleModel.append({"title":"WireName"})
            wireTitleModel.append({"title":"DateCreated"})
            wireTitleModel.append({"title":"OperatorName"})
            wireTitleModel.append({"title":"Color"})
            wireTitleModel.append({"title":"StripeType"})
            wireTitleModel.append({"title":"StripeColor"})
            wireTitleModel.append({"title":"Gauge"})
            wireTitleModel.append({"title":"MetalType"})
            wireTitleModel.append({"title":"HorizontalLocation"})
            wireTitleModel.append({"title":"VerticalLocation"})
            wireTitleModel.append({"title":"VerticalPosition"})
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
        model: partModel
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
            property var listIndex: 0
            Component.onCompleted: {
                listIndex = index
            }

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
                        text: listView.model.getValue(listIndex,headRepeater.model.get(index).title)
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
            text: qsTr("Edit Details")
            onClicked: {
                root.menuInit(0)
            }
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
