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

    property var checkString: ""
    property int checkIndex: -1

    function setData()
    {
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
        teachModel.append({"head":qsTr("Quantity"),"standardValue":spliceModel.getTeachModeValue("TestStandardQty","current"),
                                               "standardMaxValue":spliceModel.getTeachModeValue("TestStandardQty","max"),
                                               "standardMinValue":spliceModel.getTeachModeValue("TestStandardQty","min"),
                                               "autoValue":spliceModel.getTeachModeValue("TestAutoQty","current"),
                                               "autoMaxValue":spliceModel.getTeachModeValue("TestAutoQty","max"),
                                               "autoMinValue":spliceModel.getTeachModeValue("TestAutoQty","min"),
                                               "sigmaValue":spliceModel.getTeachModeValue("TestSigmaQty","current"),
                                               "sigmaMaxValue":spliceModel.getTeachModeValue("TestSigmaQty","max"),
                                               "sigmaMinValue":spliceModel.getTeachModeValue("TestSigmaQty","min"),
                          })
    }

    function setadvancesetingValue(text)
    {
        if (checkString == "standardValue")
            teachModel.set(checkIndex,{"standardValue":text})
        else if (checkString == "autoValue")
            teachModel.set(checkIndex,{"autoValue":text})
        else if (checkString == "sigmaValue")
            teachModel.set(checkIndex,{"sigmaValue":text})
    }

    function setadvancesetingdefalut()
    {

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
            setData()
        }
    }
    ListModel {
        id: titleModel
        Component.onCompleted: {
            titleModel.append({"title":"Time"})
            titleModel.append({"title":"PeakPower"})
            titleModel.append({"title":"Pre-Height"})
            titleModel.append({"title":"Post-Height"})
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

    Text {
        id: sample
        text: qsTr("SampleSize")
        horizontalAlignment: Qt.AlignHCenter
        verticalAlignment: Qt.AlignVCenter
        color: "white"
        font.pointSize: 18
        font.family: "arial"
        height: 60
        width: 150

        anchors.bottom: line3.top
        anchors.left: line1.left
        anchors.leftMargin: 30
    }

    ListView{
        anchors.top: line1.bottom
        anchors.left: line1.left
        anchors.bottom: line3.bottom
        anchors.right: line3.right
        anchors.topMargin: 5
        model: teachModel
        interactive: false
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
                    checkString = "standardValue"
                    checkIndex = index
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
                    checkString = "autoValue"
                    checkIndex = index
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
                    checkString = "sigmaValue"
                    checkIndex = index
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
            spliceModel.setTeachModeValue("TestTime+",teachModel.get(0).standardValue,teachModel.get(0).autoValue,teachModel.get(0).sigmaValue)
            spliceModel.setTeachModeValue("TestTime-",teachModel.get(1).standardValue,teachModel.get(1).autoValue,teachModel.get(1).sigmaValue)

            spliceModel.setTeachModeValue("TestPower+",teachModel.get(2).standardValue,teachModel.get(2).autoValue,teachModel.get(2).sigmaValue)
            spliceModel.setTeachModeValue("TestPower-",teachModel.get(3).standardValue,teachModel.get(3).autoValue,teachModel.get(3).sigmaValue)

            spliceModel.setTeachModeValue("TestPre+",teachModel.get(4).standardValue,teachModel.get(4).autoValue,teachModel.get(4).sigmaValue)
            spliceModel.setTeachModeValue("TestPre-",teachModel.get(5).standardValue,teachModel.get(5).autoValue,teachModel.get(5).sigmaValue)

            spliceModel.setTeachModeValue("TestPost+",teachModel.get(6).standardValue,teachModel.get(6).autoValue,teachModel.get(6).sigmaValue)
            spliceModel.setTeachModeValue("TestPost-",teachModel.get(7).standardValue,teachModel.get(7).autoValue,teachModel.get(7).sigmaValue)

            spliceModel.setTeachModeValue("TestQty",teachModel.get(8).standardValue,teachModel.get(8).autoValue,teachModel.get(8).sigmaValue)

            spliceModel.saveTeachMode()
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
                setadvancesetingValue(keyNum.inputText)
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
                setadvancesetingValue(keyNum.inputText)
            }
        }
    }
}
