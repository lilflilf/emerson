import QtQuick 2.2
import QtQuick.Controls.Styles 1.1
import QtQuick.Layouts 1.0
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtWebView 1.1
import QtQuick.Window 2.2
Item {
    signal passWordInputOk()

    Connections {
        target: hmiAdaptor
        onSignalPhysicalKeyMessage: {
            title4.text = qsTr("Scan or Enter ID(Please insert physicalkey)")
            itemChange.start()
        }
    }
    Timer {
        id: itemChange
        interval: 5000
        repeat: false
        triggeredOnStart: false;
        onTriggered: {
            title4.text = qsTr("Scan or Enter ID")
        }
    }

    ListModel {
        id: listModel
        Component.onCompleted: {
            listModel.append({"iconsource":"qrc:/images/images/key1.png","value":"1"})
            listModel.append({"iconsource":"qrc:/images/images/key2.png","value":"2"})
            listModel.append({"iconsource":"qrc:/images/images/key3.png","value":"3"})
            listModel.append({"iconsource":"qrc:/images/images/key4.png","value":"4"})
            listModel.append({"iconsource":"qrc:/images/images/key5.png","value":"5"})
            listModel.append({"iconsource":"qrc:/images/images/key6.png","value":"6"})
            listModel.append({"iconsource":"qrc:/images/images/key7.png","value":"7"})
            listModel.append({"iconsource":"qrc:/images/images/key8.png","value":"8"})
            listModel.append({"iconsource":"qrc:/images/images/key9.png","value":"9"})
            listModel.append({"iconsource":"qrc:/images/images/keyc.png","value":""})
            listModel.append({"iconsource":"qrc:/images/images/key0.png","value":"0"})
            listModel.append({"iconsource":"qrc:/images/images/keyok.png","value":"."})
//            listModel.append({"iconsource":"","value":"OK"})

        }

    }

    Image {
        anchors.fill: parent
        source: "qrc:/images/images/loginbackground.png"
    }
    Image {
        id: title1
        source: "qrc:/images/images/logo1.png"
        anchors.top: parent.top
        anchors.topMargin: 223 //parent.height/3
        anchors.left: parent.left
        anchors.leftMargin: 237 //parent.width/4
        width: 381
        height: 161
    }
//    Text {
//        id: title1
//        anchors.top: parent.top
//        anchors.topMargin: parent.height/3
//        anchors.left: parent.left
//        anchors.leftMargin: parent.width/4
//        font.pointSize: 40
//        color: "white"
//        font.family: "arial"
//        text: qsTr("EMERSON")
//    }
//    Text {
//        id: title2
//        anchors.horizontalCenter: title1.horizontalCenter
//        anchors.top: title1.bottom
//        font.pointSize: 26
//        color: "white"
//        font.family: "arial"
//        text: qsTr("Industrial Automation")
//    }
    Image {
        id: title3
        anchors.top: title1.bottom
        anchors.topMargin: 85 //parent.height/3
        anchors.horizontalCenter: title1.horizontalCenter
        width: 268
        height: 40
        source: "qrc:/images/images/logo2.png"
    }
//    Text {
//        id: title4
//        anchors.left: title1.right
//        anchors.right: parent.right
//        anchors.bottom: mima.top
//        anchors.bottomMargin: 8
//        horizontalAlignment: Qt.AlignHCenter
//        color: "white"
//        font.family: "arial"
//        font.pointSize: 24
//        text: qsTr("Enter Passcode")
//    }
    Text {
        id: title4
        anchors.left: title1.right
        anchors.right: parent.right
        anchors.bottom: mima.top
        anchors.bottomMargin: 8
        horizontalAlignment: Qt.AlignHCenter
        color: "white"
        font.family: "arial"
        font.pointSize: 24
        text: qsTr("Scan or Enter ID")
    }
//    Text {
//        id: title5
//        anchors.left: title1.right
//        anchors.right: parent.right
//        anchors.bottom: title4.top
//        anchors.bottomMargin: 8
//        horizontalAlignment: Qt.AlignHCenter
//        color: "white"
//        font.family: "arial"
//        font.pointSize: 24
//        text: qsTr("Or")
//    }
//    Text {
//        id: title6
//        anchors.left: title1.right
//        anchors.right: parent.right
//        anchors.bottom: title5.top
//        anchors.bottomMargin: 8
//        horizontalAlignment: Qt.AlignHCenter
//        color: "white"
//        font.family: "arial"
//        font.pointSize: 24
//        text: qsTr("Scan ID")
//    }
    TextInput {
        id: mima
        anchors.left: title4.horizontalCenter
        anchors.leftMargin: -120
        height: 40
//        anchors.right: parent.right
        width: 250
        anchors.verticalCenter: title1.verticalCenter
        anchors.verticalCenterOffset: -100
        visible: true
        echoMode: TextInput.Password
        font.pointSize: 16
        color: "white"
        activeFocusOnPress: false
        maximumLength: 12

        onTextChanged: {
//            if (mima.text.length == 4) {
//                if (hmiAdaptor.login(mima.text))
//                    passWordInputOk()
//            }
        }

        Rectangle {
            id: backGround
            anchors.fill: parent
            border.color: "#0079c1"
            border.width: 2
            color: Qt.rgba(0,0,0,0)
        }
        verticalAlignment: Qt.AlignVCenter
    }

//    CButton {
//        width: 40
//        height: 42
//        anchors.top: mima.top
//        anchors.left: mima.right
//        onClicked: {
//            if (hmiAdaptor.login(mima.text))
//                passWordInputOk()
//        }

//    }

    Text {
        id: mimaShow
        visible: false
        anchors.left: title4.horizontalCenter
        anchors.leftMargin: -50
        anchors.right: parent.right
        anchors.verticalCenter: title1.verticalCenter
        anchors.verticalCenterOffset: -100
        font.pixelSize: 35
        height: 40
        font.family: "arial"
        color: "white"
        text: ""
        Keys.enabled: true
        Keys.onReturnPressed: {
        }
        Keys.onPressed: {
            var temp;
            if (event.key == Qt.Key_Backspace) {
                mima.remove(mima.text.length-1,mima.text.length)
                mimaShow.text = mimaShow.text.substring(0,mimaShow.text.length - 1)
            }
            if (mimaShow.text.length >= 12 )
                return
            if (event.key == Qt.Key_0) {
                mimaShow.text = mimaShow.text + "●"
                mima.text = mima.text + "0"
            }
            else if (event.key == Qt.Key_1) {
                mimaShow.text = mimaShow.text + "●"
                mima.text = mima.text + "1"
            }
            else if (event.key == Qt.Key_2) {
                mimaShow.text = mimaShow.text + "●"
                mima.text = mima.text + "2"
            }
            else if (event.key == Qt.Key_3) {
                mimaShow.text = mimaShow.text + "●"
                mima.text = mima.text + "3"
            }
            else if (event.key == Qt.Key_4) {
                mimaShow.text = mimaShow.text + "●"
                mima.text = mima.text + "4"
            }
            else if (event.key == Qt.Key_5) {
                mimaShow.text = mimaShow.text + "●"
                mima.text = mima.text + "5"
            }
            else if (event.key == Qt.Key_6) {
                mimaShow.text = mimaShow.text + "●"
                mima.text = mima.text + "6"
            }
            else if (event.key == Qt.Key_7) {
                mimaShow.text = mimaShow.text + "●"
                mima.text = mima.text + "7"
            }
            else if (event.key == Qt.Key_8) {
                mimaShow.text = mimaShow.text + "●"
                mima.text = mima.text + "8"
            }
            else if (event.key == Qt.Key_9) {
                mimaShow.text = mimaShow.text + "●"
                mima.text = mima.text + "9"
            }

        }
        Component.onCompleted: {
            forceActiveFocus()
//            mima.cursorVisible = false
        }

    }
//    Row {
//        anchors.left: mima.left
//        anchors.leftMargin: 1.5
//        anchors.verticalCenter: mima.verticalCenter
//        anchors.verticalCenterOffset: 2
//        spacing: 3
//        Rectangle {
//            radius: 100
//            width: 18
//            height: 18
//            border.color: "white"
//            border.width: 1
//            color: Qt.rgba(0,0,0,0)
//        }
//        Rectangle {
//            radius: 100
//            width: 18
//            height: 18
//            border.color: "white"
//            border.width: 1
//            color: Qt.rgba(0,0,0,0)
//        }
//        Rectangle {
//            radius: 100
//            width: 18
//            height: 18
//            border.color: "white"
//            border.width: 1
//            color: Qt.rgba(0,0,0,0)
//        }
//        Rectangle {
//            radius: 100
//            width: 18
//            height: 18
//            border.color: "white"
//            border.width: 1
//            color: Qt.rgba(0,0,0,0)
//        }

//    }

    Grid {
        anchors.horizontalCenter: title4.horizontalCenter
        anchors.top: mima.bottom
        anchors.topMargin: 10
        columnSpacing: 35
        rowSpacing: 12
        columns: 3
        Repeater {
            model: listModel
            delegate:  Image {
                id: num
                source: iconsource
                MouseArea {
                    anchors.fill: parent
                    onPressed: {
                        num.opacity = 0.5
                    }
                    onReleased: {
                        num.opacity = 1
                    }
                    onClicked: {
                        if (index == 9) {
                            mima.text = ""
                            mimaShow.text = ""
                        } else if (index == 11) {
                            if (hmiAdaptor.login(mima.text))
                                passWordInputOk()
//                            mima.remove(mima.text.length-1,mima.text.length)
//                            mimaShow.text = mimaShow.text.substring(0,mimaShow.text.length - 1)
                        } else {
                            if (mimaShow.text.length >= 12)
                                return
                            mima.text += listModel.get(index).value
                            mimaShow.text = mimaShow.text + "●"

                            if (mima.text.length == 12) {
//                                if (hmiAdaptor.login(mima.text))
//                                    passWordInputOk()
                            }
                        }
                    }
                }
            }
        }
    }


//    WebView {
//        id: webVie1;
//        anchors.fill: parent;
//        url: ("file:///d:\\test2.html");
//    }
}
