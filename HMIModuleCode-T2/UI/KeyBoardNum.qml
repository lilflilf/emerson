import QtQuick 2.7
import QtQuick.Layouts 1.0
import QtQuick.Window 2.2
import QtQuick.Controls 1.4

Item {
    id: keyBoardnum
    signal currentClickIndex(int index)
    width: 300 //Screen.desktopAvailableWidth*0.2
    height: 300
    Grid {
        width: keyBoardnum.width
        height: keyBoardnum.height
        spacing: 30
        columns: 3
        Repeater {
            model: ["1","2","3","4","5","6","7","8","9","C","0","OK"]
            delegate: CButton {
                width: 50
                height: 50
                text: modelData
                textColor: "white"
                onClicked: {
                    currentClickIndex(index)
                }
            }
        }
    }
}

