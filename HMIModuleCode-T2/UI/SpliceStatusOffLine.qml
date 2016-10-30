import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import QtQuick.Window 2.2
import QtQuick.Controls 1.4

Item {
    property alias listModel: recRepeater.model
    width: parent.width
    height: parent.height
    function setRecColor(index)
    {
        if (index == 0) {
            return "#00aa7e"
        } else if (index == 1) {
            return "#00afe9"
        } else {
            return "#9FA1A4"
        }
    }
    function setSatusOffLineNum(index)
    {
        listModel.remove(0)
        listModel.append({"theNo":index})
    }


    Row{
        width: parent.width
        height: parent.height
        spacing: 10
        Repeater {
            id: recRepeater
            delegate: Item {
                width: (parent.width-60)/8
                height: parent.height
                Rectangle {
                    anchors.fill: parent
                    color: setRecColor(index)
                }
                Text {
                    id: num
                    anchors.centerIn: parent
                    font.family: "arial"
                    font.pixelSize: 24
                    text: theNo
                    color: "white"
                }
            }
        }
    }
}
