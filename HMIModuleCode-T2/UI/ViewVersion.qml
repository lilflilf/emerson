import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2

Item {
    Image {
        anchors.fill: parent
        source: "qrc:/images/images/bg.png"
    }
    Rectangle {
        id: back
        width: parent.width * 0.3
        height: parent.height
        color: "#052a40"
        z: 10

        Text {
            id: seach
            text: qsTr("Version Information")
            font.family: "arial"
            color: "white"
            font.pointSize: 20
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.leftMargin: 20
            anchors.topMargin: 10
        }
    }
    Text {
        id: partNumber
        anchors.top: parent.top
        anchors.topMargin: 48
        anchors.left: back.right
        anchors.leftMargin: 50
        font.family: "arial"
        font.pixelSize: 24
        color: "white"
        text: qsTr("Actuator Part Number: ")+hmiAdaptor.getSoftVerson(0)
    }
    Text {
        id: serialNumber
        anchors.top: partNumber.bottom
        anchors.topMargin: 20
        anchors.left: partNumber.left
        font.family: "arial"
        font.pixelSize: 24
        color: "white"
        text: qsTr("Actuator Serial Number: ")+hmiAdaptor.getSoftVerson(1)
    }
    Text {
        id: supplyPartNumber
        anchors.top: serialNumber.bottom
        anchors.topMargin: 100
        anchors.left: partNumber.left
        font.family: "arial"
        font.pixelSize: 24
        color: "white"
        text: qsTr("Power Supply Part Number:")
    }
    Text {
        id: supplySerialNumber
        anchors.top: supplyPartNumber.bottom
        anchors.topMargin: 20
        anchors.left: partNumber.left
        font.family: "arial"
        font.pixelSize: 24
        color: "white"
        text: qsTr("Power Supply Serial Number:")
    }
    Text {
        id: versionlNumber
        anchors.top: supplySerialNumber.bottom
        anchors.topMargin: 100
        anchors.left: partNumber.left
        font.family: "arial"
        font.pixelSize: 24
        color: "white"
        text: qsTr("Software Version Number:")
    }
    Text {
        id: controller
        anchors.top: versionlNumber.bottom
        anchors.topMargin: 20
        anchors.left: partNumber.left
        anchors.leftMargin: 10
        font.family: "arial"
        font.pixelSize: 24
        color: "white"
        text: qsTr("Controller: ") + hmiAdaptor.getSoftVerson(4)
    }
    Text {
        id: versaGraphiX
        anchors.top: controller.bottom
        anchors.topMargin: 20
        anchors.left: partNumber.left
        anchors.leftMargin: 10
        font.family: "arial"
        font.pixelSize: 24
        color: "white"
        text: qsTr("New HMI: ") + hmiAdaptor.getSoftVerson(5)
    }
    Text {
        id: actuatorModule
        anchors.top: versaGraphiX.bottom
        anchors.topMargin: 20
        anchors.left: partNumber.left
        anchors.leftMargin: 10
        font.family: "arial"
        font.pixelSize: 24
        color: "white"
        text: qsTr("Actuator: ")+hmiAdaptor.getSoftVerson(6)
    }
}
