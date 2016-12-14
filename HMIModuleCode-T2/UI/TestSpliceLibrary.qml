import QtQuick 2.7
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.0
import QtQuick.Window 2.2

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
        onLoaded: {
            if (loader.source == "qrc:/UI/TestDetail.qml")
                loader.item.selectSplice(spliceModel.getValue(selectIndx,"SpliceId"))
        }
    }
    Connections {
        target: loader.item
        onSignalCancel: {
            loader.source = ""
        }
        onSignalAdvanceOk: {
            loader.source = ""
            testDialog.visible = true
        }
        onSignalSaveSplice: {
            loader.source = ""
        }
    }
    Row {
        id: headTitle
        anchors.left: parent.left
        anchors.leftMargin: 52
        anchors.top: parent.top
        anchors.topMargin: 30
        anchors.right: parent.right
        anchors.rightMargin: 52
        height: 50
        spacing: 40
        Text {
            anchors.verticalCenter: parent.verticalCenter
            verticalAlignment: Qt.AlignVCenter
            width: (parent.width-120)/4
            color: "white"
            font.pixelSize: 25
            font.family: "arial"
            clip: true
            elide: Text.ElideRight
            text: qsTr("SPLICE NAME")
        }
        Text {
            anchors.verticalCenter: parent.verticalCenter
            verticalAlignment: Qt.AlignVCenter
            width: (parent.width-120)/4
            color: "white"
            font.pixelSize: 25
            font.family: "arial"
            clip: true
            elide: Text.ElideRight
            text: qsTr("DATE CREATED")
        }
        Text {
            anchors.verticalCenter: parent.verticalCenter
            verticalAlignment: Qt.AlignVCenter
            width: (parent.width-120)/4
            color: "white"
            font.pixelSize: 25
            font.family: "arial"
            clip: true
            elide: Text.ElideRight
            text: qsTr("#OF WIRES")
        }
        Text {
            anchors.verticalCenter: parent.verticalCenter
            verticalAlignment: Qt.AlignVCenter
            width: (parent.width-120)/4
            color: "white"
            font.pixelSize: 25
            font.family: "arial"
            clip: true
            elide: Text.ElideRight
            text: qsTr("QLIANTITY")
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
        model: spliceModel
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
    //        list << "SpliceId" << "SpliceName" << "DateCreated" << "OperatorName" << "CrossSection" << "TotalWires" << "Verified" << "WeldMode" << "Energy" << "Amplitude"
    //             << "Width" << "TriggerPressure" << "WeldPressure" << "Time+" << "Time-" << "Power+" << "Power-" << "Pre-Height+" << "Pre-Height-" << "Height+" << "Height-" << "count";
    Component {
        id: listDelegate
        Item {
            width: listView.width
            height: 50
            Text {
                id: headName
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                verticalAlignment: Qt.AlignVCenter
                width: (parent.width-120)/4
                elide: Text.ElideRight
                text: SpliceName
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
                verticalAlignment: Qt.AlignVCenter
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
                verticalAlignment: Qt.AlignVCenter
                width: (parent.width-120)/4
                text: TotalWires
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
                verticalAlignment: Qt.AlignVCenter
                width: (parent.width-120)/4
                text: count
                elide: Text.ElideRight
                color: "white"
                clip: true
                font.pixelSize: 20
                font.family: "arial"
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    if (selectIndx == -1) {
                        //listModel.set(index,{"opacityValue":"0.3"})
                        selectIndx = index
                    } else {
                        //listModel.set(selectIndx,{"opacityValue":"0"})
                        selectIndx = index
                        //listModel.set(index,{"opacityValue":"0.3"})
                    }
                    selectCheck.checked = !selectCheck.checked

                }
            }
            Rectangle {
                id: backGround
                anchors.fill: parent
                color: "black"
                opacity: 0 //opacityValue
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
        anchors.bottom: okButton.top
        anchors.bottomMargin: 24
        anchors.left: parent.left
        anchors.leftMargin: 20
        width: parent.width - 40
        clip: true
        height: 1
        color: "#0d0f11"
    }
    CButton {
        id: okButton
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 20
        anchors.right: parent.right
        anchors.rightMargin: 20
        width: 300
        pixelSize: 25
        iconSource: "qrc:/images/images/OK.png"
        text: qsTr("OK")
        textColor: "white"
        onClicked: {
            if(selectIndx == -1)
                return
            backGround.visible = true
            backGround.opacity = 0.5
            testDialog.visible = true
        }
    }
    Rectangle {
        id: backGround
        anchors.fill: parent
        opacity: 0
        color: "black"
        visible: false
        MouseArea {
            anchors.fill: parent
        }
    }
    TestSetingDialog {
        id: testDialog
        visible: false
        anchors.centerIn: parent
        width: 435
        height: 540
        onSignalAdvanceSettingStart: {
            loader.source = "qrc:/UI/AdvanceSetting.qml"
        }
        onSignalTestStart: {
            testDialog.visible = false
            backGround.visible = false
            loader.source = "qrc:/UI/TestDetail.qml"

        }
    }
}
