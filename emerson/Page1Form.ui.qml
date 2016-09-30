import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

Item {
    id: item1
    property alias button1: button1
    property alias button2: button2

    RowLayout {
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter

        Button {
            id: button1
            text: qsTr("Press Me 1")
            highlighted: false
            checkable: true
            checked: false
        }

        Button {
            id: button2
            text: qsTr("Press Me 2")
        }
    }
}
