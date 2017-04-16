import QtQuick 2.7
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.0
import QtQuick.Window 2.2

Rectangle {
    id:comboBox
    z: 10
    property var items: [
    { lang: "en", img: "" },
    { lang: "sp", img: "" },
    { lang: "fr", img: "" }
    ]
    signal comboClicked;
    property var fontColor: "#ffffff"
    property var backGroundColor: "#ffffff"
    property var dropDownColor: "#ffffff"
    property alias currentText: chosenItemText.text
//    anchors.top: pa.top;
//    anchors.topMargin: 30;
//    anchors.left: main.left;
//    anchors.leftMargin: 415;
//    width: 60;
//    height: 60;
    smooth:true
    color: backGroundColor
    Rectangle {
        id:chosenItem
        radius:4;
        width:parent.width;
        height:comboBox.height;
        smooth:true;
        color: backGroundColor
        border.color: "#1987ab"
        border.width: 2
        Image {
            id: main_img;
            fillMode: Image.PreserveAspectFit
//            source: "image/tunnel_arch.png";
            height: 100
            width:  100
        }

        Text {
            anchors.centerIn: parent;
            id:chosenItemText
            x: 11
            y: 5
            color: fontColor
            text: items[0].lang
            anchors.topMargin: 5
            anchors.left: parent.left
            anchors.leftMargin: 12
            font.family: "Arial"
            font.pointSize: 20;
            smooth:true
            visible: true;
        }

        MouseArea {
            width: 400
            height: 30
            anchors.bottomMargin: 0
            anchors.fill: parent;
            onClicked: {
                comboBox.state = comboBox.state==="dropDown"?"":"dropDown"
            }
        }
    }
    Rectangle {
        id:dropDown
        width:comboBox.width;
        height: 0;
        clip:true;
        radius:4;
        anchors.top: chosenItem.bottom;
        anchors.margins: 2;
        color: dropDownColor
        z: 10
        border.color: "#1987ab"
        border.width: 2

        ListView {
            id:listView
            height:comboBox.height * comboBox.items.length
            model: comboBox.items
            currentIndex: 0;

            delegate: Item{
                width:comboBox.width;
                height: comboBox.height;
                Image {
                    id: img3;
                    source: modelData.img;
                    fillMode: Image.PreserveAspectFit
                    anchors.fill: parent
                }

                Text {
                    text: modelData.lang
//                    anchors.top: parent.top;
//                    anchors.left: parent.left;
//                    anchors.margins: 5;
                    color: fontColor
                    font.family: "Arial"
                    font.pointSize: 20;
                    anchors.centerIn: parent

                }

                MouseArea {
                    anchors.fill: parent;
                    onClicked: {
                        comboBox.state = ""
                        chosenItemText.text = modelData.lang;
                        listView.currentIndex = index;
                        main_img.source = comboBox.items[index].img
                    }
                }
            }
        }
    }

    states: State {
        name: "dropDown";
        PropertyChanges { target: dropDown; height:comboBox.height * comboBox.items.length }
    }

    transitions: Transition {
        NumberAnimation { target: dropDown; properties: "height"; easing.type: Easing.OutExpo; duration: 1000 }
    }
}
