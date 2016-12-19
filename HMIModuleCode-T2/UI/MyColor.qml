import QtQuick 2.0
import QtQuick.Dialogs 1.2

Item {
    id: mycolor
    signal colorChanged(var color)
    ColorDialog {
        id: colorDialog
        title: qsTr("Please choose a color")
        width: 200
        height: 350
        onAccepted: {
            console.log("You chose: " + colorDialog.color)
            mycolor.colorChanged(colorDialog.color)
        }
        onRejected: {
            console.log("Canceled")
        }
        Component.onCompleted: visible = true
    }
}
