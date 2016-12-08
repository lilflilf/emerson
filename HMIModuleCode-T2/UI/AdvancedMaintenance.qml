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

//    Component.onCompleted: {
//        hmiAdaptor.maintenanceStart(2);
//    }
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
//                hmiAdaptor.advancedMaintenanceExecute(hmiAdaptor.ANVILARMCLICK)
            }
        }
        CButton {
            width: 250
            text: qsTr("2-Gather")
            onClicked: {
//                hmiAdaptor.advancedMaintenanceExecute(hmiAdaptor.GATHERCLICK)
            }
        }
        CButton {
            width: 250
            text: qsTr("3-Safety")
            onClicked: {
//                hmiAdaptor.advancedMaintenanceExecute(hmiAdaptor.SAFETYCLICK)
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
//                hmiAdaptor.advancedMaintenanceExecute(hmiAdaptor.CUTTERCLICK)
            }
        }
        CButton {
            width: 250
            text: qsTr("5-Cooling Tooling")
            onClicked: {
//                hmiAdaptor.advancedMaintenanceExecute(hmiAdaptor.TOOLINGCOOLINGCLICK)
            }
        }
        CButton {
            width: 250
            text: qsTr("6-Cooling Converter")
            onClicked: {
//                hmiAdaptor.advancedMaintenanceExecute(hmiAdaptor.CONVERTERCOOLINGCLICK)
            }
        }
        CButton {
            width: 250
            text: qsTr("7-Crash")
            onClicked: {
//                hmiAdaptor.advancedMaintenanceExecute(hmiAdaptor.CRASHCLICK)
            }
        }

    }
    ListModel {
        id: listModel
        Component.onCompleted: {
            listModel.append({"titleHead":"Power Supply","value":"4000W"})
            listModel.append({"titleHead":"Calibrated Amplitude","value":"72μm"})
            listModel.append({"titleHead":"Tune Point","value":"40%"})
            listModel.append({"titleHead":"Frequency Offset","value":"50%"})
        }
    }

    Text {
        id: title
        anchors.top: parent.top
        anchors.topMargin: 30
        anchors.left: buttonCoumn.right
        anchors.leftMargin: 20
        font.family: "arial"
        font.pixelSize: 20
        color: "white"
        text: qsTr("Sonics Test")
    }
    Grid {
        id: testSetting
        anchors.top: title.bottom
        anchors.topMargin: 20
        anchors.left: title.left
        anchors.right: parent.right
        anchors.rightMargin: 20
        anchors.bottom: test1.top
        anchors.bottomMargin: 20
        spacing: 20
        columns: 2
        rows: 2
        Repeater {
            model: listModel
            delegate: Recsetting {
                width: (testSetting.width-20)/2
                height: (testSetting.height-20)/2
                headTitle: qsTr(titleHead)
                centervalue: qsTr(value)
            }
        }
    }
    CButton {
        id: test1
        anchors.left: testSetting.left
        anchors.bottom: progressBar2.top
        anchors.bottomMargin: 20
        text: qsTr("Run Sonics")
        width: testSetting.width/2-10
    }
    CButton {
        id: test2
        anchors.left: test1.right
        anchors.leftMargin: 20
        anchors.bottom: progressBar2.top
        anchors.bottomMargin: 20
        text: qsTr("Run Sonics 100%")
        width: testSetting.width/2-10
    }
    Text {
        id: powerText
        anchors.bottom: rowButton.top
        anchors.bottomMargin: 20
        anchors.left: testSetting.left
        verticalAlignment: Qt.AlignVCenter
        height: 40
        font.family: "arial"
        font.pixelSize: 20
        color: "white"
        text: qsTr("power")
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
        maximum: 100
        value: 50
        minimum: 1
    }
    Row {
        id: rowButton
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        anchors.left: buttonCoumn.left
        anchors.right: parent.right
        anchors.rightMargin: 20
        spacing: 20
        CButton {
            text: qsTr("Reset")
            width: (rowButton.width-60)/4
        }
        CButton {
            text: qsTr("Default Setting")
            width: (rowButton.width-60)/4
        }
        CButton {
            iconSource: "qrc:/images/images/cancel.png"
            text: qsTr("Cancel")
            width: (rowButton.width-60)/4
        }
        CButton {
            iconSource: "qrc:/images/images/OK.png"
            text: qsTr("OK")
            width: (rowButton.width-60)/4
        }
    }
}
