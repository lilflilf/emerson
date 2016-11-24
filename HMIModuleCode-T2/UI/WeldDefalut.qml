import QtQuick 2.7
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.0
import QtQuick.Window 2.2

Item {
    property var coolingList: ""
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
        id: coolingModel
    }
    ListModel {
        id: graphModel
    }
    ListModel {
        id: formulaModel
    }
    ListModel {
        id: widthModel
    }
    ListModel {
        id: pressureModel
    }
    ListModel {
        id: amplitudeModel
    }

    ListModel {
        id: repeaterModel
        Component.onCompleted: {
            repeaterModel.append({"headTitle":"Width Encoder","leftText":"off","righttext":"on","switchState":hmiAdaptor.weldDefaultsGetSwitch("Width Encoder")})
            repeaterModel.append({"headTitle":"Height Encoder","leftText":"off","righttext":"on","switchState":hmiAdaptor.weldDefaultsGetSwitch("Height Encoder")})
            repeaterModel.append({"headTitle":"Foot Pedal Abort","leftText":"off","righttext":"on","switchState":hmiAdaptor.weldDefaultsGetSwitch("Foot Pedal Abort")})
            repeaterModel.append({"headTitle":"Cooling","leftText":"off","righttext":"on","switchState":hmiAdaptor.weldDefaultsGetSwitch("Cooling")})

            graphModel.append({"graphText":"1MS","isSelect":hmiAdaptor.weldDefaultsGetSwitch("Graph Data Sampling 1ms")})
            graphModel.append({"graphText":"5MS","isSelect":hmiAdaptor.weldDefaultsGetSwitch("Graph Data Sampling 5ms")})
            graphModel.append({"graphText":"10MS","isSelect":hmiAdaptor.weldDefaultsGetSwitch("Graph Data Sampling 10ms")})
            graphModel.append({"graphText":"20MS","isSelect":hmiAdaptor.weldDefaultsGetSwitch("Graph Data Sampling 20ms")})

            var list = new Array();
            list = hmiAdaptor.weldDefaultsGetValue(-1)
            coolingList = list;
            //            coolingModel.append({"formulaHead":"Range","maxValue":list[0],"currenValue":list[1],"minValue":list[2]})
            //            coolingModel.append({"formulaHead":"Range","maxValue":list[3],"currenValue":list[4],"minValue":list[5]})

            list = hmiAdaptor.weldDefaultsGetValue(0)
            checkText.text = list[9]
            formulaModel.append({"formulaHead":"Range","maxValue":list[0],"currenValue":list[1],"minValue":list[2],"identifier":list[9]})  //"formulaValue":"0.00mm²"
            formulaModel.append({"formulaHead":"","maxValue":"","currenValue":list[1],"minValue":""})
            formulaModel.append({"formulaHead":"Offset","maxValue":list[3],"currenValue":list[4],"minValue":list[5]})
            formulaModel.append({"formulaHead":"Multiplier","maxValue":list[6],"currenValue":list[7],"minValue":list[8]})

            list = hmiAdaptor.weldDefaultsGetValue(1)
            formulaModel.append({"formulaHead":"Range","maxValue":list[0],"currenValue":list[1],"minValue":list[2]})  //"formulaValue":"0.00mm²"
            formulaModel.append({"formulaHead":"","maxValue":"","currenValue":list[1],"minValue":""})
            formulaModel.append({"formulaHead":"Offset","maxValue":list[3],"currenValue":list[4],"minValue":list[5]})
            formulaModel.append({"formulaHead":"Multiplier","maxValue":list[6],"currenValue":list[7],"minValue":list[8]})

            list = hmiAdaptor.weldDefaultsGetValue(2)
            formulaModel.append({"formulaHead":"Range","maxValue":list[0],"currenValue":list[1],"minValue":list[2]})  //"formulaValue":"0.00mm²"
            formulaModel.append({"formulaHead":"","maxValue":"","currenValue":list[1],"minValue":""})
            formulaModel.append({"formulaHead":"Offset","maxValue":list[3],"currenValue":list[4],"minValue":list[5]})
            formulaModel.append({"formulaHead":"Multiplier","maxValue":list[6],"currenValue":list[7],"minValue":list[8]})

            list = hmiAdaptor.weldDefaultsGetValue(3)
            widthModel.append({"formulaHead":"Range","maxValue":list[0],"currenValue":list[1],"minValue":list[2],"identifier":list[9]})  //"formulaValue":"0.00mm²"
            widthModel.append({"formulaHead":"","maxValue":"","currenValue":list[1],"minValue":""})
            widthModel.append({"formulaHead":"Offset","maxValue":list[3],"currenValue":list[4],"minValue":list[5]})
            widthModel.append({"formulaHead":"Multiplier","maxValue":list[6],"currenValue":list[7],"minValue":list[8]})
            list = hmiAdaptor.weldDefaultsGetValue(4)
            widthModel.append({"formulaHead":"Range","maxValue":list[0],"currenValue":list[1],"minValue":list[2]})  //"formulaValue":"0.00mm²"
            widthModel.append({"formulaHead":"","maxValue":"","currenValue":list[1],"minValue":""})
            widthModel.append({"formulaHead":"Offset","maxValue":list[3],"currenValue":list[4],"minValue":list[5]})
            widthModel.append({"formulaHead":"Multiplier","maxValue":list[6],"currenValue":list[7],"minValue":list[8]})
            list = hmiAdaptor.weldDefaultsGetValue(5)
            widthModel.append({"formulaHead":"Range","maxValue":list[0],"currenValue":list[1],"minValue":list[2]})  //"formulaValue":"0.00mm²"
            widthModel.append({"formulaHead":"","maxValue":"","currenValue":list[1],"minValue":""})
            widthModel.append({"formulaHead":"Offset","maxValue":list[3],"currenValue":list[4],"minValue":list[5]})
            widthModel.append({"formulaHead":"Multiplier","maxValue":list[6],"currenValue":list[7],"minValue":list[8]})

            list = hmiAdaptor.weldDefaultsGetValue(6)
            pressureModel.append({"formulaHead":"Range","maxValue":list[0],"currenValue":list[1],"minValue":list[2],"identifier":list[9]})  //"formulaValue":"0.00mm²"
            pressureModel.append({"formulaHead":"","maxValue":"","currenValue":list[1],"minValue":""})
            pressureModel.append({"formulaHead":"Offset","maxValue":list[3],"currenValue":list[4],"minValue":list[5]})
            pressureModel.append({"formulaHead":"Multiplier","maxValue":list[6],"currenValue":list[7],"minValue":list[8]})
            list = hmiAdaptor.weldDefaultsGetValue(7)
            pressureModel.append({"formulaHead":"Range","maxValue":list[0],"currenValue":list[1],"minValue":list[2]})  //"formulaValue":"0.00mm²"
            pressureModel.append({"formulaHead":"","maxValue":"","currenValue":list[1],"minValue":""})
            pressureModel.append({"formulaHead":"Offset","maxValue":list[3],"currenValue":list[4],"minValue":list[5]})
            pressureModel.append({"formulaHead":"Multiplier","maxValue":list[6],"currenValue":list[7],"minValue":list[8]})
            list = hmiAdaptor.weldDefaultsGetValue(8)
            pressureModel.append({"formulaHead":"Range","maxValue":list[0],"currenValue":list[1],"minValue":list[2]})  //"formulaValue":"0.00mm²"
            pressureModel.append({"formulaHead":"","maxValue":"","currenValue":list[1],"minValue":""})
            pressureModel.append({"formulaHead":"Offset","maxValue":list[3],"currenValue":list[4],"minValue":list[5]})
            pressureModel.append({"formulaHead":"Multiplier","maxValue":list[6],"currenValue":list[7],"minValue":list[8]})

            list = hmiAdaptor.weldDefaultsGetValue(9)
            amplitudeModel.append({"formulaHead":"Range","maxValue":list[0],"currenValue":list[1],"minValue":list[2],"identifier":list[9]})  //"formulaValue":"0.00mm²"
            amplitudeModel.append({"formulaHead":"","maxValue":"","currenValue":list[1],"minValue":""})
            amplitudeModel.append({"formulaHead":"Offset","maxValue":list[3],"currenValue":list[4],"minValue":list[5]})
            amplitudeModel.append({"formulaHead":"Multiplier","maxValue":list[6],"currenValue":list[7],"minValue":list[8]})
            list = hmiAdaptor.weldDefaultsGetValue(10)
            amplitudeModel.append({"formulaHead":"Range","maxValue":list[0],"currenValue":list[1],"minValue":list[2]})  //"formulaValue":"0.00mm²"
            amplitudeModel.append({"formulaHead":"","maxValue":"","currenValue":list[1],"minValue":""})
            amplitudeModel.append({"formulaHead":"Offset","maxValue":list[3],"currenValue":list[4],"minValue":list[5]})
            amplitudeModel.append({"formulaHead":"Multiplier","maxValue":list[6],"currenValue":list[7],"minValue":list[8]})
            list = hmiAdaptor.weldDefaultsGetValue(11)
            amplitudeModel.append({"formulaHead":"Range","maxValue":list[0],"currenValue":list[1],"minValue":list[2]})  //"formulaValue":"0.00mm²"
            amplitudeModel.append({"formulaHead":"","maxValue":"","currenValue":list[1],"minValue":""})
            amplitudeModel.append({"formulaHead":"Offset","maxValue":list[3],"currenValue":list[4],"minValue":list[5]})
            amplitudeModel.append({"formulaHead":"Multiplier","maxValue":list[6],"currenValue":list[7],"minValue":list[8]})

        }
    }

    Column {
        id: column1
        anchors.top: parent.top
        anchors.topMargin: 10
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
                    textLeft: qsTr(leftText)
                    textRight: qsTr(righttext)
                    state: switchState ? "right" : "left"
                    clip: true
                    onStateChanged: {
                        if (index == 3 && state == "left")
                            coolingItem.visible = false
                        else if (index == 3 && state == "right")
                            coolingItem.visible = true

                        if (state == "right")
                            repeaterModel.set(index,{"switchState":true})
                        else
                            repeaterModel.set(index,{"switchState":false})

                    }
                }
            }
        }
    }
    Item {
        id: coolingItem
        anchors.top: column1.bottom
        anchors.topMargin: 20
        anchors.left: parent.left
        anchors.leftMargin: 20
        width: (parent.width-40)/3
        height: 180
        onVisibleChanged: {
            if (visible)
            {
                coolingsec.state = hmiAdaptor.weldDefaultsGetSwitch("cooling(1sec/100J)") ? "right" : "left"
                coolingTooling.state = hmiAdaptor.weldDefaultsGetSwitch("Cooling Tooling") ? "right" : "left"

            }
        }

        Text {
            id: coolingsecText
            font.family: "arial"
            font.pixelSize: 20
            color: "white"
            text: qsTr("cooling(1sec/100J)")
        }
        Switch2 {
            id: coolingsec
            anchors.right: parent.right
            anchors.verticalCenter: coolingsecText.verticalCenter
            width: 200
            height: 50
            textLeft: qsTr("off")
            textRight: qsTr("on")
            state: hmiAdaptor.weldDefaultsGetSwitch("cooling(1sec/100J)") ? "right" : "left"
            clip: true
            onStateChanged: {
                if (coolingsec.state == "right")
                    cooling1.bgvisable = false
                else if (coolingsec.state == "left")
                    cooling1.bgvisable = true
            }
        }
        Text {
            id: coolingToolingText
            anchors.top: coolingsec.bottom
            anchors.topMargin: 20
            font.family: "arial"
            font.pixelSize: 20
            color: "white"
            text: qsTr("Cooling Tooling")
        }
        Switch2 {
            id: coolingTooling
            anchors.right: parent.right
            anchors.verticalCenter: coolingToolingText.verticalCenter
            width: 200
            height: 50
            textLeft: qsTr("off")
            textRight: qsTr("on")
            state: hmiAdaptor.weldDefaultsGetSwitch("Cooling Tooling") ? "right" : "left"
            clip: true
        }
        //        Row {
        //            anchors.top: coolingTooling.bottom
        //            anchors.topMargin: 10
        //            anchors.left: parent.left
        //            anchors.leftMargin: 20
        //            spacing: 20
        //            Repeater {
        //                model: coolingModel
        //                delegate: Recsetting {
        //                    width: (coolingItem.width-40)/2 //(parent.width-40)/2
        //                    height: 80
        //                    headTitle: formulaHead //qsTr("Cooling Duration")
        //                    centervalue: currenValue //qsTr("100s")
        //                }
        //            }
        //        }

        Recsetting {
            id: cooling1
            anchors.top: coolingTooling.bottom
            anchors.topMargin: 10
            anchors.left: parent.left
            anchors.leftMargin: 20
            width: (parent.width-40)/2
            height: 80
            headTitle: qsTr("Cooling Duration")
            centervalue: coolingList[1] //hmiAdaptor.weldDefaultsGetValue(-1)[1] //qsTr("100s")
            onMouseAreaClick: {
                if (cooling1.bgvisable) {
                    localbordercolor = "#05f91c"
                    keyNum.titleText = cooling1.headTitle
                    keyNum.maxvalue = coolingList[0] //hmiAdaptor.weldDefaultsGetValue(-1)[0]
                    keyNum.currentValue = coolingList[1] //hmiAdaptor.weldDefaultsGetValue(-1)[1]
                    keyNum.minvalue = coolingList[2] //hmiAdaptor.weldDefaultsGetValue(-1)[2]
                    keyNum.visible = true
                    backGround.visible = true
                }
            }
        }
        Recsetting {
            id: cooling2
            anchors.top: coolingTooling.bottom
            anchors.topMargin: 10
            anchors.right: parent.right
            width: (parent.width-40)/2
            height: 80
            headTitle: qsTr("Cooling Delay")
            centervalue: coolingList[4] //hmiAdaptor.weldDefaultsGetValue(-1)[4] //qsTr("100s")
            onMouseAreaClick: {
                localbordercolor = "#05f91c"
                keyNum.titleText = cooling1.headTitle
                keyNum.maxvalue = coolingList[3]
                keyNum.currentValue = coolingList[4]
                keyNum.minvalue = coolingList[5]
                keyNum.visible = true
                backGround.visible = true
            }
        }
    }
    Text {
        id: conversion
        anchors.top: coolingItem.bottom
        anchors.topMargin: 10
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
        text: qsTr("-AWG/mm²\n-Psi/Bar\n-Inch/mm")
    }
    Switch2 {
        id: awg
        anchors.right: coolingItem.right
        anchors.top: conversion.bottom
        width: (parent.width-40)/6+40
        height: 50
        textRight: qsTr("Imperical")
        textLeft: qsTr("Metric")
        state: hmiAdaptor.weldDefaultsGetSwitch("Unit Conversion") ? "right" : "left"
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
                    bIsCheck: isSelect //index == 0 ? true : false
                    exclusiveGroup: mos
                    onBIsCheckChanged: {
                        graphModel.set(index,{"isSelect":bIsCheck})
                    }
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

    Rectangle{
        id: rec
        anchors.top: radioButton.bottom
        anchors.left: formula.left
        width: (radioButton.width-30)/4
        height: 6
        color: "#F79428"  //"#0079c1"
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
        property alias myModel: gridRepeater.model
        property int selectIndex: -1
        Repeater {
            id: gridRepeater
            model: formulaModel
            delegate: Recsetting {
                width: (radioButton.width-30)/4
                height: (formulaSetting.height-20)/3
                headTitle: qsTr(formulaHead)
                centervalue: qsTr(currenValue)
                Component.onCompleted: {
                    if (index == 1 || index == 5 || index == 9) {
                        localbordercolor = Qt.rgba(0,0,0,0)
                        bgvisable = false
                    }
                }
                onMouseAreaClick: {
                    if (index == 1 || index == 5 || index == 9) {
                        localbordercolor = Qt.rgba(0,0,0,0)
                        bgvisable = false
                    } else {
                        localbordercolor = "#05f91c"
                    }
                    formulaSetting.selectIndex = index
                    keyNum.titleText = formulaModel.get(index).formulaHead
                    keyNum.maxvalue = formulaModel.get(index).maxValue
                    keyNum.currentValue = formulaModel.get(index).currenValue
                    keyNum.minvalue = formulaModel.get(index).minValue
                    keyNum.visible = true
                    backGround.visible = true
                }
            }
        }
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
            id: radio1
            anchors.verticalCenter: parent.verticalCenter
            width: (radioButton.width-30)/4
            buttontext: qsTr("Energy")
            bIsCheck: true
            exclusiveGroup: mos2
            onBIsCheckChanged: {
                if (radio1.bIsCheck) {
                    rec.anchors.leftMargin = 0
                    formulaSetting.myModel = formulaModel
                    //                    checkText.text = formulaModel.get(0).identifier
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
                    formulaSetting.myModel = widthModel
                    centerTips.myText = widthModel.get(0).identifier

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
                    formulaSetting.myModel = pressureModel
                    centerTips.myText = pressureModel.get(0).identifier
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
                    formulaSetting.myModel = amplitudeModel
                    centerTips.myText = amplitudeModel.get(0).identifier
                }
            }
        }
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
        property alias myText: checkText.text
        Text {
            id: checkText
            anchors.fill: parent
            horizontalAlignment: Qt.AlignHCenter
            verticalAlignment: Qt.AlignVCenter
            font.family: "arial"
            font.pixelSize: 20
            color: "white"
            text: qsTr("Offset+(Area*Multiplier)")
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
        onClicked: {
            var i;
            var switchCount;
            var boolArray = new Array();
            var stringArray = new Array();
            var sampIndex = 0;
            for (i = 0;i < repeaterModel.count;i++ )
            {
                boolArray.push(repeaterModel.get(i).switchState)
            }
            boolArray.push(coolingsec.state == "right")
            boolArray.push(coolingTooling.state == "right")
            boolArray.push(awg.state == "right")

            for (i = 0;i < formulaModel.count;i++ )
            {
                if (i != 1 && i != 5 && i != 9)
                    stringArray.push(formulaModel.get(i).currenValue)
            }
            for (i = 0;i < widthModel.count;i++ )
            {
                if (i != 1 && i != 5 && i != 9)
                    stringArray.push(widthModel.get(i).currenValue)
            }
            for (i = 0;i < pressureModel.count;i++ )
            {
                if (i != 1 && i != 5 && i != 9)
                    stringArray.push(pressureModel.get(i).currenValue)
            }
            for (i = 0;i < amplitudeModel.count;i++ )
            {
                if (i != 1 && i != 5 && i != 9)
                    stringArray.push(amplitudeModel.get(i).currenValue)
            }
            for (i = 0;i < graphModel.count;i++ )
            {
                if (graphModel.get(i).isSelect == true) {
                    sampIndex = i;
                    break;
                }
            }

            hmiAdaptor.weldDefaultsSetValue(boolArray, stringArray, sampIndex, cooling1.centervalue,cooling2.centervalue)
            hmiAdaptor.weldDefaultsExecute("_Set")
        }
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
    Rectangle {
        id: backGround
        anchors.fill: parent
        color: "black"
        opacity: 0.7
        visible: false
        MouseArea {
            anchors.fill: parent
            onClicked: {

            }
        }
    }
    KeyBoardNum {
        id: keyNum
        anchors.centerIn: parent
        width: 962
        height: 526
        visible: false
        titleText: qsTr("")
        maxvalue: "12"
        minvalue: "3"
        currentValue: "123"
        onCurrentClickIndex: {
            if (index == 15) {
                if (hmiAdaptor.comepareCurrentValue(keyNum.minvalue,keyNum.maxvalue,keyNum.currentValue)) {
                    if (cooling1.myFocus) {
                        coolingList[1] = keyNum.inputText
                        cooling1.localbordercolor = "#0079c1"
                        cooling1.myFocus = false
                    } else if (cooling2.myFocus) {
                        coolingList[4] = keyNum.inputText
                        cooling2.localbordercolor = "#0079c1"
                        cooling2.myFocus = false
                    } else {
                        gridRepeater.itemAt(formulaSetting.selectIndex).localbordercolor = "#0079c1"
                        formulaModel.set(formulaSetting.selectIndex,{"currenValue":keyNum.inputText})
                    }
                    backGround.visible = false
                    keyNum.visible = false
                    keyNum.inputText = ""
                    keyNum.tempValue = ""
                }
            } else if (index == 11) {
                backGround.visible = false
                keyNum.visible = false
                keyNum.inputText = ""
                keyNum.tempValue = ""
            }
        }
        onInputTextChanged: {
            if (cooling1.myFocus) {
                cooling1.centervalue = keyNum.inputText
            } else if (cooling2.myFocus) {
                cooling2.centervalue = keyNum.inputText
            } else {
                if (keyNum.inputText != "") {
                    formulaModel.set(formulaSetting.selectIndex,{"currenValue":keyNum.inputText})
                }
            }
        }
    }
}
