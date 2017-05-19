import QtQuick 2.2
import QtQuick.Dialogs 1.2
import QtQuick.Window 2.2
import QtQuick.Controls 1.1

FileDialog {
    id: fileDialog
    width: Screen.width /// 2 + 100
    height: Screen.height /// 2 + 100
    signal signalFileDialogCancel()
    signal signalChoseFile(var fileName)
    title: qsTr("Please choose a file")
    folder: shortcuts.home
    nameFilters: [ "CSV files (*.wld)" ]
    selectExisting: false
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
