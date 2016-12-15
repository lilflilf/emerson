import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2

Item {
    id: spliceLocationStats
    width: parent.width
    height: parent.height
    property int columns: 0
    property int rows: 0
    property int current: 1
    property int next: 2
    property alias listModel: layoutrepeater.model
    property var array: ["A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P"]
    property string workStation: ""
    function getspliceNotopMargin(index)
    {
        if (index < 4) {
            return 0;
        } else if (index >=4 && index < 8) {
            return spliceLocationStats.height/spliceLocationStats.rows/3
        } else {
            return spliceLocationStats.height/spliceLocationStats.rows/3*2
        }
    }

    function getspliceNoLeftMargin(index)
    {
        return spliceLocationStats.width/spliceLocationStats.columns/4.8*(index%4)+8
    }

    function updateTreeModel()
    {
        var i,j
        for ( j = 0; j < listModel.count; j++) {
            var bIsFind1 = false
            for (i = 0; i < listModel.get(j).subNode.count; i++) {
                if (listModel.get(j).subNode.get(i).spliceNo == spliceLocationStats.current) {
                    listModel.get(j).subNode.set(i,{"spliceColor":"white"})
                    ++spliceLocationStats.current
                    bIsFind1 = true
                    break;
                }
            }
            if (bIsFind1)break
        }
        for ( j = 0; j < listModel.count; j++) {
            var bIsFind2 = false
            for (i = 0; i < listModel.get(j).subNode.count; i++) {
                if (listModel.get(j).subNode.get(i).spliceNo == spliceLocationStats.next) {
                    listModel.get(j).subNode.set(i,{"spliceColor":"#00aa7e"})
                    ++spliceLocationStats.next
                    bIsFind2 = true
                    spliceLocationStats.workStation = array[j]
                    break;
                }
            }
            if (bIsFind2)break
        }
        for ( j = 0; j < listModel.count; j++) {
            var bIsFind3 = false
            for (i = 0; i < listModel.get(j).subNode.count; i++) {
                if (listModel.get(j).subNode.get(i).spliceNo == spliceLocationStats.next) {
                    listModel.get(j).subNode.set(i,{"spliceColor":"#00afe9"})
                    bIsFind3 = true
                    break;
                }
            }
            if (bIsFind3)break
        }
    }
    function setTreeModelBack()
    {
        if (spliceLocationStats.current == 1) {
            return
        }
        var i,j
        for ( j = 0; j < listModel.count; j++) {
            var bIsFind1 = false
            for (i = 0; i < listModel.get(j).subNode.count; i++) {
                if (listModel.get(j).subNode.get(i).spliceNo == spliceLocationStats.current) {
                    listModel.get(j).subNode.set(i,{"spliceColor":"#00afe9"})
                    --spliceLocationStats.current
                    bIsFind1 = true
                    break;
                }
            }
            if (bIsFind1)break
        }
        for ( j = 0; j < listModel.count; j++) {
            var bIsFind2 = false
            for (i = 0; i < listModel.get(j).subNode.count; i++) {
                if (listModel.get(j).subNode.get(i).spliceNo == spliceLocationStats.next) {
                    listModel.get(j).subNode.set(i,{"spliceColor":"white"})
                    --spliceLocationStats.next
                    bIsFind2 = true
                    break;
                }
            }
            if (bIsFind2)break
        }
        for ( j = 0; j < listModel.count; j++) {
            var bIsFind3 = false
            for (i = 0; i < listModel.get(j).subNode.count; i++) {
                if (listModel.get(j).subNode.get(i).spliceNo == spliceLocationStats.current) {
                    listModel.get(j).subNode.set(i,{"spliceColor":"#00aa7e"})
                    bIsFind3 = true
                    spliceLocationStats.workStation = array[j]
                    break;
                }
            }
            if (bIsFind3)break
        }
    }

    function setTreeModelOver()
    {
        var i,j
        for ( j = 0; j < listModel.count; j++) {
            var bIsFind1 = false
            for (i = 0; i < listModel.get(j).subNode.count; i++) {
                if (listModel.get(j).subNode.get(i).spliceNo == spliceLocationStats.current) {
                    listModel.get(j).subNode.set(i,{"spliceColor":"#d31145"})
                    ++spliceLocationStats.current
                    bIsFind1 = true
                    break;
                }
            }
            if (bIsFind1)break
        }
        for ( j = 0; j < listModel.count; j++) {
            var bIsFind2 = false
            for (i = 0; i < listModel.get(j).subNode.count; i++) {
                if (listModel.get(j).subNode.get(i).spliceNo == spliceLocationStats.next) {
                    listModel.get(j).subNode.set(i,{"spliceColor":"#00aa7e"})
                    ++spliceLocationStats.next
                    bIsFind2 = true
                    spliceLocationStats.workStation = array[j]
                    break;
                }
            }
            if (bIsFind2)break
        }
        for ( j = 0; j < listModel.count; j++) {
            var bIsFind3 = false
            for (i = 0; i < listModel.get(j).subNode.count; i++) {
                if (listModel.get(j).subNode.get(i).spliceNo == spliceLocationStats.next) {
                    listModel.get(j).subNode.set(i,{"spliceColor":"#00afe9"})
                    bIsFind3 = true
                    break;
                }
            }
            if (bIsFind3)break
        }
    }
    Rectangle {
        anchors.top: parent.top
        anchors.left: parent.left
        width: parent.width
        height: parent.height
        color: "white"
        Grid {
            id: layout
            anchors.fill: parent
            columns: spliceLocationStats.columns
            rows: spliceLocationStats.rows
            spacing: 1
            Repeater {
                id: layoutrepeater
                model: listModel.count
                delegate: Item {
                    width: parent.width/spliceLocationStats.columns
                    height: parent.height/spliceLocationStats.rows
                    Rectangle {
                        anchors.fill: parent
                        color: "#6d6e71"
                        Repeater {
                            id: childRepeater
                            model:  subNode
                            delegate: Item {
                                anchors.fill: parent
                                Text {
                                    id: spliceNo
                                    anchors.top: parent.top
                                    anchors.topMargin: getspliceNotopMargin(index)
                                    anchors.left: parent.left
                                    anchors.leftMargin: getspliceNoLeftMargin(index)
                                    height: parent.height/3
                                    verticalAlignment: Qt.AlignVCenter
                                    font.pointSize: 10
                                    font.family: "arial"
                                    color: "white"
                                    text: model.spliceNo
                                }
                                Rectangle {
                                    id: rec
                                    anchors.top: spliceNo.top
                                    anchors.topMargin: 8
                                    anchors.left: spliceNo.right
                                    anchors.leftMargin: 2
                                    width: 14
                                    height: 14
                                    radius: 14
                                    color: model.spliceColor
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
