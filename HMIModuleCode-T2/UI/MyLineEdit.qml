import QtQuick 2.2
import QtQuick.Window 2.2
//import QtQuick.VirtualKeyboard 2.0
//import QtQuick.Enterprise.VirtualKeyboard 2.0

Item {
    width: parent.width
    height: parent.height
    property alias inputSize: textInput.font.pointSize
    property alias tipsSize: inputTips.font.pointSize
    property alias inputColor: textInput.color
    property alias tipsColor: inputTips.color
    property alias tipsText: inputTips.text
    property alias maxSize: textInput.maximumLength
    property alias backgroundcolor: back.color
    property string borderColor: back.border.color
    property int inputWidth: 0
    property alias tipsWidth: inputTips.width
    property alias inputHeight: textInput.height
    property alias tipsHeight: inputTips.height
    property alias regExp: textInput.validator
    property alias displayText: textInput.displayText
    property alias horizontalAlignment: textInput.horizontalAlignment
    property alias defaultText: defaultText.text
    property alias defaultTextSize: defaultText.font.pointSize
    property alias inputText: textInput.text
    property bool inputFocus: false
    signal textChange(int text)
    onInputFocusChanged: {
        if (inputFocus == false) {
            textInput.cursorVisible = false
            textInput.focus = false
        }
    }

//    signal myfocusChanged(bool focus)
    Rectangle {
        id: back
        anchors.left: parent.left
        anchors.top: parent.top
        width: inputWidth
        height: parent.height
        border.color: "#1987ab"
        border.width: 2
        color: "#052a40"
    }


    TextInput {
        id: textInput
        anchors.left: back.left
        anchors.leftMargin: 5
        anchors.verticalCenter: parent.verticalCenter
        width: inputWidth - 10
        height: parent.height
        maximumLength: 60
        clip: true
        color: "white"
        verticalAlignment: Qt.AlignVCenter
        font.pointSize: 16
        font.family: "arial"
        onFocusChanged: {
            inputFocus = textInput.focus
        }

        //validator: RegExpValidator{regExp: /^[1-9]{1,2}$/}
        Text {
            id: defaultText
            color: "white"
            font.pointSize: 12
            font.family: "arial"
            anchors.left: parent.left
            anchors.leftMargin: 8
            opacity: 0.5
            anchors.verticalCenter: parent.verticalCenter
            visible: textInput.text.length == 0 ? true : false
        }
        onTextChanged: {
            textChange(textInput.text)
        }

    }


    Text {
        id: inputTips
        anchors.left: textInput.right
        anchors.leftMargin: 8
        color: "white"
        font.family: "arial"
        font.pointSize: 10
        clip: true
        anchors.verticalCenter: textInput.verticalCenter
    }
}
