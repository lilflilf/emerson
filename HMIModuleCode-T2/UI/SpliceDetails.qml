import QtQuick 2.4
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2
import QtQuick.Controls 1.4

Item {
    id: detail
    width: Screen.width * 0.8
    height: Screen.height *0.5
    property alias leftModel: listModelLeft
    property alias rightModel: listModelRight
    property alias centerVisable: centerButton.visible

    property var selectColor: ""
    property var selectText: ""
    property var selectDirection: ""
    property var selectPosition: ""
    property var selectIndex: 0
    property var selectLocation: ""
    property var wireCount: 0
    property var wireName: ""
    signal wireSelected(var selectColor,var selectDirection,var selectPosition,var selectText,var selectWireName)
    signal changing(var bIsChang)

    function changeTop()
    {
        if (selectDirection == "left" && topLeft.sourceComponent != null)
            return true
        else if (selectDirection == "right" && topRight.sourceComponent != null)
            return true
        else
            return false
    }
    function changeBottom()
    {
        if (selectDirection == "left" && bottomLeft.sourceComponent != null)
            return true
        else if (selectDirection == "right" && bottomRight.sourceComponent != null)
            return true
        else
            return false
    }

    function addWire()
    {
        if (wireCount < 19) {
            listModelRight.append({"myLineLength":200,"mycolor":"#ff6699","isCheck":false,"linetext":"0","wireName":""})
            wireCount++
        }

    }
    function deleteWire()
    {
        if (selectPosition == "topRight") {
            topRight.sourceComponent = null
            selectPosition = ""
            if (wireCount > 0)
                wireCount--
        }
        else if (selectPosition == "bottomRight") {
            bottomRight.sourceComponent = null
            selectPosition = ""
            if (wireCount > 0)
                wireCount--
        }
        else if (selectPosition == "topLeft") {
            topLeft.sourceComponent = null
            selectPosition = ""
            if (wireCount > 0)
                wireCount--
        }
        else if (selectPosition == "bottomLeft") {
            bottomLeft.sourceComponent = null
            selectPosition = ""
            if (wireCount > 0)
                wireCount--
        }
        else if (selectPosition == "rightList") {
            selectPosition = ""
            listModelRight.remove(selectIndex,1)
            selectIndex = 0
            if (wireCount > 0)
                wireCount--
        }
        else if (selectPosition == "leftList") {
            selectPosition = ""
            listModelLeft.remove(selectIndex,1)
            selectIndex = 0
            if (wireCount > 0)
                wireCount--
        }
    }

    onWireNameChanged: {
        if (selectPosition == "topRight") {
            topRight.item.myWireName = wireName
        }
        else if (selectPosition == "bottomRight") {
            bottomRight.item.myWireName = wireName
        }
        else if (selectPosition == "topLeft") {
            topLeft.item.myWireName = wireName
        }
        else if (selectPosition == "bottomLeft") {
            bottomLeft.item.myWireName = wireName
        }
        else if (selectPosition == "rightList") {
            listModelRight.set(selectIndex,{"wireName":detail.wireName})
        }
        else if (selectPosition == "leftList") {
            listModelLeft.set(selectIndex,{"wireName":detail.wireName})
        }
    }

    onSelectLocationChanged: {
        if (selectDirection == "left" && selectLocation == "middle")
        {
            if (selectPosition == "topLeft" || selectPosition == "bottomLeft")
            {
                if (selectPosition == "topLeft")
                    topLeft.sourceComponent = null
                else if (selectPosition == "bottomLeft")
                    bottomLeft.sourceComponent = null

                selectPosition = "leftList"
                wirePositionGroup.current = null
                listModelLeft.append({"myLineLength":200,"mycolor":selectColor.toString(),"isCheck":false,"linetext":selectText,"wireName":wireName})
                selectIndex = listModelLeft.count - 1
                listModelLeft.set(selectIndex,{"isCheck":true})
            }
        }
        else if (selectDirection == "left" && selectLocation == "top")
        {
            if (selectPosition == "leftList")
            {
                selectPosition = "topLeft"
                listModelLeft.remove(selectIndex,1)
                topRight.sourceComponent = null
                topLeft.sourceComponent = left
                wirePositionGroup.current = null
                topLeft.item.isCheck = true
            }
            else if (selectPosition == "bottomLeft")
            {
                selectPosition = "topLeft"
                bottomLeft.sourceComponent = null
                topRight.sourceComponent = null
                topLeft.sourceComponent = left
                wirePositionGroup.current = null
                topLeft.item.isCheck = true
            }
        }
        else if (selectDirection == "left" && selectLocation == "bottom")
        {
            if (selectPosition == "leftList")
            {
                selectPosition = "bottomLeft"
                listModelLeft.remove(selectIndex,1)
                bottomRight.sourceComponent = null
                bottomLeft.sourceComponent = left
                wirePositionGroup.current = null
                bottomLeft.item.isCheck = true
            }
            else if (selectPosition == "topLeft")
            {
                selectPosition = "bottomLeft"
                topLeft.sourceComponent = null
                bottomLeft.sourceComponent = left
                bottomRight.sourceComponent = null
                wirePositionGroup.current = null
                bottomLeft.item.isCheck = true
            }
        }
        else if (selectDirection == "right" && selectLocation == "top")
        {
            if (selectPosition == "rightList")
            {
                selectPosition = "topRight"
                listModelRight.remove(selectIndex,1)
                topLeft.sourceComponent = null
                topRight.sourceComponent = right
                wirePositionGroup.current = null
                topRight.item.isCheck = true
            }
            else if (selectPosition == "bottomRight")
            {
                selectPosition = "topRight"
                topLeft.sourceComponent = null
                topRight.sourceComponent = right
                wirePositionGroup.current = null
                topRight.item.isCheck = true
            }
        }
        else if (selectDirection == "right" && selectLocation == "middle")
        {
            if (selectPosition == "topRight" || selectPosition == "bottomRight")
            {
                if (selectPosition == "topRight")
                    topRight.sourceComponent = null
                else if (selectPosition == "bottomRight")
                    bottomRight.sourceComponent = null
                selectPosition = "rightList"
                wirePositionGroup.current = null
                listModelRight.append({"myLineLength":200,"mycolor":detail.selectColor,"isCheck":false,"linetext":selectText,"wireName":wireName})
                selectIndex = listModelRight.count - 1
                listModelRight.set(selectIndex,{"isCheck":true})

            }
        }
        else if (selectDirection == "right" && selectLocation == "bottom")
        {
            if (selectPosition == "rightList")
            {
                selectPosition = "bottomRight"
                listModelRight.remove(selectIndex,1)
                bottomLeft.sourceComponent = null
                bottomRight.sourceComponent = right
                wirePositionGroup.current = null
                bottomRight.item.isCheck = true
            }
            else if (selectPosition == "topRight")
            {
                selectPosition = "bottomRight"
                topRight.sourceComponent = null
                bottomRight.sourceComponent = right
                bottomLeft.sourceComponent = null
                wirePositionGroup.current = null
                bottomRight.item.isCheck = true
            }
        }
    }

    onSelectColorChanged: {
        if (detail.selectPosition == "rightList"){
            listModelRight.set(detail.selectIndex,{"mycolor":selectColor.toString()})
        }
        else if (detail.selectPosition == "leftList")
            listModelLeft.set(detail.selectIndex,{"mycolor":selectColor.toString()})
        else if (detail.selectPosition == "topLeft")
            topLeft.item.myColor = selectColor
        else if (detail.selectPosition == "topRight")
            topRight.item.myColor = selectColor
        else if (detail.selectPosition == "bottomLeft")
            bottomLeft.item.myColor = selectColor
        else if (detail.selectPosition == "bottomRight")
            bottomRight.item.myColor = selectColor
    }
    onSelectTextChanged: {
        if (detail.selectPosition == "rightList"){
            listModelRight.set(detail.selectIndex,{"linetext":selectText})
        }
        else if (detail.selectPosition == "leftList")
            listModelLeft.set(detail.selectIndex,{"linetext":selectText})
        else if (detail.selectPosition == "topLeft")
            topLeft.item.myText = selectText
        else if (detail.selectPosition == "topRight")
            topRight.item.myText = selectText
        else if (detail.selectPosition == "bottomLeft")
            bottomLeft.item.myText = selectText
        else if (detail.selectPosition == "bottomRight")
            bottomRight.item.myText = selectText
    }

    onSelectDirectionChanged: {
        if (detail.selectPosition == "rightList" && selectDirection != "right"){

            listModelLeft.append({"myLineLength":200,"mycolor":listModelRight.get(selectIndex).mycolor,"isCheck":false,"linetext":selectText,"wireName":wireName})
            listModelRight.remove(detail.selectIndex, 1)
            wirePositionGroup.current = null

            detail.selectPosition = "leftList"
            listModelLeft.set(listModelLeft.count - 1, {"isCheck":true})
            detail.selectIndex = listModelLeft.count - 1

        }
        else if (detail.selectPosition == "leftList" && selectDirection != "left"){

            listModelRight.append({"myLineLength":200,"mycolor":listModelLeft.get(selectIndex).mycolor,"isCheck":false,"linetext":selectText,"wireName":wireName})
            listModelLeft.remove(detail.selectIndex, 1)
            wirePositionGroup.current = null

            detail.selectPosition = "rightList"
            detail.selectIndex = listModelRight.count - 1
            listModelRight.set(listModelRight.count - 1, {"isCheck":true})
        }
        else if (detail.selectPosition == "topLeft" && selectDirection != "left"){
            detail.selectPosition = "topRight"
            topLeft.sourceComponent = null
            topRight.sourceComponent = right
            wirePositionGroup.current = null
            topRight.item.isCheck = true
        }
        else if (detail.selectPosition == "topRight" && selectDirection != "right"){
            detail.selectPosition = "topLeft"
            topLeft.sourceComponent = left
            topRight.sourceComponent = null
            wirePositionGroup.current = null
            topLeft.item.isCheck = true
        }
        else if (detail.selectPosition == "bottomLeft" && selectDirection != "left"){
            detail.selectPosition = "bottomRight"
            bottomLeft.sourceComponent = null
            bottomRight.sourceComponent = right
            wirePositionGroup.current = null
            bottomRight.item.isCheck = true
        }
        else if (detail.selectPosition == "bottomRight" && selectDirection != "right"){
            detail.selectPosition = "bottomLeft"
            bottomLeft.sourceComponent = left
            bottomRight.sourceComponent = null
            wirePositionGroup.current = null
            bottomLeft.item.isCheck = true
        }


    }
    onSelectPositionChanged: {
//        console.log("onSelectPositionChanged",detail.selectPosition)
    }

    ExclusiveGroup {
        id: wirePositionGroup;
    }
    Rectangle {
        id: lineLeft
        width: 2
        height: parent.height
        anchors.left: parent.left
        anchors.leftMargin: parent.width / 2 - 40
    }
    Rectangle {
        id: lineRight
        width: 2
        height: parent.height
        anchors.left: parent.left
        anchors.leftMargin: parent.width / 2 + 40
    }

    Item {
        id: top
        width: parent.width
        height: parent.height * 0.1
        Rectangle {
            anchors.fill: parent
            opacity: 0.1
        }
        Loader {
            id: topLeft
            anchors.right: parent.right
            anchors.rightMargin: parent.width / 2 - 40
            //sourceComponent: left
            onLoaded: {
                topLeft.item.lineLength = 200
                topLeft.item.myColor = selectColor
                topLeft.item.myText = selectText
                topLeft.item.position = "topLeft"
                topLeft.item.myWireName = wireName
                topRight.sourceComponent = null
            }
            anchors.verticalCenter: parent.verticalCenter
        }
        Loader {
            id: topRight
            anchors.left: parent.left
            anchors.leftMargin: parent.width / 2 - 40
            //sourceComponent: right
            onLoaded: {
                topRight.item.lineLength = 200
                topRight.item.myColor = selectColor
                topRight.item.myText = selectText
                topRight.item.position = "topRight"
                topRight.item.myWireName = wireName
                topLeft.sourceComponent = null

            }
            anchors.verticalCenter: parent.verticalCenter
        }

    }
    Item {
        id: bottom
        width: parent.width
        height: parent.height * 0.1
        anchors.bottom: parent.bottom
        Rectangle {
            anchors.fill: parent
            opacity: 0.1
        }
        Loader {
            id: bottomLeft
            anchors.right: parent.right
            anchors.rightMargin: parent.width / 2 - 40
//            sourceComponent: left
            onLoaded: {
                bottomLeft.item.lineLength = 200
                bottomLeft.item.myColor = selectColor
                bottomLeft.item.myText = selectText
                bottomLeft.item.position = "bottomLeft"
                bottomLeft.item.myWireName = wireName

                bottomRight.sourceComponent = null
            }
            anchors.verticalCenter: parent.verticalCenter
        }
        Loader {
            id: bottomRight
            anchors.left: parent.left
            anchors.leftMargin: parent.width / 2 - 40
//            sourceComponent: right
            onLoaded: {
                bottomRight.item.lineLength = 200
                bottomRight.item.myColor = selectColor
                bottomRight.item.myText = selectText
                bottomRight.item.position = "bottomRight"
                bottomRight.item.myWireName = wireName
                bottomLeft.sourceComponent = null
            }
            anchors.verticalCenter: parent.verticalCenter
        }
    }


    Item {
        id: middle
        width: parent.width
        height: parent.height * 0.7
        anchors.top: top.bottom
        anchors.topMargin: parent.height * 0.1 / 2
//        Rectangle {
//            anchors.fill: parent
//            color: "black"
//            opacity: 0.2
//        }
        ListModel {
            id: listModelLeft
            Component.onCompleted: {
//                listModelLeft.append({"myLineLength":200,"mycolor":"red","isCheck":false,"linetext":"0"})
//                listModelLeft.append({"myLineLength":200,"mycolor":"black","isCheck":false,"linetext":"0"})
//                listModelLeft.append({"myLineLength":200,"mycolor":"blue","isCheck":false,"linetext":"0"})
            }
        }
        ListModel {
            id: listModelRight
            Component.onCompleted: {
//                listModelRight.append({"myLineLength":200,"mycolor":"red","isCheck":false,"linetext":"0"})
//                listModelRight.append({"myLineLength":200,"mycolor":"black","isCheck":false,"linetext":"0"})
//                listModelRight.append({"myLineLength":200,"mycolor":"blue","isCheck":false,"linetext":"0"})
            }
        }
        ListView {
            id: listViewLeft
            anchors.rightMargin: -40
            anchors.verticalCenter: parent.verticalCenter
            anchors.verticalCenterOffset: 5
            height: listModelLeft.count <= 5 ? listModelLeft.count * (detail.height * 0.1 + 10) : listModelLeft.count < 10 ? listModelLeft.count * 30 : 300
            model: listModelLeft
            delegate: left
            interactive: false
        }
        ListView {
            id: listViewRight
            anchors.left: parent.left
            anchors.leftMargin: parent.width / 2 - 40
            anchors.right: parent.right
            anchors.verticalCenter: parent.verticalCenter
            height: listModelRight.count <= 5 ? listModelRight.count * (detail.height * 0.1 + 10) : listModelRight.count < 10 ? listModelRight.count * 30 : 300
            model: listModelRight
            delegate: right
            interactive: false
            Component.onCompleted: {

            }
        }

        CButton {
            id: centerButton
            anchors.centerIn: parent
            width: 60
            height: 40
            visible: false
            onClicked: {
                if (listModelRight.count < 19)
                    listModelRight.append({"myLineLength":200,"mycolor":"#ff6699","isCheck":false,"linetext":"0","wireName":""})
                //fileDialog.open()
                //loadder.source = "qrc:/UI/MyFileDialog.qml"
            }
        }
        FileDialog {
               id: fileDialog
               title: "Please choose a file"
               onAccepted: {
                   //path = fileDialog.fileUrls[0].toString();
                   console.log("You chose: ",fileDialog.fileUrls)
               }
               onRejected: {
                   console.log("Canceled")
               }
           }
        Loader {
            id: loadder
            anchors.fill: parent
        }
    }
    Component {
        id: left
        Item {
            id: leftItem
            property alias lineLength: leftLine.width
            property alias myColor: leftRec.color
            property alias myText: mytextLeft.text
            property var position: "leftList"
            property alias isCheck: radioButtonLeft.checked
            property var myWireName: myWireNameLeft.text
            width: middle.width / 2 + 40
//            height: listModelLeft.count <= 5 ? detail.height * 0.1 + 10 : 30
            height: listModelLeft.count <= 5 ? detail.height * 0.1 + 10 : (listModelLeft.count > 5 && listModelLeft.count <= 10) ? 30 : index < (listModelLeft.count - 10) * 2 ? 15 : 30

            Rectangle {
                id: leftLine
                width: index % 2 && index < (listModelLeft.count - 10) * 2 ? myLineLength + 150 : myLineLength
                height: 2
                anchors.right: parent.right
                anchors.verticalCenter: leftRec.verticalCenter
            }
            Rectangle {
                id: leftRec
                width: 60
                height: listModelLeft.count <= 5 ? detail.height * 0.1 : 20 //20
                color: mycolor
                anchors.right: leftLine.left
                anchors.verticalCenter: parent.verticalCenter
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        radioButtonLeft.checked = !radioButtonLeft.checked

                        if (leftItem.position != "leftList" && radioButtonLeft.checked)
                        {
                            changing(true)
                            selectPosition = leftItem.position
                            selectColor = leftRec.color
                            selectText = mytextLeft.text
                            wireSelected(leftRec.color,"left",leftItem.position,mytextLeft.text,myWireNameLeft.text)
                            changing(false)

                        }
                        else if (leftItem.position == "leftList" && radioButtonLeft.checked)
                        {
                            changing(true)
                            wireSelected(leftRec.color,"left",leftItem.position,mytextLeft.text,myWireNameLeft.text)
                            selectPosition = leftItem.position
                            selectIndex = index
                            selectColor = leftRec.color
                            selectText = mytextLeft.text
                            listModelLeft.set(index,{"isCheck":radioButtonLeft.checked})
                            selectDirection = "left"
                            changing(false)

                        }
                        else if (leftItem.position == "leftList" && !radioButtonLeft.checked)
                        {
                            listModelLeft.set(index,{"isCheck":radioButtonLeft.checked})
                        }
                    }
                }
                Text {
                    id: mytextLeft
                    anchors.centerIn: parent
                    text: qsTr(linetext)
                    font.family: "arial"
                    font.pointSize: 16
                    color: "white"
                    clip: true
                }
            }
            Text {
                id: myWireNameLeft
                width: leftRec.width
                anchors.right: leftRec.left
                anchors.verticalCenter: leftRec.verticalCenter
                anchors.rightMargin: 8
                font.family: "arial"
                font.pointSize: 16
                color: "white"
                text: wireName
                clip: true
            }

            RadioButton {
                id: radioButtonLeft
                checked: listModelLeft.get(index).isCheck
                exclusiveGroup: wirePositionGroup
                visible: false
                onCheckedChanged: {
                    nameLeft.visible = checked
                }

            }
            Rectangle {
                id: nameLeft
                width: leftRec.width + 5
                height: leftRec.height + 5
                color: Qt.rgba(0,0,0,0)
                border.color: "white"
                border.width: 1
                anchors.centerIn: leftRec
                visible: radioButtonLeft.checked ? true : false
            }
        }
    }
    Component {
        id: right
        Item {
            property alias lineLength: rightLine.width
            property alias myColor: rightRec.color
            property alias myText: mytext.text
            property var position: "rightList"
            property alias isCheck: radioButton.checked
            property var myWireName: myWireNameRight.text
            id: rightItem
            width: 300
//            height: listModelRight.count <= 5 ? detail.height * 0.1 + 10 : 30
            height: listModelRight.count <= 5 ? detail.height * 0.1 + 10 : (listModelRight.count > 5 && listModelRight.count <= 10) ? 30 : index < (listModelRight.count - 10) * 2 ? 15 : 30
            Rectangle {
                id: rightLine
                width: index % 2 && index < (listModelRight.count - 10) * 2 ? myLineLength + 150 : myLineLength
                height: 2
                anchors.left: parent.left
                anchors.verticalCenter: rightRec.verticalCenter
            }
            Rectangle {
                id: rightRec
                width: 60
                height: listModelRight.count <= 5 ? detail.height * 0.1 : 20
                color: mycolor
                anchors.left: rightLine.right
                anchors.verticalCenter: parent.verticalCenter
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        radioButton.checked = !radioButton.checked
                        if (rightItem.position != "rightList" && radioButton.checked)
                        {
                            changing(true)
                            selectPosition = rightItem.position
                            selectColor = rightRec.color.toString()
                            selectText = mytext.text
                            wireSelected(rightRec.color,"right",rightItem.position,mytext.text,myWireNameRight.text)
                            changing(false)

                        }
                        else if (rightItem.position == "rightList" && radioButton.checked)
                        {
                            changing(true)
                            wireSelected(rightRec.color,"right",rightItem.position,mytext.text,myWireNameRight.text)
                            selectPosition = rightItem.position
                            selectIndex = index
                            selectColor = rightRec.color.toString()
                            selectText = mytext.text
                            listModelRight.set(index,{"isCheck":radioButton.checked})
                            selectDirection = "right"
                            changing(false)
                        }
                        else if (rightItem.position == "rightList" && !radioButton.checked)
                        {
                            listModelRight.set(index,{"isCheck":radioButton.checked})
                        }
                    }
                }
                Text {
                    id: mytext
                    anchors.centerIn: parent
                    text: qsTr(linetext)
                    font.family: "arial"
                    font.pointSize: 16
                    color: "white"
                }

            }
            Text {
                id: myWireNameRight
                width: rightRec.width
                anchors.left: rightRec.right
                anchors.verticalCenter: rightRec.verticalCenter
                anchors.leftMargin: 8
                font.family: "arial"
                font.pointSize: 16
                color: "white"
                text: wireName
                clip: true
            }
            RadioButton {
                id: radioButton
                checked: listModelRight.get(index).isCheck
                exclusiveGroup: wirePositionGroup
                visible: false
                onCheckedChanged: {
                    name.visible = checked
                }
            }
            Rectangle {
                id: name
                width: rightRec.width + 5
                height: rightRec.height + 5
                color: Qt.rgba(0,0,0,0)
                border.color: "white"
                border.width: 1
                anchors.centerIn: rightRec
                visible: radioButton.checked == true ? true : false
            }
        }
    }
}
