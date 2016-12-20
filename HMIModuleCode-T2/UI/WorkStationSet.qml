import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2


Item {
    id: workSationSet
    width: parent.width
    height: parent.height
    property variant array: ["#ff6699","#ff0033","#33FFCC","#cc99ff","#cc0099","#930202","#99ccff","#f79428",
        "#0000cc","Olive","#ffff33","#ffcc00","#cc9909","#66ff00","#009900","#00cc66","#3366ff","#cc33cc","#cc9966","#9400D3"]
    property var array2: ["A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P"]
    property int allWorkTotal: 0
    property int allZoneTotal: 0
    property int index: 0
    property int selecteIndex: 0
    property string selecteZone: ""
    property string selecteColor: ""
    onSelecteColorChanged: {
        if (selecteColor == "") {
            colorReapeter.itemAt(colorSation.num).bIsShow = false
        }
    }
    onSelecteZoneChanged: {
        if (selecteZone == "") {
            zoneRepeater.itemAt(zone.num).bIsShow = false
        }
    }
    Rectangle {
        anchors.top: parent.top
        width: parent.width
        height: parent.height
        color: "#48484A"
        Text {
            id: tips
            anchors.top: parent.top
            anchors.topMargin: 8
            anchors.left: parent.left
            anchors.leftMargin: 6
            color: "white"
            opacity: 0.5
            font.pointSize: 16
            font.family: "arial"
            text: qsTr("Work Station")
        }
        Grid {
            id: colorSation
            property int num: -1
            anchors.top: tips.bottom
            anchors.topMargin: 10
            anchors.left: parent.left
            anchors.leftMargin: 6
            clip: true
            spacing: 20
            rows: allWorkTotal > 10 ? 2 : 1
            columns: 10
            Repeater {
                id: colorReapeter
                model: allWorkTotal
                delegate: Item {
                    property bool bIsShow: false
                    width: 35
                    height: 35
                    Rectangle {
                        id: backGround
                        anchors.fill: parent
                        border.color: "white"
                        border.width: 1
                        color: "#48484A"
                        visible: bIsShow
                    }
                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            if (colorSation.num == -1) {
                                colorSation.num = index
                            } else {
                                colorReapeter.itemAt(colorSation.num).bIsShow = false
                                colorSation.num = index
                            }
                            colorReapeter.itemAt(colorSation.num).bIsShow = true
                            selecteColor = array[index]
                        }
                    }
                    Rectangle {
                        anchors.centerIn: parent
                        width: parent.width - 6
                        height: parent.height - 6
                        color: array[index]
                    }
                }
            }
        }

        Text {
            id: zoneTips
            anchors.top: colorSation.bottom
            anchors.topMargin: 12
            anchors.left: parent.left
            anchors.leftMargin: 6
            color: "white"
            opacity: 0.5
            font.pointSize: 16
            font.family: "arial"
            text: "Zone"
        }
        Grid {
            id: zone
            property int num: -1
            anchors.top: zoneTips.bottom
            anchors.topMargin: 10
            anchors.left: parent.left
            anchors.leftMargin: 8
            spacing: 20
            clip: true
            rows: allZoneTotal > 10 ? 2 : 1
            columns: 10
            Repeater {
                id: zoneRepeater
                model: allZoneTotal
                delegate: Item {
                    width: 35
                    height: 35
                    property bool bIsShow: false
                    Rectangle {
                        id: background
                        anchors.fill: parent
                        border.color: "white"
                        border.width: 1
                        color: "#48484A"
                        visible: bIsShow
                    }
                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            if (zone.num == -1) {
                                zone.num = index
                            } else {
                                zoneRepeater.itemAt(zone.num).bIsShow = false
                                zone.num = index
                            }
                            selecteIndex = index
                            zoneRepeater.itemAt(zone.num).bIsShow = true
                            selecteZone = array2[index]
                        }
                    }
                    Text {
                        text: array2[index]
                        color: "white"
                        anchors.centerIn: parent
                        font.pointSize: 16
                        font.family: "arial"
                    }
                }
            }
        }
    }
}
