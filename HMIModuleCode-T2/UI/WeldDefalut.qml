import QtQuick 2.7
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.0
import QtQuick.Window 2.2

Item {
    width: parent.width
    height: parent.height
    Image {
        anchors.fill: parent
        source: "qrc:/images/images/bg.png"
    }
    ExclusiveGroup {
        id: mos;
    }
    ExclusiveGroup {
        id: mos2;
    }
    ListModel {
        id: graphModel
    }
    ListModel {
        id: formulaModel
    }
    ListModel {
        id: repeaterModel
        Component.onCompleted: {
            repeaterModel.append({"headTitle":"Width Encoder","leftText":"off","righttext":"on"})
            repeaterModel.append({"headTitle":"Height Encoder","leftText":"off","righttext":"on"})
            repeaterModel.append({"headTitle":"Foot Pedal Abort","leftText":"off","righttext":"on"})
            repeaterModel.append({"headTitle":"Cooling","leftText":"Cooling","righttext":"cooling(100j/s)"})
            graphModel.append({"graphText":"1MS"})
            graphModel.append({"graphText":"5MS"})
            graphModel.append({"graphText":"10MS"})
            graphModel.append({"graphText":"20MS"})
            formulaModel.append({"formulaHead":"Range","formulaValue":"0.00mm²"})
            formulaModel.append({"formulaHead":"","formulaValue":"to 6.99"})
            formulaModel.append({"formulaHead":"Offset","formulaValue":"17.00J"})
            formulaModel.append({"formulaHead":"Multiplier","formulaValue":"88.00J"})
            formulaModel.append({"formulaHead":"Range","formulaValue":"7.00mm²"})
            formulaModel.append({"formulaHead":"","formulaValue":"to 14.99"})
            formulaModel.append({"formulaHead":"Offset","formulaValue":"18.70J"})
            formulaModel.append({"formulaHead":"Multiplier","formulaValue":"97.80J"})
            formulaModel.append({"formulaHead":"Range","formulaValue":"15.00mm²"})
            formulaModel.append({"formulaHead":"","formulaValue":"to 40.00"})
            formulaModel.append({"formulaHead":"Offset","formulaValue":"20.57J"})
            formulaModel.append({"formulaHead":"Multiplier","formulaValue":"106.48J"})
        }
    }

    Column {
        id: column1
        anchors.top: parent.top
        anchors.topMargin: 20
        anchors.left: parent.left
        anchors.leftMargin: 20
        width: (parent.width-40)/3
        height: 230
        spacing: 10
        Repeater {
            id: columnRepeater
            model: repeaterModel
            delegate: Item {
                width: column1.width
                height: 50
                Text {
                    anchors.verticalCenter: parent.verticalCenter
                    font.family: "arial"
                    font.pixelSize: 20
                    color: "white"
                    text: qsTr(headTitle)
                }
                Switch2 {
                    anchors.right: parent.right
                    anchors.verticalCenter: parent.verticalCenter
                    width: parent.width/2+40
                    height: parent.height
                    textLeft: qsTr(leftText)
                    textRight: qsTr(righttext)
                    state: "right"
                    clip: true
                }
            }
        }
    }
    Recsetting {
        id: cooling1
        anchors.top: column1.bottom
        anchors.topMargin: 20
        anchors.left: parent.left
        anchors.leftMargin: 20
        width: (parent.width-40)/6-10
        height: 100
        headTitle: qsTr("Cooling Duration")
        centervalue: qsTr("100s")
    }
    Recsetting {
        id: cooling2
        anchors.top: column1.bottom
        anchors.topMargin: 20
        anchors.left: cooling1.right
        anchors.leftMargin: 20
        width: (parent.width-40)/6-10
        height: 100
        headTitle: qsTr("Cooling Delay")
        centervalue: qsTr("100s")
    }
    Text {
        id: conversion
        anchors.top: cooling1.bottom
        anchors.topMargin: 20
        anchors.left: parent.left
        anchors.leftMargin: 20
        font.family: "arial"
        font.pixelSize: 20
        color: "white"
        text: qsTr("Unit Conversion")
    }
    Text {
        id: conversion2
        anchors.top: conversion.bottom
        anchors.left: parent.left
        anchors.leftMargin: 20
        font.family: "arial"
        font.pixelSize: 16
        color: "white"
        text: qsTr("-Cross Section\n-Psi/Bar\n-Inch/mm²")
    }
    Switch2 {
        id: awg
        anchors.right: cooling2.right
        anchors.top: conversion.bottom
        width: (parent.width-40)/6+40
        height: 50
        textLeft: qsTr("Imperical")
        textRight: qsTr("Metric")
        state: "right"
        clip: true
    }
    Text {
        id: graph
        anchors.top: conversion2.bottom
        anchors.topMargin: 20
        anchors.left: parent.left
        anchors.leftMargin: 20
        font.family: "arial"
        font.pixelSize: 20
        color: "white"
        text: qsTr("Graph Data Sampling")
    }
    Grid {
        anchors.top: graph.bottom
        anchors.left: parent.left
        anchors.leftMargin: 20
        width: (parent.width-40)/3
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 20
        spacing: 20
        columns: 2
        rows: 2
        Repeater {
            model: graphModel
            delegate: Item {
                width: parent.width/2-10
                height: parent.height/2-10
                MyRadioButton {
                    anchors.fill: parent
                    buttontext: qsTr(graphText)
                    bIsCheck: index == 0 ? true : false
                    exclusiveGroup: mos
                }
            }
        }
    }
    Text {
        id: formula
        anchors.left: column1.right
        anchors.leftMargin: 50
        anchors.top: parent.top
        anchors.topMargin: 20
        width: 200
        height: 50
        verticalAlignment: Qt.AlignVCenter
        font.family: "arial"
        font.pixelSize: 20
        color: "white"
        text: qsTr("Formula")
    }
    Row {
        id: radioButton
        anchors.top: formula.bottom
        anchors.topMargin: 10
        anchors.left: formula.left
        anchors.right: parent.right
        anchors.rightMargin: 20
        height: 50
        spacing: 10
        MyRadioButton {
            anchors.verticalCenter: parent.verticalCenter
            width: (radioButton.width-30)/4
            buttontext: qsTr("Energy")
            bIsCheck: true
            exclusiveGroup: mos2
            onBIsCheckChanged: {
                if (bIsCheck) {
                    rec.anchors.leftMargin = 0
                }
            }
        }
        MyRadioButton {
            anchors.verticalCenter: parent.verticalCenter
            width: (radioButton.width-30)/4
            buttontext: qsTr("Width")
            exclusiveGroup: mos2
            onBIsCheckChanged: {
                if (bIsCheck) {
                    rec.anchors.leftMargin = (radioButton.width-30)/4+10
                }
            }
        }
        MyRadioButton {
            anchors.verticalCenter: parent.verticalCenter
            width: (radioButton.width-30)/4
            buttontext: qsTr("Pressure")
            exclusiveGroup: mos2
            onBIsCheckChanged: {
                if (bIsCheck) {
                    rec.anchors.leftMargin = (radioButton.width-30)/2+20
                }
            }
        }
        MyRadioButton {
            anchors.verticalCenter: parent.verticalCenter
            width: (radioButton.width-30)/4
            buttontext: qsTr("Amplitude")
            exclusiveGroup: mos2
            onBIsCheckChanged: {
                if (bIsCheck) {
                    rec.anchors.leftMargin = (radioButton.width+10)/4*3
                }
            }
        }
    }
    Rectangle{
        id: rec
        anchors.top: radioButton.bottom
        anchors.left: formula.left
        width: (radioButton.width-30)/4
        height: 10
        color: "#0079c1"
    }
    Rectangle {
        id: centerTips
        anchors.top: rec.bottom
        anchors.left: formula.left
        anchors.right: parent.right
        anchors.rightMargin: 20
        height: 40
        border.color: "#0079c1"
        border.width: 2
        color: Qt.rgba(0,0,0,0)
        Text {
            anchors.fill: parent
            horizontalAlignment: Qt.AlignHCenter
            verticalAlignment: Qt.AlignVCenter
            font.family: "arial"
            font.pixelSize: 20
            color: "white"
            text: qsTr("Offset+(Area*Multiplier)")
        }
    }
    Grid {
        id: formulaSetting
        anchors.top: centerTips.bottom
        anchors.bottom: okButton.top
        anchors.bottomMargin: 20
        anchors.right: parent.right
        anchors.rightMargin: 20
        width: radioButton.width
        columns: 4
        rows: 3
        spacing: 10
        Repeater {
            model: formulaModel
            delegate: Recsetting {
                width: (radioButton.width-30)/4
                height: (formulaSetting.height-20)/3
                headTitle: qsTr(formulaHead)
                centervalue: qsTr(formulaValue)
            }
        }
    }
    CButton {
        id: okButton
        anchors.right: parent.right
        anchors.rightMargin: 20
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 16
        width: (radioButton.width-40)/3
        height: 70
        text: qsTr("OK")
        iconSource: "qrc:/images/images/OK.png"
        textColor: "white"
    }
    CButton {
        id: cancelButton
        anchors.right: okButton.left
        anchors.rightMargin: 20
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 16
        width: (radioButton.width-40)/3
        height: 70
        text: qsTr("Cancel")
        textColor: "white"
        iconSource: "qrc:/images/images/cancel.png"
        onClicked: {
        }
    }
    CButton {
        id: initialButton
        anchors.right: cancelButton.left
        anchors.rightMargin: 20
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 16
        width: (radioButton.width-40)/3
        height: 70
        text: qsTr("Defalut Setting")
        textColor: "white"
    }
}
