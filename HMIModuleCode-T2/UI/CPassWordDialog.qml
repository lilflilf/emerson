/*******************************************************************
Copyright:http://www.sinux.com.cn
Date:2016/12/26
Author:zhangjiyong&lilongfei
Description: password dialog component,data is from listModel
The function interface:
    hmiAdaptor.login()
    mainRoot.menuInit()
*******************************************************************/
import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2

Item {
    id: passwdDialog
    width: Screen.width
    height: Screen.height
    property int index: -1
    property var pageName: ""
    Connections {
        target: hmiAdaptor
        onSignalPhysicalKeyMessage: {
            title.text = qsTr("Scan or Enter ID(Please insert physicalkey)")
            itemChange.start()
        }
    }
    Timer {
        id: itemChange
        interval: 5000
        repeat: false
        triggeredOnStart: false;
        onTriggered: {
            title.text = qsTr("Scan or Enter ID")
        }
    }

//    NumberAnimation {
//        id: itemChange
//        target: itemTip
//        to: 0
//        property: "opacity"
//        duration: 5000
//        easing.type: Easing.InOutQuad
//    }

    Rectangle {
        id: backGround
        anchors.fill: parent
        color: "black"
        opacity: 0.5
        MouseArea {
            anchors.fill: parent
            onClicked: {
            }
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
        }

    }
    Image {
        anchors.top: parent.top
        anchors.topMargin: (parent.height-600)/2+25
        anchors.left: parent.left
        anchors.leftMargin: (parent.width - 800)/2
        width: 800
        height: 600
        source: "qrc:/images/images/dialogbg.png"

        Text {
            id: title
            anchors.top: parent.top
            anchors.topMargin: 20
            anchors.horizontalCenter: parent.horizontalCenter
            color: "white"
            font.family: "arial"
            font.pointSize: 24
            text: qsTr("Scan or Enter ID")
        }
        TextInput {
            id: mima
            anchors.top: title.bottom
            anchors.topMargin: 10
            anchors.horizontalCenter: title.horizontalCenter
            visible: true
            height: 40
            width: 250
            echoMode: TextInput.Password
            font.pointSize: 16
            color: "white"
            verticalAlignment: Qt.AlignVCenter
            maximumLength: 12
            Rectangle {
                anchors.fill: parent
                color: Qt.rgba(0,0,0,0)
                border.color: "#0079c1"
                border.width: 2
            }
        }

        Text {
            id: mimaShow
            anchors.top: title.bottom
            anchors.left: mimaShow2.left
            anchors.leftMargin: -1.5
            font.pixelSize: 35
            height: 40
            font.family: "arial"
            color: "white"
            text: ""
            visible: false
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
            }
        }
        Row {
            id: mimaShow2
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: mimaShow.verticalCenter
            anchors.verticalCenterOffset: 2
            spacing: 3
            visible: false
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
            anchors.horizontalCenter: title.horizontalCenter
            anchors.top: mima.bottom
            anchors.topMargin: 10
            columnSpacing: 30
            rowSpacing: 8
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
                                if (hmiAdaptor.borrowLogin(mima.text,pageName)) {
                                    if (pageName == "Teach Mode") {
                                        mimaShow.text = ""
                                        mima.text = ""
                                        passwdDialog.visible = false
                                    } else {
                                        mainRoot.menuInit(passwdDialog.index)
                                        mimaShow.text = ""
                                        mima.text = ""
                                        passwdDialog.visible = false
                                    }
                                }
//                                mima.remove(mima.text.length-1,mima.text.length)
//                                mimaShow.text = mimaShow.text.substring(0,mimaShow.text.length - 1)
                            } else {
                                if (mimaShow.text.length >= 12)
                                    return
                                mimaShow.text = mimaShow.text + "●"
                                mima.text += listModel.get(index).value
                            }
                        }
                    }
                }
            }
        }

        CButton {
            id: cancelButton
            anchors.right: parent.right
            anchors.rightMargin: 20
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 20
            width: 200
            pointSize: 16
            iconSource: "qrc:/images/images/cancel.png"
            text: qsTr("CANCEL")
            onClicked: {
                passwdDialog.visible = false
                mima.text = ""
                mimaShow.text = ""
            }
        }
    }
}
