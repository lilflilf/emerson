import QtQuick 2.7
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.0
import QtQuick.Window 2.2

Item {
    id: myCheck
    property string checkIcon: "qrc:/images/images/settingselect.png"
    property string unCheckIcon: "qrc:/images/images/setting.png"
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
            width: 22
            height: 22
            fillMode: Image.PreserveAspectFit
            source: myCheck.checked ? checkIcon : unCheckIcon
        }
        onClicked: {
            console.log("2222222222222222222")
            if (!myCheck.checked)
                myCheck.checked = !myCheck.checked
        }
    }
}
