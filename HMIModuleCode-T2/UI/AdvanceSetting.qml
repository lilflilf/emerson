import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2

Item {
    id: advanceset
    property int currentIndex: 0
    width: parent.width
    height: parent.height

    signal advanceSettingDefalutClick()
    function setClickColor(index)
    {
        if (standardUpperRepeater.itemAt(index).localbordercolor === "#05f91c") {
            standardUpperRepeater.itemAt(index).localbordercolor = "#f79428"
        } else if (standardlowerRepeater.itemAt(index).localbordercolor == "#05f91c") {
            standardlowerRepeater.itemAt(index).localbordercolor = "#0079c1"
        } else if (sigmaUpperRepeater.itemAt(index).localbordercolor == "#05f91c") {
            sigmaUpperRepeater.itemAt(index).localbordercolor = "#f79428"
        } else if (sigmaLowerRepeater.itemAt(index).localbordercolor == "#05f91c") {
            sigmaLowerRepeater.itemAt(index).localbordercolor = "#0079c1"
        }
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
        text: qsTr("Standard& Auto")
    }
    Text {
        id: sigma
        anchors.top: parent.top
        anchors.topMargin: 26
        anchors.left: sigmaUpperrec.left
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
    Image {
        id: upper1
        anchors.top: line2.bottom
        anchors.left: standardupperrec.left
        anchors.leftMargin: -23.5
        width: 192
        height: 49
        source: "qrc:/images/images/orange.png"
        Text {
            anchors.centerIn: parent
            font.family: "arial"
            font.pixelSize: 25
            color: "white"
            text: qsTr("Upper")
        }
    }
    Image {
        id: lower1
        anchors.top: line2.bottom
        anchors.left: standardLowerrec.left
        anchors.leftMargin: -23.5
        width: 192
        height: 49
        source: "qrc:/images/images/blue.png"
        Text {
            anchors.centerIn: parent
            font.family: "arial"
            font.pixelSize: 25
            color: "white"
            text: qsTr("Lower")
        }
    }
    Image {
        id: upper2
        anchors.top: line2.bottom
        anchors.left: sigmaUpperrec.left
        anchors.leftMargin: -23.5
        width: 192
        height: 49
        source: "qrc:/images/images/orange.png"
        Text {
            anchors.centerIn: parent
            font.family: "arial"
            font.pixelSize: 25
            color: "white"
            text: qsTr("Upper")
        }
    }
    Image {
        id: lower2
        anchors.top: line2.bottom
        anchors.left: sigmaLowerrec.left
        anchors.leftMargin: -23.5
        width: 192
        height: 49
        source: "qrc:/images/images/blue.png"
        Text {
            anchors.centerIn: parent
            font.family: "arial"
            font.pixelSize: 25
            color: "white"
            text: qsTr("Lower")
        }
    }
    ListModel {
        id: listModel
        Component.onCompleted: {
            listModel.append({"head":"Time","value":"60%"})
            listModel.append({"head":"Power","value":"60%"})
            listModel.append({"head":"Pre-Height","value":"60%"})
            listModel.append({"head":"Height","value":"60%"})
        }
    }

    Grid {
        id: standardupperrec
        anchors.top: upper1.bottom
        anchors.left: parent.left
        anchors.leftMargin: 50
        width: 300
        clip: true
        anchors.bottom: line3.top
        anchors.bottomMargin: 10
        columns: 2
        rows: 2
        columnSpacing: 10
        rowSpacing: 15
        Repeater {
            id: standardUpperRepeater
            model: listModel
            delegate: Item {
                property string localbordercolor: "#f79428"
                width: 145
                height: 154
                Image {
                    anchors.fill: parent
                    source: "qrc:/images/images/advancesetting-bg1.png"
                }
                Rectangle {
                    id: backGround
                    width: 145
                    height: 145
                    border.color: localbordercolor
                    border.width: 2
                    color: Qt.rgba(0,0,0,0)
                }
                Text {
                    id: headName
                    anchors.top: parent.top
                    anchors.topMargin: 20
                    anchors.left: parent.left
                    anchors.leftMargin: 10
                    font.family: "arial"
                    font.pixelSize: 20
                    color: "white"
                    text: qsTr(head)
                }
                Text {
                    id: centerValue
                    anchors.centerIn: parent
                    font.family: "arial"
                    font.pixelSize: 25
                    color: "white"
                    text: qsTr(value)
                }
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        setClickColor(advanceset.currentIndex)
                        advanceset.currentIndex = index
                        localbordercolor = "#05f91c"
                    }
                }
            }
        }
    }

    Grid {
        id: standardLowerrec
        anchors.top: upper1.bottom
        anchors.left: standardupperrec.right
        anchors.leftMargin: 10
        width: 300
        clip: true
        anchors.bottom: line3.top
        anchors.bottomMargin: 10
        columns: 2
        rows: 2
        columnSpacing: 10
        rowSpacing: 15
        Repeater {
            id: standardlowerRepeater
            model: listModel
            delegate: Item {
                property string localbordercolor: "#0079c1"
                width: 145
                height: 154
                Image {
                    anchors.fill: parent
                    source: "qrc:/images/images/advancesetting-bg1.png"
                }
                Rectangle {
                    id: backGround2
                    width: 145
                    height: 145
                    border.color: localbordercolor
                    border.width: 2
                    color: Qt.rgba(0,0,0,0)
                }
                Text {
                    id: headName2
                    anchors.top: parent.top
                    anchors.topMargin: 20
                    anchors.left: parent.left
                    anchors.leftMargin: 10
                    font.family: "arial"
                    font.pixelSize: 20
                    color: "white"
                    text: qsTr(head)
                }
                Text {
                    id: centerValue2
                    anchors.centerIn: parent
                    font.family: "arial"
                    font.pixelSize: 25
                    color: "white"
                    text: qsTr(value)
                }
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        setClickColor(advanceset.currentIndex)
                        advanceset.currentIndex = index
                        localbordercolor = "#05f91c"
                    }
                }
            }
        }
    }

    Grid {
        id: sigmaUpperrec
        anchors.top: upper1.bottom
        anchors.right: sigmaLowerrec.left
        anchors.rightMargin: 10
        width: 300
        clip: true
        anchors.bottom: line3.top
        anchors.bottomMargin: 10
        columns: 2
        rows: 2
        columnSpacing: 10
        rowSpacing: 15
        Repeater {
            id: sigmaUpperRepeater
            model: listModel
            delegate: Item {
                property string localbordercolor: "#f79428"
                width: 145
                height: 154
                Image {
                    anchors.fill: parent
                    source: "qrc:/images/images/advancesetting-bg1.png"
                }
                Rectangle {
                    id: backGround3
                    width: 145
                    height: 145
                    border.color: localbordercolor
                    border.width: 2
                    color: Qt.rgba(0,0,0,0)
                }
                Text {
                    id: headName3
                    anchors.top: parent.top
                    anchors.topMargin: 20
                    anchors.left: parent.left
                    anchors.leftMargin: 10
                    font.family: "arial"
                    font.pixelSize: 20
                    color: "white"
                    text: qsTr(head)
                }
                Text {
                    id: centerValue3
                    anchors.centerIn: parent
                    font.family: "arial"
                    font.pixelSize: 25
                    color: "white"
                    text: qsTr(value)
                }
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        setClickColor(advanceset.currentIndex)
                        advanceset.currentIndex = index
                        localbordercolor = "#05f91c"
                    }
                }
            }
        }
    }

    Grid {
        id: sigmaLowerrec
        anchors.top: upper1.bottom
        anchors.right: parent.right
        anchors.rightMargin: 50
        width: 300
        clip: true
        anchors.bottom: line3.top
        anchors.bottomMargin: 10
        columns: 2
        rows: 2
        columnSpacing: 10
        rowSpacing: 15
        Repeater {
            id: sigmaLowerRepeater
            model: listModel
            delegate: Item {
                property string localbordercolor: "#0079c1"
                width: 145
                height: 154
                Image {
                    anchors.fill: parent
                    source: "qrc:/images/images/advancesetting-bg1.png"
                }
                Rectangle {
                    id: backGround4
                    width: 145
                    height: 145
                    border.color: localbordercolor
                    border.width: 2
                    color: Qt.rgba(0,0,0,0)
                }
                Text {
                    id: headName4
                    anchors.top: parent.top
                    anchors.topMargin: 20
                    anchors.left: parent.left
                    anchors.leftMargin: 10
                    font.family: "arial"
                    font.pixelSize: 20
                    color: "white"
                    text: qsTr(head)
                }
                Text {
                    id: centerValue4
                    anchors.centerIn: parent
                    font.family: "arial"
                    font.pixelSize: 25
                    color: "white"
                    text: qsTr(value)
                }
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        setClickColor(advanceset.currentIndex)
                        advanceset.currentIndex = index
                        localbordercolor = "#05f91c"
                    }
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
        anchors.bottomMargin: 157
        anchors.left: parent.left
        anchors.leftMargin: 20
        width: parent.width-40
        height: 1
        lineColor: "#0d0f11"
    }
    CButton {
        id: okButton
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 44
        anchors.right: parent.right
        anchors.rightMargin: 20
        width: 300
        height: 79
        iconSource: "qrc:/images/images/OK.png"
        text: qsTr("OK")
        textColor: "white"
    }
    CButton {
        id: cacelButton
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 44
        anchors.right: okButton.left
        anchors.rightMargin: 20
        width: 300
        height: 79
        iconSource: "qrc:/images/images/cancel.png"
        text: qsTr("Cancel")
        textColor: "white"
    }
    CButton {
        id: defaultButton
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 44
        anchors.right: cacelButton.left
        anchors.rightMargin: 20
        width: 300
        height: 79
        text: qsTr("Defalut Setting")
        textColor: "white"
        onClicked: {
            advanceSettingDefalutClick()
        }
    }
}
