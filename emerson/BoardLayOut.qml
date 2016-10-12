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
    property var array: ["A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","p"]
    property alias listModel: rec.model

    function getStationColor(index)
    {
        var array = ["#f44242","#f4a142","#f4d742","#d1f442","#9ef442","#42f448","#42f4df","#42bcf4","#424ef4","#a442f4"]
        return array[index]
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
                model: listModel//layout.columns*layout.rows
                delegate:  Rectangle {
                    width: parent.width/layout.columns
                    height: parent.height/layout.rows
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
                        color: listModel.get(index).color1
                        visible: listModel.get(index).count > 0 ? true : false
                        Text {
                            anchors.centerIn: parent
                            color: "white"
                            text: listModel.get(index).listNum
                            font.pointSize: 16
                            font.family: "arial"
                        }
                    }
                    Repeater {
                        model: listModel.get(index).count
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
                            color: getStationColor(index)
                            Text {
                                anchors.centerIn: parent
                                color: "white"
                                text: "3"
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
