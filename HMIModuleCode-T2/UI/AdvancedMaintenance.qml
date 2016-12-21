import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import QtQuick.Dialogs 1.2
import Qt.labs.folderlistmodel 2.1

Item {
    id: toolChange
    width: Screen.width*0.7
    height: Screen.height*0.6

    Component.onCompleted: {
        hmiAdaptor.maintenanceStart(2);
    }
//    Component.onDestruction: {
//        hmiAdaptor.maintenanceStop(2);
//    }

    Column {
        id: column1
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.leftMargin: 50
        anchors.topMargin: 30
        spacing: 20
        Image {
            width: 280
            height: 280
            source: "qrc:/images/images/maintenance-5.png"
//            source: "file:///c:/ToolChangeImage/group2/wiredemo.jpg"
        }
        Image {
            width: 280
            height: 280
            source: "qrc:/images/images/maintenance-6.png"
//            source: "file:///c:/ToolChangeImage/group2/wiredemo.jpg"
        }
    }


//    ANVILARMCLICK,
//    ANVILCLICK,
//    GATHERCLICK,
//    CUTTERCLICK,
//    CRASHCLICK,
//    SAFETYCLICK,
//    CONVERTERCOOLINGCLICK,
//    TOOLINGCOOLINGCLICK,

    Column {
        anchors.left:column1.right
        anchors.top: column1.top
        anchors.leftMargin: 60
        spacing: 10
        CButton {
            width: 250
            text: qsTr("1-Anvil Arm")
            onClicked: {
                hmiAdaptor.advancedMaintenanceExecute(0)
            }
        }
        CButton {
            width: 250
            text: qsTr("2-Gather")
            onClicked: {
                hmiAdaptor.advancedMaintenanceExecute(2)
            }
        }
        CButton {
            width: 250
            text: qsTr("3-Safety")
            onClicked: {
                hmiAdaptor.advancedMaintenanceExecute(5)
            }
        }
    }
    Column {
        id: buttonCoumn
        anchors.left:column1.right
        anchors.top: column1.top
        anchors.topMargin: 280
        anchors.leftMargin: 60
        spacing: 10
        CButton {
            width: 250
            text: qsTr("4-Cutter")
            onClicked: {
                hmiAdaptor.advancedMaintenanceExecute(3)
            }
        }
        CButton {
            width: 250
            text: qsTr("5-Cooling Tooling")
            onClicked: {
                hmiAdaptor.advancedMaintenanceExecute(7)
            }
        }
        CButton {
            width: 250
            text: qsTr("6-Cooling Converter")
            onClicked: {
                hmiAdaptor.advancedMaintenanceExecute(6)
            }
        }
        CButton {
            width: 250
            text: qsTr("7-Crash")
            onClicked: {
                hmiAdaptor.advancedMaintenanceExecute(4)
            }
        }

    }
    ListModel {
        id: listModel
        Component.onCompleted: {
            listModel.append({"titleHead":qsTr("Power Supply"),"value":"4000W"})
            listModel.append({"titleHead":qsTr("Calibrated Amplitude"),"value":"72μm"})
            listModel.append({"titleHead":qsTr("Tune Point"),"value":"40%"})
            listModel.append({"titleHead":qsTr("Frequency Offset"),"value":"50%"})
        }
    }

    Text {
        id: title
        anchors.top: parent.top
        anchors.topMargin: 30
        anchors.left: rowButton.left
        font.family: "arial"
        font.pixelSize: 20
        color: "white"
        text: qsTr("Sonics Test")
    }
    Grid {
        id: testSetting
        anchors.horizontalCenter: rowButton.horizontalCenter
        anchors.top: title.bottom
        rowSpacing: 20
        columnSpacing: (rowButton3.width - 20) / 2 - 240
//        anchors.bottom: rowButton3.top
//        anchors.bottomMargin: 20
//        anchors.top: title.bottom
//        anchors.topMargin: 20
//        anchors.left: title.left
//        anchors.right: parent.right
//        anchors.rightMargin: 20
//        anchors.bottom: rowButton3.top
//        anchors.bottomMargin: 20
        columns: 2
        rows: 2
        Repeater {
            anchors.right: parent.right
            model: listModel
            delegate: Recsetting {
                width: 250 //(rowButton3.width-20)/3
                height: 130 //(testSetting.height-20)/3
                headTitle: titleHead
                centervalue: value
            }
        }
    }
    Row {
        id: rowButton3
        anchors.bottom: powerText.top
        anchors.bottomMargin: 20
        anchors.right: rowButton.right
        anchors.left: rowButton.left
        spacing: 20
        CButton {
            id: test1
            text: qsTr("Run Sonics")
            width: (rowButton3.width -20)/2
        }
        CButton {
            id: test2
            text: qsTr("Run Sonics 100%")
            width: (rowButton3.width -20)/2
        }
    }
    Text {
        id: powerText
        anchors.bottom: rowButton2.top
        anchors.bottomMargin: 20
        anchors.left: rowButton2.left
        verticalAlignment: Qt.AlignVCenter
        height: 40
        font.family: "arial"
        font.pixelSize: 20
        color: "white"
        text: qsTr("Power")
    }
    Row {
        id: progressBar2
        anchors.bottom: progressBar.top
        anchors.bottomMargin: 2
        spacing: (progressBar.width-2*14)/13
        anchors.left: progressBar.left
        Repeater {
            model: 14
            delegate: Item {
                width: 2
                height: 30
                Text {
                    id: num
                    anchors.top: parent.top
                    anchors.horizontalCenter:line.horizontalCenter
                    font.pixelSize: 10
                    font.family: "arial"
                    color: "white"
                    text: index*10
                }
                Rectangle {
                    id: line
                    anchors.top: num.bottom
                    width: 2
                    height: 10
                    color: "blue"
                }
            }
        }
    }

    CProgressBar {
        id: progressBar
        anchors.verticalCenter: powerText.verticalCenter
        anchors.left: powerText.right
        anchors.leftMargin: 10
        anchors.right: rowButton2.right
        maximum: 100
        value: 50
        minimum: 1
    }


    Row {
        id: rowButton2
        anchors.bottom: rowButton.top
        anchors.bottomMargin: 20
        anchors.right: rowButton.right
        anchors.left: rowButton.left
        spacing: 20
        CButton {
            text: qsTr("Reset")
            width: (rowButton2.width-20)/2
        }
        CButton {
            text: qsTr("Default Setting")
            width: (rowButton2.width-20)/2
        }
    }
    Row {
        id: rowButton
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 20
        anchors.left: buttonCoumn.right
        anchors.leftMargin: 20
        anchors.right: parent.right
        anchors.rightMargin: 20
        spacing: 20
        CButton {
            iconSource: "qrc:/images/images/cancel.png"
            text: qsTr("Cancel")
            width: (rowButton.width-20)/2
        }
        CButton {
            iconSource: "qrc:/images/images/OK.png"
            text: qsTr("OK")
            width: (rowButton.width-20)/2
        }
    }
}
