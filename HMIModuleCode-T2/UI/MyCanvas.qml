import QtQuick 2.7
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.0
import QtQuick.Window 2.2

Item {
    id: myCanvas
    property alias canvasModel: listModel
    ListModel {
        id: listModel
    }

    Canvas {
        id: canvas
        anchors.fill: parent
        onPaint: {
            var ctx = getContext("2d")
            ctx.lineWidth = 2
            ctx.strokeStyle = "blue"
//            ctx.fillStyle = "steelblue"
            ctx.beginPath()
            ctx.moveTo(0,0)
            ctx.lineTo(width,0)
            ctx.lineTo(width,height)
            ctx.lineTo(0,height)
//            ctx.closePath()
            ctx.stroke()
//            for (var i = 0; i < listModel.count; i++)
//            {

//            }
        }
        Component.onCompleted: {
            console.log("width ===",canvas.width,canvas.height)
        }
    }
}
