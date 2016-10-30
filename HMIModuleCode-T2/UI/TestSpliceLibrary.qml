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
    }
    Connections {
        target: loader.item
        onSignalCancel: {
            loader.source = ""
        }
        onSignalAdvanceOk: {
            loader.source = ""
        }
        onSignalSaveSplice: {
            loader.source = ""
        }
    }

    ListModel {
        id: listModel
        Component.onCompleted: {
            listModel.append({"name":"work order id1","date":"2016/10/13","middle":"part65487911111111111111111111111111111111","count":"1adasd","opacityValue":"0"})
            listModel.append({"name":"work order id2","date":"2016/10/13","middle":"part654879","count":"sdsd","opacityValue":"0"})
            listModel.append({"name":"work order id3","date":"2016/10/13","middle":"part654879","count":"asdad","opacityValue":"0"})
            listModel.append({"name":"work order id4","date":"2016/10/13","middle":"part654879","count":"asdsa","opacityValue":"0"})
            listModel.append({"name":"work order id5","date":"2016/10/13","middle":"part65487911","count":"10","opacityValue":"0"})
            listModel.append({"name":"work order id5","date":"2016/10/13","middle":"part6548791","count":"10","opacityValue":"0"})
            listModel.append({"name":"work order id5","date":"2016/10/13","middle":"part6548","count":"100111","opacityValue":"0"})
            listModel.append({"name":"work order id5","date":"2016/10/13","middle":"123","count":"123","opacityValue":"0"})
            listModel.append({"name":"work order id5","date":"2016/10/13","middle":"123","count":"123","opacityValue":"0"})
            listModel.append({"name":"work order id5","date":"2016/10/13","middle":"213","count":"213","opacityValue":"0"})
            listModel.append({"name":"work order id5","date":"2016/10/13","middle":"123","count":"123","opacityValue":"0"})
            listModel.append({"name":"work order id5","date":"2016/10/13","middle":"123","count":"123","opacityValue":"0"})
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
        text: qsTr("SPLICE NAME")
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
        text: qsTr("#OF WIRES")
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
                anchors.leftMargin: 24
                width: (parent.width-96)/4-24
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
        anchors.bottomMargin: 35
        anchors.right: parent.right
        anchors.rightMargin: 20
        height: 79
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
            testparameters.visible = true
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
    Image {
        id: testparameters
        anchors.centerIn: parent
        width: 435
        height: 540
        visible: false
        source: "qrc:/images/images/dialogbg.png"
        Text {
            id: testTitle
            anchors.top: parent.top
            anchors.topMargin: 14
            anchors.left: parent.left
            anchors.leftMargin: 14
            text: qsTr("Test Parameters")
            color: "white"
            font.pixelSize: 24
            font.family: "arial"
            clip: true
        }
        Text {
            id: samplesize
            anchors.top: testTitle.bottom
            anchors.topMargin: 46
            anchors.left: parent.left
            anchors.leftMargin: 14
            text: qsTr("Sample Size")
            color: "white"
            font.pixelSize: 20
            font.family: "arial"
            clip: true
        }
        ExclusiveGroup {
            id: mos
        }
        MyRadioButton {
            id: unButton
            anchors.left: samplesize.right
            anchors.leftMargin: 24
            anchors.top: testTitle.bottom
            anchors.topMargin: 32
            height: 57
            width: 217
            clip: true
            buttontext: qsTr("Unconstrained")
            exclusiveGroup: mos
            bIsCheck: true
        }
        MyRadioButton {
            id: splices
            anchors.left: samplesize.right
            anchors.leftMargin: 24
            anchors.top: unButton.bottom
            anchors.topMargin: 7
            height: 57
            width: 217
            clip: true
            buttontext: qsTr("#of Splices")
            exclusiveGroup: mos
            bIsCheck: false
        }
        Text {
            id: teachMode
            anchors.left: parent.left
            anchors.leftMargin: 14
            anchors.verticalCenter: diagram.verticalCenter
            color: "white"
            font.pixelSize: 20
            font.family: "arial"
            clip: true
            text: qsTr("Teach Mode")
        }
        Switch2 {
            id: diagram
            anchors.top: splices.bottom
            anchors.topMargin: 7
            anchors.left: teachMode.right
            anchors.leftMargin: 24
            backgroundwidth: 200
            backgroundheight: 47
            textLeft: qsTr("OFF")
            textRight: qsTr("ON")
            state: "left"
        }
        ExclusiveGroup {
            id: mos2
        }
        MyRadioButton {
            id: standard
            anchors.left: teachMode.right
            anchors.leftMargin: 24
            anchors.top: diagram.bottom
            anchors.topMargin: 7
            height: 57
            width: 217
            visible: diagram.on
            clip: true
            buttontext: qsTr("Standard")
            exclusiveGroup: mos2
            bIsCheck: true
        }
        MyRadioButton {
            id: auto
            anchors.left: teachMode.right
            anchors.leftMargin: 24
            anchors.top: standard.bottom
            anchors.topMargin: 7
            height: 57
            width: 217
            clip: true
            visible: diagram.on
            buttontext: qsTr("Auto")
            exclusiveGroup: mos2
            bIsCheck: false
        }
        MyRadioButton {
            id: sigma
            anchors.left: teachMode.right
            anchors.leftMargin: 24
            anchors.top: auto.bottom
            anchors.topMargin: 7
            height: 57
            width: 217
            clip: true
            visible: diagram.on
            buttontext: qsTr("Sigma")
            exclusiveGroup: mos2
            bIsCheck: false
        }
        CButton {
            id: advanceSet
            anchors.top: sigma.bottom
            anchors.topMargin: 7
            anchors.left: parent.left
            anchors.leftMargin: 14
            width: 210
            height: 60
            text: qsTr("Advanced Setting")
            textColor: "white"
            onClicked: {
                backGround.visible = false
                backGround.opacity = 0
                testparameters.visible = false
                loader.source = ""
                loader.source = "qrc:/UI/AdvanceSetting.qml"
            }
        }
        CButton {
            id: start
            anchors.top: sigma.bottom
            anchors.topMargin: 7
            anchors.left: advanceSet.right
            anchors.leftMargin: 15
            width: 180
            height: 60
            text: qsTr("Start")
            textColor: "white"
            onClicked: {
                backGround.visible = false
                backGround.opacity = 0
                testparameters.visible = false
                loader.source = "qrc:/UI/TestDetail.qml"
            }
        }
    }
}
