import QtQuick 2.4
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2
import QtQuick.Controls 1.1

Item {
    id: detail
    width: Screen.width * 0.8
    height: Screen.height *0.5
    property alias leftModel: listModelLeft
    property alias rightModel: listModelRight
    property alias centerVisable: centerButton.visible
    property alias topLeft: topLeft

    property var selectColor: ""
    property var selectText: ""
    property var selectDirection: ""
    property var selectPosition: ""
    property var selectIndex: 0
    property var selectLocation: ""
    property var wireCount: 0
    property var wireName: " "
    property var selectWireType: -1
    property var selectWireGauge: -1
    property var selectWireAWG: -1
    property var selectWireStripeColor: ""
    property var selectWireStripeType: -1
    property var selectWireId: -1
    property var selectModuleType: ""

    property bool isSafe: false
    property bool bIsLibrary: false
    signal wireSelected(var selectColor,var selectDirection,var selectPosition,var selectText,var selectWireName, var selectWireType, var selectWireStripeColor, var selectWireStripeType,var selectModuleType)
    signal changing(var bIsChang)
    signal gaugeChanged(var type, var value)
    signal wireDetailHide()


    function colorReverse(OldColorValue){
        OldColorValue="0x"+OldColorValue.replace(/#/g,"");
        var str
//                var str = "000000"+(0xFFFFFF-OldColorValue).toString(16);
//                str = "#" + str.substring(str.length-6,str.length);
        if (0xFFF000 > OldColorValue)
            str = "#ffffff"
        else
            str = "#000000"
        return str
    }

    function clear()
    {
        listModelLeft.clear()
        listModelRight.clear()
        topLeft.sourceComponent = null
        topRight.sourceComponent = null
        bottomLeft.sourceComponent = null
        bottomRight.sourceComponent = null
        detail.wireCount = 0

    }

    function setState(setPosition,setLine,setText,setColor)
    {
        selectColor = setColor
        selectText = setText
        if (setPosition == "topLeft")
            topLeft.sourceComponent = left
        else if (setPosition == "topRight")
            topRight.sourceComponent = right
        else if (setPosition == "bottomLeft")
            bottomLeft.sourceComponent = left
        else if (setPosition == "bottomRight")
            bottomRight.sourceComponent = right

    }

    function safeChange(change)
    {
        isSafe = change
        changing(change)
    }

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

    function addWireFromSplice()
    {
        if (listModelRight.count < 22) {
            bIsLibrary = true
            if (wireModel.getStructValue("WireDirection") == 0)
            {
                if (wireModel.getStructValue("WirePosition") == 0)
                {
                    if (topLeft.sourceComponent != null || topRight.sourceComponent != null)
                    {
                        return;
                    }
                    topLeft.sourceComponent = left
                    topLeft.item.lineLength = 200
                    topLeft.item.myColor = wireModel.getStructValue("WireColor")
                    topLeft.item.myText = hmiAdaptor.getStringValue(wireModel.getStructValue2("Gauge","current"))
                    topLeft.item.position = "topLeft"
                    topLeft.item.myWireName = wireModel.getStructValue("WireName")
                    topLeft.item.myGauge = wireModel.getStructValue("Gauge")
                    topLeft.item.myAwg = wireModel.getStructValue("AWG")
                    topLeft.item.myWireType = wireModel.getStructValue("WireType")
                    topLeft.item.myStripeColor = wireModel.getStructValue2("StripeColor","")
                    topLeft.item.myStripeType = wireModel.getStructValue3("StripeType","")
                    topLeft.item.myWireId = wireModel.getStructValue("WireId")
                }
                else if (wireModel.getStructValue("WirePosition") == 1)
                {
                    listModelLeft.append({"myLineLength":200,"mycolor":wireModel.getStructValue("WireColor"),"isCheck":false,"linetext":hmiAdaptor.getStringValue(wireModel.getStructValue2("Gauge","current")),
                                              "wireName":wireModel.getStructValue("WireName"),"wireType":wireModel.getStructValue("WireType"),"gauge":wireModel.getStructValue("Gauge"),"gaugeawg":wireModel.getStructValue("AWG"),
                                              "stripeColor":wireModel.getStructValue2("StripeColor",""),"stripeType":wireModel.getStructValue3("StripeType",""),"wireId":wireModel.getStructValue("WireId"),"moduleType":wireModel.getStructValue("ModuleType")})

                }
                else if (wireModel.getStructValue("WirePosition") == 2)
                {
                    bottomLeft.sourceComponent = left
                    bottomLeft.item.lineLength = 200
                    bottomLeft.item.myColor = wireModel.getStructValue("WireColor")
                    bottomLeft.item.myText = hmiAdaptor.getStringValue(wireModel.getStructValue2("Gauge","current"))
                    bottomLeft.item.position = "bottomLeft"
                    bottomLeft.item.myWireName = wireModel.getStructValue("WireName")
                    bottomLeft.item.myGauge = wireModel.getStructValue("Gauge")
                    bottomLeft.item.myAwg = wireModel.getStructValue("AWG")
                    bottomLeft.item.myWireType = wireModel.getStructValue("WireType")
                    bottomLeft.item.myStripeColor = wireModel.getStructValue2("StripeColor","")
                    bottomLeft.item.myStripeType = wireModel.getStructValue3("StripeType","")
                    bottomLeft.item.myWireId = wireModel.getStructValue("WireId")
                }
            }
            else if (wireModel.getStructValue("WireDirection") == 1)
            {
                if (wireModel.getStructValue("WirePosition") == 0)
                {
                    if (topLeft.sourceComponent != null || topRight.sourceComponent != null)
                    {
                        return;
                    }
                    topRight.sourceComponent = right
                    topRight.item.lineLength = 200
                    topRight.item.myColor = wireModel.getStructValue("WireColor")
                    topRight.item.myText = hmiAdaptor.getStringValue(wireModel.getStructValue2("Gauge","current"))
                    topRight.item.position = "topRight"
                    topRight.item.myWireName = wireModel.getStructValue("WireName")
                    topRight.item.myGauge = wireModel.getStructValue("Gauge")
                    topRight.item.myAwg = wireModel.getStructValue("AWG")
                    topRight.item.myWireType = wireModel.getStructValue("WireType")
                    topRight.item.myStripeColor = wireModel.getStructValue2("StripeColor","")
                    topRight.item.myStripeType = wireModel.getStructValue3("StripeType","")
                    topRight.item.myWireId = wireModel.getStructValue("WireId")
                }
                else if (wireModel.getStructValue("WirePosition") == 1)
                {
                    listModelRight.append({"myLineLength":200,"mycolor":wireModel.getStructValue("WireColor"),"isCheck":false,"linetext":hmiAdaptor.getStringValue(wireModel.getStructValue2("Gauge","current")),
                                              "wireName":wireModel.getStructValue("WireName"),"wireType":wireModel.getStructValue("WireType"),"gauge":wireModel.getStructValue("Gauge"),"gaugeawg":wireModel.getStructValue("AWG"),
                                              "stripeColor":wireModel.getStructValue2("StripeColor",""),"stripeType":wireModel.getStructValue3("StripeType",""),"wireId":wireModel.getStructValue("WireId"),"moduleType":wireModel.getStructValue("ModuleType")})

                }
                else if (wireModel.getStructValue("WirePosition") == 2)
                {
                    bottomRight.sourceComponent = right
                    bottomRight.item.lineLength = 200
                    bottomRight.item.myColor = wireModel.getStructValue("WireColor")
                    bottomRight.item.myText = hmiAdaptor.getStringValue(wireModel.getStructValue2("Gauge","current"))
                    bottomRight.item.position = "bottomRight"
                    bottomRight.item.myWireName = wireModel.getStructValue("WireName")
                    bottomRight.item.myGauge = wireModel.getStructValue("Gauge")
                    bottomRight.item.myAwg = wireModel.getStructValue("AWG")
                    bottomRight.item.myWireType = wireModel.getStructValue("WireType")
                    bottomRight.item.myStripeColor = wireModel.getStructValue2("StripeColor","")
                    bottomRight.item.myStripeType = wireModel.getStructValue3("StripeType","")
                    bottomRight.item.myWireId = wireModel.getStructValue("WireId")
                }
            }

            wireCount++
            gaugeChanged("add",wireModel.getStructValue("Gauge"))
            bIsLibrary = false
        }
    }

    function addWireFromLibrary()
    {
        if (listModelRight.count < 10) {
            bIsLibrary = true
//            if (wireModel.getStructValue("WireDirection") == 0)
//            {
//                if (wireModel.getStructValue("WirePosition") == 0)
//                {
//                    if (topLeft.sourceComponent != null || topRight.sourceComponent != null)
//                    {
//                        return;
//                    }
//                    topLeft.sourceComponent = left
//                    topLeft.item.lineLength = 200
//                    topLeft.item.myColor = wireModel.getStructValue("WireColor")
//                    topLeft.item.myText = hmiAdaptor.getStringValue(wireModel.getStructValue2("Gauge","current"))
//                    topLeft.item.position = "topLeft"
//                    topLeft.item.myWireName = wireModel.getStructValue("WireName")
//                    topLeft.item.myGauge = wireModel.getStructValue("Gauge")
//                    topLeft.item.myAwg = wireModel.getStructValue("AWG")
//                    topLeft.item.myWireType = wireModel.getStructValue("WireType")
//                    topLeft.item.myStripeColor = wireModel.getStructValue2("StripeColor","")
//                    topLeft.item.myStripeType = wireModel.getStructValue3("StripeType","")
//                    topLeft.item.myWireId = wireModel.getStructValue("WireId")
//                }
//                else if (wireModel.getStructValue("WirePosition") == 1)
//                {
//                    listModelLeft.append({"myLineLength":200,"mycolor":wireModel.getStructValue("WireColor"),"isCheck":false,"linetext":hmiAdaptor.getStringValue(wireModel.getStructValue2("Gauge","current")),
//                                              "wireName":wireModel.getStructValue("WireName"),"wireType":wireModel.getStructValue("WireType"),"gauge":wireModel.getStructValue("Gauge"),"gaugeawg":wireModel.getStructValue("AWG"),
//                                              "stripeColor":wireModel.getStructValue2("StripeColor",""),"stripeType":wireModel.getStructValue3("StripeType",""),"wireId":wireModel.getStructValue("WireId")})

//                }
//                else if (wireModel.getStructValue("WirePosition") == 2)
//                {
//                    bottomLeft.sourceComponent = left
//                    bottomLeft.item.lineLength = 200
//                    bottomLeft.item.myColor = wireModel.getStructValue("WireColor")
//                    bottomLeft.item.myText = hmiAdaptor.getStringValue(wireModel.getStructValue2("Gauge","current"))
//                    bottomLeft.item.position = "bottomLeft"
//                    bottomLeft.item.myWireName = wireModel.getStructValue("WireName")
//                    bottomLeft.item.myGauge = wireModel.getStructValue("Gauge")
//                    bottomLeft.item.myAwg = wireModel.getStructValue("AWG")
//                    bottomLeft.item.myWireType = wireModel.getStructValue("WireType")
//                    bottomLeft.item.myStripeColor = wireModel.getStructValue2("StripeColor","")
//                    bottomLeft.item.myStripeType = wireModel.getStructValue3("StripeType","")
//                    bottomLeft.item.myWireId = wireModel.getStructValue("WireId")
//                }
//            }
//            else if (wireModel.getStructValue("WireDirection") == 1)
//            {
//                if (wireModel.getStructValue("WirePosition") == 0)
//                {
//                    if (topLeft.sourceComponent != null || topRight.sourceComponent != null)
//                    {
//                        return;
//                    }
//                    topRight.sourceComponent = right
//                    topRight.item.lineLength = 200
//                    topRight.item.myColor = wireModel.getStructValue("WireColor")
//                    topRight.item.myText = hmiAdaptor.getStringValue(wireModel.getStructValue2("Gauge","current"))
//                    topRight.item.position = "topRight"
//                    topRight.item.myWireName = wireModel.getStructValue("WireName")
//                    topRight.item.myGauge = wireModel.getStructValue("Gauge")
//                    topRight.item.myAwg = wireModel.getStructValue("AWG")
//                    topRight.item.myWireType = wireModel.getStructValue("WireType")
//                    topRight.item.myStripeColor = wireModel.getStructValue2("StripeColor","")
//                    topRight.item.myStripeType = wireModel.getStructValue3("StripeType","")
//                    topRight.item.myWireId = wireModel.getStructValue("WireId")
//                }
//                else if (wireModel.getStructValue("WirePosition") == 1)
//                {
//                    listModelRight.append({"myLineLength":200,"mycolor":wireModel.getStructValue("WireColor"),"isCheck":false,"linetext":hmiAdaptor.getStringValue(wireModel.getStructValue2("Gauge","current")),
//                                              "wireName":wireModel.getStructValue("WireName"),"wireType":wireModel.getStructValue("WireType"),"gauge":wireModel.getStructValue("Gauge"),"gaugeawg":wireModel.getStructValue("AWG"),
//                                              "stripeColor":wireModel.getStructValue2("StripeColor",""),"stripeType":wireModel.getStructValue3("StripeType",""),"wireId":wireModel.getStructValue("WireId")})

//                }
//                else if (wireModel.getStructValue("WirePosition") == 2)
//                {
//                    bottomRight.sourceComponent = right
//                    bottomRight.item.lineLength = 200
//                    bottomRight.item.myColor = wireModel.getStructValue("WireColor")
//                    bottomRight.item.myText = hmiAdaptor.getStringValue(wireModel.getStructValue2("Gauge","current"))
//                    bottomRight.item.position = "bottomRight"
//                    bottomRight.item.myWireName = wireModel.getStructValue("WireName")
//                    bottomRight.item.myGauge = wireModel.getStructValue("Gauge")
//                    bottomRight.item.myAwg = wireModel.getStructValue("AWG")
//                    bottomRight.item.myWireType = wireModel.getStructValue("WireType")
//                    bottomRight.item.myStripeColor = wireModel.getStructValue2("StripeColor","")
//                    bottomRight.item.myStripeType = wireModel.getStructValue3("StripeType","")
//                    bottomRight.item.myWireId = wireModel.getStructValue("WireId")
//                }
//            }


                listModelRight.append({"myLineLength":200,"mycolor":wireModel.getStructValue("WireColor"),"isCheck":true,"linetext":hmiAdaptor.getStringValue(wireModel.getStructValue2("Gauge","current")),
                                          "wireName":wireModel.getStructValue("WireName"),"wireType":wireModel.getStructValue("WireType"),"gauge":wireModel.getStructValue("Gauge"),"gaugeawg":wireModel.getStructValue("AWG"),
                                          "stripeColor":wireModel.getStructValue2("StripeColor",""),"stripeType":wireModel.getStructValue3("StripeType",""),"wireId":-1,"moduleType":wireModel.getStructValue("ModuleType")}) //wireModel.getStructValue("WireId")



            wireCount++
            gaugeChanged("add",wireModel.getStructValue("Gauge"))
            bIsLibrary = false
        }
    }

    function addWire()
    {
        if (wireCount < 19 && listModelRight.count < 10) {
            listModelRight.append({"myLineLength":200,"mycolor":wireModel.getStructValue("WireColor"),"isCheck":false,"linetext":hmiAdaptor.getStringValue(wireModel.getStructValue2("Gauge","current")),
                "wireName":" ","wireType":wireModel.getStructValue("WireType"),"gauge":wireModel.getStructValue("Gauge"),"gaugeawg":wireModel.getStructValue("AWG"),
                "stripeColor":wireModel.getStructValue2("StripeColor",""),"stripeType":wireModel.getStructValue3("StripeType",""),"wireId":-1,"moduleType":wireModel.getStructValue("ModuleType")})
            wireCount++
            gaugeChanged("add",wireModel.getStructValue("Gauge"))
        }
    }
    function deleteWire()
    {
        if (selectPosition == "topRight") {
            gaugeChanged("sub",topRight.item.myGauge)
            topRight.sourceComponent = null
            selectPosition = ""
            if (wireCount > 0)
                wireCount--
            wireDetailHide()


        }
        else if (selectPosition == "bottomRight") {
            gaugeChanged("sub",bottomRight.item.myGauge)
            bottomRight.sourceComponent = null
            selectPosition = ""
            if (wireCount > 0)
                wireCount--
        }
        else if (selectPosition == "topLeft") {
            gaugeChanged("sub",topLeft.item.myGauge)
            topLeft.sourceComponent = null
            selectPosition = ""
            if (wireCount > 0)
                wireCount--
            wireDetailHide()

        }
        else if (selectPosition == "bottomLeft") {
            gaugeChanged("sub",bottomLeft.item.myGauge)
            bottomLeft.sourceComponent = null
            selectPosition = ""
            if (wireCount > 0)
                wireCount--
        }
        else if (selectPosition == "rightList") {
            gaugeChanged("sub",listModelRight.get(selectIndex).gauge)
            selectPosition = ""
            listModelRight.remove(selectIndex,1)
            selectIndex = 0
            if (wireCount > 0)
                wireCount--
            wireDetailHide()

        }
        else if (selectPosition == "leftList") {
            gaugeChanged("sub",listModelLeft.get(selectIndex).gauge)
            selectPosition = ""
            listModelLeft.remove(selectIndex,1)
            selectIndex = 0
            if (wireCount > 0)
                wireCount--
            wireDetailHide()

        }
    }

    function saveAllWire()
    {
//        topLeft.sourceComponent = left
        var type = "insert"
        var wireIdList = new Array;
        var wireId;
        if (topLeft.sourceComponent != null)
        {
            if (topLeft.item.myWireId == -1)
                type = "insert"
            else
                type ="update"
            wireId = wireModel.insertValueToTable(type,topLeft.item.myWireName,topLeft.item.myWireId,hmiAdaptor.getCurrentOperatorId(),topLeft.item.myColor,
                                         topLeft.item.myStripeColor,topLeft.item.myStripeType,topLeft.item.myGauge,topLeft.item.myAwg,topLeft.item.myWireType,0,1,0,topLeft.item.myModuleType)

            if (wireId != -1)
                wireIdList.push(wireId)
        }
        if (listModelLeft.count > 0)
        {
            for (var j = 0;j < listModelLeft.count;j++) {
                if (listModelLeft.get(j).wireId == -1)
                    type = "insert"
                else
                    type ="update"
                wireId = wireModel.insertValueToTable(type,listModelLeft.get(j).wireName,listModelLeft.get(j).wireId,hmiAdaptor.getCurrentOperatorId(),listModelLeft.get(j).mycolor,
                                         listModelLeft.get(j).stripeColor,listModelLeft.get(j).stripeType,listModelLeft.get(j).gauge,listModelLeft.get(j).gaugeawg,listModelLeft.get(j).wireType,0,0,1,listModelLeft.get(j).moduleType)
                if (wireId != -1)
                    wireIdList.push(wireId)
            }
        }
        if (bottomLeft.sourceComponent != null)
        {
            if (bottomLeft.item.myWireId == -1)
                type = "insert"
            else
                type ="update"
            wireId = wireModel.insertValueToTable(type,bottomLeft.item.myWireName,bottomLeft.item.myWireId,hmiAdaptor.getCurrentOperatorId(),bottomLeft.item.myColor,
                                         bottomLeft.item.myStripeColor,bottomLeft.item.myStripeType,bottomLeft.item.myGauge,bottomLeft.item.myAwg,bottomLeft.item.myWireType,0,1,2,bottomLeft.item.myModuleType)
            if (wireId != -1)
                wireIdList.push(wireId)
        }

        if (topRight.sourceComponent != null)
        {
            if (topRight.item.myWireId == -1)
                type = "insert"
            else
                type ="update"
            wireId = wireModel.insertValueToTable(type,topRight.item.myWireName,topRight.item.myWireId,hmiAdaptor.getCurrentOperatorId(),topRight.item.myColor,
                                         topRight.item.myStripeColor,topRight.item.myStripeType,topRight.item.myGauge,topRight.item.myAwg,topRight.item.myWireType,1,1,0,topRight.item.myModuleType)
            if (wireId != -1)
                wireIdList.push(wireId)

        }
        if (listModelRight.count > 0)
        {
            for (var i = 0;i < listModelRight.count;i++) {
                if (listModelRight.get(i).wireId == -1)
                    type = "insert"
                else
                    type ="update"
                wireId = wireModel.insertValueToTable(type,listModelRight.get(i).wireName,listModelRight.get(i).wireId,hmiAdaptor.getCurrentOperatorId(),listModelRight.get(i).mycolor,listModelRight.get(i).stripeColor,listModelRight.get(i).stripeType,listModelRight.get(i).gauge,listModelRight.get(i).gaugeawg,listModelRight.get(i).wireType,1,0,1,listModelRight.get(i).moduleType)
                if (wireId != -1)
                    wireIdList.push(wireId)
            }
        }
        if (bottomRight.sourceComponent != null)
        {
            if (bottomRight.item.myWireId == -1)
                type = "insert"
            else
                type ="update"
            wireId = wireModel.insertValueToTable(type,bottomRight.item.myWireName,bottomRight.item.myWireId,hmiAdaptor.getCurrentOperatorId(),bottomRight.item.myColor,
                                         bottomRight.item.myStripeColor,bottomRight.item.myStripeType,bottomRight.item.myGauge,bottomRight.item.myAwg,bottomRight.item.myWireType,1,1,2,bottomRight.item.myModuleType)
            if (wireId != -1)
                wireIdList.push(wireId)
        }
        return wireIdList;
    }

    onSelectWireStripeTypeChanged: {
        if (selectPosition == "topRight") {
            topRight.item.myStripeType = selectWireStripeType
        }
        else if (selectPosition == "bottomRight") {
            bottomRight.item.myStripeType = selectWireStripeType
        }
        else if (selectPosition == "topLeft") {
            topLeft.item.myStripeType = selectWireStripeType
        }
        else if (selectPosition == "bottomLeft") {
            bottomLeft.item.myStripeType = selectWireStripeType
        }
        else if (selectPosition == "rightList") {
            listModelRight.set(selectIndex,{"stripeType":detail.selectWireStripeType})
        }
        else if (selectPosition == "leftList") {
            listModelLeft.set(selectIndex,{"stripeType":detail.selectWireStripeType})
        }
    }

    onSelectWireStripeColorChanged: {
        if (isSafe)
            return
        if (selectPosition == "topRight") {
            topRight.item.myStripeColor = selectWireStripeColor
        }
        else if (selectPosition == "bottomRight") {
            bottomRight.item.myStripeColor = selectWireStripeColor
        }
        else if (selectPosition == "topLeft") {
            topLeft.item.myStripeColor = selectWireStripeColor
        }
        else if (selectPosition == "bottomLeft") {
            bottomLeft.item.myStripeColor = selectWireStripeColor
        }
        else if (selectPosition == "rightList") {
            listModelRight.set(selectIndex,{"stripeColor":selectWireStripeColor.toString()})
        }
        else if (selectPosition == "leftList") {
            listModelLeft.set(selectIndex,{"stripeColor":selectWireStripeColor.toString()})
        }
    }

    onSelectWireGaugeChanged: {
        gaugeChanged("add",selectWireGauge)
        if (selectPosition == "topRight") {
            gaugeChanged("sub",topRight.item.myGauge)
            topRight.item.myGauge = selectWireGauge
        }
        else if (selectPosition == "bottomRight") {
            gaugeChanged("sub",bottomRight.item.myGauge)
            bottomRight.item.myGauge = selectWireGauge
        }
        else if (selectPosition == "topLeft") {
            gaugeChanged("sub",topLeft.item.myGauge)
            topLeft.item.myGauge = selectWireGauge
        }
        else if (selectPosition == "bottomLeft") {
            gaugeChanged("sub",bottomLeft.item.myGauge)
            bottomLeft.item.myGauge = selectWireGauge
        }
        else if (selectPosition == "rightList") {
            gaugeChanged("sub",listModelRight.get(selectIndex).gauge)
            listModelRight.set(selectIndex,{"gauge":detail.selectWireGauge})
        }
        else if (selectPosition == "leftList") {
            gaugeChanged("sub",listModelLeft.get(selectIndex).gauge)
            listModelLeft.set(selectIndex,{"gauge":detail.selectWireGauge})
        }
    }

    onSelectWireAWGChanged: {
        if (selectPosition == "topRight") {
            topRight.item.myAwg = selectWireAWG
        }
        else if (selectPosition == "bottomRight") {
            bottomRight.item.myAwg = selectWireAWG
        }
        else if (selectPosition == "topLeft") {
            topLeft.item.myAwg = selectWireAWG
        }
        else if (selectPosition == "bottomLeft") {
            bottomLeft.item.myAwg = selectWireAWG
        }
        else if (selectPosition == "rightList") {
            listModelRight.set(selectIndex,{"gaugeawg":detail.selectWireAWG})
        }
        else if (selectPosition == "leftList") {
            listModelLeft.set(selectIndex,{"gaugeawg":detail.selectWireAWG})
        }
    }

    onSelectModuleTypeChanged: {
        if (selectPosition == "topRight") {
            topRight.item.myModuleType = selectModuleType
        }
        else if (selectPosition == "bottomRight") {
            bottomRight.item.myModuleType = selectModuleType
        }
        else if (selectPosition == "topLeft") {
            topLeft.item.myModuleType = selectModuleType
        }
        else if (selectPosition == "bottomLeft") {
            bottomLeft.item.myModuleType = selectModuleType
        }
        else if (selectPosition == "rightList") {
            listModelRight.set(selectIndex,{"moduleType":detail.selectModuleType})

        }
        else if (selectPosition == "leftList") {
            listModelLeft.set(selectIndex,{"moduleType":detail.selectModuleType})
        }
    }

    onSelectWireTypeChanged:{
        if (selectPosition == "topRight") {
            topRight.item.myWireType = selectWireType
        }
        else if (selectPosition == "bottomRight") {
            bottomRight.item.myWireType = selectWireType
        }
        else if (selectPosition == "topLeft") {
            topLeft.item.myWireType = selectWireType
        }
        else if (selectPosition == "bottomLeft") {
            bottomLeft.item.myWireType = selectWireType
        }
        else if (selectPosition == "rightList") {
            listModelRight.set(selectIndex,{"wireType":detail.selectWireType})

        }
        else if (selectPosition == "leftList") {
            listModelLeft.set(selectIndex,{"wireType":detail.selectWireType})
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
                listModelLeft.append({"myLineLength":200,"mycolor":selectColor.toString(),"isCheck":false,"linetext":selectText,"wireName":wireName,"wireType":selectWireType,"gauge":selectWireGauge,"gaugeawg":selectWireAWG,"stripeColor":selectWireStripeColor.toString(),"stripeType":selectWireStripeType,"wireId":selectWireId,"moduleType":selectModuleType})
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
                bottomRight.sourceComponent = null
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
                listModelRight.append({"myLineLength":200,"mycolor":detail.selectColor,"isCheck":false,"linetext":selectText,"wireName":wireName,"wireType":selectWireType,"gauge":selectWireGauge,"gaugeawg":selectWireAWG,"stripeColor":selectWireStripeColor.toString(),"stripeType":selectWireStripeType,"wireId":selectWireId,"moduleType":selectModuleType})
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
            listModelLeft.append({"myLineLength":200,"mycolor":listModelRight.get(selectIndex).mycolor,"isCheck":false,"linetext":selectText,"wireName":wireName,"wireType":selectWireType,"gauge":selectWireGauge,"gaugeawg":selectWireAWG,"stripeColor":selectWireStripeColor.toString(),"stripeType":selectWireStripeType,"wireId":selectWireId,"moduleType":selectModuleType})
            listModelRight.remove(detail.selectIndex, 1)
            wirePositionGroup.current = null

            detail.selectPosition = "leftList"
            listModelLeft.set(listModelLeft.count - 1, {"isCheck":true})
            detail.selectIndex = listModelLeft.count - 1

        }
        else if (detail.selectPosition == "leftList" && selectDirection != "left"){

            listModelRight.append({"myLineLength":200,"mycolor":listModelLeft.get(selectIndex).mycolor,"isCheck":false,"linetext":selectText,"wireName":wireName,"wireType":selectWireType,"gauge":selectWireGauge,"gaugeawg":selectWireAWG,"stripeColor":selectWireStripeColor.toString(),"stripeType":selectWireStripeType,"wireId":selectWireId,"moduleType":selectModuleType})
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
//            sourceComponent: left
            onLoaded: {
                if (bIsLibrary)
                    return;
                topLeft.item.lineLength = 200
                topLeft.item.myColor = selectColor
                topLeft.item.myText = selectText
                topLeft.item.position = "topLeft"
                topLeft.item.myWireName = wireName
                topLeft.item.myGauge = selectWireGauge
                topLeft.item.myAwg = selectWireAWG
                topLeft.item.myWireType = selectWireType
                topLeft.item.myStripeColor = selectWireStripeColor
                topLeft.item.myStripeType = selectWireStripeType
                topLeft.item.myWireId = selectWireId
                topLeft.item.myModuleType = selectModuleType
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
                if (bIsLibrary)
                    return;
                topRight.item.lineLength = 200
                topRight.item.myColor = selectColor
                topRight.item.myText = selectText
                topRight.item.position = "topRight"
                topRight.item.myWireName = wireName
                topRight.item.myGauge = selectWireGauge
                topRight.item.myAwg = selectWireAWG
                topRight.item.myWireType = selectWireType
                topRight.item.myStripeColor = selectWireStripeColor

                topRight.item.myStripeType = selectWireStripeType
                topRight.item.myWireId = selectWireId
                topRight.item.myModuleType = selectModuleType

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
                if (bIsLibrary)
                    return;
                bottomLeft.item.lineLength = 200
                bottomLeft.item.myColor = selectColor
                bottomLeft.item.myText = selectText
                bottomLeft.item.position = "bottomLeft"
                bottomLeft.item.myWireName = wireName
                bottomLeft.item.myGauge = selectWireGauge
                bottomLeft.item.myAwg = selectWireAWG
                bottomLeft.item.myWireType = selectWireType
                bottomLeft.item.myStripeColor = selectWireStripeColor
                bottomLeft.item.myStripeType = selectWireStripeType
                bottomLeft.item.myWireId = selectWireId
                bottomLeft.item.myModuleType = selectModuleType

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
                if (bIsLibrary)
                    return;
                bottomRight.item.lineLength = 200
                bottomRight.item.myColor = selectColor
                bottomRight.item.myText = selectText
                bottomRight.item.position = "bottomRight"
                bottomRight.item.myWireName = wireName
                bottomRight.item.myGauge = selectWireGauge
                bottomRight.item.myAwg = selectWireAWG
                bottomRight.item.myWireType = selectWireType
                bottomRight.item.myStripeColor = selectWireStripeColor
                bottomRight.item.myStripeType = selectWireStripeType
                bottomRight.item.myWireId = selectWireId
                bottomRight.item.myModuleType = selectModuleType

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
        ListModel {
            id: listModelLeft
            Component.onCompleted: {
            }
        }
        ListModel {
            id: listModelRight
            Component.onCompleted: {
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
                addWire()
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
            property alias myWireName: myWireNameLeft.text
            property var myGauge: gauge//10
            property var myAwg: 37
            property var myWireType: 1
            property var myStripeColor: tripecolor.color //""
            property var myStripeType: -1
            property var myWireId: -1
            property var myModuleType: ""
            width: middle.width / 2 + 40
            height: position == "leftList" ? listModelLeft.count <= 5 ? detail.height * 0.1 + 10 : (listModelLeft.count > 5 && listModelLeft.count <= 10) ? 30 : index < (listModelLeft.count - 10) * 2 ? 15 : 30 : 30

            Rectangle {
                id: leftLine
                width: leftItem.position == "leftList" ? index % 2 && index < (listModelLeft.count - 10) * 2 ? myLineLength + 150 : myLineLength : 200
                height: myGauge / 100 < 1 ? 1 : myGauge / 100
                anchors.right: parent.right
                anchors.verticalCenter: leftRec.verticalCenter
            }
            Rectangle {
                id: leftRec
                width: 60
                height: leftItem.position == "leftList" ? listModelLeft.count <= 5 ? detail.height * 0.1 : 20 : detail.height * 0.1
                color: leftItem.position == "leftList" ? mycolor : ""
                anchors.right: leftLine.left
                anchors.verticalCenter: parent.verticalCenter
                Rectangle {
                    id: tripecolor
                    height: 5
                    width: leftItem.position == "leftList" ? (stripeType == 2 ? parent.height : parent.width) : (myStripeType == 2 ? parent.height : parent.width)
                    anchors.verticalCenter: parent.verticalCenter
                    color: leftItem.position == "leftList" ? stripeColor : myStripeColor
                    visible: leftItem.position == "leftList" ? (stripeType == 3 ? false : true) : (myStripeType == 3 ? false : true)
                    rotation: leftItem.position == "leftList" ? (stripeType == 0 ? 0 : stripeType == 1 ? 30 : stripeType == 2 ? 90 : 0) : (myStripeType == 0 ? 0 : myStripeType == 1 ? 30 : myStripeType == 2 ? 90 : 0)
                    clip: false
                }
                MouseArea {
//                    anchors.fill: parent
                    anchors.right: leftRec.right
                    height: leftRec.height
                    width: 120
                    onClicked: {
                        radioButtonLeft.checked = !radioButtonLeft.checked

                        if (leftItem.position != "leftList" && radioButtonLeft.checked)
                        {
                            changing(true)
                            detail.selectPosition = leftItem.position
                            detail.selectColor = leftRec.color
                            detail.selectText = mytextLeft.text
                            detail.selectDirection = "left"
                            detail.selectWireType = leftItem.myWireType
                            detail.selectWireGauge = leftItem.myGauge
                            detail.selectWireAWG = leftItem.myAwg
                            detail.selectWireStripeColor = leftItem.myStripeColor
                            detail.selectWireStripeType = leftItem.myStripeType
                            detail.selectWireId = leftItem.myWireId
                            detail.wireName = leftItem.myWireName
                            wireSelected(leftRec.color,"left",leftItem.position,wireModel.getStructValue4(leftItem.myGauge,leftItem.myAwg),myWireNameLeft.text,leftItem.myWireType,leftItem.myStripeColor.toString(),leftItem.myStripeType,leftItem.myModuleType)
                            changing(false)

                        }
                        else if (leftItem.position == "leftList" && radioButtonLeft.checked)
                        {
                            changing(true)
                            detail.selectPosition = leftItem.position
                            detail.selectIndex = index
                            detail.selectWireType = listModelLeft.get(index).wireType
                            detail.selectWireGauge = listModelLeft.get(index).gauge
                            detail.selectWireAWG = listModelLeft.get(index).gaugeawg
                            detail.selectWireStripeColor = listModelLeft.get(index).stripeColor
                            detail.selectWireStripeType = listModelLeft.get(index).stripeType
                            detail.selectWireId = listModelLeft.get(index).wireId
                            detail.selectColor = listModelLeft.get(index).mycolor
                            detail.selectText = listModelLeft.get(index).linetext
                            detail.wireName = listModelLeft.get(index).wireName
                            listModelLeft.set(index,{"isCheck":radioButtonLeft.checked})
                            detail.selectDirection = "left"
                            wireSelected(leftRec.color,"left",leftItem.position,wireModel.getStructValue4(listModelLeft.get(index).gauge,listModelLeft.get(index).gaugeawg),myWireNameLeft.text,listModelLeft.get(index).wireType,listModelLeft.get(index).stripeColor,listModelLeft.get(index).stripeType,listModelLeft.get(index).moduleType)
                            changing(false)

                        }
                        else if (leftItem.position == "leftList" && !radioButtonLeft.checked)
                        {
                            detail.selectIndex = -1
                            listModelLeft.set(index,{"isCheck":radioButtonLeft.checked})
                        }
                    }
                }
            }
            Rectangle {
                id: leftRect2
                width: 60
                height: leftItem.position == "leftList" ? listModelLeft.count <= 5 ? detail.height * 0.1 : 20 :  detail.height * 0.1
                color: leftRec.color //"white"
                anchors.right: leftRec.left
                anchors.verticalCenter: parent.verticalCenter
                Text {
                    id: mytextLeft
                    anchors.centerIn: parent
                    text: leftItem.position == "leftList" ? linetext : ""
                    font.family: "arial"
                    font.pointSize: 16
                    color: colorReverse(mycolor)
                    clip: true
                }
            }
            Text {
                id: myWireNameLeft
                width: leftRect2.width * 3
                anchors.right: leftRect2.left
                anchors.verticalCenter: leftRect2.verticalCenter
                horizontalAlignment: Qt.AlignRight

                anchors.rightMargin: 8
                font.family: "arial"
                font.pointSize: 16
                color: "white"
                text: wireName
                clip: true
            }

            RadioButton {
                id: radioButtonLeft
                checked: leftItem.position == "leftList" ? listModelLeft.get(index).isCheck : false
                exclusiveGroup: wirePositionGroup
                visible: false
                onCheckedChanged: {
                    nameLeft.visible = checked
                }

            }
            Rectangle {
                id: nameLeft
                width: leftRec.width + leftRect2.width + 5
                height: leftRec.height + 5
                color: Qt.rgba(0,0,0,0)
                border.color: "white"
                border.width: 1
//                anchors.centerIn: leftRec
                anchors.right: leftRec.right
                anchors.rightMargin: -2
                anchors.verticalCenter: leftRec.verticalCenter
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
            property alias myWireName: myWireNameRight.text
            property var myGauge: gauge //10
            property var myAwg: 37
            property var myWireType: 1 // wireTypeText.text
            property var myStripeColor:  tripecolor.color //"" // stripeColor.color
            property var myStripeType: -1
            property var myWireId: -1
            property var myModuleType: ""
            id: rightItem
            width: 300
            height: rightItem.position == "rightList" ? listModelRight.count <= 5 ? detail.height * 0.1 + 10 : 30 : 30//(listModelRight.count > 5 && listModelRight.count <= 10) ? 30 : index < (listModelRight.count - 10) * 2 ? 15 : 30 : 30
            Rectangle {
                id: rightLine
                width: 200 //rightItem.position == "rightList" ? index % 2 && index < (listModelRight.count - 10) * 2 ? myLineLength + 150 : myLineLength : 200
                height: myGauge / 100 < 1 ? 1 : myGauge / 100 // > 5 ? 12 : 6
                anchors.left: parent.left
                anchors.verticalCenter: rightRec.verticalCenter
            }
            Rectangle {
                id: rightRec
                width: 60
                height: rightItem.position == "rightList" ? listModelRight.count <= 5 ? detail.height * 0.1 : 20 :  detail.height * 0.1
                color: mycolor
                anchors.left: rightLine.right
                anchors.verticalCenter: parent.verticalCenter
                Rectangle {
                    id: tripecolor
                    height: 5
                    width: rightItem.position == "rightList" ? (stripeType == 2 ? parent.height : parent.width) : (myStripeType == 2 ? parent.height : parent.width)
                    anchors.verticalCenter: parent.verticalCenter
                    color: rightItem.position == "rightList" ? stripeColor : myStripeColor
                    visible: rightItem.position == "rightList" ? (stripeType == 3 ? false : true) : (myStripeType == 3 ? false : true)
                    rotation: rightItem.position == "rightList" ? (stripeType == 0 ? 0 : stripeType == 1 ? 30 : stripeType == 2 ? 90 : 0) : (myStripeType == 0 ? 0 : myStripeType == 1 ? 30 : myStripeType == 2 ? 90 : 0)
                    clip: false
                }

                MouseArea {
                    id: clickArea
//                    anchors.fill: parent
                    anchors.left: rightRec.left
                    width: 120
                    height: rightRec.height
                    onClicked: {
                        radioButton.checked = !radioButton.checked
                        if (rightItem.position != "rightList" && radioButton.checked)
                        {
                            safeChange(true)
                            detail.selectPosition = rightItem.position
                            detail.selectColor = rightRec.color.toString()
                            detail.selectText = mytext.text
                            detail.selectWireType = rightItem.myWireType
                            detail.selectWireGauge = rightItem.myGauge
                            detail.selectWireAWG = rightItem.myAwg
                            detail.selectWireStripeColor = rightItem.myStripeColor
                            detail.selectWireStripeType = rightItem.myStripeType
                            detail.selectWireId = rightItem.myWireId
                            detail.wireName = rightItem.myWireName
                            wireSelected(rightRec.color,"right",rightItem.position,wireModel.getStructValue4(rightItem.myGauge,rightItem.myAwg),myWireNameRight.text,rightItem.myWireType,rightItem.myStripeColor.toString(),rightItem.myStripeType,rightItem.myModuleType)
                            detail.selectDirection = "right"
                            safeChange(false)

                        }
                        else if (rightItem.position == "rightList" && radioButton.checked)
                        {
                            safeChange(true)
                            wireSelected(rightRec.color,"right",rightItem.position,wireModel.getStructValue4(listModelRight.get(index).gauge,listModelRight.get(index).gaugeawg),myWireNameRight.text,listModelRight.get(index).wireType,listModelRight.get(index).stripeColor,listModelRight.get(index).stripeType,listModelRight.get(index).moduleType)
                            detail.selectPosition = rightItem.position
                            detail.selectIndex = index
                            detail.selectWireType = listModelRight.get(index).wireType
                            detail.selectWireGauge = listModelRight.get(index).gauge
                            detail.selectWireAWG = listModelRight.get(index).gaugeawg
                            detail.selectWireStripeColor = listModelRight.get(index).stripeColor
                            detail.selectWireStripeType = listModelRight.get(index).stripeType
                            detail.selectWireId = listModelRight.get(index).wireId
                            detail.selectColor = listModelRight.get(index).mycolor  //mycolor
                            detail.selectText = listModelRight.get(index).linetext
                            detail.wireName = listModelRight.get(index).wireName
                            listModelRight.set(index,{"isCheck":radioButton.checked})
                            detail.selectDirection = "right"
                            safeChange(false)
                        }
                        else if (rightItem.position == "rightList" && !radioButton.checked)
                        {
                            detail.selectIndex = -1
                            listModelRight.set(index,{"isCheck":radioButton.checked})
                        }
                    }
                }
            }
            Rectangle {
                id: rightRect2
                width: 60
                height: rightItem.position == "rightList" ? listModelRight.count <= 5 ? detail.height * 0.1 : 20 :  detail.height * 0.1
                color: rightRec.color //"white"
                anchors.left: rightRec.right
                anchors.verticalCenter: parent.verticalCenter
                Text {
                    id: mytext
                    anchors.centerIn: parent
                    text: linetext
                    font.family: "arial"
                    font.pointSize: 16
                    color: colorReverse(mycolor) //mycolor  //"black"
                }
            }
            Text {
                id: myWireNameRight
                width: rightRect2.width * 3
                anchors.left: rightRect2.right
                anchors.verticalCenter: rightRect2.verticalCenter
                anchors.leftMargin: 8
                font.family: "arial"
                font.pointSize: 16
                color: "white"
                text: wireName
                clip: true
            }
            RadioButton {
                id: radioButton
                checked: rightItem.position == "rightList" ? listModelRight.get(index).isCheck : false
                exclusiveGroup: wirePositionGroup
                visible: false
                onCheckedChanged: {
                    name.visible = checked
                }
            }
            Rectangle {
                id: name
                width: rightRec.width + rightRect2.width + 5
                height: rightRec.height + 5
                color: Qt.rgba(0,0,0,0)
                border.color: "white"
                border.width: 1
//                anchors.centerIn: rightRec
                anchors.left: rightRec.left
                anchors.leftMargin: -2
                anchors.verticalCenter: rightRec.verticalCenter
                visible: radioButton.checked == true ? true : false
            }
        }
    }
}
