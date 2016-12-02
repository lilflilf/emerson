import QtQuick 2.0

Item {
    property alias tipsText: tips.text
    property alias inputText: mytext.text
    property bool inputFocus: false
    property alias inputWidth: miniKey.width

    CButton {
        id: miniKey
        height: parent.height
    //    property alias inputSize: mytext.font.pointSize
    //    property alias tipsSize: tips.font.pointSize
    //    property alias inputColor: mytext.color
    //    property alias tipsColor: tips.color
    //    property alias maxSize: mytext.maximumLineCount
    //    property alias backgroundcolor: miniKey.backgroundItem.color
    //    property string borderColor: miniKey.backgroundItem.border.color
    //    property alias tipsWidth: miniKey.width
    //    property alias inputHeight: miniKey.height
    //    property alias tipsHeight: miniKey.height

    //    property alias regExp: mytext.validator
    //    property alias displayText: textInput.displayText
    //    property alias horizontalAlignment: textInput.horizontalAlignment
    //    property alias defaultText: defaultText.text
    //    property alias defaultTextSize: defaultText.font.pointSize



        Text {
            id: mytext
            anchors.centerIn: parent
            font.family: "arial"
            color: "white"
            font.pointSize: 16
        }

        backgroundComponent: Rectangle {
            anchors.fill: parent
            color: "#052a40"
            border.color: "#1987ab"
            border.width: 2
        }
        onClicked: {
            inputFocus = true
        }
    }

    Text {
        id: tips
        anchors.left: miniKey.right
        anchors.leftMargin: 8
        anchors.verticalCenter: miniKey.verticalCenter
        font.family: "arial"
        color: "white"
        font.pointSize: 16
    }
}


