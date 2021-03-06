import QtQuick 2.2
import QtQuick.Controls 1.1
import QtQuick.Controls.Styles 1.1
import QtQuick.Layouts 1.0
import QtQuick.Window 2.2

Item {
    id: weldDefault
    property var coolingList: ""
  	Component.onCompleted: {
        initPage()
    }
    function initPage()
    {
        repeaterModel.clear()
        coolingModel.clear()
        graphModel.clear()
        formulaModel.clear()
        widthModel.clear()
        pressureModel.clear()
        amplitudeModel.clear()
        repeaterModel.clear()
        repeaterModel2.clear()

        mos.current = null
        crossSectionRowMos.current = null
        pressureRowMos.current = null
        lengthRowMos.current = null

        crossRadio1.bIsCheck = hmiAdaptor.weldDefaultsGetValue2(1,0)
        crossRadio2.bIsCheck = hmiAdaptor.weldDefaultsGetValue2(1,1)
        pressRadio1.bIsCheck = hmiAdaptor.weldDefaultsGetValue2(0,0)
        pressRadio2.bIsCheck = hmiAdaptor.weldDefaultsGetValue2(0,1)
        lengthRadio1.bIsCheck = hmiAdaptor.weldDefaultsGetValue2(2,0)
        lengthRadio2.bIsCheck = hmiAdaptor.weldDefaultsGetValue2(2,1)

        repeaterModel.append({"headTitle":qsTr("Width Encoder"),"leftText":qsTr("OFF"),"righttext":qsTr("ON"),"switchState":hmiAdaptor.weldDefaultsGetSwitch("Width Encoder")})
        repeaterModel.append({"headTitle":qsTr("Height Encoder"),"leftText":qsTr("OFF"),"righttext":qsTr("ON"),"switchState":hmiAdaptor.weldDefaultsGetSwitch("Height Encoder")})
        repeaterModel2.append({"headTitle":qsTr("Foot Pedal Abort"),"leftText":qsTr("OFF"),"righttext":qsTr("ON"),"switchState":hmiAdaptor.weldDefaultsGetSwitch("Foot Pedal Abort")})
        repeaterModel2.append({"headTitle":qsTr("Seek"),"leftText":qsTr("OFF"),"righttext":qsTr("ON"),"switchState":hmiAdaptor.weldDefaultsGetSwitch("Seek")})
        repeaterModel2.append({"headTitle":qsTr("Cooling"),"leftText":qsTr("OFF"),"righttext":qsTr("ON"),"switchState":hmiAdaptor.weldDefaultsGetSwitch("Cooling")})
//        repeaterModel2.append({"headTitle":qsTr("Lock on Alarm"),"leftText":qsTr("OFF"),"righttext":qsTr("ON"),"switchState":hmiAdaptor.weldDefaultsGetSwitch("Cooling")})

        graphModel.append({"graphText":"1ms","isSelect":hmiAdaptor.weldDefaultsGetSwitch("Graph Data Sampling 1ms")})
        graphModel.append({"graphText":"5ms","isSelect":hmiAdaptor.weldDefaultsGetSwitch("Graph Data Sampling 5ms")})
        graphModel.append({"graphText":"10ms","isSelect":hmiAdaptor.weldDefaultsGetSwitch("Graph Data Sampling 10ms")})
        graphModel.append({"graphText":"20ms","isSelect":hmiAdaptor.weldDefaultsGetSwitch("Graph Data Sampling 20ms")})

        var list = new Array();
        list = hmiAdaptor.weldDefaultsGetValue(-1)
        coolingList = list
//        coolingModel.append({"formulaHead":"Range","maxValue":list[0],"currenValue":list[1],"minValue":list[2]})
//        coolingModel.append({"formulaHead":"Range","maxValue":list[3],"currenValue":list[4],"minValue":list[5]})

        list = hmiAdaptor.weldDefaultsGetValue(0)
        checkText.text = list[9]
        formulaModel.append({"formulaHead":qsTr("From"),"maxValue":list[0],"currenValue":list[1],"minValue":list[2],"identifier":list[9]})  //"formulaValue":"0.00mm²"
        formulaModel.append({"formulaHead":qsTr("To"),"maxValue":"","currenValue":list[2],"minValue":""})
        formulaModel.append({"formulaHead":qsTr("Offset"),"maxValue":list[3],"currenValue":list[4],"minValue":list[5]})
        formulaModel.append({"formulaHead":qsTr("Multiplier"),"maxValue":list[6],"currenValue":list[7],"minValue":list[8]})

        list = hmiAdaptor.weldDefaultsGetValue(1)
        formulaModel.append({"formulaHead":qsTr("From"),"maxValue":list[0],"currenValue":list[1],"minValue":list[2]})
        formulaModel.set(1,{"currenValue":hmiAdaptor.weldDefaultsGetNum(list[1])})
        formulaModel.append({"formulaHead":qsTr("To"),"maxValue":"","currenValue":list[1],"minValue":""})
        formulaModel.append({"formulaHead":qsTr("Offset"),"maxValue":list[3],"currenValue":list[4],"minValue":list[5]})
        formulaModel.append({"formulaHead":qsTr("Multiplier"),"maxValue":list[6],"currenValue":list[7],"minValue":list[8]})

        list = hmiAdaptor.weldDefaultsGetValue(2)
        formulaModel.append({"formulaHead":qsTr("From"),"maxValue":list[0],"currenValue":list[1],"minValue":list[2]})
        formulaModel.set(5,{"currenValue":hmiAdaptor.weldDefaultsGetNum(list[1])})
        formulaModel.append({"formulaHead":qsTr("To"),"maxValue":"","currenValue":list[0],"minValue":""})
        formulaModel.append({"formulaHead":qsTr("Offset"),"maxValue":list[3],"currenValue":list[4],"minValue":list[5]})
        formulaModel.append({"formulaHead":qsTr("Multiplier"),"maxValue":list[6],"currenValue":list[7],"minValue":list[8]})

        list = hmiAdaptor.weldDefaultsGetValue(3)
        formulaModel.append({"formulaHead":qsTr("From"),"maxValue":list[0],"currenValue":list[1],"minValue":list[2]})
        formulaModel.set(9,{"currenValue":hmiAdaptor.weldDefaultsGetNum(list[1])})
        formulaModel.append({"formulaHead":qsTr("To"),"maxValue":"","currenValue":list[0],"minValue":""})
        formulaModel.append({"formulaHead":qsTr("Offset"),"maxValue":list[3],"currenValue":list[4],"minValue":list[5]})
        formulaModel.append({"formulaHead":qsTr("Multiplier"),"maxValue":list[6],"currenValue":list[7],"minValue":list[8]})


        list = hmiAdaptor.weldDefaultsGetValue(4)
        widthModel.append({"formulaHead":qsTr("From"),"maxValue":list[0],"currenValue":list[1],"minValue":list[2],"identifier":list[9]})
        widthModel.append({"formulaHead":qsTr("To"),"maxValue":"","currenValue":list[2],"minValue":""})
        widthModel.append({"formulaHead":qsTr("Offset"),"maxValue":list[3],"currenValue":list[4],"minValue":list[5]})
        widthModel.append({"formulaHead":qsTr("Multiplier"),"maxValue":list[6],"currenValue":list[7],"minValue":list[8]})
        list = hmiAdaptor.weldDefaultsGetValue(5)
        widthModel.append({"formulaHead":qsTr("From"),"maxValue":list[0],"currenValue":list[1],"minValue":list[2]})
        widthModel.set(1,{"currenValue":hmiAdaptor.weldDefaultsGetNum(list[1])})
        widthModel.append({"formulaHead":qsTr("To"),"maxValue":"","currenValue":list[1],"minValue":""})
        widthModel.append({"formulaHead":qsTr("Offset"),"maxValue":list[3],"currenValue":list[4],"minValue":list[5]})
        widthModel.append({"formulaHead":qsTr("Multiplier"),"maxValue":list[6],"currenValue":list[7],"minValue":list[8]})
        list = hmiAdaptor.weldDefaultsGetValue(6)
        widthModel.append({"formulaHead":qsTr("From"),"maxValue":list[0],"currenValue":list[1],"minValue":list[2]})
        widthModel.set(5,{"currenValue":hmiAdaptor.weldDefaultsGetNum(list[1])})
        widthModel.append({"formulaHead":qsTr("To"),"maxValue":"","currenValue":list[0],"minValue":""})
        widthModel.append({"formulaHead":qsTr("Offset"),"maxValue":list[3],"currenValue":list[4],"minValue":list[5]})
        widthModel.append({"formulaHead":qsTr("Multiplier"),"maxValue":list[6],"currenValue":list[7],"minValue":list[8]})
        list = hmiAdaptor.weldDefaultsGetValue(7)
        widthModel.append({"formulaHead":qsTr("From"),"maxValue":list[0],"currenValue":list[1],"minValue":list[2]})
        widthModel.set(9,{"currenValue":hmiAdaptor.weldDefaultsGetNum(list[1])})
        widthModel.append({"formulaHead":qsTr("To"),"maxValue":"","currenValue":list[0],"minValue":""})
        widthModel.append({"formulaHead":qsTr("Offset"),"maxValue":list[3],"currenValue":list[4],"minValue":list[5]})
        widthModel.append({"formulaHead":qsTr("Multiplier"),"maxValue":list[6],"currenValue":list[7],"minValue":list[8]})



        list = hmiAdaptor.weldDefaultsGetValue(8)
        pressureModel.append({"formulaHead":qsTr("From"),"maxValue":list[0],"currenValue":list[1],"minValue":list[2],"identifier":list[9]})
        pressureModel.append({"formulaHead":qsTr("To"),"maxValue":"","currenValue":list[1],"minValue":""})
        pressureModel.append({"formulaHead":qsTr("Offset"),"maxValue":list[3],"currenValue":list[4],"minValue":list[5]})
        pressureModel.append({"formulaHead":qsTr("Multiplier"),"maxValue":list[6],"currenValue":list[7],"minValue":list[8]})
        list = hmiAdaptor.weldDefaultsGetValue(9)
        pressureModel.append({"formulaHead":qsTr("From"),"maxValue":list[0],"currenValue":list[1],"minValue":list[2]})
        pressureModel.set(1,{"currenValue":hmiAdaptor.weldDefaultsGetNum(list[1])})
        pressureModel.append({"formulaHead":qsTr("To"),"maxValue":"","currenValue":list[1],"minValue":""})
        pressureModel.append({"formulaHead":qsTr("Offset"),"maxValue":list[3],"currenValue":list[4],"minValue":list[5]})
        pressureModel.append({"formulaHead":qsTr("Multiplier"),"maxValue":list[6],"currenValue":list[7],"minValue":list[8]})
        list = hmiAdaptor.weldDefaultsGetValue(10)
        pressureModel.append({"formulaHead":qsTr("From"),"maxValue":list[0],"currenValue":list[1],"minValue":list[2]})
        pressureModel.set(5,{"currenValue":hmiAdaptor.weldDefaultsGetNum(list[1])})
        pressureModel.append({"formulaHead":qsTr("To"),"maxValue":"","currenValue":list[0],"minValue":""})
        pressureModel.append({"formulaHead":qsTr("Offset"),"maxValue":list[3],"currenValue":list[4],"minValue":list[5]})
        pressureModel.append({"formulaHead":qsTr("Multiplier"),"maxValue":list[6],"currenValue":list[7],"minValue":list[8]})
        list = hmiAdaptor.weldDefaultsGetValue(11)
        pressureModel.append({"formulaHead":qsTr("From"),"maxValue":list[0],"currenValue":list[1],"minValue":list[2]})
        pressureModel.set(9,{"currenValue":hmiAdaptor.weldDefaultsGetNum(list[1])})
        pressureModel.append({"formulaHead":qsTr("To"),"maxValue":"","currenValue":list[0],"minValue":""})
        pressureModel.append({"formulaHead":qsTr("Offset"),"maxValue":list[3],"currenValue":list[4],"minValue":list[5]})
        pressureModel.append({"formulaHead":qsTr("Multiplier"),"maxValue":list[6],"currenValue":list[7],"minValue":list[8]})


        list = hmiAdaptor.weldDefaultsGetValue(12)
        amplitudeModel.append({"formulaHead":qsTr("From"),"maxValue":list[0],"currenValue":list[1],"minValue":list[2],"identifier":list[9]})
        amplitudeModel.append({"formulaHead":qsTr("To"),"maxValue":"","currenValue":list[1],"minValue":""})
        amplitudeModel.append({"formulaHead":qsTr("Offset"),"maxValue":list[3],"currenValue":list[4],"minValue":list[5]})
        amplitudeModel.append({"formulaHead":qsTr("Multiplier"),"maxValue":list[6],"currenValue":list[7],"minValue":list[8]})
        list = hmiAdaptor.weldDefaultsGetValue(13)
        amplitudeModel.append({"formulaHead":qsTr("From"),"maxValue":list[0],"currenValue":list[1],"minValue":list[2]})
        amplitudeModel.set(1,{"currenValue":hmiAdaptor.weldDefaultsGetNum(list[1])})
        amplitudeModel.append({"formulaHead":qsTr("To"),"maxValue":"","currenValue":list[1],"minValue":""})
        amplitudeModel.append({"formulaHead":qsTr("Offset"),"maxValue":list[3],"currenValue":list[4],"minValue":list[5]})
        amplitudeModel.append({"formulaHead":qsTr("Multiplier"),"maxValue":list[6],"currenValue":list[7],"minValue":list[8]})
        list = hmiAdaptor.weldDefaultsGetValue(14)
        amplitudeModel.append({"formulaHead":qsTr("From"),"maxValue":list[0],"currenValue":list[1],"minValue":list[2]})
        amplitudeModel.set(5,{"currenValue":hmiAdaptor.weldDefaultsGetNum(list[1])})
        amplitudeModel.append({"formulaHead":qsTr("To"),"maxValue":"","currenValue":list[0],"minValue":""})
        amplitudeModel.append({"formulaHead":qsTr("Offset"),"maxValue":list[3],"currenValue":list[4],"minValue":list[5]})
        amplitudeModel.append({"formulaHead":qsTr("Multiplier"),"maxValue":list[6],"currenValue":list[7],"minValue":list[8]})
        list = hmiAdaptor.weldDefaultsGetValue(15)
        amplitudeModel.append({"formulaHead":qsTr("From"),"maxValue":list[0],"currenValue":list[1],"minValue":list[2]})
        amplitudeModel.set(9,{"currenValue":hmiAdaptor.weldDefaultsGetNum(list[1])})
        amplitudeModel.append({"formulaHead":qsTr("To"),"maxValue":"","currenValue":list[0],"minValue":""})
        amplitudeModel.append({"formulaHead":qsTr("Offset"),"maxValue":list[3],"currenValue":list[4],"minValue":list[5]})
        amplitudeModel.append({"formulaHead":qsTr("Multiplier"),"maxValue":list[6],"currenValue":list[7],"minValue":list[8]})

        cooling1.centervalue = hmiAdaptor.weldDefaultsGetValue(-1)[1]
        cooling2.centervalue = hmiAdaptor.weldDefaultsGetValue(-1)[4]
        coolingTooling.state = hmiAdaptor.weldDefaultsGetSwitch("Cooling Tooling") ? "right" : "left"
        coolingsec.state = hmiAdaptor.weldDefaultsGetSwitch("Cooling(1sec/100J)") ? "right" : "left"

        //        awg.state = hmiAdaptor.weldDefaultsGetSwitch("Unit Conversion") ? "right" : "left"

        loadValue2.inputText = hmiAdaptor.weldDefaultsGetCutterNum("Load Time","current")
        cutteronoroff.state = hmiAdaptor.weldDefaultsGetCutterNum("Cut Off","current")
        cutterModel.clear()
        cutterModel.append({"headText":qsTr("Time"),"switchState":hmiAdaptor.weldDefaultsGetCutterNum("Time","")})
        cutterModel.append({"headText":qsTr("Peak Power"),"switchState":hmiAdaptor.weldDefaultsGetCutterNum("Peak Power","")})
        cutterModel.append({"headText":qsTr("Pre-Height"),"switchState":hmiAdaptor.weldDefaultsGetCutterNum("Pre-Height","")})
        cutterModel.append({"headText":qsTr("Post-Height"),"switchState":hmiAdaptor.weldDefaultsGetCutterNum("Post-Height","")})
        onoroff.state = hmiAdaptor.weldDefaultsGetCutterNum("Anti-Side","current")
        loadValue.inputText = hmiAdaptor.weldDefaultsGetCutterNum("Unload Time","current")  //qsTr("0.00mm")
        lockOnAlarmSwitch.state = hmiAdaptor.weldDefaultsGetCutterNum("LockOnAlarm", "current")
    }

    function weldDefaultUpdate()
    {
        var stringArray = new Array();
        var i;
        for (i = 0;i < formulaModel.count;i++ )
        {
            if (i != 1 && i != 5 && i != 9 && i != 13)
                stringArray.push(formulaModel.get(i).currenValue)
        }
        for (i = 0;i < widthModel.count;i++ )
        {
            if (i != 1 && i != 5 && i != 9 && i != 13)
                stringArray.push(widthModel.get(i).currenValue)
        }
        for (i = 0;i < pressureModel.count;i++ )
        {
            if (i != 1 && i != 5 && i != 9 && i != 13)
                stringArray.push(pressureModel.get(i).currenValue)
        }
        for (i = 0;i < amplitudeModel.count;i++ )
        {
            if (i != 1 && i != 5 && i != 9 && i != 13)
                stringArray.push(amplitudeModel.get(i).currenValue)
        }
        hmiAdaptor.weldDefaultsSetValue3(stringArray)
        hmiAdaptor.weldDefaultFormulaUpdate()
        initPage()

    }

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
    }

    ListModel {
        id: repeaterModel2
    }

    ListModel {
        id: crossSectionDisplayModel
    }

    ListModel {
        id: pressureDisplayModel
    }

    ListModel {
        id: lengthDisplayModel
    }

    Row {
        id: column1
        anchors.top: parent.top
        anchors.topMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 20
        width: 700
        height: 50
        spacing: 10
        Repeater {
            id: columnRepeater
            model: repeaterModel
            delegate: Item {
                width: column1.width / 2
                height: 50
                Text {
                    anchors.verticalCenter: parent.verticalCenter
                    font.family: "arial"
                    font.pixelSize: 20
                    color: "white"
                    text: headTitle
                }
                Switch2 {
                    anchors.right: parent.right
                    anchors.verticalCenter: parent.verticalCenter
                    width: 150
                    textLeft: leftText
                    textRight: righttext
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
    Grid {
        id: column2
        anchors.top: column1.bottom
        anchors.topMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 20
        width: 350
        height: 110
        spacing: 10
        rows: 2
        columns: 2
        Repeater {
            id: columnRepeater2
            model: repeaterModel2
            delegate: Item {
                width: column2.width
                height: 50
                Text {
                    anchors.verticalCenter: parent.verticalCenter
                    font.family: "arial"
                    font.pixelSize: 20
                    color: "white"
                    text: headTitle
                }
                Switch2 {
                    anchors.right: parent.right
                    anchors.verticalCenter: parent.verticalCenter
                    width: 150
                    textLeft: leftText
                    textRight: righttext
                    state: switchState ? "right" : "left"
                    clip: true
                    onStateChanged: {
                        if (index == 2 && state == "left")
                            coolingItem.visible = false
                        else if (index == 2 && state == "right")
                            coolingItem.visible = true

                        if (state == "right")
                            repeaterModel2.set(index,{"switchState":true})
                        else
                            repeaterModel2.set(index,{"switchState":false})

                    }
                }
            }
        }
    }

    Item {
        id: coolingItem
        anchors.top: column2.bottom
        anchors.topMargin: 20
        anchors.left: parent.left
        anchors.leftMargin: 20
        width: 700
        height: 110
        onVisibleChanged: {
            if (visible)
            {
                coolingsec.state = hmiAdaptor.weldDefaultsGetSwitch("Cooling(1sec/100J)") ? "right" : "left"
                coolingTooling.state = hmiAdaptor.weldDefaultsGetSwitch("Cooling Tooling") ? "right" : "left"

            }
        }
        Item {
            id: item1
            width: 350
            height: 50
            Text {
                id: coolingsecText
                font.family: "arial"
                font.pixelSize: 20
                color: "white"
                text: qsTr("Cooling(1sec/100J)")
            }
            Switch2 {
                id: coolingsec
                anchors.right: parent.right
                anchors.verticalCenter: coolingsecText.verticalCenter
                width: 150
                height: 50
                textLeft: qsTr("OFF")
                textRight: qsTr("ON")
                state: hmiAdaptor.weldDefaultsGetSwitch("Cooling(1sec/100J)") ? "right" : "left"
                clip: true
                onStateChanged: {
                    if (coolingsec.state == "right")
                        cooling1.bgvisable = false
                    else if (coolingsec.state == "left")
                        cooling1.bgvisable = true
                }
            }
        }

        Item {
            id: item2
            width: 350
            height: 50
            anchors.bottom: parent.bottom
            Text {
                id: coolingToolingText
                font.family: "arial"
                font.pixelSize: 20
                color: "white"
                text: qsTr("Cooling Tooling")
            }
            Switch2 {
                id: coolingTooling
                anchors.right: parent.right
                anchors.verticalCenter: coolingToolingText.verticalCenter
                width: 150
                height: 50
                textLeft: qsTr("OFF")
                textRight: qsTr("ON")
                state: hmiAdaptor.weldDefaultsGetSwitch("Cooling Tooling") ? "right" : "left"
                clip: true
            }
        }

        Item {
            id: item3
            width: 350
            height: 50
            anchors.top: parent.top
            anchors.right: parent.right
            Text {
                id: durationTitle
                anchors.left: parent.left
                anchors.leftMargin: 10
                anchors.topMargin: 20
                font.family: "arial"
                font.pixelSize: 20
                color: "white"
                text: qsTr("Duration")
            }
            Recsetting {
                id: cooling1
                anchors.verticalCenter: durationTitle.verticalCenter
                anchors.right: parent.right
                width: 150
                height: 50
    //            headTitle: qsTr("Cooling Duration")
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
        }

        Item {
            id: item4
            width: 350
            height: 50
            anchors.bottom: parent.bottom
            anchors.right: parent.right
            Text {
                id: delayTitle
                anchors.left: parent.left
                anchors.leftMargin: 10
                anchors.topMargin: 20
                font.family: "arial"
                font.pixelSize: 20
                color: "white"
                text: qsTr("Delay")
            }
            Recsetting {
                id: cooling2
                anchors.verticalCenter: delayTitle.verticalCenter
                anchors.right: parent.right
                width: 150
                height: 50
                //            headTitle: qsTr("Cooling Delay")
                onMouseAreaClick: {
                    localbordercolor = "#05f91c"
                    keyNum.titleText = cooling2.headTitle
                    keyNum.maxvalue = coolingList[3]
                    keyNum.currentValue = coolingList[4]
                    keyNum.minvalue = coolingList[5]
                    keyNum.visible = true
                    backGround.visible = true
                }
            }
        }
    }
//    Text {
//        id: conversion
//        anchors.top: coolingItem.bottom
//        anchors.topMargin: 10
//        anchors.left: parent.left
//        anchors.leftMargin: 20
//        font.family: "arial"
//        font.pixelSize: 20
//        color: "white"
//        text: qsTr("Unit Conversion")
//    }
//    Text {
//        id: conversion2
//        anchors.top: conversion.bottom
//        anchors.left: parent.left
//        anchors.leftMargin: 20
//        font.family: "arial"
//        font.pixelSize: 16
//        color: "white"
//        text: qsTr("-AWG/mm²\n-Psi/Bar\n-Inch/mm")
//    }
//    Switch2 {
//        id: awg
//        anchors.right: coolingItem.right
//        anchors.top: conversion.bottom
//        width: (parent.width-40)/6+40
//        height: 50
//        textRight: qsTr("Imperial")
//        textLeft: qsTr("Metric")
//        state: hmiAdaptor.weldDefaultsGetSwitch("Unit Conversion") ? "right" : "left"
//        clip: true
//    }

    Text {
        id: graph
        anchors.top: coolingItem.bottom
        anchors.topMargin: 20
        anchors.left: parent.left
        anchors.leftMargin: 20
        font.family: "arial"
        font.pixelSize: 20
        color: "white"
        text: qsTr("Graph Data Sampling")
    }
    Row {
        id: graphRow
        anchors.top: graph.bottom
        anchors.left: parent.left
        anchors.leftMargin: 20
        width: 700 //(parent.width-40)/3
        height: 50
        spacing: 20
        Repeater {
            model: graphModel
            delegate: Item {
                width: 640/4 //parent.width/2-10
                height: 50 //parent.height/2-10
                MyRadioButton {
                    anchors.fill: parent
                    buttontext: graphText
                    bIsCheck: isSelect
                    exclusiveGroup: mos
                    onBIsCheckChanged: {
                        graphModel.set(index,{"isSelect":bIsCheck})
                    }
                }
            }
        }
    }

    Text {
        id: display
        text: qsTr("Display")
        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.top: graphRow.bottom
        anchors.topMargin: 40
        font.family: "arial"
        font.pixelSize: 20
        color: "white"
    }

    ExclusiveGroup {
        id: crossSectionRowMos;
    }
    Row {
        id: crossSectionRow
        anchors.top: display.bottom
        anchors.left: parent.left
        anchors.leftMargin: 20
        width: 700
        height: 50
        spacing: 20
        Text {
            color: "white"
            font.family: "arial"
            font.pointSize: 14
            text: qsTr("Cross Section")
            height: 50
            width: 640/4
            verticalAlignment: Qt.AlignVCenter
        }
        Item {
            width: 640/4
            height: 50
            MyRadioButton {
                id: crossRadio1
                anchors.fill: parent
                buttontext: "mm²"
                bIsCheck: hmiAdaptor.weldDefaultsGetValue2(1,0)
                exclusiveGroup: crossSectionRowMos
                onBIsCheckChanged: {
                    if (crossRadio1.bIsCheck)
                        hmiAdaptor.weldDefaultsSetValue2(1,1)
                }
            }
        }
        Item {
            width: 640/4
            height: 50
            MyRadioButton {
                id: crossRadio2
                anchors.fill: parent
                buttontext: "AWG"
                bIsCheck: hmiAdaptor.weldDefaultsGetValue2(1,1)
                exclusiveGroup: crossSectionRowMos
                onBIsCheckChanged: {
                    if (crossRadio2.bIsCheck)
                        hmiAdaptor.weldDefaultsSetValue2(1,0)
                }
            }
        }
    }

    ExclusiveGroup {
        id: pressureRowMos;
    }
    Row {
        id: pressureRow
        anchors.top: crossSectionRow.bottom
        anchors.topMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 20
        width: 700
        height: 50
        spacing: 20
        Text {
            color: "white"
            font.family: "arial"
            font.pointSize: 14
            text: qsTr("Pressure")
            height: 50
            width: 640/4
            verticalAlignment: Qt.AlignVCenter
        }
        Item {
            width: 640/4
            height: 50
            MyRadioButton {
                id: pressRadio1
                anchors.fill: parent
                buttontext: "psi"
                bIsCheck: hmiAdaptor.weldDefaultsGetValue2(0,0)
                exclusiveGroup: pressureRowMos
                onBIsCheckChanged: {
                    if (pressRadio1.bIsCheck)
                        hmiAdaptor.weldDefaultsSetValue2(0,0)
                }
            }
        }
        Item {
            width: 640/4
            height: 50
            MyRadioButton {
                id: pressRadio2
                anchors.fill: parent
                buttontext: "bar"
                bIsCheck: hmiAdaptor.weldDefaultsGetValue2(0,1)
                exclusiveGroup: pressureRowMos
                onBIsCheckChanged: {
                    if (pressRadio2.bIsCheck)
                        hmiAdaptor.weldDefaultsSetValue2(0,1)
                }
            }
        }
    }

    ExclusiveGroup {
        id: lengthRowMos;
    }
    Row {
        id: lengthRow
        anchors.top: pressureRow.bottom
        anchors.topMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 20
        width: 700
        height: 50
        spacing: 20
        Text {
            color: "white"
            font.family: "arial"
            font.pointSize: 14
            text: qsTr("Length")
            height: 50
            width: 640/4
            verticalAlignment: Qt.AlignVCenter
        }
        Item {
            width: 640/4
            height: 50
            MyRadioButton {
                id: lengthRadio1
                anchors.fill: parent
                buttontext: "mm"
                bIsCheck: hmiAdaptor.weldDefaultsGetValue2(2,0)
                exclusiveGroup: lengthRowMos
                onBIsCheckChanged: {
                    if (lengthRadio1.bIsCheck)
                        hmiAdaptor.weldDefaultsSetValue2(2,1)
                }
            }
        }
        Item {
            width: 640/4
            height: 50
            MyRadioButton {
                id: lengthRadio2
                anchors.fill: parent
                buttontext: "inch"
                bIsCheck: hmiAdaptor.weldDefaultsGetValue2(2,1)
                exclusiveGroup: lengthRowMos
                onBIsCheckChanged: {
                    if (lengthRadio2.bIsCheck)
                        hmiAdaptor.weldDefaultsSetValue2(2,0)
                }

            }
        }
    }


    CButton {
        width: okButton.width
        height: okButton.height
        anchors.right: column1.right
        anchors.bottom: okButton.bottom
        iconSource: "qrc:/images/images/arrowRight.png"
        onClicked: {
            itemCutter.visible = true
            headBar.selectsubIndex = 54
        }
    }
    Item {
        id: itemCutter
        height: parent.height
        anchors.left: parent.left
        anchors.right: middLine.left
        visible: false
        Image {
            anchors.fill: parent
            source: "qrc:/images/images/bg.png"
        }
        Text {
            id: loadName2
            anchors.top: cutterText.bottom
            anchors.topMargin: 10
            anchors.left: cutterText.left
            verticalAlignment: Qt.AlignVCenter
            font.pointSize: 16
            font.family: "arial"
            text: qsTr("Load")
            color: "white"
            clip: true
            visible: cutteronoroff.state == "left" ? true : false
        }
        MiniKeyNumInput {
            id: loadValue2
            visible: loadName2.visible
            anchors.verticalCenter: loadName2.verticalCenter
//            anchors.left: cutteronoroff.left
            anchors.right: cutterColumn.right
            width: 150
            height: cutteronoroff.height
            inputWidth: 150
            clip: true
            inputText: hmiAdaptor.weldDefaultsGetCutterNum("Load Time","current") //qsTr("0.00mm")
            onInputFocusChanged: {
                if (loadValue2.inputFocus) {
                    backGround.visible = true
                    backGround.opacity = 0.5
                    keyNum.visible = true
                    keyNum.titleText = loadName2.text
                    keyNum.currentValue = loadValue2.inputText
                    keyNum.minvalue = hmiAdaptor.weldDefaultsGetCutterNum("Load Time","min")
                    keyNum.maxvalue = hmiAdaptor.weldDefaultsGetCutterNum("Load Time","max")
                }
            }
        }

        Text {
            id: cutterText
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.leftMargin: 24
            anchors.topMargin: 10
            verticalAlignment: Qt.AlignVCenter
            text: qsTr("Cutter")
            color: "white"
            font.pointSize: 16
            font.family: "arial"
            height: parent.height * 0.1
        }

        Switch2 {
            id: cutteronoroff
//            anchors.left: cutterText.right
//            anchors.leftMargin: 50
            anchors.right: cutterColumn.right
            anchors.verticalCenter: cutterText.verticalCenter
            width: 150
            textLeft: qsTr("ON")
            textRight: qsTr("OFF")
            clip: true
            state: hmiAdaptor.weldDefaultsGetCutterNum("Cut Off","current")
            onStateChanged: {
                if (cutteronoroff.state == "left"){
                    cutterColumn.visible = true
                    loadName2.visible = true
                    loadValue2.visible = true
                    for (var i = 0; i < cutterModel.count; i++)
                    {
                        cutterModel.set(i,{"switchState":"left"})
                        cutterColumn.model = null
                        cutterColumn.model = cutterModel
                    }
                }
                else {
                    cutterColumn.visible = false
                    loadName2.visible = false
                    loadValue2.visible = false
                }
            }
        }

        ListModel {
            id: cutterModel
        }

        Column {
            id: cutterColumn
            anchors.top: loadName2.bottom
            anchors.topMargin: 20
            anchors.left: cutterText.left
            width: 350
            height: parent.height*0.46
            clip: true
            spacing: 10
            visible: cutteronoroff.state == "left" ? true : false
            property alias model: repeater1.model
            Repeater {
                id: repeater1
                model: cutterModel
                delegate: Item {
                    height: cutteronoroff.height //(cutterColumn.height-30)/4
                    width: parent.width
                    Text {
                        id: cutterColumnName
                        anchors.verticalCenter: parent.verticalCenter
                        verticalAlignment: Qt.AlignVCenter
                        anchors.left: parent.left
                        width: parent.width/3
                        font.pointSize: 16
                        font.family: "arial"
                        text: headText
                        color: "white"
                        clip: true
                    }
                    Switch2 {
                        id: columnOnoroff
                        anchors.verticalCenter: cutterColumnName.verticalCenter
                        anchors.right: parent.right
                        width: 150
                        textLeft: qsTr("ON")
                        textRight: qsTr("OFF")
                        state: switchState
                        clip: true
                        onStateChanged: {
                            cutterModel.set(index,{"switchState":columnOnoroff.state})
                        }
                    }
                }
            }
        }

        Text {
            id: lockOnAlarmName
            anchors.top: cutterColumn.visible ? cutterColumn.bottom : loadName2.bottom
            anchors.topMargin: 10
            anchors.left: cutterColumn.left
//                verticalAlignment: Qt.AlignVCenter
            font.pointSize: 16
            font.family: "arial"
            text: qsTr("Lock On Alarm")
            color: "white"
            clip: true
        }

        Switch2{
            id: lockOnAlarmSwitch
            anchors.verticalCenter: lockOnAlarmName.verticalCenter
            anchors.right: cutteronoroff.right
            width: 150
            textLeft: qsTr("ON")
            textRight: qsTr("OFF")
            state: hmiAdaptor.weldDefaultsGetCutterNum("LockOnAlarm","current")
            clip: true
//            onStateChanged: {
//                hmiAdaptor.weldDefaultsSetCutterNum("LockOnAlarm", lockOnAlarmSwitch.state)
//            }
        }


            Text {
                id: thirdSwitchName
                anchors.left: cutterColumn.right
                anchors.leftMargin: 24
                anchors.verticalCenter: cutterText.verticalCenter
                text: qsTr("Anti-Side")
                verticalAlignment: Qt.AlignVCenter
                color: "white"
                font.pointSize: 16
                font.family: "arial"
                height: parent.height * 0.1
            }
            Switch2 {
                id: onoroff
                anchors.verticalCenter: thirdSwitchName.verticalCenter
                anchors.left: thirdSwitchName.right
                anchors.leftMargin: 100
                width: 150
                textLeft: qsTr("ON")
                textRight: qsTr("OFF")
                state: hmiAdaptor.weldDefaultsGetCutterNum("Anti-Side","current")
                clip: true
                onStateChanged: {
//                    thirdSwitchModel.set(index,{"switchState":onoroff.state})
                    if (onoroff.state == "left"){
                        loadValue.visible = true
                        loadName.visible = true
                    }
                    else {
                        loadValue.visible = false
                        loadName.visible = false
                    }
                }
            }

            Text {
                id: loadName
                anchors.top: thirdSwitchName.bottom
                anchors.topMargin: 10
                anchors.left: thirdSwitchName.left
                verticalAlignment: Qt.AlignVCenter
                font.pointSize: 16
                font.family: "arial"
                text: qsTr("Unload")
                color: "white"
                clip: true
            }
            MiniKeyNumInput {
                id: loadValue
                anchors.verticalCenter: loadName.verticalCenter
                anchors.left: onoroff.left
                width: 150
                height: onoroff.height
                inputWidth: 150
                clip: true
                inputText: hmiAdaptor.weldDefaultsGetCutterNum("Unload Time","current")  //qsTr("0.00mm")
                onInputFocusChanged: {
                    if (loadValue.inputFocus) {
                        backGround.visible = true
                        backGround.opacity = 0.5
                        keyNum.visible = true
                        keyNum.titleText = loadName.text
                        keyNum.currentValue = loadValue.inputText
                        keyNum.minvalue = hmiAdaptor.weldDefaultsGetCutterNum("Unload Time","min")
                        keyNum.maxvalue = hmiAdaptor.weldDefaultsGetCutterNum("Unload Time","max")
                    }
                }
            }

        CButton {
            width: okButton.width
            height: okButton.height
            anchors.left: parent.left
            anchors.leftMargin: 20
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 16
            iconSource: "qrc:/images/images/arrowLeft.png"
            onClicked: {
                itemCutter.visible = false
                headBar.selectsubIndex = 51
            }
        }
    }

    Rectangle {
        id: middLine
        anchors.top: parent.top
        anchors.topMargin: 15
        anchors.bottomMargin: 15
        anchors.bottom: parent.bottom
        width: 2
        color: "white"
        anchors.left: column1.right
        anchors.leftMargin: 25
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
        color: "#F79428"
    }

    Grid {
        id: formulaSetting
        anchors.top: rec.bottom
//        anchors.topMargin: 20
        anchors.bottom: okButton.top
        anchors.bottomMargin: 20
        anchors.right: parent.right
        anchors.rightMargin: 20
        width: radioButton.width
        columns: 4
        rows: 4
        columnSpacing: 10
        rowSpacing: 10
        property alias myModel: gridRepeater.model
        property int selectIndex: -1
        Repeater {
            id: gridRepeater
            model: formulaModel
            delegate: Item {
                width: (radioButton.width-30)/4
                height: (formulaSetting.height-20)/4
                property alias localbordercolor: recset.localbordercolor
                Text {
                    id: gridTitle
                    text: formulaHead
                    height: 40
                    width: (radioButton.width-30)/4
                    color: "white"
                    font.family: "arial"
                    font.pointSize: 14
                    verticalAlignment: Qt.AlignBottom
                    anchors.left: parent.left
                    anchors.leftMargin: 5
                }
                Text {
                    id: lineTip
                    text: qsTr("Cross Section Range")
                    height: 40
                    width: (radioButton.width-30)/4
                    color: "white"
                    font.family: "arial"
                    font.pointSize: 14
                    verticalAlignment: Qt.AlignTop
                    visible: false
                }
                Recsetting {
                    id: recset
                    anchors.top: gridTitle.bottom
                    width: (radioButton.width-30)/4
                    height: (formulaSetting.height-20)/4 - 40
                    //                headTitle: formulaHead
                    centervalue: currenValue
                    Component.onCompleted: {
                        if (index == 1 || index == 5 || index == 9 || index == 13) {
                            localbordercolor = Qt.rgba(0,0,0,0)
                            bgvisable = false
                        }
                        if (index == 0 || index == 4 || index == 8 || index == 12) {
                            lineTip.visible = true
                            lineTip.text = qsTr("Cross Section Range ") + (index / 4 + 1)
                        }
                        if (index == 2 || index == 6 || index == 10 || index == 14) {
                            if (gridRepeater.model == widthModel)
                            {
                                localbordercolor = Qt.rgba(0,0,0,0)
                                bgvisable = false
                            }
                        }

                    }
                    onMouseAreaClick: {
                        if (index == 1 || index == 5 || index == 9 || index == 13) {
                            localbordercolor = Qt.rgba(0,0,0,0)
                            bgvisable = false
                            return
                        }
                        else if (index == 2 || index == 6 || index == 10 || index == 14) {
                            if (gridRepeater.model == widthModel)
                            {
                                localbordercolor = Qt.rgba(0,0,0,0)
                                bgvisable = false
                            }
                            return
                        }
                        else {
                            localbordercolor = "#05f91c"
                        }
                        formulaSetting.selectIndex = index
                        keyNum.titleText = gridRepeater.model.get(index).formulaHead
                        keyNum.maxvalue = gridRepeater.model.get(index).maxValue
                        keyNum.currentValue = gridRepeater.model.get(index).currenValue
                        keyNum.minvalue = gridRepeater.model.get(index).minValue
                        keyNum.visible = true
                        backGround.visible = true
                    }
                }
            }
        }
    }

    Row {
        id: radioButton
        anchors.top: centerTips.bottom
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
                    centerTips.myText = formulaModel.get(0).identifier
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
        anchors.top: formula.bottom
        anchors.left: formula.left
        anchors.right: parent.right
        anchors.rightMargin: 20
        height: 40
        border.color: Qt.rgba(0,0,0,0) //"#0079c1"
        border.width: 2
        color: Qt.rgba(0,0,0,0)
        property alias myText: checkText.text
        Text {
            id: checkText
            anchors.fill: parent
//            horizontalAlignment: Qt.AlignHCenter
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
            console.log(width,height)
            var i;
            var switchCount;
            var boolArray = new Array();
            var stringArray = new Array();
            var sampIndex = 0;
            for (i = 0;i < repeaterModel.count;i++ )
            {
                boolArray.push(repeaterModel.get(i).switchState)
            }
            for (i = 0;i < repeaterModel2.count;i++ )
            {
                boolArray.push(repeaterModel2.get(i).switchState)
            }
            boolArray.push(coolingsec.state == "right")
            boolArray.push(coolingTooling.state == "right")
//            boolArray.push(awg.state == "right")

            for (i = 0;i < formulaModel.count;i++ )
            {
                if (i != 1 && i != 5 && i != 9 && i != 13)
                    stringArray.push(formulaModel.get(i).currenValue)
            }
            for (i = 0;i < widthModel.count;i++ )
            {
                if (i != 1 && i != 5 && i != 9 && i != 13)
                    stringArray.push(widthModel.get(i).currenValue)
            }
            for (i = 0;i < pressureModel.count;i++ )
            {
                if (i != 1 && i != 5 && i != 9 && i != 13)
                    stringArray.push(pressureModel.get(i).currenValue)
            }
            for (i = 0;i < amplitudeModel.count;i++ )
            {
                if (i != 1 && i != 5 && i != 9 && i != 13)
                    stringArray.push(amplitudeModel.get(i).currenValue)
            }
            for (i = 0;i < graphModel.count;i++ )
            {
                if (graphModel.get(i).isSelect == true) {
                    sampIndex = i;
                    break;
                }
            }

            hmiAdaptor.weldDefaultsSetCutterNum("Load Time",loadValue2.inputText)
            hmiAdaptor.weldDefaultsSetCutterNum("Unload Time",loadValue.inputText)
            hmiAdaptor.weldDefaultsSetCutterNum("Cut Off",cutteronoroff.state)
            if (cutteronoroff.state == "left")
                mainRoot.cutterButtonVisible = true
            else
                mainRoot.cutterButtonVisible = false

            hmiAdaptor.weldDefaultsSetCutterNum("Anti-Side",onoroff.state)

            hmiAdaptor.weldDefaultsSetCutterNum("Time",cutterModel.get(0).switchState)
            hmiAdaptor.weldDefaultsSetCutterNum("Peak Power",cutterModel.get(1).switchState)
            hmiAdaptor.weldDefaultsSetCutterNum("Pre-Height",cutterModel.get(2).switchState)
            hmiAdaptor.weldDefaultsSetCutterNum("Post-Height",cutterModel.get(3).switchState)
            hmiAdaptor.weldDefaultsSetCutterNum("LockOnAlarm", lockOnAlarmSwitch.state)


            hmiAdaptor.weldDefaultsSetValue(boolArray, stringArray, sampIndex, cooling1.centervalue,cooling2.centervalue)
            hmiAdaptor.weldDefaultsExecute("_Set")
            hmiAdaptor.weldDefaultsExecute("_Recall")
            initPage()
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
        text: qsTr("Default Setting")
        textColor: "white"
        onClicked: {
            hmiAdaptor.weldDefaultsExecute("_Default")
            hmiAdaptor.weldDefaultsExecute("_Recall")
            for (var i = 0 ;i < graphModel.count; i++)
            {
                graphModel.set(i,{"isSelect":false})
            }
            initPage()
            if (cutteronoroff.state == "left")
                mainRoot.cutterButtonVisible = true
            else
                mainRoot.cutterButtonVisible = false
        }
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
        titleText: ""
        maxvalue: "12"
        minvalue: "3"
        currentValue: "123"

        onCurrentClickIndex: {
            if (index == 15) {
                if (hmiAdaptor.comepareCurrentValue(keyNum.minvalue,keyNum.maxvalue,keyNum.inputText)) {
                    var tempString
                    if (cooling1.myFocus) {
                        tempString = hmiAdaptor.dataProcessing("CoolDur", keyNum.inputText)
                        coolingList[1] = tempString
                        cooling1.centervalue = tempString

                        cooling1.localbordercolor = "#0079c1"
                        cooling1.myFocus = false
                    } else if (cooling2.myFocus) {
                        tempString = hmiAdaptor.dataProcessing("CoolDel", keyNum.inputText)
                        cooling2.centervalue = tempString
                        coolingList[4] = tempString
                        cooling2.localbordercolor = "#0079c1"
                        cooling2.myFocus = false
                    } else if (loadValue.inputFocus) {
                        tempString = hmiAdaptor.dataProcessing("UnLoad Time", keyNum.inputText)
                        loadValue.inputText = tempString
                        loadValue.inputFocus = false
                    } else if (loadValue2.inputFocus) {
                        tempString = hmiAdaptor.dataProcessing("Load Time", keyNum.inputText)
                        loadValue2.inputText = tempString
                        loadValue2.inputFocus = false
                    }
                    else {
                        var arr = [0,4,8,12,1,5,9,13];
                        var result = (formulaSetting.selectIndex in arr);
                        if (result)
                        {
                            tempString = hmiAdaptor.dataProcessing("FormulaArea", keyNum.inputText)
                        }
                        else
                        {
                            if (formulaSetting.selectIndex in [2,6,10,14])
                            {
                                if (gridRepeater.model == formulaModel)
                                    tempString = hmiAdaptor.dataProcessing("FormulaEnergyOffset", keyNum.inputText)
                                else if (gridRepeater.model == widthModel)
                                    tempString = hmiAdaptor.dataProcessing("FormulaWidthOffset", keyNum.inputText)
                                else if (gridRepeater.model == pressureModel)
                                    tempString = hmiAdaptor.dataProcessing("FormulaPressureOffset", keyNum.inputText)
                                else if (gridRepeater.model == amplitudeModel)
                                    tempString = hmiAdaptor.dataProcessing("FormulaAmplitudeOffset", keyNum.inputText)
                            }
                            else if (formulaSetting.selectIndex in [3,7,11,15])
                            {
                                if (gridRepeater.model == formulaModel)
                                    tempString = hmiAdaptor.dataProcessing("FormulaEnergyMult", keyNum.inputText)
                                else if (gridRepeater.model == widthModel)
                                    tempString = hmiAdaptor.dataProcessing("FormulaWidthMult", keyNum.inputText)
                                else if (gridRepeater.model == pressureModel)
                                    tempString = hmiAdaptor.dataProcessing("FormulaPressureMult", keyNum.inputText)
                                else if (gridRepeater.model == amplitudeModel)
                                    tempString = hmiAdaptor.dataProcessing("FormulaAmplitudeMult", keyNum.inputText)
                            }
                        }
                        gridRepeater.itemAt(formulaSetting.selectIndex).localbordercolor = "#0079c1"
                        gridRepeater.model.set(formulaSetting.selectIndex,{"currenValue":tempString})
                        weldDefaultUpdate()
                    }
                    backGround.visible = false
                    keyNum.visible = false
                    keyNum.inputText = ""
                    keyNum.tempValue = ""
                } else {
                    keyNum.timeRun = true
                }
            } else if (index == 11) {
                if (cooling1.myFocus) {
                    cooling1.localbordercolor = "#0079c1"
                    cooling1.myFocus = false
                } else if (cooling2.myFocus) {
                    cooling2.localbordercolor = "#0079c1"
                    cooling2.myFocus = false
                } else if (loadValue2.inputFocus) {
                    loadValue2.inputFocus = false
                }
                else if (loadValue.inputFocus) {
                    loadValue.inputFocus = false
                }
                else {
                    gridRepeater.itemAt(formulaSetting.selectIndex).localbordercolor = "#0079c1"
                }
                backGround.visible = false
                keyNum.visible = false
                keyNum.inputText = ""
                keyNum.tempValue = ""
            }
        }
//        onInputTextChanged: {
//            if (cooling1.myFocus) {
//                cooling1.centervalue = keyNum.inputText
//            }
//            else if (cooling2.myFocus) {
//                cooling2.centervalue = keyNum.inputText
//            }
//            else if (loadValue.inputFocus) {
//                loadValue.inputFocus = keyNum.inputText
//            }
//            else if (loadValue2.inputFocus) {
//                loadValue2.inputFocus = keyNum.inputText
//            }
//            else {
//                if (keyNum.inputText != "") {
//                    gridRepeater.model.set(formulaSetting.selectIndex,{"currenValue":keyNum.inputText})
//                    weldDefaultUpdate()
//                }
//            }
//        }
    }
}
