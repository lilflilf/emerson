import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import QtQuick.Dialogs 1.2

Item {
    id: viewLib
    property int selectIndx: -1
    property int count: partTitleModel.count
    function shrinkGetValue(index1,index2)
    {
        if (index2 == 0 )
            return shrinkModel.get(index1).shrinkid
        else if (index2 == 1 )
            return shrinkModel.get(index1).temperature
        else if (index2 == 2 )
            return shrinkModel.get(index1).times
    }

    function initPage()
    {
        var list
        list = hmiAdaptor.dataCommunicationGetValue("shrinkData")
        if (list.length % 3 == 0)
        {
            for (var i = 0 ;i < list.length / 3; i++)
            {
                shrinkModel.append({shrinkid:list[i*3],temperature:list[i*3+1],times:list[i*3+2]})
            }
        }
    }

    Rectangle {
        id: leftArea
        anchors.top: parent.top
        anchors.left: parent.left
        width: Screen.width*0.3
        height: parent.height
        color: "#052a40"
        z: 10
        ExclusiveGroup {
            id: checkGroup
        }
        CButton {
            width: parent.width - 40
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 20
            anchors.left: parent.left
            anchors.leftMargin: 20
            iconSource: "qrc:/images/images/import.png"
            spacing: 10
            text: qsTr("IMPORT")

        }

        Column {
            id: column
            anchors.top: parent.top
            anchors.topMargin: 2
            anchors.left: parent.left
            anchors.leftMargin: 2
            height: 50*3+4
            width: parent.width-4
            CButton {
                id: part
                width: column.width
                textColor: "white"
                RadioButton {
                    id: partRadio
                    visible: false
                    exclusiveGroup: checkGroup
                    onCheckedChanged: {
                        if (partRadio.checked) {
                            part.backgroundItem.source = "qrc:/images/images/icon-bg.png"
                            headRepeater.model = partTitleModel
                            viewLib.count = partTitleModel.count
                            button2.x = 0
                            listView.model = partModel
                        }
                        else {
                            part.backgroundItem.source = ""

                        }
                    }
                }
                backgroundComponent: Image {
                    anchors.fill: parent
                    source: ""
                }

                onClicked: {
                    if (!partRadio.checked)
                        partRadio.checked = !partRadio.checked
                }
                Component.onCompleted: {
                    partRadio.checked = true
                }
                Line {
                    width: parent.width
                    height: 1
                    lineColor: "#1987ab"
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 3

                }
                Image {
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.right: parent.right
                    anchors.rightMargin: 18
                    source: "qrc:/images/images/right.png"
                }
                Text {
                    text: qsTr("Part")
                    font.pointSize: 20
                    font.family: "arial"
                    color: "white"
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    anchors.leftMargin: 10
                }
            }
            CButton {
                id: splice
                width: column.width
                textColor: "white"
                RadioButton {
                    id: spliceRadio
                    visible: false
                    exclusiveGroup: checkGroup
                    onCheckedChanged: {
                        if (spliceRadio.checked) {
                            splice.backgroundItem.source = "qrc:/images/images/icon-bg.png"
                            headRepeater.model = spliceTitleModel
                            viewLib.count = spliceTitleModel.count
                            button2.x = 0
                            listView.model = spliceModel
                        }
                        else {
                            splice.backgroundItem.source = ""

                        }
                    }
                }
                backgroundComponent: Image {
                    anchors.fill: parent
                    source: ""
                }
                onClicked: {
                    if (!spliceRadio.checked)
                        spliceRadio.checked = !spliceRadio.checked
                }
                Line {
                    width: parent.width
                    height: 1
                    lineColor: "#1987ab"
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 3

                }
                Image {
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.right: parent.right
                    anchors.rightMargin: 18
                    source: "qrc:/images/images/right.png"
                }
                Text {
                    text: qsTr("Splice")
                    font.pointSize: 20
                    font.family: "arial"
                    color: "white"
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    anchors.leftMargin: 10
                }
            }
            CButton {
                id: wire
                width: column.width
                textColor: "white"
                RadioButton {
                    id: wireRadio
                    visible: false
                    exclusiveGroup: checkGroup
                    onCheckedChanged: {
                        if (wireRadio.checked) {
                            wire.backgroundItem.source = "qrc:/images/images/icon-bg.png"
                            headRepeater.model = wireTitleModel
                            viewLib.count = wireTitleModel.count
                            button2.x = 0
                            listView.model = wireModel
                        }
                        else {
                            wire.backgroundItem.source = ""
                        }
                    }
                }
                backgroundComponent: Image {
                    anchors.fill: parent
                    source: ""
                }
                onClicked: {
                    if (!wireRadio.checked)
                        wireRadio.checked = !wireRadio.checked
                }
                Line {
                    width: parent.width
                    height: 1
                    lineColor: "#1987ab"
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 3
                }
                Image {
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.right: parent.right
                    anchors.rightMargin: 18
                    source: "qrc:/images/images/right.png"
                }
                Text {
                    text: qsTr("Wire")
                    font.pointSize: 20
                    font.family: "arial"
                    color: "white"
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    anchors.leftMargin: 10
                }
            }

            CButton {
                id: shrink
                width: column.width
                textColor: "white"
                RadioButton {
                    id: shrinkRadio
                    visible: false
                    exclusiveGroup: checkGroup
                    onCheckedChanged: {
                        if (shrinkRadio.checked) {
                            shrink.backgroundItem.source = "qrc:/images/images/icon-bg.png"
                            headRepeater.model = shrinkTitleModel
                            viewLib.count = shrinkTitleModel.count
                            button2.x = 0
                            listView.model = shrinkModel
                        }
                        else {
                            shrink.backgroundItem.source = ""
                        }
                    }
                }
                backgroundComponent: Image {
                    anchors.fill: parent
                    source: ""
                }
                onClicked: {
                    if (!shrinkRadio.checked)
                        shrinkRadio.checked = !shrinkRadio.checked
                }
                Line {
                    width: parent.width
                    height: 1
                    lineColor: "#1987ab"
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 3
                }
                Image {
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.right: parent.right
                    anchors.rightMargin: 18
                    source: "qrc:/images/images/right.png"
                }
                Text {
                    text: qsTr("Insulation")
                    font.pointSize: 20
                    font.family: "arial"
                    color: "white"
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    anchors.leftMargin: 10
                }
            }
        }
    }
    ListModel {
        id: shrinkTitleModel
    }

    ListModel {
        id: shrinkModel
    }

    ListModel {
        id: partKeyModel
    }
    ListModel {
        id: partTitleModel
    }
    ListModel {
        id: spliceTitleModel
    }
    ListModel {
        id: wireTitleModel
//        list << "partId" << "name" << "date" << "totalSplices" << "type" << "operatorName" << "processMode" << "ofWorkstation" << "ofSplicesperWorkstation" << "rows" << "columns" << "maxSplicesPerZone";

        Component.onCompleted: {
            initPage()
            partKeyModel.append({"title":qsTr("name")})
            partKeyModel.append({"title":qsTr("date")})
            partKeyModel.append({"title":qsTr("totalSplices")})
            partKeyModel.append({"title":qsTr("type")})
            partKeyModel.append({"title":qsTr("operatorName")})
            partKeyModel.append({"title":qsTr("processMode")})
            partKeyModel.append({"title":qsTr("ofWorkstation")})
            partKeyModel.append({"title":qsTr("ofSplicesperWorkstation")})
            partKeyModel.append({"title":qsTr("rows")})
            partKeyModel.append({"title":qsTr("columns")})
            partKeyModel.append({"title":qsTr("maxSplicesPerZone")})

            shrinkTitleModel.append({title:qsTr("Insulation Name")})
            shrinkTitleModel.append({title:qsTr("Temp(℃)")})
            shrinkTitleModel.append({title:qsTr("Time(S)")})

            partTitleModel.append({"title":qsTr("PartName")})
            partTitleModel.append({"title":qsTr("DateCreated")})
            partTitleModel.append({"title":qsTr("OperatorName")})
            partTitleModel.append({"title":qsTr("TotalSplices")})
            partTitleModel.append({"title":qsTr("ProcessMode")})
            partTitleModel.append({"title":qsTr("#ofWorkstation")})
            partTitleModel.append({"title":qsTr("#ofSplicesperWorkstation")})
            partTitleModel.append({"title":qsTr("Rows")})
            partTitleModel.append({"title":qsTr("Columns")})
            partTitleModel.append({"title":qsTr("MaxSplicesPerZone")})

            spliceTitleModel.append({"title":qsTr("SpliceName")})
            spliceTitleModel.append({"title":qsTr("DateCreated")})
            spliceTitleModel.append({"title":qsTr("OperatorName")})
            spliceTitleModel.append({"title":qsTr("CrossSection")})
            spliceTitleModel.append({"title":qsTr("TotalWires")})
            spliceTitleModel.append({"title":qsTr("Verified")})
            spliceTitleModel.append({"title":qsTr("WeldMode")})
            spliceTitleModel.append({"title":qsTr("Energy")})
            spliceTitleModel.append({"title":qsTr("Amplitude")})
            spliceTitleModel.append({"title":qsTr("Width")})
            spliceTitleModel.append({"title":qsTr("TriggerPressure")})
            spliceTitleModel.append({"title":qsTr("WeldPressure")})
            spliceTitleModel.append({"title":qsTr("Time+")})
            spliceTitleModel.append({"title":qsTr("Time-")})
            spliceTitleModel.append({"title":qsTr("Power+")})
            spliceTitleModel.append({"title":qsTr("Power-")})
            spliceTitleModel.append({"title":qsTr("Pre-Height+")})
            spliceTitleModel.append({"title":qsTr("Pre-Height-")})
            spliceTitleModel.append({"title":qsTr("Height+")})
            spliceTitleModel.append({"title":qsTr("Height-")})

//            list <<"WireId"<< "WireName" << "DateCreated" << "OperatorName" << "Color" << "StripeType" << "StripeColor" << "Gauge" << "MetalType" << "HorizontalLocation" << "VerticalLocation" << "VerticalPosition";
            wireTitleModel.append({"title":qsTr("WireName")})
            wireTitleModel.append({"title":qsTr("DateCreated")})
            wireTitleModel.append({"title":qsTr("OperatorName")})
            wireTitleModel.append({"title":qsTr("Color")})
            wireTitleModel.append({"title":qsTr("StripeType")})
            wireTitleModel.append({"title":qsTr("StripeColor")})
            wireTitleModel.append({"title":qsTr("Gauge")})
            wireTitleModel.append({"title":qsTr("MetalType")})
            wireTitleModel.append({"title":qsTr("HorizontalLocation")})
            wireTitleModel.append({"title":qsTr("VerticalLocation")})
            wireTitleModel.append({"title":qsTr("VerticalPosition")})
        }
    }
    Image {
        id: back
        anchors.left: leftArea.right
        width: parent.width-leftArea.width
        height: parent.height
        source: "qrc:/images/images/bg.png"
    }
    Rectangle {
        id: tipsRec
        anchors.top: headTitle.bottom
        anchors.topMargin: 10
        anchors.left: leftArea.right
        anchors.leftMargin: 20
        anchors.right: parent.right
        anchors.rightMargin: 20
        clip: true
        height: 2
        color: "#ffffff"
    }
    Row {
        id: headTitle
        anchors.top: parent.top
        anchors.topMargin: 15
        anchors.left: tipsRec.left
        anchors.leftMargin: 20
        spacing: 30
        clip: true
        Repeater {
            id: headRepeater
            model: partTitleModel
            delegate:  Text {
                id: tempTitle
                verticalAlignment: Qt.AlignVCenter
                width: 200
                font.family: "arial"
                font.pixelSize: 25
                color: "white"
                clip: true
                elide: Text.ElideRight
                text: title
//                Rectangle {
//                    id: rect
//                    width: 10
//                    height: parent.height
//                    anchors.right: parent.right
//                    MouseArea {
//                        id: mymouse
//                        anchors.fill: parent
//                        cursorShape: Qt.SizeHorCursor
//                        drag.target: parent
//                        drag.axis: Drag.XAxis
//                        drag.maximumX: 400
//                        drag.minimumX: 200
//                        hoverEnabled: true
////                        onMouseXChanged: {
////                            if (mouse.accepted)
////                            {
////                                parent.parent.width = 200 + mouseX
////                            }
////                        }
//                    }
//                    onXChanged: {
//                        if (mymouse.pressed) {
//                            console.log("xxxxxxxxxxxxx",rect.x)
//                            parent.width = 200 + rect.x
//                        }
//                    }
//                }
            }
        }
    }


    Rectangle {
        id: tipsRec2
        anchors.top: tipsRec.bottom
        anchors.left: leftArea.right
        anchors.leftMargin: 20
        anchors.right: parent.right
        anchors.rightMargin: 20
        clip: true
        height: 1
        color: "#0d0f11"
    }

    ListView {
        id: listView
        anchors.top: tipsRec2.bottom
        anchors.topMargin: 5
        anchors.bottom: scrollbar2.top
        anchors.left: tipsRec2.left
        anchors.leftMargin: 20
        width: headTitle.width
        clip: true
        model: partModel
        delegate: listDelegate
    }
    Image {
        id: scrollLeft
        anchors.verticalCenter:scrollbar2.verticalCenter
        anchors.right: scrollbar2.left
        width: 11
        height: 17
        visible: listView.width > scrollbar2.width ? true : false
        source: "qrc:/images/images/left.png"
    }
    Image {
        id: scrollRight
        anchors.verticalCenter:scrollbar2.verticalCenter
        anchors.left: scrollbar2.right
        width: 11
        height: 17
        visible: listView.width > scrollbar2.width ? true : false
        source: "qrc:/images/images/right.png"
    }
    Image {
        id: scrollUp
        anchors.top: tipsRec2.bottom
        anchors.topMargin: 2
        anchors.right: parent.right
        anchors.rightMargin: 6
        width: 17
        height: 10
        visible: listView.contentHeight > listView.height ? true : false
        source: "qrc:/images/images/up.png"
    }
    Image {
        id: scrollDown
        anchors.bottom: scrollbar2.top
        anchors.bottomMargin: 2
        anchors.right: parent.right
        anchors.rightMargin: 6
        width: 17
        height: 10
        visible: listView.contentHeight > listView.height ? true : false
        source: "qrc:/images/images/down.png"
    }
    Rectangle {
        id: scrollbar
        width: 10
        height: listView.height-24
        anchors.top: scrollUp.bottom
        anchors.right: parent.right
        anchors.rightMargin: 8
        color: "#585858"
        radius: 10
        visible: listView.contentHeight > listView.height ? true : false
        Rectangle {
            id: button
            anchors.left: parent.left
            y: (listView.visibleArea.yPosition < 0 ) ? 0 : (listView.contentY+listView.height>listView.contentHeight) ?
                scrollbar.height - button.height : listView.visibleArea.yPosition * scrollbar.height
            width: 10
            height: listView.visibleArea.heightRatio * scrollbar.height // < 5 ? 20 : listView.visibleArea.heightRatio * scrollbar.height;
            color: "#ccbfbf"
            radius: 10
            // 鼠标区域
        }
        MouseArea {
            id: mouseArea
//                anchors.fill: button
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: button.top
            height: button.height < 5 ? 20 : button.height
            drag.target: button
            drag.axis: Drag.YAxis
            drag.minimumY: 0
            drag.maximumY: scrollbar.height - button.height
            // 拖动
            onMouseYChanged: {
                listView.contentY = (button.y + button.height) / scrollbar.height * listView.contentHeight
            }
            Rectangle {
                anchors.fill: parent
                color: "#585858"
                radius: 10

            }
        }
    }
    Rectangle {
        id: scrollbar2
        anchors.left: tipsRec2.left
        anchors.leftMargin: 11
        anchors.bottom: rowButton.top
        anchors.bottomMargin: 20
        width: tipsRec2.width-22
        height: 17
        color: "#585858"
        radius: 10
        visible: listView.width > scrollbar2.width ? true : false
        Rectangle {
            id: button2
            anchors.top: parent.top
            x: viewLib.buttonX
            width: scrollbar2.width / headTitle.width * scrollbar2.width
            height: 17
            color: "#ccbfbf"
            radius: 10
            // 鼠标区域
            MouseArea {
                id: mouseArea2
                anchors.fill: button2
                drag.target: button2
                drag.axis: Drag.XAxis
                drag.minimumX: 0
                drag.maximumX: scrollbar2.width - button2.width
            }
            onXChanged: {
                listView.anchors.leftMargin = -button2.x/scrollbar2.width*headTitle.width + 20
                headTitle.anchors.leftMargin = -button2.x/scrollbar2.width*headTitle.width + 20
            }
        }
    }
    ExclusiveGroup {
        id: listviewPositionGroup
    }
    Component {
        id: listDelegate
        Item {
            width: listView.width
            height: 50
            clip: true
            property var listIndex: 0
            Component.onCompleted: {
                listIndex = index
            }

            Row {
                width: parent.width
                height: parent.height
                spacing: 30
                clip: true
                Repeater {
                    id: listRepeater
                    model: viewLib.count
                    delegate:  Text {
                        id: tempText
                        property var newObject: null
                        anchors.verticalCenter: parent.verticalCenter
                        width: 200
                        font.family: "arial"
                        font.pixelSize: 20
                        color: "white"
                        clip: true
                        elide: Text.ElideRight
                        text: listView.model == shrinkModel ? shrinkGetValue(listIndex,index) : listView.model.getValue(listIndex,headRepeater.model.get(index).title)
                        MouseArea {
                            anchors.fill: parent
//                            z:10
                            hoverEnabled: true
                            onEntered: {
                                tempText.color = "red"
                                tempText.newObject = Qt.createQmlObject('import QtQuick 2.0;Rectangle {color: "#052a40";property alias mytext: tempText.text;height: tempText.height; width:tempText.width;Text {id: tempText;anchors.verticalCenter: parent.verticalCenter;text: qsTr("")
;font.family: "arial";font.pixelSize: 20;color: "white";wrapMode: Text.WordWrap; maximumLineCount: 60}}',listView,"");
                                tempText.newObject.mytext = tempText.text
//                                if (tempText.width > 600)
//                                    tempText.width = 600
//                                console.log("xxxxxxxxx",tempText.x,tempText.y)
                                tempText.newObject.x = tempText.x
                                tempText.newObject.y = tempText.y + listIndex * 50
//                                tempText.newObject.width = tempText.width
//                                tempText.newObject.height = tempText.height

                            }
                            onExited: {
                                tempText.color = "white"
                                tempText.newObject.destroy()
                            }
                        }
                    }
                }
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    selectIndx = index
                    selectCheck.checked = !selectCheck.checked
                }
            }
            Rectangle {
                id: backGround
                anchors.fill: parent
                color: "black"
                opacity: 0//opacityValue
                RadioButton {
                    id: selectCheck
                    exclusiveGroup: listviewPositionGroup
                    visible: false
                    onCheckedChanged: {
                        if (checked)
                            backGround.opacity = 0.3
                        else
                            backGround.opacity = 0
                    }
                }
            }
        }
    }


    Row {
        id: rowButton
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 20
        anchors.right: parent.right
        anchors.rightMargin: 20
        anchors.left: leftArea.right
        anchors.leftMargin: 20
        spacing: 18
        CButton {
            width: (parent.width-54)/4
            textColor: "white"
            text: qsTr("Edit Details")
            onClicked: {
                if (partRadio.checked)
                    root.menuInit(0)
                else if (spliceRadio.checked)
                    root.menuInit(0)
                else if (wireRadio.checked)
                    root.menuInit(19)
                else if (shrinkRadio.checked){
                    backGround.visible = true
                    dialog.visible = true
                }
            }
        }
        CButton {
            width: (parent.width-54)/4
            textColor: "white"
            text: qsTr("Delete")
            onClicked: {
                if (partRadio.checked)
                    partModel.removeValue(partModel.getValue(selectIndx,"PartId"),partModel.getValue(selectIndx,"PartName"))
                else if (spliceRadio.checked)
                    spliceModel.removeValue(spliceModel.getValue(selectIndx,"SpliceId"),spliceModel.getValue(selectIndx,"SpliceName"))
                else if (wireRadio.checked)
                    wireModel.removeValue(wireModel.getValue(selectIndx,"WireId"),wireModel.getValue(selectIndx,"WireName"))
                else if (shrinkRadio.checked){
                    shrinkModel.remove(selectIndx)
                }
            }
        }
        CButton {
            width: (parent.width-54)/4
            textColor: "white"
            text: qsTr("Export")
        }
        CButton {
            width: (parent.width-54)/4
            textColor: "white"
            text: qsTr("Back")
        }
    }
    Rectangle {
        id: backGround
        z: leftArea.z+1
        anchors.fill: parent
        color: "black"
        opacity: 0.5
        visible: false
        MouseArea {
            anchors.fill: parent
            onClicked: {
            }
        }

    }
    Image {
        id: dialog
        visible: false
        anchors.centerIn: parent
        width: 639
        height: 390
        z: leftArea.z+2
        source: "qrc:/images/images/dialogbg.png"
        onVisibleChanged: {
            if (dialog.visible) {
                inputTemperature.inputText = shrinkModel.get(selectIndx).temperature
                inputtimeText.inputText = shrinkModel.get(selectIndx).times
            }
        }

        Text {
            id: shrinkId
            anchors.top: parent.top
            anchors.topMargin: 60
            anchors.right: inputshrinkId.left
            anchors.rightMargin: 20
            width: 150
            height: 60
            font.pointSize: 18
            font.family: "arial"
            text: qsTr("Shrink Tube ID")
            verticalAlignment: Qt.AlignVCenter
            horizontalAlignment: Qt.AlignRight
            color: "white"
        }
        MyLineEdit {
            id: inputshrinkId
            anchors.top: parent.top
            anchors.topMargin: 60
            anchors.right: parent.right
            anchors.rightMargin: 72
            horizontalAlignment: Qt.AlignHCenter
            width: 375
            height: 60
            inputWidth: 375
            inputColor: "white"
            inputHeight: 60
            inputText: shrinkModel.get(selectIndx).shrinkid
        }
        Text {
            id: temperatureText
            anchors.top: inputshrinkId.bottom
            anchors.topMargin: 20
            anchors.right: inputTemperature.left
            anchors.rightMargin: 20
            width: 150
            height: 60
            font.pointSize: 18
            font.family: "arial"
            text: qsTr("Temp")
            verticalAlignment: Qt.AlignVCenter
            horizontalAlignment: Qt.AlignRight
            color: "white"
        }
        MiniKeyNumInput {
            id: inputTemperature
            property var partId: 1
            anchors.top: inputshrinkId.bottom
            anchors.topMargin: 20
            anchors.right: parent.right
            anchors.rightMargin: 72
            width: 375
            height: 60
            inputWidth: 375
            inputText: shrinkModel.get(selectIndx).temperature
            onInputFocusChanged: {
                if (inputTemperature.inputFocus) {
                    keyNum.visible = true
                    keyNum.titleText = temperatureText.text
                    keyNum.currentValue = shrinkModel.get(selectIndx).temperature
                    keyNum.minvalue = "1"
                    keyNum.maxvalue = "20"
                }
            }
        }
        Text {
            id: timeText
            anchors.top: temperatureText.bottom
            anchors.topMargin: 20
            anchors.right: inputtimeText.left
            anchors.rightMargin: 20
            width: 150
            height: 60
            font.pointSize: 18
            font.family: "arial"
            text: qsTr("Time")
            verticalAlignment: Qt.AlignVCenter
            horizontalAlignment: Qt.AlignRight
            color: "white"
        }
        MiniKeyNumInput {
            id: inputtimeText
            property var partId: 1
            anchors.top: temperatureText.bottom
            anchors.topMargin: 20
            anchors.right: parent.right
            anchors.rightMargin: 72
            width: 375
            height: 60
            inputWidth: 375
            inputText: shrinkModel.get(selectIndx).times
            onInputFocusChanged: {
                if (inputtimeText.inputFocus) {
                    keyNum.visible = true
                    keyNum.titleText = timeText.text
                    keyNum.currentValue = shrinkModel.get(selectIndx).times
                    keyNum.minvalue = "1"
                    keyNum.maxvalue = "20"
                }
            }
        }
        CButton {
            id: cancel
            anchors.right: sure.left
            anchors.rightMargin: 15
            anchors.top: timeText.bottom
            anchors.topMargin: 16
            width: 180
            text: qsTr("CANCEL")
            textColor: "white"
            iconSource: "qrc:/images/images/cancel.png"
            onClicked: {
                backGround.visible = false
                dialog.visible = false
            }
        }

        CButton {
            id: sure
            anchors.right: parent.right
            anchors.rightMargin: 72
            anchors.top: timeText.bottom
            anchors.topMargin: 16
            width: 180
            text: qsTr("OK")
            textColor: "white"
            iconSource: "qrc:/images/images/OK.png"
            onClicked: {
                shrinkModel.remove(selectIndx)
                shrinkModel.insert(selectIndx,{shrinkid:inputshrinkId.inputText,temperature:inputTemperature.inputText,times:inputtimeText.inputText})
                backGround.visible = false
                dialog.visible = false
            }
        }
    }
    KeyBoardNum {
        id: keyNum
        anchors.centerIn: parent
        z: leftArea.z+3
        width: 962
        height: 526
        visible: false
        titleText: ""
        maxvalue: "4"
        minvalue: "1"
        currentValue: "4"
        onCurrentClickIndex: {
            if (index == 15) {
                if (hmiAdaptor.comepareCurrentValue(keyNum.minvalue,keyNum.maxvalue,keyNum.inputText)) {
                    if (inputTemperature.inputFocus) {
                        inputTemperature.inputText = keyNum.inputText
                        inputTemperature.inputFocus = false
                    } else if (inputtimeText.inputFocus) {
                        inputtimeText.inputText = keyNum.inputText
                        inputtimeText.inputFocus = false
                    }

                    keyNum.visible = false
                    keyNum.inputText = ""
                    keyNum.tempValue = ""
                } else {
                    keyNum.timeRun = true
                }
            } else if (index == 11) {
                if (inputTemperature.inputFocus) {
                    inputTemperature.inputFocus = false
                } else if (inputtimeText.inputFocus) {
                    inputtimeText.inputFocus = false
                }
                keyNum.visible = false
                keyNum.inputText = ""
                keyNum.tempValue = ""
            }
        }
        onInputTextChanged: {
            if (keyNum.inputText != "") {
                if (inputTemperature.inputFocus) {
                    inputTemperature.inputText = keyNum.inputText
                } else if (inputtimeText.inputFocus) {
                    inputtimeText.inputText = keyNum.inputText
                }
            }
        }
    }
}
