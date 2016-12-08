import QtQuick 2.2
import QtQuick.Dialogs 1.2
import QtQuick.Window 2.2
import QtQuick.Controls 1.4

FileDialog {
    id: fileDialog
    width: Screen.width / 2
    height: Screen.height / 2
    signal signalFileDialogCancel()
    signal signalChoseFile(var fileName)
    title: "Please choose a file"
    folder: shortcuts.home
    nameFilters: [ "Image files (*.jpg *.png)", "All files (*)" ]

    onAccepted: {
        console.log("You chose: " + fileDialog.fileUrls)
        signalChoseFile(fileDialog.fileUrls)
    }
    onRejected: {
        console.log("Canceled")
        signalFileDialogCancel()
    }
    Component.onCompleted: visible = true
}

