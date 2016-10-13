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
        var i;
        for ( i = 0; i < boardLayout.columns*boardLayout.rows; i++) {
            if (selecteIndex == rec.itemAt(i).centerNum) {
                rec.itemAt(i).bIsCenterShow = false
                break
            }
            if (rec.itemAt(i).zoneModel.count != 0) {
                for (var j = 0; j < rec.itemAt(i).zoneModel.count; j++) {
                    if (selecteIndex == rec.itemAt(i).zoneModel.get(j).selecteNum) {
                        rec.itemAt(i).zoneModel.remove(j)
                        break
                    }
                }
            }
        }

        if (rec.itemAt(index).centerNum == selecteIndex) {
            rec.itemAt(index).centerColor = color
            return
        }
        for (var i = 0; i < rec.itemAt(index).zoneModel.count; i++) {
            if (rec.itemAt(index).zoneModel.get(i).selecteNum == selecteIndex) {
                rec.itemAt(index).zoneModel.remove(i);
                rec.itemAt(index).zoneModel.insert(i,{"zonecolor":color,"selecteNum":selecteIndex})
                return
            }
        }

        if (rec.itemAt(index).bIsCenterShow) {
            rec.itemAt(index).zoneModel.append({"zonecolor":color,"selecteNum":selecteIndex})
        } else {
            rec.itemAt(index).bIsCenterShow = true
            rec.itemAt(index).centerColor = color
            rec.itemAt(index).centerNum = selecteIndex
        }
    }
    function setBoardLayoutYPosition(index)
    {
        if (index < 5) {
            return 2
        } else {
            return boardLayout.height/boardLayout.rows-37
        }
    }

    function setBoardLayoutXPosition(index)
    {
        if (index < 5) {
            return 34+index*(boardLayout.width/boardLayout.columns/5 - 10)
        } else {
            return 5+(index-5)*(boardLayout.width/boardLayout.columns/5 - 10)
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
                            text: qsTr(boardLayout.array[index])
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
                                anchors.topMargin: setBoardLayoutYPosition(index)
                                anchors.left: parent.left
                                anchors.leftMargin: setBoardLayoutXPosition(index)//35+index*35+6
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
