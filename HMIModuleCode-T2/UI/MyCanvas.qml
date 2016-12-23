import QtQuick 2.7
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.0
import QtQuick.Window 2.2

Item {
    id: myCanvas
    property alias canvasModel: listModel
    property var timeMax: 0
    property var powerMax: 0
    property var heightMax: 0
    Connections {
        target: hmiAdaptor
        onSignalWeldCycleCompleted: {
            if (result)
            {
                setPoint()
            }
        }
    }

    function setPoint()
    {
        timeMax = alarmModel.getAxes("Time") * 1.1
        powerMax = alarmModel.getAxes("Power") * 1.1
        heightMax = alarmModel.getAxes("Post-Height") * 1.1
        leftRepeater.model = 0
        rightRepeater.model = 0
        bottomRepeater.model = 0
        leftRepeater.model = 10
        rightRepeater.model = 10
        bottomRepeater.model = 10
        var powerList = new Array;
        var heightList = new Array;
        var pointx
        var pointy
        var i
        powerList = alarmModel.getPoint()
        pointx = canvas.width / timeMax;
        pointy = canvas.height / powerMax
        for (i = 0; i < powerList.length; i++)
        {
            listModel.append({"x":i * pointx,"y":canvas.height - powerList[i] * pointy})
        }
        heightList = alarmModel.getPoint2()
        pointy = canvas.height / heightMax
        for (i = 0; i < heightList.length; i++)
        {
            listModelRight.append({"x":i * pointx,"y":canvas.height - heightList[i] * pointy})
        }
    }

    ListModel {
        id: listModel
//        Component.onCompleted: {
//            var list = new Array;
//            list = hmiAdaptor.getPoint()
//            var pointx = canvas.width / 600;
//            var pointy = canvas.height / 700
//            for (var i = 0; i < list.length; i++)
//            {
//                listModel.append({"x":i * pointx,"y":canvas.height - list[i] * pointy})
//            }
//        }
    }
    ListModel {
        id: listModelRight
    }
    Line {
        id: bottomLine
        height: 1
        width: parent.width - 40
        lineColor: "white"
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.leftMargin: 20
        Text {
            anchors.top: bottomLineRow.bottom
            anchors.topMargin: 5
            color: "white"
            font.pointSize: 12
            text: qsTr("TIME(msec)")
            font.family: "arial"

        }
        Row {
            id: bottomLineRow
            width: parent.width + 100
            Repeater {
                id: bottomRepeater
                model: 10
                delegate: Text {
                    width: bottomLine.width / 10
                    color: "#adaeae"
                    font.pixelSize: 14
                    text: index / 10 * myCanvas.timeMax //index * 100
                    horizontalAlignment: Qt.AlignLeft
                }
            }
        }
    }
    Line {
        id: leftLine
        height: parent.height
        width: 1
        lineColor: "white"
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.leftMargin: 20
        Column {
            height: parent.height + 100
            anchors.right: leftLine.left
            Repeater {
                id: leftRepeater
                model: 10
                delegate: Text {
                    height: leftLine.height / 10
                    color: "#adaeae"
                    font.pixelSize: 14
                    text: (10 - index) / 10 * myCanvas.powerMax  //(7 - index) * 100
                    verticalAlignment: Qt.AlignTop
                }
            }
        }
        Text {
            anchors.bottom: leftLine.top
            anchors.bottomMargin: 5
            color: "white"
            font.pointSize: 12
            text: qsTr("POWER(W)")
            font.family: "arial"
        }
    }
    Line {
        id: rightLine
        height: parent.height
        width: 1
        lineColor: "white"
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        anchors.rightMargin: 20
        Text {
            anchors.bottom: rightLine.top
            anchors.bottomMargin: 5
            color: "white"
            font.pointSize: 12
            text: qsTr("POST-HEIGHT(mm)")
            font.family: "arial"
            anchors.right: rightLine.left
        }
        Column {
            height: parent.height + 100
            anchors.left: rightLine.right
            Repeater {
                id: rightRepeater
                model: 10
                delegate: Text {
                    height: rightLine.height / 10
                    color: "#adaeae"
                    font.pixelSize: 14
                    text: (10 - index) / 10 * myCanvas.heightMax //(7 - index) * 100
                    verticalAlignment: Qt.AlignTop
                }
            }
        }
    }

    Canvas {
        id: canvas
        anchors.left: leftLine.right
        anchors.right: rightLine.left
        anchors.bottom: bottomLine.bottom
        anchors.top: parent.top
        onPaint: {
            var i
            var ctx = getContext("2d")
            ctx.lineWidth = 2
            ctx.strokeStyle = "lightblue"
//            ctx.fillStyle = "steelblue"
            ctx.beginPath()
            if (listModel.count > 0)
                ctx.moveTo(listModel.get(0).x,listModel.get(0).y)
//            ctx.lineTo(width,0)
//            ctx.lineTo(width,height)
//            ctx.lineTo(0,height)
//            ctx.closePath()
//            ctx.stroke()
            for (i = 0; i < listModel.count; i++)
            {
                ctx.lineTo(listModel.get(i).x,listModel.get(i).y)
            }
            ctx.stroke()
            ctx.strokeStyle = "red"
            ctx.beginPath()
            if (listModelRight.count > 0)
                ctx.moveTo(listModelRight.get(0).x,listModelRight.get(0).y)
            for (i = 0; i < listModelRight.count; i++)
            {
                ctx.lineTo(listModelRight.get(i).x,listModelRight.get(i).y)
            }
            ctx.stroke()

        }
        Component.onCompleted: {
            console.log("width ===",canvas.width,canvas.height)
        }
    }
}
