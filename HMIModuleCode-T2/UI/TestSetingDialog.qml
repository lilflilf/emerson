import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2

Item {
    width: parent.width
    height: parent.height
    signal signalAdvanceSettingStart()
    signal signalTestStart()

    function setData()
    {

    }

    Image {
        anchors.fill: parent
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
//            buttontext: qsTr("#of Splices")
            exclusiveGroup: mos
        }
        Rectangle {
            id: lineEdit
            anchors.left: samplesize.right
            anchors.leftMargin: 78
            anchors.top: unButton.bottom
            anchors.topMargin: 12
            height: 45
            width: 140
            color: "black"
            TextInput {
                id: input
                anchors.fill: parent
                horizontalAlignment: Qt.AlignHCenter
                verticalAlignment: Qt.AlignVCenter
                color: "white"
                text: qsTr("")
                clip: true
                font.pixelSize: 24
                font.family: "arial"
                onFocusChanged: {
                    if (input.focus) {
                        splices.bIsCheck = true
                    }
                }

                Text {
                    id: defalut
                    anchors.fill: parent
                    font.pixelSize: 24
                    font.family: "arial"
                    horizontalAlignment: Qt.AlignHCenter
                    verticalAlignment: Qt.AlignVCenter
                    color: "white"
                    text: qsTr("#of Splices")
                    visible: input.text.length > 0 ? false : true
                }
            }
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
            anchors.right: parent.right
            anchors.rightMargin: 10
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
                signalAdvanceSettingStart()
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
                signalTestStart()
            }
        }
    }
}
