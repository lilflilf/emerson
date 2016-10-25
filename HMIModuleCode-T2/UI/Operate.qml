import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import QtQuick.Window 2.2

Item {
    width: Screen.desktopAvailableWidth
    height: Screen.desktopAvailableHeight*0.8
    property int selectIndx: -1
//    Rectangle {
//        anchors.fill: parent
//        color: "#6d6e71"
//    }
    Image {
        anchors.fill: parent
        source: "qrc:/images/images/bg.png"
    }
    Loader {
        id: loader
        z: 10
        anchors.fill: parent
    }
    ListModel {
        id: listModel
        Component.onCompleted: {
            listModel.append({"name":"work order id111111111111111111111111","date":"2016/10/13","middle":"part65487911111111111111111111111","count":"10011111111111111111111111","opacityValue":"0"})
            listModel.append({"name":"work order id211111111111111111111111","date":"2016/10/13","middle":"part65487911111111111111111111111","count":"10011111111111111111111111","opacityValue":"0"})
            listModel.append({"name":"work order id311111111111111111111111","date":"2016/10/13","middle":"part65487911111111111111111111111","count":"10011111111111111111111111","opacityValue":"0"})
            listModel.append({"name":"work order id411111111111111111111111","date":"2016/10/13","middle":"part65487911111111111111111111111","count":"10011111111111111111111111","opacityValue":"0"})
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
            listModel.append({"name":"work order id511111111111111111111111","date":"2016/10/13","middle":"part65487911111111111111111111111","count":"10011111111111111111111111","opacityValue":"0"})
            listModel.append({"name":"work order id511111111111111111111111","date":"2016/10/13","middle":"part65487911111111111111111111111","count":"10011111111111111111111111","opacityValue":"0"})
            listModel.append({"name":"work order id511111111111111111111111","date":"2016/10/13","middle":"part65487911111111111111111111111","count":"10011111111111111111111111","opacityValue":"0"})
        }
    }
    Text {
        id: title
        anchors.top: parent.top
        anchors.topMargin: 14
        anchors.left: parent.left
        anchors.leftMargin: 24
        width: parent.width/5
        color: "white"
        clip: true
        font.pointSize: 16
        font.family: "arial"
        text: qsTr("Work Order Library")
    }
    Text {
        id: head1
        anchors.top: title.bottom
        anchors.topMargin: 14
        anchors.left: parent.left
        anchors.leftMargin: parent.width*0.023
        width: parent.width/5
        color: "white"
        font.pointSize: 16
        horizontalAlignment: Qt.AlignHCenter
        clip: true
        font.family: "arial"
        text: qsTr("WORK ORDER ID")
    }
    Text {
        id: head2
        anchors.top: title.bottom
        anchors.topMargin: 14
        anchors.left: head1.right
        anchors.leftMargin: parent.width*0.07
        width: parent.width*0.15
        color: "white"
        font.pointSize: 16
        horizontalAlignment: Qt.AlignHCenter
        clip: true
        font.family: "arial"
        text: qsTr("DATE CREATED")
    }
    Text {
        id: head3
        anchors.top: title.bottom
        anchors.topMargin: 14
        anchors.left: head2.right
        anchors.leftMargin: parent.width*0.056
        width: parent.width*0.2
        horizontalAlignment: Qt.AlignHCenter
        color: "white"
        font.pointSize: 16
        clip: true
        font.family: "arial"
        text: qsTr("PART#")
    }
    Text {
        id: head4
        anchors.top: title.bottom
        anchors.topMargin: 14
        anchors.left: head3.right
        anchors.leftMargin: parent.width*0.083
        width: parent.width*0.1
        horizontalAlignment: Qt.AlignCenter
        color: "white"
        font.pointSize: 16
        font.family: "arial"
        clip: true
        text: qsTr("QLIANTITY")
    }
    Rectangle {
        id: tipsRec
        anchors.top: head1.bottom
        anchors.topMargin: 4
        width: parent.width
        height: 10
        color: "#585858"
    }
    ListView {
        id: listView
        anchors.top: tipsRec.bottom
        anchors.left: parent.left
        anchors.leftMargin: 24
        width: parent.width - 48
        height: Screen.desktopAvailableHeight*0.55
        clip: true
        model: listModel
        delegate: listDelegate
    }
    Rectangle {
        id: scrollbar
        width: 10
        height: listView.height
        anchors.top: tipsRec.bottom
        anchors.left: listView.right
        color: "#585858"
        radius: 10
        //z: 9
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
            height: 40
            Text {
                id: headName
                anchors.top: parent.top
                anchors.topMargin: 10
                anchors.left: parent.left
                anchors.leftMargin: parent.width*0.02
                width: parent.width/5
                horizontalAlignment: Qt.AlignLeft
                elide: Text.ElideRight
                text: name
                clip: true
                color: "white"
                font.pointSize: 16
                font.family: "arial"
            }
            Text {
                id: headData
                anchors.top: parent.top
                anchors.topMargin: 10
                anchors.left: headName.right
                anchors.leftMargin: parent.width*0.09
                width: parent.width*0.1
                horizontalAlignment: Qt.AlignCenter
                text: date
                clip: true
                color: "white"
                font.pointSize: 16
                font.family: "arial"
            }
            Text {
                id: headMiddle
                anchors.top: parent.top
                anchors.topMargin: 10
                anchors.left: headData.right
                anchors.leftMargin: parent.width*0.09
                width: parent.width*0.2
                horizontalAlignment: Qt.AlignCenter
                text: middle
                clip: true
                color: "white"
                font.pointSize: 16
                font.family: "arial"
            }
            Text {
                id: headCount
                anchors.top: parent.top
                anchors.topMargin: 10
                anchors.left: headMiddle.right
                anchors.leftMargin: parent.width*0.09
                horizontalAlignment: Qt.AlignCenter
                width: parent.width*0.1
                text: count
                color: "white"
                clip: true
                font.pointSize: 16
                font.family: "arial"
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    if (selectIndx == -1) {
                        listModel.set(index,{"opacityValue":"0.3"})
                        selectIndx = index
                    } else {
                        listModel.set(selectIndx,{"opacityValue":"0"})
                        selectIndx = index
                        listModel.set(index,{"opacityValue":"0.3"})
                    }
                }
            }
            Rectangle {
                id: backGround
                anchors.fill: parent
                color: "black"
                opacity: opacityValue
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
        id: addnewOrder
        anchors.top: bottomTip.bottom
        anchors.topMargin: 18
        anchors.left: parent.left
        anchors.leftMargin: 24
        height: 79
        width: 300//parent.width/4.4
        text: qsTr("+ ADD NEW WORK ORDEAR")
        pointSize: 14
        clip: true
        textColor: "white"
        onClicked: {
            backGround.visible = true
            backGround.opacity = 0.5
            dialog.visible = true
            dialog.bIsEdit = false
        }
    }
    CButton {
        id: editExistingOrder
        anchors.top: bottomTip.bottom
        anchors.topMargin: 18
        anchors.left: addnewOrder.right
        anchors.leftMargin: 24
        height: 79
        width: 300//parent.width/4.4
        text: qsTr("EDIT EXISTING WORK ORDER")
        pointSize: 14
        clip: true
        textColor: "white"
        onClicked: {
            backGround.visible = true
            backGround.opacity = 0.5
            dialog.visible = true
            dialog.bIsEdit = true
        }
    }
    CButton {
        id: importOrder
        anchors.top: bottomTip.bottom
        anchors.topMargin: 18
        anchors.left: editExistingOrder.right
        anchors.leftMargin: 24
        height: 79
        width: 300//parent.width/4.4
        text: qsTr("IMPORT WORK ORDER")
        pointSize: 14
        clip: true
        textColor: "white"
    }
    CButton {
        id: selectOk
        anchors.top: bottomTip.bottom
        anchors.topMargin: 18
        anchors.left: importOrder.right
        anchors.leftMargin: 24
        height: 79
        width: 300//parent.width/4.4
        text: qsTr("SELECT")
        pointSize: 14
        clip: true
        textColor: "white"
        onClicked: {
            console.log("ssssssddddddddd")
            //loader.source = "qrc:/UI/OperateDetails.qml"
            loader.source = "qrc:/UI/TestDetail.qml"
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
    Rectangle {
        id: dialog
        visible: false
        anchors.centerIn: parent
        property bool bIsEdit: false
        width: parent.width*0.6
        height: parent.height*0.4
        color: "gray"
        Text {
            id: orderId
            anchors.top: parent.top
            anchors.topMargin: 24
            anchors.left: parent.left
            anchors.leftMargin: parent.width*0.1
            width: parent.width/6
            font.pointSize: 16
            font.family: "arial"
            text: qsTr("Work Order ID")
            color: "white"
        }
        MyLineEdit {
            id: inputworkId
            anchors.left: orderId.right
            anchors.leftMargin: parent.width*0.03
            anchors.top: parent.top
            anchors.topMargin: 18
            width: parent.width/2
            horizontalAlignment: Qt.AlignHCenter
            height: 40
            inputWidth: parent.width/2
            inputColor: "white"
            inputHeight: 40
            inputText: dialog.bIsEdit ? listModel.get(selectIndx).name : ""
        }
        Text {
            id: selectTips
            anchors.top: orderId.bottom
            anchors.topMargin: parent.height*0.15
            anchors.left: parent.left
            anchors.leftMargin: parent.width*0.1
            width: parent.width/6
            font.pointSize: 16
            font.family: "arial"
            text: qsTr("Select Part")
            color: "white"
        }
        MyLineEdit {
            id: selectworkId
            anchors.left: orderId.right
            anchors.leftMargin: parent.width*0.03
            anchors.top: orderId.bottom
            anchors.topMargin: parent.height*0.12
            width: parent.width/2
            horizontalAlignment: Qt.AlignHCenter
            height: 40
            inputWidth: parent.width/2
            inputColor: "white"
            inputHeight: 40
            visible: dialog.bIsEdit
            inputText: dialog.bIsEdit ? listModel.get(selectIndx).middle : ""
        }
        CButton {
            id: selectPart
            anchors.left: orderId.right
            anchors.leftMargin: parent.width*0.03
            anchors.top: orderId.bottom
            anchors.topMargin: parent.height*0.12
            width: parent.width/2
            visible: !dialog.bIsEdit
            height: 40
            text: qsTr("SELECT PART")
            textColor: "white"
        }
        Text {
            id: quantity
            anchors.top: selectTips.bottom
            anchors.topMargin: parent.height*0.15
            anchors.left: parent.left
            anchors.leftMargin: parent.width*0.1
            width: parent.width/6
            font.pointSize: 16
            font.family: "arial"
            text: qsTr("Quantity")
            color: "white"
        }
        MyLineEdit {
            id: inputquantity
            anchors.left: orderId.right
            anchors.leftMargin: parent.width*0.03
            anchors.top: selectTips.bottom
            anchors.topMargin: parent.height*0.12
            width: parent.width/2
            horizontalAlignment: Qt.AlignHCenter
            height: 40
            inputWidth: parent.width/2
            inputColor: "white"
            inputHeight: 40
            inputText: dialog.bIsEdit ? listModel.get(selectIndx).count : ""
        }
        CButton {
            id: cancel
            anchors.right: sure.left
            anchors.rightMargin: 24
            anchors.top: quantity.bottom
            anchors.topMargin: parent.height*0.15
            width: parent.width/3
            height: 79
            text: qsTr("CANCEL")
            textColor: "white"
            onClicked: {
                backGround.visible = false
                backGround.opacity = 0
                dialog.visible = false
            }
        }
        CButton {
            id: sure
            anchors.right: parent.right
            anchors.rightMargin: 24
            anchors.top: quantity.bottom
            anchors.topMargin: parent.height*0.15
            width: parent.width/3
            height: 79
            text: qsTr("OK")
            textColor: "white"
            onClicked: {
                backGround.visible = false
                backGround.opacity = 0
                dialog.visible = false
            }
        }
    }
}
