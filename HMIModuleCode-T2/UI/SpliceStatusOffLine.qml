import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import QtQuick.Window 2.2
import QtQuick.Controls 1.4

Item {
    id: offLine
    property alias listModel: recRepeater.model
    property int maxNum: 0
    width: parent.width
    height: parent.height

    function offLineInit()
    {
        var count = offLine.maxNum
        if (offLine.maxNum > 8)
            count = 8
        for (var i = 0; i < count; i++) {
            if (i == 0) {
                recRepeater.itemAt(i).recColor = "#00aa7e"
            } else if (i == 1) {
                recRepeater.itemAt(i).recColor = "#00afe9"
            } else {
                recRepeater.itemAt(i).recColor = "#9fa1a4"
            }
            recRepeater.itemAt(i).numIndex = i+1
        }
    }

    function setStusOffLineBack(index)
    {

        console.log("setStusOffLineBack",index)
        if (index + 7 > maxNum) {
            var count2 = offLine.maxNum
            if (offLine.maxNum > 8)
                count2 = 8
            for (var i = 0; i < count2; i++) {
                if (recRepeater.itemAt(i).numIndex == (index ))
                    recRepeater.itemAt(i).recColor = "#00aa7e"
                else if (recRepeater.itemAt(i).numIndex == (index + 1))
                    recRepeater.itemAt(i).recColor = "#00afe9"
                else if (recRepeater.itemAt(i).numIndex == (index + 2))
                    recRepeater.itemAt(i).recColor = "#9fa1a4"
            }
        } else {
            if (index == 1) {
                offLineInit()
            } else {
                var count = offLine.maxNum
                if (offLine.maxNum > 8)
                    count = 8
                for (var i = 0; i < count; i++) {
                    recRepeater.itemAt(i).numIndex = index-1+i
                }
            }
        }
    }

    function setStusOffLineUpdate(index)
    {
        console.log("setStusOffLineUpdate",index)
        if (index + 7 > maxNum) {
            var count2 = offLine.maxNum
            if (offLine.maxNum > 8)
                count2 = 8
            for (var i = 0; i < count2; i++) {
                if (recRepeater.itemAt(i).numIndex == (index - 1))
                    recRepeater.itemAt(i).recColor = "#60bb46"
                else if (recRepeater.itemAt(i).numIndex == index)
                    recRepeater.itemAt(i).recColor = "#00aa7e"
                else if (recRepeater.itemAt(i).numIndex == (index + 1))
                    recRepeater.itemAt(i).recColor = "#00afe9"
            }
        } else {
            if (index == 1) {
                offLineInit()
            } else {
                var count = offLine.maxNum
                if (offLine.maxNum > 8)
                    count = 8
                for (var i = 0; i < count; i++) {
                    recRepeater.itemAt(i).numIndex = index+i
                }
            }
        }
    }

    function setSatusOffLineOver(index)
    {
        console.log("setSatusOffLineOver",index)
        if (index + 7 > maxNum) {
            var count2 = offLine.maxNum
            if (offLine.maxNum > 8)
                count2 = 8
            for (var i = 0; i < count2; i++) {
                if (recRepeater.itemAt(i).numIndex == (index - 1))
                    recRepeater.itemAt(i).recColor = "#d31145"
                else if (recRepeater.itemAt(i).numIndex == index)
                    recRepeater.itemAt(i).recColor = "#00aa7e"
                else if (recRepeater.itemAt(i).numIndex == (index + 1))
                    recRepeater.itemAt(i).recColor = "#00afe9"
            }
        } else {
            if (index == 1) {
                offLineInit()
            } else {
                var count = offLine.maxNum
                if (offLine.maxNum > 8)
                    count = 8
                for (var i = 0; i < count; i++) {
                    recRepeater.itemAt(i).numIndex = index+i
                }
            }
        }
    }


    Row{
        width: parent.width
        height: parent.height
        spacing: 10
        Repeater {
            id: recRepeater
            delegate: Item {
                property string recColor: "#00aa7e"
                property int numIndex: 1
                width: (parent.width-60)/8
                height: parent.height
                Rectangle {
                    id: rec
                    anchors.fill: parent
                    color: recColor
                }
                Text {
                    id: num
                    anchors.centerIn: parent
                    font.family: "arial"
                    font.pixelSize: 24
                    text: numIndex
                    color: "white"
                }
            }
        }
    }
}
