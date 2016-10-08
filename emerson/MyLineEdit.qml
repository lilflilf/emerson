import QtQuick 2.0

Item {
    width: parent.width
    height: parent.width
    property alias inputSize: textInput.font.pointSize
    property alias tipsSize: inputTips.font.pointSize
    property alias inputColor: textInput.color
    property alias tipsColor: inputTips.color
    property alias tipsText: inputTips.text
    property alias maxSize: textInput.maximumLength
    property alias backgroundcolor: back.color
    property alias inputWidth: textInput.width
    property alias tipsWidth: inputTips.width
    property alias inputHeight: textInput.height
    property alias tipsHeight: inputTips.height
    property alias regExp: textInput.validator
    property alias displayText: textInput.displayText
    property alias horizontalAlignment: textInput.horizontalAlignment
    property alias defaultText: defaultText.text
    property alias defaultTextSize: defaultText.font.pointSize
    property alias inputText: textInput.text
    signal textChange(int text)
    Rectangle {
        id: back
        anchors.fill: textInput
        border.color: "#1987ab"
        border.width: 2
        color: "black"
    }
    TextInput {
        id: textInput
        width: parent.width * 0.5
        height: parent.height
        maximumLength: 60
        clip: true
        color: "white"
        verticalAlignment: Qt.AlignVCenter
        font.pointSize: 16
        font.family: "arial"
        //validator: RegExpValidator{regExp: /^[1-9]{1,2}$/}
        Text {
            id: defaultText
            color: "white"
            font.pointSize: 12
            font.family: "arial"
            anchors.centerIn: parent
            opacity: 0.5
            anchors.verticalCenter: parent.verticalCenter
        }
        onTextChanged: {
            textChange(textInput.text)
        }
    }


    Text {
        id: inputTips
        anchors.left: textInput.right
        anchors.leftMargin: 6
        color: "white"
        font.family: "arial"
        font.pointSize: 10
        anchors.verticalCenter: textInput.verticalCenter
    }
}
