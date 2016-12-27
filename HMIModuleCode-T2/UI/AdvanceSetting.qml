/*******************************************************************
Copyright:http://www.sinux.com.cn
Date:2016/12/26
Author:zhangjiyong&lilongfei
Description:Testing interface AdvanceSetting interface,data from the
standardUpperModel,standardLowerModel,sigmaUpperModel,sigmaLowerModel
The function interface:
    setClickColor()
    setadvancesetingValue()
    setadvancesetingdefalut()
*******************************************************************/
import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2

Item {
    id: advanceset
    property int currentIndex: 0
    signal signalCancel()
    signal signalAdvanceOk()

    function setState(checkIndex)
    {
        if (checkIndex == 0 || checkIndex == 1) {
           sigmaUpperrecbg.source = ""
           sigmaLowerrecbg.source = ""
        }
        else if (checkIndex == 2)
        {
            standardupperrecbg.source = ""
            standardLowerrecbg.source = ""
        }
    }

    function defaultData()
    {
        standardUpperModel.clear()
        standardLowerModel.clear()
        sigmaUpperModel.clear()
        sigmaLowerModel.clear()

        standardUpperModel.append({"head":qsTr("Time"),"value":spliceModel.getStructValue("TestStandardTime+","current"),"maxValue":spliceModel.getStructValue("TestStandardTime+","max"),"minValue":spliceModel.getStructValue("TestStandardTime+","min")})
        standardUpperModel.append({"head":qsTr("Power"),"value":spliceModel.getStructValue("TestStandardPower+","current"),"maxValue":spliceModel.getStructValue("TestStandardPower+","max"),"minValue":spliceModel.getStructValue("TestStandardPower+","min")})
        standardUpperModel.append({"head":qsTr("Pre-Height"),"value":spliceModel.getStructValue("TestStandardPre+","current"),"maxValue":spliceModel.getStructValue("TestStandardPre+","max"),"minValue":spliceModel.getStructValue("TestStandardPre+","min")})
        standardUpperModel.append({"head":qsTr("Height"),"value":spliceModel.getStructValue("TestStandardPost+","current"),"maxValue":spliceModel.getStructValue("TestStandardPost+","max"),"minValue":spliceModel.getStructValue("TestStandardPost+","min")})

        standardLowerModel.append({"head":qsTr("Time"),"value":spliceModel.getStructValue("TestStandardTime-","current"),"maxValue":spliceModel.getStructValue("TestStandardTime-","max"),"minValue":spliceModel.getStructValue("TestStandardTime-","min")})
        standardLowerModel.append({"head":qsTr("Power"),"value":spliceModel.getStructValue("TestStandardPower-","current"),"maxValue":spliceModel.getStructValue("TestStandardPower-","max"),"minValue":spliceModel.getStructValue("TestStandardPower-","min")})
        standardLowerModel.append({"head":qsTr("Pre-Height"),"value":spliceModel.getStructValue("TestStandardPre-","current"),"maxValue":spliceModel.getStructValue("TestStandardPre-","max"),"minValue":spliceModel.getStructValue("TestStandardPre-","min")})
        standardLowerModel.append({"head":qsTr("Height"),"value":spliceModel.getStructValue("TestStandardPost-","current"),"maxValue":spliceModel.getStructValue("TestStandardPost-","max"),"minValue":spliceModel.getStructValue("TestStandardPost-","min")})

        sigmaUpperModel.append({"head":qsTr("Time"),"value":spliceModel.getStructValue("TestSigmaTime+","current"),"maxValue":spliceModel.getStructValue("TestSigmaTime+","max"),"minValue":spliceModel.getStructValue("TestSigmaTime+","min")})
        sigmaUpperModel.append({"head":qsTr("Power"),"value":spliceModel.getStructValue("TestSigmaPower+","current"),"maxValue":spliceModel.getStructValue("TestSigmaPower+","max"),"minValue":spliceModel.getStructValue("TestSigmaPower+","min")})
        sigmaUpperModel.append({"head":qsTr("Pre-Height"),"value":spliceModel.getStructValue("TestSigmaPre+","current"),"maxValue":spliceModel.getStructValue("TestSigmaPre+","max"),"minValue":spliceModel.getStructValue("TestSigmaPre+","min")})
        sigmaUpperModel.append({"head":qsTr("Height"),"value":spliceModel.getStructValue("TestSigmaPost+","current"),"maxValue":spliceModel.getStructValue("TestSigmaPost+","max"),"minValue":spliceModel.getStructValue("TestSigmaPost+","min")})

        sigmaLowerModel.append({"head":qsTr("Time"),"value":spliceModel.getStructValue("TestSigmaTime-","current"),"maxValue":spliceModel.getStructValue("TestSigmaTime-","max"),"minValue":spliceModel.getStructValue("TestSigmaTime-","min")})
        sigmaLowerModel.append({"head":qsTr("Power"),"value":spliceModel.getStructValue("TestSigmaPower-","current"),"maxValue":spliceModel.getStructValue("TestSigmaPower-","max"),"minValue":spliceModel.getStructValue("TestSigmaPower-","min")})
        sigmaLowerModel.append({"head":qsTr("Pre-Height"),"value":spliceModel.getStructValue("TestSigmaPre-","current"),"maxValue":spliceModel.getStructValue("TestSigmaPre-","max"),"minValue":spliceModel.getStructValue("TestSigmaPre-","min")})
        sigmaLowerModel.append({"head":qsTr("Height"),"value":spliceModel.getStructValue("TestSigmaPost-","current"),"maxValue":spliceModel.getStructValue("TestSigmaPost-","max"),"minValue":spliceModel.getStructValue("TestSigmaPost-","min")})

    }

    function setClickColor(index)
    {
        if (standardUpperRepeater.itemAt(index).localbordercolor === "#05f91c") {
            standardUpperRepeater.itemAt(index).localbordercolor = "#f79428"
        } else if (standardlowerRepeater.itemAt(index).localbordercolor == "#05f91c") {
            standardlowerRepeater.itemAt(index).localbordercolor = "#0079c1"
        } else if (sigmaUpperRepeater.itemAt(index).localbordercolor == "#05f91c") {
            sigmaUpperRepeater.itemAt(index).localbordercolor = "#f79428"
        } else if (sigmaLowerRepeater.itemAt(index).localbordercolor == "#05f91c") {
            sigmaLowerRepeater.itemAt(index).localbordercolor = "#0079c1"
        }
    }

    function setadvancesetingValue(index,text)
    {
        if (standardUpperRepeater.itemAt(index).localbordercolor === "#05f91c") {
                standardUpperModel.set(index,{"value":text})
        } else if (standardlowerRepeater.itemAt(index).localbordercolor == "#05f91c") {
                standardLowerModel.set(index,{"value":text})
        } else if (sigmaUpperRepeater.itemAt(index).localbordercolor == "#05f91c") {
                sigmaUpperModel.set(index,{"value":text})
        } else if (sigmaLowerRepeater.itemAt(index).localbordercolor == "#05f91c") {
                sigmaLowerModel.set(index,{"value":text})
        }
    }

    function setadvancesetingdefalut()
    {
        standardUpperModel.clear()
        standardUpperModel.append({"head":qsTr("Time"),"value":"40%"})
        standardUpperModel.append({"head":qsTr("Power"),"value":"25%"})
        standardUpperModel.append({"head":qsTr("Pre-Height"),"value":"15%"})
        standardUpperModel.append({"head":qsTr("Height"),"value":"10%"})
        standardLowerModel.clear()
        standardLowerModel.append({"head":qsTr("Time"),"value":"40%"})
        standardLowerModel.append({"head":qsTr("Power"),"value":"25%"})
        standardLowerModel.append({"head":qsTr("Pre-Height"),"value":"15%"})
        standardLowerModel.append({"head":qsTr("Height"),"value":"10%"})
        sigmaUpperModel.clear()
        sigmaUpperModel.append({"head":qsTr("Time"),"value":"4"})
        sigmaUpperModel.append({"head":qsTr("Power"),"value":"4"})
        sigmaUpperModel.append({"head":qsTr("Pre-Height"),"value":"4"})
        sigmaUpperModel.append({"head":qsTr("Height"),"value":"4"})
        sigmaLowerModel.clear()
        sigmaLowerModel.append({"head":qsTr("Time"),"value":"4"})
        sigmaLowerModel.append({"head":qsTr("Power"),"value":"4"})
        sigmaLowerModel.append({"head":qsTr("Pre-Height"),"value":"4"})
        sigmaLowerModel.append({"head":qsTr("Height"),"value":"4"})
    }

    Image {
        anchors.fill: parent
        source: "qrc:/images/images/bg.png"
    }
    Text {
        id: standard
        anchors.top: parent.top
        anchors.topMargin: 26
        anchors.left: parent.left
        anchors.leftMargin: 50
        font.family: "arial"
        font.pixelSize: 25
        color: "white"
        text: qsTr("Standard & Auto")
    }
    Text {
        id: sigma
        anchors.top: parent.top
        anchors.topMargin: 26
        anchors.left: sigmaUpperrec.left
        font.family: "arial"
        font.pixelSize: 25
        color: "white"
        text: qsTr("Sigma")
    }
    Line {
        id: line1
        anchors.top: standard.bottom
        anchors.topMargin: 26
        anchors.left: parent.left
        anchors.leftMargin: 20
        width: parent.width-40
        height: 1
        lineColor: "#ffffff"
    }
    Line {
        id: line2
        anchors.top: line1.bottom
        anchors.left: parent.left
        anchors.leftMargin: 20
        width: parent.width-40
        height: 1
        lineColor: "#0d0f11"
    }
    Image {
        id: upper1
        anchors.top: line2.bottom
        anchors.left: standardupperrec.left
        anchors.leftMargin: -23.5
        width: 192
        height: 49
        source: "qrc:/images/images/orange.png"
        Text {
            anchors.centerIn: parent
            font.family: "arial"
            font.pixelSize: 25
            color: "white"
            text: qsTr("Upper")
        }
    }
    Image {
        id: lower1
        anchors.bottom: standardLowerrec.top
        anchors.left: standardLowerrec.left
        anchors.leftMargin: -23.5
        width: 192
        height: 49
        source: "qrc:/images/images/blue.png"
        Text {
            anchors.centerIn: parent
            font.family: "arial"
            font.pixelSize: 25
            color: "white"
            text: qsTr("Lower")
        }
    }
    Image {
        id: upper2
        anchors.top: line2.bottom
        anchors.left: sigmaUpperrec.left
        anchors.leftMargin: -23.5
        width: 192
        height: 49
        source: "qrc:/images/images/orange.png"
        Text {
            anchors.centerIn: parent
            font.family: "arial"
            font.pixelSize: 25
            color: "white"
            text: qsTr("Upper")
        }
    }
    Image {
        id: lower2
        anchors.bottom: sigmaLowerrec.top
        anchors.left: sigmaLowerrec.left
        anchors.leftMargin: -23.5
        width: 192
        height: 49
        source: "qrc:/images/images/blue.png"
        Text {
            anchors.centerIn: parent
            font.family: "arial"
            font.pixelSize: 25
            color: "white"
            text: qsTr("Lower")
        }
    }
    ListModel {
        id: standardUpperModel
    }
    ListModel {
        id: standardLowerModel
    }
    ListModel {
        id: sigmaUpperModel
    }
    ListModel {
        id: sigmaLowerModel
        Component.onCompleted: {
            standardUpperModel.append({"head":qsTr("Time"),"value":spliceModel.getStructValue("TestStandardTime+","current"),"maxValue":spliceModel.getStructValue("TestStandardTime+","max"),"minValue":spliceModel.getStructValue("TestStandardTime+","min")})
            standardUpperModel.append({"head":qsTr("Power"),"value":spliceModel.getStructValue("TestStandardPower+","current"),"maxValue":spliceModel.getStructValue("TestStandardPower+","max"),"minValue":spliceModel.getStructValue("TestStandardPower+","min")})
            standardUpperModel.append({"head":qsTr("Pre-Height"),"value":spliceModel.getStructValue("TestStandardPre+","current"),"maxValue":spliceModel.getStructValue("TestStandardPre+","max"),"minValue":spliceModel.getStructValue("TestStandardPre+","min")})
            standardUpperModel.append({"head":qsTr("Height"),"value":spliceModel.getStructValue("TestStandardPost+","current"),"maxValue":spliceModel.getStructValue("TestStandardPost+","max"),"minValue":spliceModel.getStructValue("TestStandardPost+","min")})

            standardLowerModel.append({"head":qsTr("Time"),"value":spliceModel.getStructValue("TestStandardTime-","current"),"maxValue":spliceModel.getStructValue("TestStandardTime-","max"),"minValue":spliceModel.getStructValue("TestStandardTime-","min")})
            standardLowerModel.append({"head":qsTr("Power"),"value":spliceModel.getStructValue("TestStandardPower-","current"),"maxValue":spliceModel.getStructValue("TestStandardPower-","max"),"minValue":spliceModel.getStructValue("TestStandardPower-","min")})
            standardLowerModel.append({"head":qsTr("Pre-Height"),"value":spliceModel.getStructValue("TestStandardPre-","current"),"maxValue":spliceModel.getStructValue("TestStandardPre-","max"),"minValue":spliceModel.getStructValue("TestStandardPre-","min")})
            standardLowerModel.append({"head":qsTr("Height"),"value":spliceModel.getStructValue("TestStandardPost-","current"),"maxValue":spliceModel.getStructValue("TestStandardPost-","max"),"minValue":spliceModel.getStructValue("TestStandardPost-","min")})

            sigmaUpperModel.append({"head":qsTr("Time"),"value":spliceModel.getStructValue("TestSigmaTime+","current"),"maxValue":spliceModel.getStructValue("TestSigmaTime+","max"),"minValue":spliceModel.getStructValue("TestSigmaTime+","min")})
            sigmaUpperModel.append({"head":qsTr("Power"),"value":spliceModel.getStructValue("TestSigmaPower+","current"),"maxValue":spliceModel.getStructValue("TestSigmaPower+","max"),"minValue":spliceModel.getStructValue("TestSigmaPower+","min")})
            sigmaUpperModel.append({"head":qsTr("Pre-Height"),"value":spliceModel.getStructValue("TestSigmaPre+","current"),"maxValue":spliceModel.getStructValue("TestSigmaPre+","max"),"minValue":spliceModel.getStructValue("TestSigmaPre+","min")})
            sigmaUpperModel.append({"head":qsTr("Height"),"value":spliceModel.getStructValue("TestSigmaPost+","current"),"maxValue":spliceModel.getStructValue("TestSigmaPost+","max"),"minValue":spliceModel.getStructValue("TestSigmaPost+","min")})

            sigmaLowerModel.append({"head":qsTr("Time"),"value":spliceModel.getStructValue("TestSigmaTime-","current"),"maxValue":spliceModel.getStructValue("TestSigmaTime-","max"),"minValue":spliceModel.getStructValue("TestSigmaTime-","min")})
            sigmaLowerModel.append({"head":qsTr("Power"),"value":spliceModel.getStructValue("TestSigmaPower-","current"),"maxValue":spliceModel.getStructValue("TestSigmaPower-","max"),"minValue":spliceModel.getStructValue("TestSigmaPower-","min")})
            sigmaLowerModel.append({"head":qsTr("Pre-Height"),"value":spliceModel.getStructValue("TestSigmaPre-","current"),"maxValue":spliceModel.getStructValue("TestSigmaPre-","max"),"minValue":spliceModel.getStructValue("TestSigmaPre-","min")})
            sigmaLowerModel.append({"head":qsTr("Height"),"value":spliceModel.getStructValue("TestSigmaPost-","current"),"maxValue":spliceModel.getStructValue("TestSigmaPost-","max"),"minValue":spliceModel.getStructValue("TestSigmaPost-","min")})

        }
    }
    Row {
        id: standardupperrec
        anchors.top: upper1.bottom
        anchors.left: parent.left
        anchors.leftMargin: 50
        width: 630
        clip: true
        spacing: 10
        Repeater {
            id: standardUpperRepeater
            model: standardUpperModel
            delegate: Item {
                property string localbordercolor: "#f79428"
                width: 145
                height: 154
                Image {
                    id: standardupperrecbg
                    anchors.fill: parent
                    source: "qrc:/images/images/advancesetting-bg1.png"
                }
                Rectangle {
                    id: backGround
                    width: 145
                    height: 145
                    border.color: localbordercolor
                    border.width: 2
                    color: Qt.rgba(0,0,0,0)
                }
                Text {
                    id: headName
                    anchors.top: parent.top
                    anchors.topMargin: 20
                    anchors.left: parent.left
                    anchors.leftMargin: 10
                    font.family: "arial"
                    font.pixelSize: 20
                    color: "white"
                    text: head
                }
                Text {
                    id: centerValue
                    anchors.centerIn: parent
                    font.family: "arial"
                    font.pixelSize: 25
                    color: "white"
                    text: value
                    onTextChanged: {
                        standardUpperModel.set(index,{"value":centerValue.text})
                    }
                }
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        if (standardupperrecbg.source == "")
                            return
                        setClickColor(advanceset.currentIndex)
                        advanceset.currentIndex = index
                        localbordercolor = "#05f91c"
                        background.visible = true
                        background.opacity = 0.3
                        keyNum.visible = true
                        keyNum.titleText = head
                        keyNum.currentValue = value
                        keyNum.maxvalue = maxValue
                        keyNum.minvalue = minValue
                    }
                }
            }
        }
    }

    Row {
        id: standardLowerrec
        anchors.top: standardupperrec.bottom
        anchors.topMargin: 49
        anchors.left: standardupperrec.left
        width: 630
        clip: true
        spacing: 10
        Repeater {
            id: standardlowerRepeater
            model: standardLowerModel
            delegate: Item {
                property string localbordercolor: "#0079c1"
                width: 145
                height: 154
                Image {
                    id: standardLowerrecbg
                    anchors.fill: parent
                    source: "qrc:/images/images/advancesetting-bg1.png"
                }
                Rectangle {
                    id: backGround2
                    width: 145
                    height: 145
                    border.color: localbordercolor
                    border.width: 2
                    color: Qt.rgba(0,0,0,0)
                }
                Text {
                    id: headName2
                    anchors.top: parent.top
                    anchors.topMargin: 20
                    anchors.left: parent.left
                    anchors.leftMargin: 10
                    font.family: "arial"
                    font.pixelSize: 20
                    color: "white"
                    text: head
                }
                Text {
                    id: centerValue2
                    anchors.centerIn: parent
                    font.family: "arial"
                    font.pixelSize: 25
                    color: "white"
                    text: value
                    onTextChanged: {
                        standardLowerModel.set(index,{"value":centerValue2.text})
                    }
                }
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        if (standardLowerrecbg.source == "")
                            return
                        setClickColor(advanceset.currentIndex)
                        advanceset.currentIndex = index
                        localbordercolor = "#05f91c"
                        background.visible = true
                        background.opacity = 0.3
                        keyNum.visible = true
                        keyNum.titleText = head
                        keyNum.currentValue = value
                        keyNum.maxvalue = maxValue
                        keyNum.minvalue = minValue
                    }
                }
            }
        }
    }

    Row {
        id: sigmaUpperrec
        anchors.top: upper1.bottom
        anchors.right: parent.right
        anchors.rightMargin: 50
        width: 630
        clip: true
        spacing: 10
        Repeater {
            id: sigmaUpperRepeater
            model: sigmaUpperModel
            delegate: Item {
                property string localbordercolor: "#f79428"
                width: 145
                height: 154
                Image {
                    id: sigmaUpperrecbg
                    anchors.fill: parent
                    source: "qrc:/images/images/advancesetting-bg1.png"
                }
                Rectangle {
                    id: backGround3
                    width: 145
                    height: 145
                    border.color: localbordercolor
                    border.width: 2
                    color: Qt.rgba(0,0,0,0)
                }
                Text {
                    id: headName3
                    anchors.top: parent.top
                    anchors.topMargin: 20
                    anchors.left: parent.left
                    anchors.leftMargin: 10
                    font.family: "arial"
                    font.pixelSize: 20
                    color: "white"
                    text: head
                }
                Text {
                    id: centerValue3
                    anchors.centerIn: parent
                    font.family: "arial"
                    font.pixelSize: 25
                    color: "white"
                    text: value
                    onTextChanged: {
                        sigmaUpperModel.set(index,{"value":centerValue3.text})
                    }
                }
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        if (sigmaUpperrecbg.source == "")
                            return
                        setClickColor(advanceset.currentIndex)
                        advanceset.currentIndex = index
                        localbordercolor = "#05f91c"
                        background.visible = true
                        background.opacity = 0.3
                        keyNum.visible = true
                        keyNum.titleText = head
                        keyNum.currentValue = value
                        keyNum.maxvalue = maxValue
                        keyNum.minvalue = minValue
                    }
                }
            }
        }
    }

    Row {
        id: sigmaLowerrec
        anchors.top: sigmaUpperrec.bottom
        anchors.topMargin: 49
        anchors.right: parent.right
        anchors.rightMargin: 50
        width: 630
        clip: true
        spacing: 10
        Repeater {
            id: sigmaLowerRepeater
            model: sigmaLowerModel
            delegate: Item {
                property string localbordercolor: "#0079c1"
                width: 145
                height: 154
                Image {
                    id: sigmaLowerrecbg
                    anchors.fill: parent
                    source: "qrc:/images/images/advancesetting-bg1.png"
                }
                Rectangle {
                    id: backGround4
                    width: 145
                    height: 145
                    border.color: localbordercolor
                    border.width: 2
                    color: Qt.rgba(0,0,0,0)
                }
                Text {
                    id: headName4
                    anchors.top: parent.top
                    anchors.topMargin: 20
                    anchors.left: parent.left
                    anchors.leftMargin: 10
                    font.family: "arial"
                    font.pixelSize: 20
                    color: "white"
                    text: head
                }
                Text {
                    id: centerValue4
                    anchors.centerIn: parent
                    font.family: "arial"
                    font.pixelSize: 25
                    color: "white"
                    text: value
                    onTextChanged: {
                        sigmaLowerModel.set(index,{"value":centerValue4.text})
                    }
                }
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        if (sigmaLowerrecbg.source == "")
                            return
                        setClickColor(advanceset.currentIndex)
                        advanceset.currentIndex = index
                        localbordercolor = "#05f91c"
                        background.visible = true
                        background.opacity = 0.3
                        keyNum.visible = true
                        keyNum.titleText = head
                        keyNum.currentValue = value
                        keyNum.maxvalue = maxValue
                        keyNum.minvalue = minValue
                    }
                }
            }
        }
    }

    Line {
        id: line3
        anchors.bottom: line4.top
        anchors.left: parent.left
        anchors.leftMargin: 20
        width: parent.width-40
        height: 1
        lineColor: "#ffffff"
    }
    Line {
        id: line4
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 157
        anchors.left: parent.left
        anchors.leftMargin: 20
        width: parent.width-40
        height: 1
        lineColor: "#0d0f11"
    }
    CButton {
        id: okButton
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 44
        anchors.right: parent.right
        anchors.rightMargin: 20
        width: 300
        height: 79
        iconSource: "qrc:/images/images/OK.png"
        text: qsTr("OK")
        textColor: "white"
        onClicked: {
            spliceModel.setStructValue("TestStandardTime+",standardUpperModel.get(0).value)
            spliceModel.setStructValue("TestStandardPower+",standardUpperModel.get(1).value)
            spliceModel.setStructValue("TestStandardPre+",standardUpperModel.get(2).value)
            spliceModel.setStructValue("TestStandardPost+",standardUpperModel.get(3).value)

            spliceModel.setStructValue("TestStandardTime-",standardLowerModel.get(0).value)
            spliceModel.setStructValue("TestStandardPower-",standardLowerModel.get(1).value)
            spliceModel.setStructValue("TestStandardPre-",standardLowerModel.get(2).value)
            spliceModel.setStructValue("TestStandardPost-",standardLowerModel.get(3).value)

            spliceModel.setStructValue("TestSigmaTime+",sigmaUpperModel.get(0).value)
            spliceModel.setStructValue("TestSigmaPower+",sigmaUpperModel.get(1).value)
            spliceModel.setStructValue("TestSigmaPre+",sigmaUpperModel.get(2).value)
            spliceModel.setStructValue("TestSigmaPost+",sigmaUpperModel.get(3).value)

            spliceModel.setStructValue("TestSigmaTime-",sigmaLowerModel.get(0).value)
            spliceModel.setStructValue("TestSigmaPower-",sigmaLowerModel.get(1).value)
            spliceModel.setStructValue("TestSigmaPre-",sigmaLowerModel.get(2).value)
            spliceModel.setStructValue("TestSigmaPost-",sigmaLowerModel.get(3).value)
            spliceModel.saveSplice(true)
            signalAdvanceOk()
        }
    }
    CButton {
        id: cacelButton
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 44
        anchors.right: okButton.left
        anchors.rightMargin: 20
        width: 300
        height: 79
        iconSource: "qrc:/images/images/cancel.png"
        text: qsTr("Cancel")
        textColor: "white"
        onClicked: {
            signalCancel()
        }
    }
    CButton {
        id: defaultButton
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 44
        anchors.right: cacelButton.left
        anchors.rightMargin: 20
        width: 300
        height: 79
        text: qsTr("Defalut Setting")
        textColor: "white"
        onClicked: {
            setadvancesetingdefalut()
        }
    }
    Rectangle {
        id: background
        anchors.fill: parent
        color: "black"
        visible: false
        opacity: 0
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
        maxvalue: "100%"
        minvalue: "1%"
        currentValue: "123"
        onCurrentClickIndex: {
            if (index == 15) {
                setadvancesetingValue(advanceset.currentIndex,keyNum.inputText)
                setClickColor(advanceset.currentIndex)
                background.visible = false
                background.opacity = 0
                keyNum.visible = false
                keyNum.inputText = ""
                keyNum.tempValue = ""
            } else if (index == 11) {
                setClickColor(advanceset.currentIndex)
                background.visible = false
                background.opacity = 0
                keyNum.visible = false
                keyNum.inputText = ""
                keyNum.tempValue = ""
            }
        }
        onInputTextChanged: {
            if (keyNum.inputText != "") {
                setadvancesetingValue(advanceset.currentIndex,keyNum.inputText)
            }
        }
    }
}
