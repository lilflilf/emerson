import QtQuick 2.4
import QtQuick.Controls 1.3


Item {
    id: toggleswitch
    property int backgroundwidth: 0
    property int backgroundheight: 0
    property string textLeft: ""
    property string textRight: ""
    property bool on: false
    width: backgroundwidth
    height: backgroundheight
    function toggle() {
        if (toggleswitch.state == "right") {
            toggleswitch.state = "left";
            leftSwitch.color = "black"
            rightSwitch.color = "white"
        } else {
            toggleswitch.state = "right";
            leftSwitch.color = "white"
            rightSwitch.color = "black"
        }
    }

    function releaseSwitch() {
        if (knob.x == 1) {
            if (toggleswitch.state == "left") return;
        }
        console.log("33333333333",knob.x)
        if (knob.x == toggleswitch.width/2) {
            if (toggleswitch.state == "right") return;
        }
        toggle();
    }

    Rectangle {
        id: background
        width: parent.width
        height: parent.height
        radius: 5
        color: "black"
        MouseArea { anchors.fill: parent; onClicked: toggle() }
    }

    Rectangle {
        id: knob
        width: parent.width/2
        height: parent.height
        radius: 5
        color: "white"
        MouseArea {
            anchors.fill: parent
            drag.target: knob; drag.axis: Drag.XAxis; drag.minimumX: 1; drag.maximumX: toggleswitch.width/2
            onClicked: toggle()
            onReleased: releaseSwitch()
        }
    }

    Text {
        id: leftSwitch
        width: parent.width/2
        height: parent.height
        verticalAlignment: Qt.AlignVCenter
        horizontalAlignment: Qt.AlignHCenter
        text: textLeft
        color: "white"
        font.family: "arial"
        font.pointSize: 14
    }
    Text {
        id: rightSwitch
        anchors.left: leftSwitch.right
        width: parent.width/2
        height: parent.height
        verticalAlignment: Qt.AlignVCenter
        horizontalAlignment: Qt.AlignHCenter
        text: textRight
        color: "black"
        font.family: "arial"
        font.pointSize: 14
    }

    states: [
        State {
            name: "right"
            PropertyChanges { target: knob; x: toggleswitch.width/2 }
            PropertyChanges { target: toggleswitch; on: true }
            PropertyChanges { target: leftSwitch; color: "white" }
            PropertyChanges { target: rightSwitch; color: "black" }
        },
        State {
            name: "left"
            PropertyChanges { target: knob; x: 1 }
            PropertyChanges { target: toggleswitch; on: false }
            PropertyChanges { target: leftSwitch; color: "black" }
            PropertyChanges { target: rightSwitch; color: "white" }

        }
    ]

    transitions: Transition {
        NumberAnimation { properties: "x"; easing.type: Easing.InOutQuad; duration: 200 }
    }
}
