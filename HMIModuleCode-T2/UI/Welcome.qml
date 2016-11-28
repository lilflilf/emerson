import QtQuick 2.7
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.0
import QtQuick.Controls 1.3
import QtQuick.Window 2.2

Item {
    signal passWordInputOk()
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
            listModel.append({"iconsource":"qrc:/images/images/keydel.png","value":"."})
        }

    }

    Image {
        anchors.fill: parent
        source: "qrc:/images/images/loginbackground.png"
    }
    Image {
        id: title1
        source: "qrc:/images/images/logo.png"
        anchors.top: parent.top
        anchors.topMargin: parent.height/3
        anchors.left: parent.left
        anchors.leftMargin: parent.width/4
        width: 271
        height: 115
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
    Text {
        id: title2
        anchors.horizontalCenter: title1.horizontalCenter
        anchors.top: title1.bottom
        font.pointSize: 26
        color: "white"
        font.family: "arial"
        text: qsTr("Industrial Automation")
    }
    Text {
        id: title3
        anchors.bottom: parent.bottom
        anchors.bottomMargin: parent.height/3
        anchors.left: parent.left
        anchors.leftMargin: parent.width/4
        font.pointSize: 40
        color: "white"
        font.family: "arial"
        text: qsTr("BRANSON")
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
        anchors.leftMargin: -50
        anchors.right: parent.right
//        horizontalAlignment: Qt.AlignHCenter
        anchors.verticalCenter: title1.verticalCenter
        anchors.verticalCenterOffset: -50
        maximumLength: 4
        font.pixelSize: 35
        height: 40
        font.family: "arial"
        color: "white"
        text: qsTr("")
        echoMode: TextInput.Password
    }
    Row {
        anchors.left: mima.left
        anchors.leftMargin: 1.5
        anchors.verticalCenter: mima.verticalCenter
        anchors.verticalCenterOffset: 2
        spacing: 3
        Rectangle {
            radius: 100
            width: 18
            height: 18
            border.color: "white"
            border.width: 1
            color: Qt.rgba(0,0,0,0)
        }
        Rectangle {
            radius: 100
            width: 18
            height: 18
            border.color: "white"
            border.width: 1
            color: Qt.rgba(0,0,0,0)
        }
        Rectangle {
            radius: 100
            width: 18
            height: 18
            border.color: "white"
            border.width: 1
            color: Qt.rgba(0,0,0,0)
        }
        Rectangle {
            radius: 100
            width: 18
            height: 18
            border.color: "white"
            border.width: 1
            color: Qt.rgba(0,0,0,0)
        }

    }

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
                        } else if (index == 11) {
                            mima.remove(mima.text.length-1,mima.text.length)
                        } else {
                            mima.text += listModel.get(index).value
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
}
