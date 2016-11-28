import QtQuick 2.7
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.0
import QtQuick.Controls 1.3
import QtQuick.Window 2.2

Item {
    signal passWordInputOk()
    Image {
        anchors.fill: parent
        source: "qrc:/images/images/loginbackground.png"
    }

    Image {
        id: welcomeImage
        anchors.verticalCenter: parent.verticalCenter
        anchors.verticalCenterOffset: -150
        height: 115 //parent.height*0.5
        width: 271 //parent.width*0.35
        anchors.left: parent.left
        anchors.leftMargin: parent.width/5
        source: "qrc:/images/images/logo.png"
    }
    Text {
        id: title1
        anchors.top: welcomeImage.bottom
        anchors.horizontalCenter: welcomeImage.horizontalCenter
        color: "white"
        font.family: "arial"
        font.pixelSize: 26
        text: qsTr("Industrial Automation")
    }
    Text {
        id: title2
        anchors.top: welcomeImage.bottom
        anchors.topMargin: 100
        anchors.horizontalCenter: welcomeImage.horizontalCenter
        color: "white"
        font.family: "arial"
        font.pixelSize: 40
        text: qsTr("BRANSON")
    }




    Text {
        id: title
        anchors.top: welcomeImage.top
        anchors.left: welcomeImage.right
        anchors.leftMargin: parent.width/5
        color: "white"
        font.family: "arial"
        font.pixelSize: 24
        text: qsTr("Scan Or \nEnter ID")
    }
    TextInput {
        id: mima
        anchors.horizontalCenter: title.horizontalCenter
        anchors.top: title.bottom
        maximumLength: 4
        font.pixelSize: 35
        height: 40
        font.family: "arial"
        color: "white"
        text: qsTr("")
        echoMode: TextInput.Password
    }
    Grid {
        anchors.horizontalCenter: title.horizontalCenter
        anchors.top: mima.bottom
        anchors.topMargin: 10
        spacing: 12
        columns: 3
        Repeater {
            model: ["1","2","3","4","5","6","7","8","9","C","0","Del"]
            delegate: CButton {
                width: 98
                height: 93
                text: modelData
                textColor: "white"
                onClicked: {
                    if (index == 9) {
                        mima.text = ""
                    } else if (index == 11) {
                        mima.remove(mima.text.length-1,mima.text.length)
                    } else {
                        mima.text += modelData
                        if (mima.text.length == 4) {
                            if (hmiAdaptor.login(mima.text))
                                passWordInputOk()
                        }
                    }
                }
            }
        }
    }
}
