import QtQuick 2.2
import QtQuick.Dialogs 1.2
import QtQuick.Window 2.2
import QtQuick.Controls 1.4

Item {
    width: Screen.desktopAvailableWidth / 2
    height: Screen.desktopAvailableHeight / 2
    FileDialog {
        id: fileDialog
        title: "Please choose a file"
        folder: shortcuts.home
        onAccepted: {
            console.log("You chose: " + fileDialog.fileUrls)
        }
        onRejected: {
            console.log("Canceled")
        }
        Component.onCompleted: visible = true
    }
}
