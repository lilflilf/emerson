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
        height: parent.height*0.5
        width: parent.width*0.35
        anchors.left: parent.left
        anchors.leftMargin: parent.width/8
        opacity: 0.7
        source: "qrc:/images/images/welcome.png"
    }
    Text {
        id: title
        anchors.top: welcomeImage.top
        anchors.left: welcomeImage.right
        anchors.leftMargin: 150
        color: "white"
        font.family: "arial"
        font.pixelSize: 24
        text: qsTr("Scan Or Enter ID")
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
        spacing: 20
        columns: 3
        Repeater {
            model: ["1","2","3","4","5","6","7","8","9","Del","0","C"]
            delegate: CButton {
                width: 50
                height: 50
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
