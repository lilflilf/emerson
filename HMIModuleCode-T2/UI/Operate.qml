import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import QtQuick.Dialogs 1.2

Item {
    property int selectIndx: -1
    Image {
        anchors.fill: parent
        source: "qrc:/images/images/bg.png"
    }
    ExclusiveGroup {
        id: listviewPositionGroup;
    }
    Loader {
        id: loader
        z: 10
        anchors.fill: parent
    }
    Connections{
        target: loader.item
        onSignalFileDialogCancel: {
            loader.source = ""
        }
    }

    ListModel {
        id: testModel
    }

    ListModel {
        id: listModel
        Component.onCompleted: {
            listModel.append({"name":"work order id111111111111111111111111","date":"2016/10/13","middle":"part65487911111111111111111111111","count":"10011111111111111111111111","opacityValue":"0"})
            listModel.append({"name":"work order id211111111111111111111111","date":"2016/10/13","middle":"part65487911111111111111111111111","count":"10011111111111111111111111","opacityValue":"0"})
            listModel.append({"name":"work order id311111111111111111111111","date":"2016/10/13","middle":"part65487911111111111111111111111","count":"10011111111111111111111111","opacityValue":"0"})
            listModel.append({"name":"work order id411111111111111111111111","date":"2016/10/13","middle":"part65487911111111111111111111111","count":"10011111111111111111111111","opacityValue":"0"})
            listModel.append({"name":"work order","date":"2016/10/13","middle":"part65487911","count":"10","opacityValue":"0"})
            listModel.append({"name":"work order","date":"2016/10/13","middle":"part6548791","count":"10","opacityValue":"0"})
            listModel.append({"name":"work order","date":"2016/10/13","middle":"part6548","count":"100111","opacityValue":"0"})
            listModel.append({"name":"work order id511111111111111111111111","date":"2016/10/13","middle":"part65487911111111111111111111111","count":"10011111111111111111111111","opacityValue":"0"})
            listModel.append({"name":"work order id511111111111111111111111","date":"2016/10/13","middle":"part65487911111111111111111111111","count":"10011111111111111111111111","opacityValue":"0"})
            listModel.append({"name":"work order id511111111111111111111111","date":"2016/10/13","middle":"part65487911111111111111111111111","count":"10011111111111111111111111","opacityValue":"0"})
            listModel.append({"name":"work order id511111111111111111111111","date":"2016/10/13","middle":"part65487911111111111111111111111","count":"10011111111111111111111111","opacityValue":"0"})
            listModel.append({"name":"work order id511111111111111111111111","date":"2016/10/13","middle":"part65487911111111111111111111111","count":"10011111111111111111111111","opacityValue":"0"})
            listModel.append({"name":"work order id511111111111111111111111","date":"2016/10/13","middle":"part65487911111111111111111111111","count":"10011111111111111111111111","opacityValue":"0"})
            listModel.append({"name":"work order id511111111111111111111111","date":"2016/10/13","middle":"part65487911111111111111111111111","count":"10011111111111111111111111","opacityValue":"0"})
            listModel.append({"name":"work order id511111111111111111111111","date":"2016/10/13","middle":"part65487911111111111111111111111","count":"10011111111111111111111111","opacityValue":"0"})
            listModel.append({"name":"work order id511111111111111111111111","date":"2016/10/13","middle":"part65487911111111111111111111111","count":"10011111111111111111111111","opacityValue":"0"})
            listModel.append({"name":"work order id511111111111111111111111","date":"2016/10/13","middle":"part65487911111111111111111111111","count":"10011111111111111111111111","opacityValue":"0"})
            listModel.append({"name":"work order id511111111111111111111111","date":"2016/10/13","middle":"part65487911111111111111111111111","count":"10011111111111111111111111","opacityValue":"0"})
            listModel.append({"name":"work order id511111111111111111111111","date":"2016/10/13","middle":"part65487911111111111111111111111","count":"10011111111111111111111111","opacityValue":"0"})
            listModel.append({"name":"work order id511111111111111111111111","date":"2016/10/13","middle":"part65487911111111111111111111111","count":"10011111111111111111111111","opacityValue":"0"})
            listModel.append({"name":"work order id511111111111111111111111","date":"2016/10/13","middle":"part65487911111111111111111111111","count":"10011111111111111111111111","opacityValue":"0"})
            listModel.append({"name":"work order id511111111111111111111111","date":"2016/10/13","middle":"part65487911111111111111111111111","count":"10011111111111111111111111","opacityValue":"0"})
            listModel.append({"name":"work order id511111111111111111111111","date":"2016/10/13","middle":"part65487911111111111111111111111","count":"10011111111111111111111111","opacityValue":"0"})
            testModel.append({"name":"splice test title 11111111111222","date":"2016/10/13","middle":"VW","type":"YES"})
            testModel.append({"name":"splice test title 1111111111122","date":"2016/10/13","middle":"VW","type":"YES"})
            testModel.append({"name":"splice test title 11111111111","date":"2016/10/13","middle":"VW","type":"YES"})
            testModel.append({"name":"splice test title 11111111111","date":"2016/10/13","middle":"VW","type":"YES"})
            testModel.append({"name":"splice test title 1111111111133333333333333","date":"2016/10/13","middle":"VW","type":"YES"})
        }
    }
    Text {
        id: head1
        anchors.top: parent.top
        anchors.topMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 52
        width: (parent.width-104)/4
        horizontalAlignment: Qt.AlignHCenter
        color: "white"
        font.pixelSize: 25
        clip: true
        font.family: "arial"
        text: qsTr("WORK ORDER ID")
    }
    Text {
        id: head2
        anchors.top: parent.top
        anchors.topMargin: 14
        anchors.left: head1.right
        width: (parent.width-104)/4
        horizontalAlignment: Qt.AlignHCenter
        color: "white"
        font.pixelSize: 25
        clip: true
        font.family: "arial"
        text: qsTr("DATE CREATED")
    }
    Text {
        id: head3
        anchors.top: parent.top
        anchors.topMargin: 14
        anchors.left: head2.right
        width: (parent.width-104)/4
        horizontalAlignment: Qt.AlignHCenter
        color: "white"
        font.pixelSize: 25
        clip: true
        font.family: "arial"
        text: qsTr("PART#")
    }
    Text {
        id: head4
        anchors.top: parent.top
        anchors.topMargin: 14
        anchors.left: head3.right
        width: (parent.width-104)/4
        horizontalAlignment: Qt.AlignHCenter
        color: "white"
        font.pixelSize: 25
        font.family: "arial"
        clip: true
        text: qsTr("QLIANTITY")
    }
    Rectangle {
        id: tipsRec
        anchors.top: head1.bottom
        anchors.topMargin: 20
        anchors.left: parent.left
        anchors.leftMargin: 20
        width: parent.width - 40
        clip: true
        height: 1
        color: "#ffffff"
    }
    Rectangle {
        id: tipsRec2
        anchors.top: tipsRec.bottom
        anchors.left: parent.left
        anchors.leftMargin: 20
        width: parent.width - 40
        clip: true
        height: 1
        color: "#0d0f11"
    }

    ListView {
        id: listView
        anchors.top: tipsRec2.bottom
        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.bottom: bottomTip.top
        width: parent.width - 60
        clip: true
        model: workOrderModel
        delegate: listDelegate
    }
    Image {
        id: scrollUp
        anchors.top: tipsRec2.bottom
        anchors.topMargin: 2
        anchors.left: listView.right
        width: 17
        height: 10
        visible: listView.contentHeight > listView.height ? true : false
        source: "qrc:/images/images/up.png"
    }
    Image {
        id: scrollDown
        anchors.bottom: bottomTip.top
        anchors.bottomMargin: 2
        anchors.left: listView.right
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
    Component {
        id: listDelegate
        Item {
            width: listView.width
            height: 50
            Text {
                id: headName
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                anchors.leftMargin: 48
                width: (parent.width-96)/4
                horizontalAlignment: Qt.AlignLeft
                elide: Text.ElideRight
                text: name
                clip: true
                color: "white"
                font.pointSize: 20
                font.family: "arial"
            }
            Text {
                id: headData
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: headName.right
                width: (parent.width-96)/4
                horizontalAlignment: Qt.AlignCenter
                text: date
                clip: true
                color: "white"
                font.pointSize: 20
                font.family: "arial"
            }
            Text {
                id: headMiddle
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: headData.right
                width: (parent.width-96)/4
                horizontalAlignment: Qt.AlignLeft
                text: middle
                elide: Text.ElideRight
                clip: true
                color: "white"
                font.pointSize: 20
                font.family: "arial"
            }
            Text {
                id: headCount
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: headMiddle.right
                anchors.leftMargin: (parent.width-96)/12
                horizontalAlignment: Qt.AlignLeft
                width: (parent.width-96)/12
                text: count
                elide: Text.ElideRight
                color: "white"
                clip: true
                font.pointSize: 20
                font.family: "arial"
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
    Rectangle {
        id: bottomTip
        anchors.bottom: bottomTip2.top
        anchors.left: parent.left
        anchors.leftMargin: 20
        width: parent.width - 40
        clip: true
        height: 1
        color: "#ffffff"
    }
    Rectangle {
        id: bottomTip2
        anchors.bottom: addnewOrder.top
        anchors.bottomMargin: 24
        anchors.left: parent.left
        anchors.leftMargin: 20
        width: parent.width - 40
        clip: true
        height: 1
        color: "#0d0f11"
    }
    CButton {
        id: addnewOrder
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 15
//        height: 79
        width: (parent.width-230)/4
        spacing: 10
        iconSource: "qrc:/images/images/Add.png"
        text: qsTr("ADD NEW")
        pointSize: 20
        clip: true
        textColor: "white"
        onClicked: {
            backGround.visible = true
            backGround.opacity = 0.5
            dialog.bIsEdit = false
            dialog.visible = true
        }
    }
    CButton {
        id: editExistingOrder
        anchors.bottom: addnewOrder.bottom
//        anchors.bottomMargin: 43
        anchors.left: addnewOrder.right
        anchors.leftMargin: 15
//        height: 79
        width: (parent.width-230)/4
        spacing: 10
        iconSource: "qrc:/images/images/stting.png"
        text: qsTr("EDIT EXISTING")
        pointSize: 20
        clip: true
        textColor: "white"
        onClicked: {
            if(workOrderModel.count() == 0 || selectIndx == -1) {
                return
            }
            backGround.visible = true
            backGround.opacity = 0.5
            dialog.bIsEdit = true
            dialog.visible = true
        }
    }
    CButton {
        id: deleOrder
        anchors.bottom: addnewOrder.bottom
//        anchors.bottomMargin: 43
        anchors.left: editExistingOrder.right
        anchors.leftMargin: 15
//        height: 79
        width: (parent.width-230)/4
        spacing: 10
//        iconSource: "qrc:/images/images/import.png"
        text: qsTr("DELETE WORK ORDER")
        pointSize: 20
        clip: true
        textColor: "white"
        onClicked: {
        }
    }
    CButton {
        id: importOrder
        anchors.bottom: addnewOrder.bottom
//        anchors.bottomMargin: 43
        anchors.left: deleOrder.right
        anchors.leftMargin: 15
//        height: 79
        width: (parent.width-230)/4
        spacing: 10
        iconSource: "qrc:/images/images/import.png"
        text: qsTr("IMPORT WORK ORDER")
        pointSize: 20
        clip: true
        textColor: "white"
        onClicked: {
            loader.source = "qrc:/UI/MyFileDialog.qml"
        }
    }
    CButton {
        id: selectOk
        anchors.bottom: addnewOrder.bottom
//        anchors.bottomMargin: 43
        anchors.right: parent.right
        anchors.rightMargin: 20
//        height: 79
        width: 130
        spacing: 10
        iconSource: "qrc:/images/images/OK.png"
        text: qsTr("OK")
        pointSize: 20
        clip: true
        textColor: "white"
        onClicked: {
            if (selectIndx != -1)
                loader.source = "qrc:/UI/OperateDetails.qml"
        }
    }
    Rectangle {
        id: backGround
        anchors.fill: parent
        color: "black"
        opacity: 0
        visible: false
        MouseArea {
            anchors.fill: parent
            onClicked: {
            }
        }

    }

    Image {
        id: dialog
        visible: false
        anchors.centerIn: parent
        property bool bIsEdit: false
        property var oldWorkOrderName: ""
        width: 639
        height: 390
        source: "qrc:/images/images/dialogbg.png"
        onBIsEditChanged: {
            if (bIsEdit)
               selectPart.text = workOrderModel.getWorkOrderValue(selectIndx, "middle")
        }
        onVisibleChanged: {
            if (dialog.bIsEdit && dialog.visible)
                dialog.oldWorkOrderName = workOrderModel.getWorkOrderValue(selectIndx, "name")
        }

        Text {
            id: orderId
            anchors.top: parent.top
            anchors.topMargin: 60
            anchors.right: inputworkId.left
            anchors.rightMargin: 20
            width: 150
            height: 60
            font.pointSize: 18
            font.family: "arial"
            text: qsTr("Work Order ID")
            verticalAlignment: Qt.AlignVCenter
            horizontalAlignment: Qt.AlignRight
            color: "white"
        }
        MyLineEdit {
            id: inputworkId
            anchors.top: parent.top
            anchors.topMargin: 60
            anchors.right: parent.right
            anchors.rightMargin: 72
            horizontalAlignment: Qt.AlignHCenter
            width: 375
            height: 60
            inputWidth: 375
            inputColor: "white"
            inputHeight: 60
            inputText: dialog.bIsEdit ? workOrderModel.getWorkOrderValue(selectIndx, "name") : "" //workOrderModel.get(selectIndx).name : ""
        }
        Text {
            id: selectTips
            anchors.top: inputworkId.bottom
            anchors.topMargin: 20
            anchors.right: selectPart.left
            anchors.rightMargin: 20
            width: 150
            height: 60
            font.pointSize: 18
            font.family: "arial"
            text: qsTr("Select Part")
            verticalAlignment: Qt.AlignVCenter
            horizontalAlignment: Qt.AlignRight
            color: "white"
        }
        CButton {
            id: selectPart
            property var partId: 1
            anchors.top: inputworkId.bottom
            anchors.topMargin: 20
            anchors.right: parent.right
            anchors.rightMargin: 72
            width: 375
            height: 60
            clip: true
            text: dialog.bIsEdit ? workOrderModel.getWorkOrderValue(selectIndx, "middle") : "SELECT PART" //workOrderModel.get(selectIndx).middle : qsTr("SELECT PART")
            textColor: "white"
            onClicked: {
                addExit.visible = true
            }
        }
        Text {
            id: quantity
            anchors.top: selectTips.bottom
            anchors.topMargin: 20
            anchors.right: inputquantity.left
            anchors.rightMargin: 20
            width: 150
            height: 60
            font.pointSize: 18
            font.family: "arial"
            text: qsTr("Quantity")
            verticalAlignment: Qt.AlignVCenter
            horizontalAlignment: Qt.AlignRight
            color: "white"
        }
        MyLineEdit {
            id: inputquantity
            anchors.top: selectTips.bottom
            anchors.topMargin: 20
            anchors.right: parent.right
            anchors.rightMargin: 72
            width: 375
            height: 60
            inputWidth: 375
            inputHeight: 60
            inputColor: "white"
            horizontalAlignment: Qt.AlignHCenter
            inputText: dialog.bIsEdit ? workOrderModel.getWorkOrderValue( selectIndx, "count") : "" //.get(selectIndx).count : ""
        }
        CButton {
            id: cancel
            anchors.right: sure.left
            anchors.rightMargin: 15
            anchors.top: quantity.bottom
            anchors.topMargin: 16
            width: 180
            text: qsTr("CANCEL")
            textColor: "white"
            iconSource: "qrc:/images/images/cancel.png"
            onClicked: {
                backGround.visible = false
                backGround.opacity = 0
                dialog.visible = false
                dialog.bIsEdit = false
                if (!dialog.bIsEdit) {
                    selectPart.text = "SELECT PART"
                }
            }
        }

        CButton {
            id: sure
            anchors.right: parent.right
            anchors.rightMargin: 72
            anchors.top: quantity.bottom
            anchors.topMargin: 16
            width: 180
            text: qsTr("OK")
            textColor: "white"
            iconSource: "qrc:/images/images/OK.png"
            onClicked: {
                backGround.visible = false
                backGround.opacity = 0
                dialog.visible = false
                if (dialog.bIsEdit)
                    workOrderModel.updateRecordIntoTable(workOrderModel.getWorkOrderValue(selectIndx, "workOrderId"),dialog.oldWorkOrderName, inputworkId.inputText,selectPart.partId,selectPart.text, inputquantity.inputText )
                else {
                    workOrderModel.insertRecordIntoTable(inputworkId.inputText,selectPart.partId,selectPart.text,inputquantity.inputText)
                    selectPart.text = "SELECT PART"
                }
//                selectIndx = -1
                dialog.bIsEdit = false
            }
        }
    }

    AddExistingSpliceWire {
        id: addExit
        anchors.centerIn: parent
        width: Screen.width*0.7
        height: Screen.height*0.6
        visible: false
        listModel: partModel //testModel
        titleName: qsTr("ADD WORK ORDEAR")
        componentName: qsTr("PART NAME")
        componentData: qsTr("DATE CREATED")
        componentMiddle: qsTr("# OF SPLICE")
        componenttype: qsTr("CROSS SECTION")
        componentCount: qsTr("")
        bIsOnlyOne: true
        onSignalAddExistCancel : {
            addExit.visible = false
        }
        onSignalAddExistSelectClick: {
            selectPart.partId = partId
            selectPart.text = name
            addExit.visible = false
        }
    }
}
