import QtQuick 2.0
import QtQuick.Controls 1.2

Item {
    property int selectIndx: -1
    property var listModel: partModel
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
                headRepeater.model = partModel
                listModel = partModel
            }
        }
        CButton {
            width: column.width
            height: 79
            textColor: "white"
            text: qsTr("Splice")
            onClicked: {
                headRepeater.model = spliceModel
                listModel = spliceModel
            }
        }
        CButton {
            width: column.width
            height: 79
            textColor: "white"
            text: qsTr("Wire")
            onClicked: {
                headRepeater.model = wireModel
                listModel = wireModel
            }
        }
    }
    ListModel {
        id: partModel
    }
    ListModel {
        id: spliceModel
    }
    ListModel {
        id: wireModel
        Component.onCompleted: {
            partModel.append({"title":"Part Name"})
            partModel.append({"title":"Date Created"})
            partModel.append({"title":"Operator Name"})
            partModel.append({"title":"Total Splices"})
            partModel.append({"title":"Process Mode"})
            partModel.append({"title":"# of Workstation"})
            partModel.append({"title":"# of Splices per Workstation"})
            partModel.append({"title":"Rows"})
            partModel.append({"title":"Columns"})
            partModel.append({"title":"Max Splices Per Zone"})

            spliceModel.append({"title":"Splice Name"})
            spliceModel.append({"title":"Date Created"})
            spliceModel.append({"title":"Operator Name"})
            spliceModel.append({"title":"Cross Section"})
            spliceModel.append({"title":"Total Wires"})
            spliceModel.append({"title":"Verified"})
            spliceModel.append({"title":"Weld Mode"})
            spliceModel.append({"title":"Energy"})
            spliceModel.append({"title":"Amplitude"})
            spliceModel.append({"title":"Width"})
            spliceModel.append({"title":"Trigger Pressure"})
            spliceModel.append({"title":"Weld Pressure"})
            spliceModel.append({"title":"Time+"})
            spliceModel.append({"title":"Time-"})
            spliceModel.append({"title":"Power+"})
            spliceModel.append({"title":"Power-"})
            spliceModel.append({"title":"Pre-Height+"})
            spliceModel.append({"title":"Pre-Height-"})
            spliceModel.append({"title":"Height+"})
            spliceModel.append({"title":"Height-"})

            wireModel.append({"title":"Wire Name"})
            wireModel.append({"title":"Date Created"})
            wireModel.append({"title":"Operator Name"})
            wireModel.append({"title":"Color"})
            wireModel.append({"title":"StripeType"})
            wireModel.append({"title":"Stripe Color"})
            wireModel.append({"title":"Gauge"})
            wireModel.append({"title":"Metal Type"})
            wireModel.append({"title":"Horizontal Location"})
            wireModel.append({"title":"Vertical Location"})
            wireModel.append({"title":"Vertical Position"})
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
            model: partModel
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
        model: listModel
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
                    model: listModel
                    delegate:  Text {
                        anchors.verticalCenter: parent.verticalCenter
                        width: 200
                        font.family: "arial"
                        font.pixelSize: 20
                        color: "white"
                        clip: true
                        elide: Text.ElideRight
                        text: qsTr(title)
                        onTextChanged: {
                            console.log("222222222222222222",listView.model.get(index).title,title,index)
                        }
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
