import QtQuick 2.7
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.0
import QtQuick.Window 2.2

Item {
    id: myCanvas
    property alias canvasModel: listModel
    ListModel {
        id: listModel
        Component.onCompleted: {
            listModel.append({"x":0,"y":0})
            listModel.append({"x":20,"y":20})
            listModel.append({"x":40,"y":40})
            listModel.append({"x":80,"y":50})
            listModel.append({"x":115,"y":60})
            listModel.append({"x":145,"y":70})
            listModel.append({"x":170,"y":80})
            listModel.append({"x":190,"y":90})
            listModel.append({"x":205,"y":100})
            listModel.append({"x":215,"y":110})
            listModel.append({"x":210,"y":120})
            listModel.append({"x":213,"y":130})

        }
    }
    ListModel {
        id: listModelRight
        Component.onCompleted: {
            listModelRight.append({"x":canvas.width,"y":0})
            listModelRight.append({"x":canvas.width - 6,"y":20})
            listModelRight.append({"x":canvas.width - 10,"y":40})
            listModelRight.append({"x":canvas.width - 20,"y":60})
            listModelRight.append({"x":canvas.width - 25,"y":80})
            listModelRight.append({"x":canvas.width - 35,"y":100})
            listModelRight.append({"x":canvas.width - 50,"y":120})
            listModelRight.append({"x":canvas.width - 70,"y":140})
            listModelRight.append({"x":canvas.width - 100,"y":160})
            listModelRight.append({"x":canvas.width - 150,"y":180})
            listModelRight.append({"x":canvas.width - 200,"y":200})
            listModelRight.append({"x":canvas.width - 300,"y":220})

        }
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
            text: qsTr("TIME(sec)")
            font.family: "arial"

        }
        Row {
            id: bottomLineRow
            spacing: bottomLine.width / 5
            Text {
                color: "#adaeae"
                font.pixelSize: 14
                text: qsTr("0")
            }
            Text {
                text: qsTr("0.25")
                color: "#adaeae"
                font.pixelSize: 14
            }
            Text {
                text: qsTr("0.5")
                color: "#adaeae"
                font.pixelSize: 14
            }
            Text {
                text: qsTr("0.75")
                color: "#adaeae"
                font.pixelSize: 14
            }
            Text {
                text: qsTr("1.0")
                color: "#adaeae"
                font.pixelSize: 14
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
            spacing: leftLine.height / 5
            anchors.right: leftLine.left
            Text {
                color: "#adaeae"
                font.pixelSize: 14
                text: qsTr("1800")
            }
            Text {
                text: qsTr("1350")
                color: "#adaeae"
                font.pixelSize: 14
            }
            Text {
                text: qsTr("900")
                color: "#adaeae"
                font.pixelSize: 14
            }
            Text {
                text: qsTr("450")
                color: "#adaeae"
                font.pixelSize: 14
            }
            Text {
                text: qsTr("0")
                color: "#adaeae"
                font.pixelSize: 14
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
            text: qsTr("HEIGHT(mm)")
            font.family: "arial"
            anchors.right: rightLine.left
        }
        Column {
            spacing: rightLine.height / 5
            anchors.left: rightLine.right
            Text {
                color: "#adaeae"
                font.pixelSize: 14
                text: qsTr("1800")
            }
            Text {
                text: qsTr("1350")
                color: "#adaeae"
                font.pixelSize: 14
            }
            Text {
                text: qsTr("900")
                color: "#adaeae"
                font.pixelSize: 14
            }
            Text {
                text: qsTr("450")
                color: "#adaeae"
                font.pixelSize: 14
            }
            Text {
                text: qsTr("0")
                color: "#adaeae"
                font.pixelSize: 14
            }
        }
    }

    Canvas {
        id: canvas
        width: parent.width * 0.8
        height: parent.height * 0.8
        anchors.centerIn: parent
        onPaint: {
            var ctx = getContext("2d")
            ctx.lineWidth = 2
            ctx.strokeStyle = "blue"
//            ctx.fillStyle = "steelblue"
            ctx.beginPath()
            ctx.moveTo(0,0)
//            ctx.lineTo(width,0)
//            ctx.lineTo(width,height)
//            ctx.lineTo(0,height)
//            ctx.closePath()
//            ctx.stroke()
            for (var i = 0; i < listModel.count; i++)
            {
                ctx.lineTo(listModel.get(i).x,listModel.get(i).y)
            }
            ctx.stroke()
            ctx.strokeStyle = "red"
            ctx.beginPath()
            ctx.moveTo(width,0)
            for (var i = 0; i < listModelRight.count; i++)
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
