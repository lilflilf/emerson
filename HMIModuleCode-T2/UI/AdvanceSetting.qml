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

    function setadvancesetingValue(index,text)
    {

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
        anchors.left: standard.right
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

    ListModel {
        id: teachModel
        Component.onCompleted: {
            teachModel.append({"head":qsTr("Upper"),"standardValue":spliceModel.getTeachModeValue("TestStandardTime+","current"),
                                                   "standardMaxValue":spliceModel.getTeachModeValue("TestStandardTime+","max"),
                                                   "standardMinValue":spliceModel.getTeachModeValue("TestStandardTime+","min"),
                                                   "autoValue":spliceModel.getTeachModeValue("TestAutoTime+","current"),
                                                   "autoMaxValue":spliceModel.getTeachModeValue("TestAutoTime+","max"),
                                                   "autoMinValue":spliceModel.getTeachModeValue("TestAutoTime+","min"),
                                                   "sigmaValue":spliceModel.getTeachModeValue("TestSigmaTime+","current"),
                                                   "sigmaMaxValue":spliceModel.getTeachModeValue("TestSigmaTime+","max"),
                                                   "sigmaMinValue":spliceModel.getTeachModeValue("TestSigmaTime+","min"),
                              })
            teachModel.append({"head":qsTr("Lower"),"standardValue":spliceModel.getTeachModeValue("TestStandardTime-","current"),
                                                   "standardMaxValue":spliceModel.getTeachModeValue("TestStandardTime-","max"),
                                                   "standardMinValue":spliceModel.getTeachModeValue("TestStandardTime-","min"),
                                                   "autoValue":spliceModel.getTeachModeValue("TestAutoTime-","current"),
                                                   "autoMaxValue":spliceModel.getTeachModeValue("TestAutoTime-","max"),
                                                   "autoMinValue":spliceModel.getTeachModeValue("TestAutoTime-","min"),
                                                   "sigmaValue":spliceModel.getTeachModeValue("TestSigmaTime-","current"),
                                                   "sigmaMaxValue":spliceModel.getTeachModeValue("TestSigmaTime-","max"),
                                                   "sigmaMinValue":spliceModel.getTeachModeValue("TestSigmaTime-","min"),
                              })
            teachModel.append({"head":qsTr("Upper"),"standardValue":spliceModel.getTeachModeValue("TestStandardPower+","current"),
                                                   "standardMaxValue":spliceModel.getTeachModeValue("TestStandardPower+","max"),
                                                   "standardMinValue":spliceModel.getTeachModeValue("TestStandardPower+","min"),
                                                   "autoValue":spliceModel.getTeachModeValue("TestAutoPower+","current"),
                                                   "autoMaxValue":spliceModel.getTeachModeValue("TestAutoPower+","max"),
                                                   "autoMinValue":spliceModel.getTeachModeValue("TestAutoPower+","min"),
                                                   "sigmaValue":spliceModel.getTeachModeValue("TestSigmaPower+","current"),
                                                   "sigmaMaxValue":spliceModel.getTeachModeValue("TestSigmaPower+","max"),
                                                   "sigmaMinValue":spliceModel.getTeachModeValue("TestSigmaPower+","min"),
                              })
            teachModel.append({"head":qsTr("Lower"),"standardValue":spliceModel.getTeachModeValue("TestStandardPower-","current"),
                                                   "standardMaxValue":spliceModel.getTeachModeValue("TestStandardPower-","max"),
                                                   "standardMinValue":spliceModel.getTeachModeValue("TestStandardPower-","min"),
                                                   "autoValue":spliceModel.getTeachModeValue("TestAutoPower-","current"),
                                                   "autoMaxValue":spliceModel.getTeachModeValue("TestAutoPower-","max"),
                                                   "autoMinValue":spliceModel.getTeachModeValue("TestAutoPower-","min"),
                                                   "sigmaValue":spliceModel.getTeachModeValue("TestSigmaPower-","current"),
                                                   "sigmaMaxValue":spliceModel.getTeachModeValue("TestSigmaPower-","max"),
                                                   "sigmaMinValue":spliceModel.getTeachModeValue("TestSigmaPower-","min"),
                              })
            teachModel.append({"head":qsTr("Upper"),"standardValue":spliceModel.getTeachModeValue("TestStandardPre+","current"),
                                                   "standardMaxValue":spliceModel.getTeachModeValue("TestStandardPre+","max"),
                                                   "standardMinValue":spliceModel.getTeachModeValue("TestStandardPre+","min"),
                                                   "autoValue":spliceModel.getTeachModeValue("TestAutoPre+","current"),
                                                   "autoMaxValue":spliceModel.getTeachModeValue("TestAutoPre+","max"),
                                                   "autoMinValue":spliceModel.getTeachModeValue("TestAutoPre+","min"),
                                                   "sigmaValue":spliceModel.getTeachModeValue("TestSigmaPre+","current"),
                                                   "sigmaMaxValue":spliceModel.getTeachModeValue("TestSigmaPre+","max"),
                                                   "sigmaMinValue":spliceModel.getTeachModeValue("TestSigmaPre+","min"),
                              })
            teachModel.append({"head":qsTr("Lower"),"standardValue":spliceModel.getTeachModeValue("TestStandardPre-","current"),
                                                   "standardMaxValue":spliceModel.getTeachModeValue("TestStandardPre-","max"),
                                                   "standardMinValue":spliceModel.getTeachModeValue("TestStandardPre-","min"),
                                                   "autoValue":spliceModel.getTeachModeValue("TestAutoPre-","current"),
                                                   "autoMaxValue":spliceModel.getTeachModeValue("TestAutoPre-","max"),
                                                   "autoMinValue":spliceModel.getTeachModeValue("TestAutoPre-","min"),
                                                   "sigmaValue":spliceModel.getTeachModeValue("TestSigmaPre-","current"),
                                                   "sigmaMaxValue":spliceModel.getTeachModeValue("TestSigmaPre-","max"),
                                                   "sigmaMinValue":spliceModel.getTeachModeValue("TestSigmaPre-","min"),
                              })
            teachModel.append({"head":qsTr("Upper"),"standardValue":spliceModel.getTeachModeValue("TestStandardPost+","current"),
                                                   "standardMaxValue":spliceModel.getTeachModeValue("TestStandardPost+","max"),
                                                   "standardMinValue":spliceModel.getTeachModeValue("TestStandardPost+","min"),
                                                   "autoValue":spliceModel.getTeachModeValue("TestAutoPost+","current"),
                                                   "autoMaxValue":spliceModel.getTeachModeValue("TestAutoPost+","max"),
                                                   "autoMinValue":spliceModel.getTeachModeValue("TestAutoPost+","min"),
                                                   "sigmaValue":spliceModel.getTeachModeValue("TestSigmaPost+","current"),
                                                   "sigmaMaxValue":spliceModel.getTeachModeValue("TestSigmaPost+","max"),
                                                   "sigmaMinValue":spliceModel.getTeachModeValue("TestSigmaPost+","min"),
                              })
            teachModel.append({"head":qsTr("Lower"),"standardValue":spliceModel.getTeachModeValue("TestStandardPost-","current"),
                                                   "standardMaxValue":spliceModel.getTeachModeValue("TestStandardPost-","max"),
                                                   "standardMinValue":spliceModel.getTeachModeValue("TestStandardPost-","min"),
                                                   "autoValue":spliceModel.getTeachModeValue("TestAutoPost-","current"),
                                                   "autoMaxValue":spliceModel.getTeachModeValue("TestAutoPost-","max"),
                                                   "autoMinValue":spliceModel.getTeachModeValue("TestAutoPost-","min"),
                                                   "sigmaValue":spliceModel.getTeachModeValue("TestSigmaPost-","current"),
                                                   "sigmaMaxValue":spliceModel.getTeachModeValue("TestSigmaPost-","max"),
                                                   "sigmaMinValue":spliceModel.getTeachModeValue("TestSigmaPost-","min"),
                              })

        }
    }
    ListModel {
        id: titleModel
        Component.onCompleted: {
            titleModel.append({"title":"Time"})
            titleModel.append({"title":"PeakPower"})
            titleModel.append({"title":"Pre-Height"})
            titleModel.append({"title":"Post-Height"})
//            titleModel.append({"title":"SampleSize"})
        }
    }
    Column {
        id: titleColumn
        anchors.top: line1.bottom
        anchors.left: line1.left
        anchors.bottom: line3.bottom
        anchors.right: line3.right
        anchors.topMargin: 20
        anchors.leftMargin: 30
        spacing: 42
        Repeater {
            model: titleModel
            delegate: Text {
                height: 60
                text: title
                width: 150
                horizontalAlignment: Qt.AlignHCenter
                verticalAlignment: Qt.AlignVCenter
                color: "white"
                font.pointSize: 18
                font.family: "arial"
            }
        }
    }

    ListView{
        anchors.top: line1.bottom
        anchors.left: line1.left
        anchors.bottom: line3.bottom
        anchors.right: line3.right
        anchors.topMargin: 5
        model: teachModel
        delegate: Item {
            width: line1.width
            height: 50
            Text {
                id: headText
                anchors.left: parent.left
                anchors.leftMargin: 300
                height: 40
                text: head
                width: 150
                horizontalAlignment: Qt.AlignHCenter
                verticalAlignment: Qt.AlignVCenter
                color: "white"
                font.pointSize: 16
                font.family: "arial"
            }
            Recsetting {
                id: standardRec
                centervalue: standardValue
                width: 130
                height: 46
                anchors.left: headText.right
                onMouseAreaClick: {
                    keyNum.visible = true
                    keyNum.titleText = head
                    keyNum.currentValue = standardValue
                    keyNum.minvalue = standardMinValue
                    keyNum.maxvalue = standardMaxValue
                }
            }
            Text {
                id: headText2
                height: 40
                anchors.left: standardRec.right
                anchors.leftMargin: 40
                text: head
                width: 150
                horizontalAlignment: Qt.AlignHCenter
                verticalAlignment: Qt.AlignVCenter
                color: "white"
                font.pointSize: 16
                font.family: "arial"
            }
            Recsetting {
                id: autoRec
                centervalue: autoValue
                width: 130
                height: 46
                anchors.left: headText2.right
                onMouseAreaClick: {
                    keyNum.visible = true
                    keyNum.titleText = head
                    keyNum.currentValue = autoValue
                    keyNum.minvalue = autoMinValue
                    keyNum.maxvalue = autoMaxValue
                }
            }
            Text {
                id: headText3
                height: 40
                anchors.left: autoRec.right
                anchors.leftMargin: 40
                text: head
                width: 150
                horizontalAlignment: Qt.AlignHCenter
                verticalAlignment: Qt.AlignVCenter
                color: "white"
                font.pointSize: 16
                font.family: "arial"
            }
            Recsetting {
                id: sigmaRec
                centervalue: sigmaValue
                width: 130
                height: 46
                anchors.left: headText3.right
                onMouseAreaClick: {
                    keyNum.visible = true
                    keyNum.titleText = head
                    keyNum.currentValue = sigmaValue
                    keyNum.minvalue = sigmaMinValue
                    keyNum.maxvalue = sigmaMaxValue
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
        anchors.bottomMargin: 127
        anchors.left: parent.left
        anchors.leftMargin: 20
        width: parent.width-40
        height: 1
        lineColor: "#0d0f11"
    }
    CButton {
        id: okButton
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 24
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
        anchors.bottomMargin: 24
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
        anchors.bottomMargin: 24
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
                background.visible = false
                background.opacity = 0
                keyNum.visible = false
                keyNum.inputText = ""
                keyNum.tempValue = ""
            } else if (index == 11) {
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
