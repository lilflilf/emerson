import QtQuick 2.7
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.0
import QtQuick.Window 2.2

Item {
    id: myCheck
    property string checkIcon: "qrc:/images/images/check-click.png"
    property string unCheckIcon: "qrc:/images/images/check-bg.png"
    property bool checked: false
    property ExclusiveGroup exclusiveGroup: null
    width: parent.width
    height: parent.height
    onExclusiveGroupChanged: {
        if (exclusiveGroup)
           exclusiveGroup.bindCheckable(myCheck)
    }
    MouseArea {
        anchors.fill: parent
        Image {
            anchors.centerIn: parent
            width: 30
            height: 30
            fillMode: Image.PreserveAspectFit
            source: myCheck.checked ? checkIcon : unCheckIcon
        }
        onClicked: {
//            if (!myCheck.checked)
                myCheck.checked = !myCheck.checked
        }
    }
}
