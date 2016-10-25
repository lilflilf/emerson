import QtQuick 2.7
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.0
import QtQuick.Window 2.2

Item {
    property alias exclusiveGroup: checkBox.exclusiveGroup
    property alias buttontext: buttonText.text
    property alias fontSize: buttonText.font.pixelSize
    property int checkLeftmargin: 7
    property int textOffLeftCheckBoxWidth: 20
    property bool bIsCheck: checkBox.checked
    width: parent.width
    height: parent.height

    BorderImage {
        id: backGround
        anchors.fill: parent
        source: "qrc:/images/images/check-border.png"
        border.left: 2; border.top: 2
        border.right: 2; border.bottom: 2
        visible: checkBox.checked
    }
    /*Rectangle {
                    implicitWidth: 20
                    implicitHeight: 20
                    radius: 40
                    Canvas{
                        anchors.fill: parent
                        anchors.margins: 3
                        visible: control.checked
                        onPaint: {
                            var ctx = getContext("2d")
                            ctx.save()
                            ctx.strokeStyle = "black"
                            ctx.lineWidth = 2
                            ctx.beginPath()
                            ctx.moveTo(0,height/2)
                            ctx.lineTo(width/2,height)
                            ctx.lineTo(width , 0)
                            ctx.stroke()
                            ctx.restore()
                        }
                    }
                }*/
    Component{
        id: checkStyle;
        CheckBoxStyle{
            indicator: Image {
                id: checkIcon
                source: control.checked ? "qrc:/images/images/check-click.png" : "qrc:/images/images/check-bg.png"
            }
        }
    }

    CheckBox {
        id: checkBox
        anchors.left: parent.left
        anchors.leftMargin: checkLeftmargin
        anchors.verticalCenter: parent.verticalCenter
        height: 30
        width:  30
        style: checkStyle
    }
    Text {
        id: buttonText
        anchors.left: checkBox.right
        anchors.leftMargin: textOffLeftCheckBoxWidth
        anchors.verticalCenter: parent.verticalCenter
        width: parent.width- checkBox.width - 34
        font.pixelSize: 20
        font.family: "arial"
        text: qsTr("text")
        color: "white"
    }
    MouseArea {
        anchors.fill: parent
        onClicked: {
            checkBox.checked = true
        }
    }
}
