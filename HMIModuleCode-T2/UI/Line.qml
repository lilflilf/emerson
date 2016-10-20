import QtQuick 2.0

Item {
    property alias lineColor: line.color
    Rectangle {
        id: line
        width: parent.width
        height: parent.height
        color: "white"
    }
}
