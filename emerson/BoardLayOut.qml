import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2

Item {
    id: boardLayout
    width: Screen.desktopAvailableWidth * 0.6
    height: Screen.desktopAvailableHeight*0.5
    property int columns: 0
    property int rows: 0
    property int theIndex: 0
    property int count: 0
    property string selecte: ""
    property var array: ["A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P"]
    function getStationColor(index)
    {
        var array = ["#ff6699","#ff0033","#33FFCC","#cc99ff","#cc0099","#930202","#99ccff","#f79428","#0000cc","Olive"]
        return array[index]
    }

    function setBoardLayoutColor(index,color,selecteIndex)
    {
        if (rec.itemAt(index).bIsCenterShow) {
            rec.itemAt(index).zoneModel.append({"zonecolor":color,"selecteNum":selecteIndex})
        } else {
            rec.itemAt(index).bIsCenterShow = true
            rec.itemAt(index).centerColor = color
            rec.itemAt(index).centerNum = selecteIndex
        }
    }

    Rectangle {
        anchors.top: parent.top
        anchors.left: parent.left
        width: parent.width
        height: parent.height
        color: (rows == 0 || columns == 0) ? "#6d6e71" : "white"
        Grid {
            id: layout
            visible: (rows == 0 || columns == 0) ? false : true
            anchors.fill: parent
            columns: boardLayout.columns
            rows: boardLayout.rows
            spacing: 1
            Repeater {
                id: rec
                model: layout.columns*layout.rows
                delegate:  Item {
                    property alias zoneModel: zoneRepeater.model
                    property bool bIsCenterShow: false
                    property string centerColor: ""
                    property int centerNum: 0
                    width: parent.width/layout.columns
                    height: parent.height/layout.rows
                    Rectangle {
                        anchors.fill: parent
                        color: "#6d6e71"
                        Text {
                            id: name
                            anchors.left: parent.left
                            anchors.leftMargin: 10
                            anchors.top: parent.top
                            anchors.topMargin: 6
                            color: "#b2a9b9"
                            text: boardLayout.array[index]
                            font.pointSize: 16
                            font.family: "arial"
                        }
                        Rectangle {
                            anchors.centerIn: parent
                            width: 35
                            height: 35
                            radius: 35
                            border.color: "white"
                            border.width: 1
                            color: centerColor
                            visible: bIsCenterShow
                            Text {
                                anchors.centerIn: parent
                                color: "white"
                                text: centerNum
                                font.pointSize: 16
                                font.family: "arial"
                            }
                        }
                        ListModel {
                            id: testModel
                        }
                        Repeater {
                            id: zoneRepeater
                            model: testModel
                            Rectangle {
                                anchors.top: parent.top
                                anchors.topMargin: 10
                                anchors.left: parent.left
                                anchors.leftMargin: 35+index*35+6
                                width: 35
                                height: 35
                                radius: 35
                                border.color: "white"
                                border.width: 1
                                color: testModel.get(index).zonecolor
                                Text {
                                    anchors.centerIn: parent
                                    color: "white"
                                    text: testModel.get(index).selecteNum
                                    font.pointSize: 16
                                    font.family: "arial"
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
