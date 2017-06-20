/*******************************************************************
Copyright:http://www.sinux.com.cn
Date:2016/12/26
Author:zhangjiyong&lilongfei
Description: This is boardLayout components,arrayColor is the initial color
The function interface:
    spliceModelUpdata() //boardLayout updata signal
    checkBoardLayout()
    reSetBoardLayoutColor()
    reSetBoardLayoutStation()
    clearBoardLayout()
    setBoardLayoutYPosition()
    setBoardLayoutXPosition()
*******************************************************************/
import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2

Item {
    id: boardLayout
    width: parent.width
    height: parent.height
    property int columns: 0
    property int rows: 0
    property int count: 0
    property int maxSplicePerWork: 0
    property int maxSplicePerZone: 0
    property string selecte: ""
    property var array: ["A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P"]
    property variant arrayColor: ["#ff6699","#ff0033","#33FFCC","#cc99ff","#cc0099","#930202","#99ccff","#f79428",
        "#0000cc","Olive","#ffff33","#ffcc00","#cc9909","#66ff00","#009900","#00cc66","#3366ff","#cc33cc","#cc9966","#9400D3"]
    signal spliceModelUpdata(int index,string color)

    function checkBoardLayout(index,color,selecteIndex)
    {
        var maxSplicePerWork = 0,maxSplicePerZone = 0
        maxSplicePerZone = rec.itemAt(index).zoneModel.count
        if (rec.itemAt(index).bIsCenterShow) {
            ++maxSplicePerZone
        }
        var i
        for (i = 0; i < boardLayout.columns*boardLayout.rows; i++) {
            if (rec.itemAt(i).zoneModel.count != 0) {

                for (var j = 0; j < rec.itemAt(i).zoneModel.count; j++) {
                    if (color == rec.itemAt(i).zoneModel.get(j).zonecolor) {
                        ++maxSplicePerWork
                    }
                }
            }
            if (rec.itemAt(i).bIsCenterShow) {
                if (rec.itemAt(i).centerColor == color) {
                    ++maxSplicePerWork
                }
            }
        }
        if (maxSplicePerWork == boardLayout.maxSplicePerWork) {
                return -1;
        }
        if (maxSplicePerZone == boardLayout.maxSplicePerZone) {
            return -1;
        }
        return 0
    }

    function setBoardLayoutColor(bIsInsert,index,color,selecteIndex)
    {
        if (!bIsInsert) {
            if (checkBoardLayout(index,color,selecteIndex) == -1)
                return -1
        }
        var i;
        for ( i = 0; i < boardLayout.columns*boardLayout.rows; i++) {
            if (selecteIndex == rec.itemAt(i).centerNum && rec.itemAt(i).bIsCenterShow) {
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
        if (rec.itemAt(index).centerNum == selecteIndex && rec.itemAt(index).bIsCenterShow) {
            rec.itemAt(index).centerColor = color
            rec.itemAt(index).bIsCenterShow = true
            return 0
        }
        for (var i = 0; i < rec.itemAt(index).zoneModel.count; i++) {
            if (rec.itemAt(index).zoneModel.get(i).selecteNum == selecteIndex) {
                rec.itemAt(index).zoneModel.remove(i);
                rec.itemAt(index).zoneModel.insert(i,{"zonecolor":color,"selecteNum":selecteIndex})
                return 0
            }
        }
        if (bIsInsert) {
            if (checkBoardLayout(index,color,selecteIndex) == -1)
                return -1
        }
        if (rec.itemAt(index).bIsCenterShow) {
            rec.itemAt(index).zoneModel.append({"zonecolor":color,"selecteNum":selecteIndex})
        } else {
            rec.itemAt(index).bIsCenterShow = true
            rec.itemAt(index).centerColor = color
            rec.itemAt(index).centerNum = selecteIndex
        }
        return 0
    }
    function reSetBoardLayoutColor(maxSplicePerWork,WorkNum)
    {
        var i,k
        for (k = 0; k < WorkNum; k++) {
            var splicePerWork = 0
            for (i = 0; i < boardLayout.columns*boardLayout.rows; i++) {
                if (rec.itemAt(i).zoneModel.count != 0) {
                    for (var j = 0; j < rec.itemAt(i).zoneModel.count; j++) {
                        if (arrayColor[k] == rec.itemAt(i).zoneModel.get(j).zonecolor) {
                            ++splicePerWork
                            if (splicePerWork > maxSplicePerWork) {
                                rec.itemAt(i).zoneModel.remove(j)
                                spliceModelUpdata(rec.itemAt(i).zoneModel.get(j).selecteNum,arrayColor[k])
                            }
                        }
                    }
                }
                if (rec.itemAt(i).bIsCenterShow) {
                    if (rec.itemAt(i).centerColor == arrayColor[k]) {
                        ++splicePerWork
                        if (splicePerWork > maxSplicePerWork) {
                            rec.itemAt(i).bIsCenterShow = false
                            spliceModelUpdata(rec.itemAt(i).centerNum,arrayColor[k])
                        }
                    }
                }
            }
        }
    }
    function reSetBoardLayoutStation(maxSplicePerZone)
    {
        var i
        for (i = 0; i < boardLayout.columns*boardLayout.rows; i++) {
            var splicePerZone = 0
            splicePerZone = rec.itemAt(i).zoneModel.count
            if (rec.itemAt(i).bIsCenterShow) {
                maxSplicePerZone -= 1
            }
            if (splicePerZone > maxSplicePerZone) {
                for (var j = maxSplicePerZone; j < splicePerZone; j++) {
                    spliceModelUpdata(rec.itemAt(i).zoneModel.get(j).selecteNum,rec.itemAt(i).zoneModel.get(j).zonecolor)
                    rec.itemAt(i).zoneModel.remove(j)
                }
            }
        }
    }

    function clearBoardLayout()
    {
        var i
        for (i = 0; i < boardLayout.columns*boardLayout.rows; i++) {
            if (rec.itemAt(i).zoneModel.count != 0) {
                for (var j = 0; j < rec.itemAt(i).zoneModel.count; j++) {
                    rec.itemAt(i).zoneModel.remove(j)
                }
            }
            if (rec.itemAt(i).bIsCenterShow) {
                rec.itemAt(i).bIsCenterShow = false
            }
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
                    property var centerRec: centerWork
                    width: (parent.width-layout.columns+1)/layout.columns
                    height: (parent.height-layout.rows+1)/layout.rows
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
                            id: centerWork
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

//                            MouseArea {
//                                id: dragArea
//                                anchors.fill: parent
//                                drag.target: parent
//                                drag.axis: Drag.XAxis; drag.minimumX: 1; drag.maximumX: 200
//                                onClicked: {
//                                }
//                            }
                        }
                        ListModel {
                            id: testModel
                        }
                        Repeater {
                            id: zoneRepeater
                            model: testModel
                            property string zonecolor: ""
                            property string selecteNum: ""
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
                                color: zonecolor
                                Text {
                                    anchors.centerIn: parent
                                    color: "white"
                                    text: selecteNum
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
