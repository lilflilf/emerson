import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2

Item {
    property int selectIndx: -1
    property var fourLevelIdentifier: ""
    function setDialogLevel()
    {
        fourLevelIdentifier = hmiAdaptor.permissionsettingGetValue("FourLevelIdentifier")
    }

    Image {
        anchors.fill: parent
        source: "qrc:/images/images/bg.png"
    }

    ExclusiveGroup {
        id: listviewPositionGroup;
    }

    Row {
        id: headTitle
        anchors.top: parent.top
        anchors.topMargin: 50
        anchors.left: parent.left
        anchors.leftMargin: 50
        width: parent.width - 100
        spacing: 10
        Text {
            anchors.verticalCenter: headTitle.verticalCenter
            width: (parent.width-30)/4
            color: "white"
            clip: true
            font.pointSize: 24
            font.family: "arial"
            text: qsTr("User Name")
        }
        Text {
            anchors.verticalCenter: headTitle.verticalCenter
            width: (parent.width-30)/4
            color: "white"
            clip: true
            font.pointSize: 24
            font.family: "arial"
            text: qsTr("Date Created")
        }
        Text {
            anchors.verticalCenter: headTitle.verticalCenter
            width: (parent.width-30)/4
            color: "white"
            clip: true
            font.pointSize: 24
            font.family: "arial"
            text: qsTr("Password")
        }
        Text {
            anchors.verticalCenter: headTitle.verticalCenter
            width: (parent.width-30)/4
            text: qsTr("Permission Level")
            color: "white"
            clip: true
            font.pointSize: 24
            font.family: "arial"
        }
    }
    Rectangle {
        id: line1
        anchors.top: headTitle.bottom
        anchors.topMargin: 24
        anchors.left: parent.left
        anchors.leftMargin: 20
        width: parent.width-40
        clip: true
        height: 1
        color: "#ffffff"
    }
    Rectangle {
        id: line2
        anchors.top: line1.bottom
        anchors.left: parent.left
        anchors.leftMargin: 20
        width: parent.width-40
        clip: true
        height: 1
        color: "#0d0f11"
    }
    ListView {
        id: listView
        anchors.top: line2.bottom
        anchors.left: parent.left
        anchors.leftMargin: 50
        width: parent.width - 100
        anchors.bottom: line3.top
        clip: true
        delegate: listDelegate
        model: operatorModel
    }
    Image {
        id: scrollUp
        anchors.top: line2.bottom
        anchors.topMargin: 2
        anchors.left: listView.right
        width: 17
        height: 10
        visible: listView.contentHeight > listView.height ? true : false
        source: "qrc:/images/images/up.png"
    }
    Image {
        id: scrollDown
        anchors.bottom: line3.top
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
                width: (parent.width-30)/4
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
                anchors.leftMargin: 10
                width: (parent.width-30)/4
                horizontalAlignment: Qt.AlignLeft
                text: date
                clip: true
                elide: Text.ElideRight
                color: "white"
                font.pointSize: 20
                font.family: "arial"
            }
            Text {
                id: headMiddle
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: headData.right
                anchors.leftMargin: 10
                width: (parent.width-30)/4
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
                anchors.leftMargin: 10
                horizontalAlignment: Qt.AlignHCenter
                width: (parent.width-30)/4
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
        id: line3
        anchors.bottom: line4.top
        anchors.left: parent.left
        anchors.leftMargin: 20
        width: parent.width-40
        clip: true
        height: 1
        color: "#ffffff"
    }
    Rectangle {
        id: line4
        anchors.bottom: deleteButton.top
        anchors.bottomMargin: 20
        anchors.left: parent.left
        anchors.leftMargin: 20
        width: parent.width-40
        clip: true
        height: 1
        color: "#0d0f11"
    }
    CButton {
        id: deleteButton
        anchors.right: parent.right
        anchors.rightMargin: 20
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 20
        width: 300
        text: qsTr("Delete")
        textColor: "white"
        onClicked: {
            if (selectIndx < 0)
                return
            operatorModel.removeValue(operatorModel.getOperatorValue(selectIndx,"operatorId"),operatorModel.getOperatorValue(selectIndx,"name"))
        }
    }
    CButton {
        id: editButton
        anchors.right: deleteButton.left
        anchors.rightMargin: 43
        anchors.bottom: deleteButton.bottom
        width: 300
        iconSource: "qrc:/images/images/stting.png"
        text: qsTr("Edit")
        textColor: "white"
        onClicked: {
            if (selectIndx < 0)
                return
            operatorDialog.bIsEdit = true
            backGround.visible = true
            backGround.opacity = 0.5
            operatorDialog.visible = true
            setDialogLevel()
//            operatorModel.editNew(selectIndx)
        }
    }
    CButton {
        id: addButton
        anchors.right: editButton.left
        anchors.rightMargin: 43
        anchors.bottom: deleteButton.bottom
//        anchors.bottomMargin: 40
        width: 300
        iconSource: "qrc:/images/images/Add.png"
        text: qsTr("Add New")
        textColor: "white"
        onClicked: {
            backGround.visible = true
            backGround.opacity = 0.5
            operatorDialog.visible = true
            setDialogLevel()
        }
    }
    Rectangle {
        id: backGround
        anchors.fill: parent
        visible: false
        color: "black"
        opacity: 0
        MouseArea {
            anchors.fill: parent
            onClicked: {

            }
        }
    }
    Image {
        id: operatorDialog
        property bool bIsEdit: false
        anchors.centerIn: parent
        anchors.verticalCenterOffset: -80
        width: 570
        height: 480
        visible: false
        source: "qrc:/images/images/dialogbg.png"
        onBIsEditChanged: {
            if (bIsEdit) {
                operatorNameInput.inputText = operatorModel.getOperatorValue(selectIndx,"name")
                passwordInput.inputText = operatorModel.getOperatorValue(selectIndx,"middle")
                var level = operatorModel.getOperatorValue(selectIndx,"count")
                if (level == administratorRadio.buttontext) {
                    administratorRadio.bIsCheck = true
                } else if (level == technicianRadio.buttontext) {
                    technicianRadio.bIsCheck = true
                } else if (level == qualityRadio.buttontext) {
                    qualityRadio.bIsCheck = true
                } else if (level == openRadio.buttontext) {
                    openRadio.bIsCheck = true
                }
            }
        }
        onVisibleChanged: {
            if(!bIsEdit && operatorDialog.visible){
                operatorNameInput.inputText = ""
                passwordInput.inputText = ""
                administratorRadio.bIsCheck = true
            }
        }

        Text {
            id: title
            anchors.top: parent.top
            anchors.topMargin: 10
            anchors.left: parent.left
            anchors.leftMargin: 20
            font.family: "arial"
            font.pixelSize: 24
            color: "white"
            text: qsTr("Add New Operator")
        }
        Text {
            id: operatorName
            anchors.top: title.bottom
            anchors.topMargin: 24
            anchors.right: title.right
            font.family: "arial"
            font.pixelSize: 24
            color: "white"
            text: qsTr("Operator Name")
        }
        MyLineEdit {
            id: operatorNameInput
            anchors.left: operatorName.right
            anchors.leftMargin: 10
            anchors.verticalCenter: operatorName.verticalCenter
            width: 300
            height: 40
            inputColor: "white"
            clip: true
            inputWidth: 290
            inputHeight: 36
            horizontalAlignment: Qt.AlignHCenter
        }
        Text {
            id: password
            anchors.top: operatorName.bottom
            anchors.topMargin: 24
            anchors.right: title.right
            font.family: "arial"
            font.pixelSize: 24
            color: "white"
            text: qsTr("Password")
        }
        MyLineEdit {
            id: passwordInput
            anchors.left: password.right
            anchors.leftMargin: 10
            anchors.verticalCenter: password.verticalCenter
            width: 300
            height: 40
            inputColor: "white"
            clip: true
            inputWidth: 290
            inputHeight: 36
            horizontalAlignment: Qt.AlignHCenter
        }
        Text {
            id: permission
            anchors.top: password.bottom
            anchors.topMargin: 24
            anchors.right: title.right
            font.family: "arial"
            font.pixelSize: 24
            color: "white"
            text: qsTr("Permission Level")
        }
        ExclusiveGroup {
            id: mos
        }

        MyRadioButton {
            id: administratorRadio
            anchors.left: permission.right
            anchors.leftMargin: 10
            anchors.verticalCenter: permission.verticalCenter
            width: 300
            height: 40
            bIsCheck: true
            exclusiveGroup: mos
            buttontext: fourLevelIdentifier[0]//qsTr("Administrator")
        }
        MyRadioButton {
            id: technicianRadio
            anchors.left: permission.right
            anchors.leftMargin: 10
            anchors.top: administratorRadio.bottom
            anchors.topMargin: 4
            width: 300
            height: 40
            exclusiveGroup: mos
            buttontext: fourLevelIdentifier[1]//qsTr("Technician")
        }
        MyRadioButton {
            id: qualityRadio
            anchors.left: permission.right
            anchors.leftMargin: 10
            anchors.top: technicianRadio.bottom
            anchors.topMargin: 4
            width: 300
            height: 40
            exclusiveGroup: mos
            buttontext: fourLevelIdentifier[2]//qsTr("Quality Control")
        }
        MyRadioButton {
            id: openRadio
            anchors.left: permission.right
            anchors.leftMargin: 10
            anchors.top: qualityRadio.bottom
            anchors.topMargin: 4
            width: 300
            height: 40
            exclusiveGroup: mos
            buttontext: fourLevelIdentifier[3]//qsTr("Open")
        }
        CButton {
            id: cancelButton
            anchors.top: openRadio.bottom
            anchors.topMargin: 24
            anchors.left: parent.left
            anchors.leftMargin: 20
            width: (parent.width-60)/2
            text: qsTr("Cancel")
            textColor: "white"
            iconSource: "qrc:/images/images/cancel.png"
            onClicked: {
                backGround.visible = false
                backGround.opacity = 0
                operatorDialog.visible = false
                operatorDialog.bIsEdit = false
            }
        }
        CButton {
            id: okButton
            anchors.top: openRadio.bottom
            anchors.topMargin: 24
            anchors.left: cancelButton.right
            anchors.leftMargin: 20
            width: (parent.width-60)/2
            text: qsTr("OK")
            iconSource: "qrc:/images/images/OK.png"
            textColor: "white"
            onClicked: {
                backGround.visible = false
                backGround.opacity = 0
                operatorDialog.visible = false
                var level = 0
                if (administratorRadio.bIsCheck) {
                    level = 1
                } else if (technicianRadio.bIsCheck) {
                    level = 2
                } else if (qualityRadio.bIsCheck) {
                    level = 3
                } else if (openRadio.bIsCheck) {
                    level = 4
                }
                if (operatorDialog.bIsEdit) {
                    operatorModel.updateOperator(operatorModel.getOperatorValue(selectIndx,"operatorId"),operatorNameInput.inputText,passwordInput.inputText,level)
                    operatorDialog.bIsEdit = false
                } else {
                    operatorModel.insertValue(operatorNameInput.inputText,passwordInput.inputText,level);
                }
            }
        }
    }
}
