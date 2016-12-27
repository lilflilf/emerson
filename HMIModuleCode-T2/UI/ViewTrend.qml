import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import QtQuick.Dialogs 1.2

Item {
    id: viewTrend
    property var datalist: new Array()
    property var weldActualLsit: new Array()
    property var statisticsList: new Array()
    width: Screen.width*0.7
    height: Screen.height*0.6
    MyTimeSelect {
        id: newCalendar
        anchors.centerIn: parent
        z: 12
        visible: false
    }
    Rectangle {
        id: back
        width: parent.width * 0.3
        height: parent.height
        color: "#052a40"
        z: 10

        Text {
            id: seach
            text: qsTr("Seach")
            font.family: "arial"
            color: "white"
            font.pointSize: 16
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.leftMargin: 20
            anchors.topMargin: 10
        }
        Line {
            id: line
            anchors.top: seach.bottom
            anchors.topMargin: 10
            anchors.left: parent.left
            anchors.leftMargin: 10
            width: parent.width-58
            height: 1
            lineColor: "#375566"
        }

        Item {
            id: searchArea
            property int selectNum: -2
            property int buttonIndex: -1
            anchors.left: seach.left
            anchors.right: parent.right
            anchors.rightMargin: 48
            anchors.top: seach.bottom
            anchors.bottom: parent.bottom
            z: 12
            visible: false
            Image {
                anchors.fill: parent
                source: "qrc:/images/images/bg.png"
            }
            ExclusiveGroup {
                id: searchMos
            }
            Text {
                id: allText
                anchors.top: parent.top
                anchors.left: parent.left
                anchors.leftMargin: 6
                font.family: "arial"
                font.pixelSize: 16
                verticalAlignment: Qt.AlignVCenter
                width: parent.width
                height: 40
                color: "white"
                text: qsTr("All")
                visible: false
                MouseArea {
                    anchors.top: parent.top
                    anchors.left: parent.left
                    anchors.leftMargin: -6
                    width: parent.width
                    height: parent.height
                    onClicked: {
                        searchArea.selectNum = -2
                        selectCheck.checked = !selectCheck.checked
                    }
                }
                Rectangle {
                    id: backGround
                    anchors.top: parent.top
                    anchors.left: parent.left
                    anchors.leftMargin: -6
                    width: parent.width
                    height: parent.height
                    color: "black"
                    opacity: 0.3//opacityValue
                    RadioButton {
                        id: selectCheck
                        exclusiveGroup: searchMos
                        visible: false
                        checked: true
                        onCheckedChanged: {
                            if (checked)
                                backGround.opacity = 0.3
                            else
                                backGround.opacity = 0
                        }
                    }
                }
            }

            ListView {
                id: searchList
                anchors.top: parent.top
                anchors.left: parent.left
                width: parent.width
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 20
                clip: true
                model: spliceModel
                delegate: Component {
                    id: seachComponent
                    Item {
                        width: searchList.width
                        height: 40
                        Text {
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.left: parent.left
                            anchors.leftMargin: 6
                            font.family: "arial"
                            font.pixelSize: 16
                            color: "white"
                            elide: Text.ElideRight
                            text: SpliceName
                        }
                        MouseArea {
                            anchors.fill: parent
                            onClicked: {
                                searchArea.selectNum = index
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
                                exclusiveGroup: searchMos
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
            }
            CButton {
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 10
                anchors.left: parent.left
                width: parent.width
                text: qsTr("OK")
                iconSource: "qrc:/images/images/OK.png"
                onClicked: {
                    if (searchArea.selectNum != -2) {
                        searchArea.visible = false
                        workOrderName.text = searchList.model.getValue(searchArea.selectNum,"SpliceName")
                    }/* else {
                        searchArea.visible = false
                        workOrderName.text = qsTr("All")
                    }*/
                }
            }
        }

        Text {
            id: title2
            text: qsTr("Splice Number")
            font.family: "arial"
            color: "white"
            font.pointSize: 16
            anchors.top: line.bottom
            anchors.topMargin: 10
            anchors.left: seach.left
        }
        CButton {
            id: workOrderName
            anchors.left: title2.left
            anchors.leftMargin: 10
            anchors.right: parent.right
            anchors.rightMargin: 48
            anchors.top: title2.bottom
            text: qsTr("Click to Select")
            clip: true
            height: mytimeSelect1.height
            backgroundComponent: Rectangle {
                anchors.fill: parent
                color: "#052a40"
                border.color: "#1987ab"
                border.width: 2
            }
            onClicked: {
                searchArea.visible = true
            }
        }
        Text {
            id: date
            text: qsTr("Date and Time")
            font.family: "arial"
            color: "white"
            font.pointSize: 16
            anchors.top: workOrderName.bottom
            anchors.left: parent.left
            anchors.leftMargin: 20
            anchors.topMargin: 10
        }
        Text {
            id: from
            text: qsTr("From:")
            font.family: "arial"
            color: "white"
            font.pointSize: 16
            anchors.top: date.bottom
            anchors.left: parent.left
            anchors.leftMargin: 20
        }
    ExclusiveGroup {
        id: timeSelectGroup
    }

    MyCalendar {
        id: mycalendar1
        anchors.left: from.left
        anchors.leftMargin: 10
        anchors.top: from.bottom
        width: (parent.width-98)/2
        bIsdate: true
        selecter: newCalendar
        exclusiveGroup: timeSelectGroup
    }

    MyCalendar {
        id: mytimeSelect1
        width: (parent.width-98)/2
        anchors.top: mycalendar1.top
        anchors.left: mycalendar1.right
        anchors.leftMargin: 20
        bIsdate: false
        selecter: newCalendar
        exclusiveGroup: timeSelectGroup
    }

    Text {
        id: to
        text: qsTr("To:")
        font.family: "arial"
        color: "white"
        font.pointSize: 16
        anchors.top: mycalendar1.bottom
        anchors.left: parent.left
        anchors.leftMargin: 20
    }
    MyCalendar {
        id: mycalendar2
        bIsdate: true
        selecter: newCalendar
        exclusiveGroup: timeSelectGroup
        anchors.left: from.left
        anchors.leftMargin: 10
        anchors.top: to.bottom
        width: (parent.width-98)/2
    }

    MyCalendar {
        id: mytimeSelect2
        bIsdate: false
        selecter: newCalendar
        exclusiveGroup: timeSelectGroup
        width: (parent.width-98)/2
        anchors.top: mycalendar2.top
        anchors.left: mycalendar2.right
        anchors.leftMargin: 20
    }
    Column {
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.right: parent.right
        anchors.rightMargin: 48
        spacing: 10
            CButton {
                id: applyButton
                width: parent.width
                text: qsTr("APPLY")
                onClicked: {
                    if (newCalendar.visible) {
                        newCalendar.visible = false
                    }
                    if (workOrderName.text == qsTr("Click to Select")) {
                        return
                    } else {
                        var fromtime = hmiAdaptor.timeChangeToInt(mycalendar1.text + " " + mytimeSelect1.text)
                        var totime = hmiAdaptor.timeChangeToInt(mycalendar2.text + " " + mytimeSelect2.text)
                        var spliceId = spliceModel.getValue(searchArea.selectNum,"SpliceId")
                        hmiAdaptor.statisticalTrendApply(spliceId,workOrderName.text,fromtime,totime)
                        datalist = hmiAdaptor.getStatisticalTrendDataList(0)
                        qualityListViewTwo.model = datalist.length
                        selectRepeater.itemAt(0).bIsCheck = true
                        weldActualLsit = hmiAdaptor.getWeldActualParameterDataList(0)
                        for (var i = 0; i < leftTextModel.count; i++) {
                            leftTextModel.set(i,{myvalue:weldActualLsit[i]})
                        }
                        statisticsList = hmiAdaptor.getCurrentStatisticsParameterList(0)
                        for (var j = 0; j < rightTextModel.count; j++) {
                            rightTextModel.set(j,{myvalue:statisticsList[j]})
                        }
                    }
                }
            }
        }

    }

    Rectangle {
        id: fiveLine
        anchors.fill: qualityListViewTwo
        color: "#6d6e71"
        visible: qualityListViewTwo.visible
        Line {
            anchors.top: parent.top
            anchors.topMargin: parent.height / 2
            lineColor: "white"
            width: parent.width
            height: 2
        }
        Line {
            anchors.top: parent.top
            anchors.topMargin: parent.height * 0.1
            lineColor: "red"
            width: parent.width
            height: 2
        }
        Line {
            anchors.top: parent.top
            anchors.topMargin: parent.height * 0.2
            lineColor: "yellow"
            width: parent.width
            height: 2
        }
        Line {
            anchors.bottom: parent.bottom
            anchors.bottomMargin: parent.height * 0.2
            lineColor: "yellow"
            width: parent.width
            height: 2
        }
        Line {
            anchors.bottom: parent.bottom
            anchors.bottomMargin: parent.height * 0.1
            lineColor: "red"
            width: parent.width
            height: 2
        }
        Line {
            id: scrollLine
            width: 2
            height: parent.height
            lineColor: "green"
        }
    }

    ListView {
        id: qualityListViewTwo
        anchors.left: back.right
        anchors.leftMargin: 20
        anchors.right: parent.right
        anchors.rightMargin: 30
        height: Screen.height *0.32
        orientation: Qt.Horizontal
        //interactive: false
        anchors.top: parent.top
        anchors.topMargin: 20
        delegate: qualityListViewTwoDelegate
        model: datalist.length
    }
    Rectangle {
        id: scrollbar
        anchors.left: scrollLeft.right
        anchors.top: qualityListViewTwo.bottom
        anchors.bottom: selectButton.top
        anchors.topMargin: 10
        anchors.bottomMargin: 10
        anchors.right: scrollRight.left
        color: "#585858"
        radius: 10
        Rectangle {
            id: button
            anchors.top: parent.top
            x: 0
            width: 50
            height: scrollbar.height
            color: "#ccbfbf"
            radius: 10
            MouseArea {
                id: mouseArea
                anchors.fill: button
                drag.target: button
                drag.axis: Drag.XAxis
                drag.minimumX: 0
                drag.maximumX: scrollbar.width - button.width
            }
            onXChanged: {
                scrollLine.x = button.x/(scrollbar.width-50)*qualityListViewTwo.width
                qualityListViewTwo.currentIndex = scrollLine.x*qualityListViewTwo.contentWidth/qualityListViewTwo.width/8
                weldActualLsit = hmiAdaptor.getWeldActualParameterDataList((scrollLine.x/8).toFixed(0))
                for (var i = 0; i < leftTextModel.count; i++) {
                    leftTextModel.set(i,{myvalue:weldActualLsit[i]})
                }
            }
        }
    }

    Image {
        id: scrollLeft
        anchors.left: qualityListViewTwo.left
        anchors.verticalCenter: scrollbar.verticalCenter
        width: 11
        height: 17
        source: "qrc:/images/images/left.png"
    }
    Image {
        id: scrollRight
        anchors.right: qualityListViewTwo.right
        anchors.verticalCenter: scrollbar.verticalCenter
        width: 11
        height: 17
        source: "qrc:/images/images/right.png"
    }
    Component {
        id: qualityListViewTwoDelegate
        Item {
            width: 8
            height: Screen.height * 0.25
            Rectangle {
                id: point
                radius: 100
                width: 4
                height: 4
                anchors.top: parent.top
                anchors.topMargin: 50
                Component.onCompleted: {
                    point.anchors.topMargin = hmiAdaptor.randPoint() + qualityListViewTwo.height / 2 - 20
                }
            }
        }
    }
    ExclusiveGroup {
        id: weldModelGrop
    }

    Row {
        id: selectButton
        anchors.left: back.right
        anchors.leftMargin: 20
        anchors.top: qualityListViewTwo.bottom
        anchors.topMargin: 50
        spacing: 30
        Repeater {
            id: selectRepeater
            model : [qsTr("Time"),qsTr("Pre-Height"),qsTr("Post-Hight"),qsTr("Peak Power")]
            CButton {
                id: timeButton
                property alias bIsCheck: weldModelCheck.checked
                width: (qualityListViewTwo.width - 90) / 4
                text: modelData
                textColor: weldModelCheck.checked ? "white" : "black"
                backgroundComponent: Rectangle {
                    anchors.centerIn: parent
                    anchors.fill: parent
                    radius: 3
                    color: weldModelCheck.checked ? "#0079c1" : "#ffffff"
                    Rectangle{
                        anchors.fill: parent
                        anchors.margins: 1
                        radius: 3
                        anchors.centerIn: parent
                        color: weldModelCheck.checked ? "#0079c1" : "#ffffff"
                    }
                }
                RadioButton {
                    id: weldModelCheck
                    exclusiveGroup: weldModelGrop
                    visible: false
                    checked: index == 0 ? true : false
                }
                onClicked: {
                    weldModelCheck.checked = !weldModelCheck.checked
                    datalist = hmiAdaptor.getStatisticalTrendDataList(index)
                    qualityListViewTwo.model = datalist.length
                    button.x = 0
                    weldActualLsit = hmiAdaptor.getWeldActualParameterDataList(0)
                    for (var i = 0; i < leftTextModel.count; i++) {
                        leftTextModel.set(i,{myvalue:weldActualLsit[i]})
                    }
                    statisticsList = hmiAdaptor.getCurrentStatisticsParameterList(index)
                    for (var j = 0; j < rightTextModel.count; j++) {
                        rightTextModel.set(j,{myvalue:statisticsList[j]})
                    }
                }
            }
        }
//        CButton {
//            id: preHeightButton
//            width: (qualityListViewTwo.width - 90) / 4
//            text: qsTr("Pre-Height")
//            backgroundComponent: Rectangle{
//                id: backColor2
//                anchors.fill: parent
//                anchors.margins: 1
//                radius: 3
//                anchors.centerIn: parent
//                color: "#ffffff"
//            }
//            textColor: weldModelCheck2.checked ? "white" : "black"
//            RadioButton {
//                id: weldModelCheck2
//                exclusiveGroup: weldModelGrop
//                visible: false
//                onCheckedChanged: {
//                    if (weldModelCheck2.checked)
//                        backColor2.color = "#0079c1"
//                    else
//                        backColor2.color = "#ffffff"
//                }
//            }
//        }
//        CButton {
//            id: postHightButton
//            width: (qualityListViewTwo.width - 90) / 4
//            text: qsTr("Post-Hight")
//            backgroundComponent: Rectangle{
//                id: backColor3
//                anchors.fill: parent
//                anchors.margins: 1
//                radius: 3
//                anchors.centerIn: parent
//                color: "#ffffff"
//            }
//            textColor: weldModelCheck3.checked ? "white" : "black"
//            RadioButton {
//                id: weldModelCheck3
//                exclusiveGroup: weldModelGrop
//                visible: false
//                onCheckedChanged: {
//                    if (weldModelCheck3.checked)
//                        backColor3.color = "#0079c1"
//                    else
//                        backColor3.color = "#ffffff"
//                }
//            }
//        }


//        CButton {
//            width: (qualityListViewTwo.width - 90) / 4
//            text: qsTr("Peak Power")
//        }
    }
    Text {
        id: bottomText
        anchors.left: qualityListViewTwo.left
        anchors.top: selectButton.bottom
        font.family: "arial"
        font.pointSize: 16
        color: "white"
        text: qsTr("Weld Actual Result\n")
    }
    ListModel {
        id: leftTextModel
        Component.onCompleted: {
            leftTextModel.append({"mytitle":qsTr("Cross section:"),"myvalue":""})
            leftTextModel.append({"mytitle":qsTr("Weld Time:"),"myvalue":""})
            leftTextModel.append({"mytitle":qsTr("Energy:"),"myvalue":"",})
            leftTextModel.append({"mytitle":qsTr("Peak Power:"),"myvalue":""})
            leftTextModel.append({"mytitle":qsTr("Weld Pressure:"),"myvalue":""})
            leftTextModel.append({"mytitle":qsTr("Pre-Heigh:"),"myvalue":""})
            leftTextModel.append({"mytitle":qsTr("Trigger Pressure:"),"myvalue":""})
            leftTextModel.append({"mytitle":qsTr("Post-Heigh:"),"myvalue":""})
            leftTextModel.append({"mytitle":qsTr("Amplitude:"),"myvalue":""})
            leftTextModel.append({"mytitle":qsTr("Part Name:"),"myvalue":""})
            leftTextModel.append({"mytitle":qsTr("Width:"),"myvalue":""})
            leftTextModel.append({"mytitle":qsTr("Date Created:"),"myvalue":""})
            leftTextModel.append({"mytitle":qsTr("Work Order Name:"),"myvalue":""})
        }
    }

    Grid {
        id: leftTextList
        anchors.left: qualityListViewTwo.left
        anchors.top: bottomText.bottom
        columnSpacing: 5
        columns: 2
        Repeater {
            model: leftTextModel
            delegate: Row {
                spacing: 5
                Text {
                    font.family: "arial"
                    font.pointSize: 16
                    color: "white"
                    width: qualityListViewTwo.width / 8 + 60
                    text: mytitle
                }
                Text {
                    font.family: "arial"
                    font.pointSize: 16
                    color: "white"
                    width: qualityListViewTwo.width / 8
                    text: myvalue
                }
//                Text {
//                    font.family: "arial"
//                    font.pointSize: 16
//                    color: "white"
//                    width: qualityListViewTwo.width / 8 + 40
//                    text: mytitle2
//                }
//                Text {
//                    font.family: "arial"
//                    font.pointSize: 16
//                    color: "white"
//                    width: qualityListViewTwo.width / 8
//                    text: myvalue2
//                }
            }
        }
    }

    Text {
        id: bottomText2
        anchors.left: leftTextList.right
        anchors.leftMargin: 30
        anchors.top: selectButton.bottom
        font.family: "arial"
        font.pointSize: 16
        color: "white"
        text: qsTr("Statistics\n")
    }
    ListModel {
        id: rightTextModel
        Component.onCompleted: {
            rightTextModel.append({"mytitle":qsTr("Sample Size:"),"myvalue":""})
            rightTextModel.append({"mytitle":qsTr("Mean:"),"myvalue":""})
            rightTextModel.append({"mytitle":qsTr("Median:"),"myvalue":""})
            rightTextModel.append({"mytitle":qsTr("Sigma:"),"myvalue":""})
            rightTextModel.append({"mytitle":qsTr("CPK:"),"myvalue":""})
        }
    }
    Column {
        id: rightTextList
        anchors.left: bottomText2.left
        anchors.top: bottomText2.bottom
        Repeater {
            model: rightTextModel
            delegate: Row {
                spacing: 5
                Text {
                    font.family: "arial"
                    font.pointSize: 16
                    color: "white"
                    width: qualityListViewTwo.width / 8 + 40
                    text: mytitle
                }
                Text {
                    font.family: "arial"
                    font.pointSize: 16
                    color: "white"
                    width: qualityListViewTwo.width / 8
                    text: myvalue
                }
            }
        }
    }

    CButton {
        anchors.bottom: parent.bottom
        anchors.right: selectButton.right
        width: 200
        text: qsTr("Export Data")
        iconSource: "qrc:/images/images/export.png"
    }
}
