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
    signal wireSelected(var selectColor,var selectDirection,var selectPosition,var selectText)
    signal changing(var bIsChang)

    onSelectLocationChanged: {
        if (selectDirection == "left" && selectLocation == "middle")
        {
            if (selectPosition == "topLeft" || selectPosition == "bottomLeft")
            {
                selectPosition = "leftList"
                topLeft.sourceComponent = null
                bottomLeft.sourceComponent = null
                listModelLeft.append({"myLineLength":200,"mycolor":selectColor.toString(),"isCheck":false,"linetext":selectText})
                selectIndex = listModelLeft.count - 1
            }
        }
        else if (selectDirection == "left" && selectLocation == "top")
        {
            if (selectPosition == "leftList")
            {
                selectPosition = "topLeft"
                listModelLeft.remove(selectIndex,1)
                topLeft.sourceComponent = left
            }
        }
        else if (selectDirection == "left" && selectLocation == "bottom")
        {
            console.log("bottomLeft")
        }
        else if (selectDirection == "right" && selectLocation == "middle")
        {
            console.log("listRight")
        }
        else if (selectDirection == "right" && selectLocation == "top")
        {
            console.log("topRight")
        }
        else if (selectDirection == "right" && selectLocation == "bottom")
        {
            console.log("bottomRight")
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
    }
    onSelectDirectionChanged: {
        if (detail.selectPosition == "rightList" && selectDirection != "right"){
//            listModelLeft.append(listModelRight.get(detail.selectIndex))
            listModelLeft.append({"myLineLength":200,"mycolor":selectColor.toString(),"isCheck":false,"linetext":selectText})
            wirePositionGroup.current = null
            listModelRight.remove(detail.selectIndex, 1)
            detail.selectPosition = "leftList"
            listModelLeft.set(listModelLeft.count - 1, {"isCheck":true})
            detail.selectIndex = listModelLeft.count - 1
        }
        else if (detail.selectPosition == "leftList" && selectDirection != "left"){
//            listModelRight.append(listModelLeft.get(detail.selectIndex))
            listModelRight.append({"myLineLength":200,"mycolor":selectColor.toString(),"isCheck":false,"linetext":selectText})
            wirePositionGroup.current = null
            listModelLeft.remove(detail.selectIndex, 1)
            detail.selectPosition = "rightList"
            listModelRight.set(listModelRight.count - 1, {"isCheck":true})
            detail.selectIndex = listModelRight.count - 1
        }
        else if (detail.selectPosition == "topLeft" && selectDirection != "left"){
            topLeft.sourceComponent = null
            topRight.sourceComponent = right
        }
        else if (detail.selectPosition == "topRight" && selectDirection != "right"){
            topLeft.sourceComponent = left
            topRight.sourceComponent = null
        }


    }
    onSelectPositionChanged: {
        console.log("onSelectPositionChanged",detail.selectPosition)
    }

    onSelectTextChanged: {
        if (detail.selectPosition == "rightList"){
            listModelRight.set(detail.selectIndex,{"linetext":selectText})
        }
        else if (detail.selectPosition == "leftList")
            listModelLeft.set(detail.selectIndex,{"linetext":selectText})
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
            sourceComponent: left
            onLoaded: {
                bottomLeft.item.lineLength = 200
                bottomLeft.item.myColor = "red"
                bottomLeft.item.myText = "red"
                bottomLeft.item.position = "bottomRight"
            }
            anchors.verticalCenter: parent.verticalCenter
        }
        Loader {
            id: bottomRight
            anchors.left: parent.left
            anchors.leftMargin: parent.width / 2 - 40
            sourceComponent: right
            onLoaded: {
                bottomRight.item.lineLength = 200
                bottomRight.item.myColor = "red"
                bottomRight.item.myText = "red"
                bottomRight.item.position = "bottomRight"

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
        Rectangle {
            anchors.fill: parent
            color: "black"
            opacity: 0.2
        }
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
            onClicked: {
                if (listModelRight.count < 19)
                    listModelRight.append({"myLineLength":200,"mycolor":"white","isCheck":false,"linetext":"0"})
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
                            wireSelected(leftRec.color,"left",leftItem.position,mytextLeft.text)
                            changing(false)

                        }
                        else if (leftItem.position == "leftList" && radioButtonLeft.checked)
                        {
                            changing(true)
                            wireSelected(leftRec.color,"left",leftItem.position,mytextLeft.text)
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
                }
            }

            RadioButton {
                id: radioButtonLeft
                checked: isCheck
                exclusiveGroup: wirePositionGroup
                visible: false
                onCheckedChanged: {
                    if (!checked)
                    {
                        nameLeft.visible = false
                    }
                    else
                        nameLeft.visible = true
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
                        radioButton.checked = true
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
            RadioButton {
                id: radioButton
                checked: isCheck
                exclusiveGroup: wirePositionGroup
                visible: false
                onCheckedChanged: {
                    if (rightItem.position != "rightList" && radioButton.checked)
                    {
                        selectPosition = rightItem.position
                        selectColor = rightRec.color
                        selectText = mytext.text
                        wireSelected(rightRec.color,"right",rightItem.position,mytext.text)
                    }
                    else if (rightItem.position == "rightList" && radioButton.checked)
                    {
                        changing(true)
                        wireSelected(rightRec.color,"right",rightItem.position,mytext.text)
                        selectPosition = rightItem.position
                        selectIndex = index
                        selectColor = rightRec.color
                        selectText = mytext.text
                        listModelRight.set(index,{"isCheck":checked})
                        selectDirection = "right"
                        changing(false)
                    }
                    else if (rightItem.position == "rightList" && !radioButton.checked)
                    {
                        listModelRight.set(index,{"isCheck":checked})
                    }
                    name.visible = radioButton.checked
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
                visible: radioButton.checked ? true : false
            }
        }
    }
}
