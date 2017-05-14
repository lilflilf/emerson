import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import QtQuick.Dialogs 1.2

Item {
    id: operate
    property int selectIndx: -1
    property int selectWorkId: -1
    property int setCheckIndex: -1

    Image {
        anchors.fill: parent
        source: "qrc:/images/images/bg.png"
    }
    ExclusiveGroup {
        id: listviewPositionGroup;
    }
    Component.onCompleted: {
        if (mainRoot.headTitle == "Operate Sequence"){
            listView.model = sequenceModel
        }
        else if (mainRoot.headTitle == "Operate Harness"){
            listView.model = partModel
            nameText.text = qsTr("HARNESS NAME")
        }
    }

    Row {
        id: headTitle
        anchors.top: parent.top
        anchors.topMargin: 30
        anchors.left: parent.left
        anchors.leftMargin: 52
        anchors.right: parent.right
        anchors.rightMargin: 52
        spacing: 40
        height: 40
        Text {
            id: nameText
            anchors.verticalCenter: parent.verticalCenter
            color: "white"
            width: (parent.width-120)/4
            font.pixelSize: 25
            clip: true
            font.family: "arial"
            text: qsTr("SEQUENCE NAME")
        }
        Text {
            anchors.verticalCenter: parent.verticalCenter
            color: "white"
            width: (parent.width-120)/4
            font.pixelSize: 25
            clip: true
            font.family: "arial"
            text: qsTr("DATE CREATED")
        }
        Text {
            anchors.verticalCenter: parent.verticalCenter
            color: "white"
            width: (parent.width-120)/4
            font.pixelSize: 25
            clip: true
            font.family: "arial"
            text: qsTr("#OF STEPS")
        }
        Text {
            anchors.verticalCenter: parent.verticalCenter
            color: "white"
            width: (parent.width-120)/4
            font.pixelSize: 25
            clip: true
            font.family: "arial"
            text: qsTr("QUANTITY")
        }
    }
    Rectangle {
        id: tipsRec
        anchors.top: headTitle.bottom
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
        anchors.leftMargin: 52
        anchors.bottom: bottomTip.top
        width: parent.width - 104
        clip: true
        model: sequenceModel
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
                width: (parent.width-120)/4
                elide: Text.ElideRight
                text: listView.model == sequenceModel ? SequenceName : HarnessName
                clip: true
                color: "white"
                font.pixelSize: 20
                font.family: "arial"
            }
            Text {
                id: headData
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: headName.right
                anchors.leftMargin: 40
                width: (parent.width-120)/4
                text: DateCreated
                clip: true
                color: "white"
                font.pixelSize: 20
                font.family: "arial"
            }
            Text {
                id: headMiddle
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: headData.right
                anchors.leftMargin: 40
                width: (parent.width-120)/4
                text: TotalSplices
                elide: Text.ElideRight
                clip: true
                color: "white"
                font.pixelSize: 20
                font.family: "arial"
            }
            Text {
                id: headCount
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: headMiddle.right
                anchors.leftMargin: 40
                width: (parent.width-120)/4
                text: listView.model == sequenceModel ? QUANTITY : ""
                elide: Text.ElideRight
                color: "white"
                clip: true
                font.pixelSize: 20
                font.family: "arial"
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    operate.selectIndx = index
                    if (listView.model == sequenceModel)
                        operate.selectWorkId = SequenceId
                    else if (listView.model == partModel )
                        operate.selectWorkId = PartId
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
        anchors.bottom: selectOk.top
        anchors.bottomMargin: 24
        anchors.left: parent.left
        anchors.leftMargin: 20
        width: parent.width - 40
        clip: true
        height: 1
        color: "#0d0f11"
    }
    CButton {
        id: selectOk
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        anchors.right: parent.right
        anchors.rightMargin: 20
        width: (parent.width-100)/5
        spacing: 10
        iconSource: "qrc:/images/images/OK.png"
        text: qsTr("OK")
        pointSize: 20
        clip: true
        textColor: "white"
        onClicked: {

            if (listView.model == sequenceModel)
            {
                hmiAdaptor.setWorkFlow(1,operate.selectWorkId)
                mainRoot.checkNeedPassWd(-5)
                if (listView.model == sequenceModel)
                    mainRoot.headTitle = qsTr("Operate Sequence")
                else
                    mainRoot.headTitle = qsTr("Operate Harness")
            }
            else if (listView.model == partModel )
            {
                harnessSetting.visible = true
//                hmiAdaptor.setWorkFlow(2,operate.selectWorkId)
            }




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

    Item {
        id: harnessSetting
        visible: false
        width: 540
        height: 435
        anchors.centerIn: parent
        Image {
            anchors.fill: parent
            source: "qrc:/images/images/dialogbg.png"
        }

        Text {
            id: settingTitle
            text: qsTr("HarnessName:")
            color: "white"
            font.pointSize: 20
            font.family: "arial"
            anchors.top: parent.top
            anchors.topMargin: 46
            anchors.left: parent.left
            anchors.leftMargin: 24
        }
        Text {
            id: batchSize
            anchors.top: settingTitle.bottom
            anchors.topMargin: 46
            anchors.right: settingTitle.right
            text: qsTr("Batch Size")
            color: "white"
            font.pointSize: 20
            font.family: "arial"
            clip: true
        }
        Text {
            id: settingName
            anchors.top: settingTitle.top
            anchors.left: settingTitle.right
            anchors.leftMargin: 50
            text: qsTr("Batch Size")
            color: "white"
            font.pointSize: 20
            font.family: "arial"
            clip: true
        }

        ExclusiveGroup {
            id: mos
        }

        MyRadioButton {
            id: splices
            anchors.left: batchSize.right
            anchors.leftMargin: 14
            anchors.top: batchSize.top
            height: 57
            width: 217
            clip: true
            exclusiveGroup: mos
            bIsCheck: true

        }
        MyRadioButton {
            id: unButton
            anchors.left: batchSize.right
            anchors.leftMargin: 14
            anchors.top: splices.bottom
            height: 57
            width: 217
            clip: true
            buttontext: qsTr("Unconstrained")
            exclusiveGroup: mos
        }
        Image {
            id: lineEdit
            anchors.left: batchSize.right
            anchors.leftMargin: 78
            anchors.top: splices.top
            anchors.topMargin: 6

            height: 45
            width: 140
            source: "qrc:/images/images/advancesetting-bg1.png"
            Rectangle {
                id: backGroundd
                width: parent.width
                height: parent.height-2
                border.color: "#0079c1"
                border.width: 2
                color: Qt.rgba(0,0,0,0)
            }
            Text {
                id: defalut
                anchors.fill: parent
                font.pixelSize: 24
                font.family: "arial"
                horizontalAlignment: Qt.AlignHCenter
                verticalAlignment: Qt.AlignVCenter
                color: "white"
                text: qsTr("1")
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    keyNum.visible = true
                    keyNum.currentValue = defalut.text
                    keyNum.maxvalue = 80
                    keyNum.minvalue = 0
                }
                onPressed: {
                    splices.bIsCheck = true
                }
            }
        }

        Row {
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 20
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: 14
            CButton {
                id: advanceSet
                width: 210
                height: 60
                text: qsTr("CANCEL")
                textColor: "white"
                onClicked: {
                    harnessSetting.visible = false
                }
            }
            CButton {
                id: start
                width: 210
                height: 60
                text: qsTr("START")
                textColor: "white"
                onClicked: {
                    harnessSetting.visible = false
                    hmiAdaptor.setWorkFlow(2,operate.selectWorkId)

                    if (splices.bIsCheck)
                    {
                        if (defalut.text.length > 0) {
                            hmiAdaptor.setWorkValue("WorkCount",defalut.text)
                        }
                        else
                            return
                    }
                    else if (unButton.bIsCheck)
                    {
                        hmiAdaptor.setWorkValue("WorkCount","-1")
                    }

                    mainRoot.checkNeedPassWd(-5)
                    mainRoot.headTitle = qsTr("Operate Harness")
                }
            }
        }


    }

    KeyBoardNum {
        id: keyNum
        anchors.centerIn: parent
        width: 962
        height: 526
        visible: false
        titleText: ""
        maxvalue: "4"
        minvalue: "1"
        currentValue: "4"
        onCurrentClickIndex: {
            if (index == 15) {
                if (hmiAdaptor.comepareCurrentValue(keyNum.minvalue,keyNum.maxvalue,keyNum.inputText)) {
                    if (keyNum.inputText != "") {
                        defalut.text = keyNum.inputText
                    }
//                    defalut.text = keyNum.inputText
                    keyNum.visible = false
                    keyNum.inputText = ""
                    keyNum.tempValue = ""
                } else {
                    keyNum.timeRun = true
                }
            } else if (index == 11) {
                keyNum.visible = false
                keyNum.inputText = ""
                keyNum.tempValue = ""
            }
        }
        onInputTextChanged: {
            if (keyNum.inputText != "") {
                defalut.text = keyNum.inputText
            }
        }
    }

}
