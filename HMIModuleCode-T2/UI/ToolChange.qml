import QtQuick 2.0
import QtQuick.Controls 1.0
import QtQuick.Layouts 1.0
import QtQuick.Window 2.2
import QtQuick.Controls 1.1
import QtQuick.Dialogs 1.2
import Qt.labs.folderlistmodel 2.1

Item {
    id: toolChange
    width: Screen.width*0.7
    height: Screen.height*0.6

    property color hightlightColor: "#d0d0d0"     // 高亮行背景色
    property var fileFilter : ["*.qml"]           // 文件过滤器
    property string initFolder: "file:///c:/BransonData/ToolChangeImage"             // 初始目录
    property string rootFolder : '../'            // 限制根目录，不可再往上查找
    property string initFolder2: "file:///c:/BransonData/ToolChangeImage/group1"             // 初始目录

    property var dirCount: dirModel.count
    property var fileCount: fileModel.count
    property var currentDir: 0
    property var currentFile: 0

    Component.onCompleted: {
        hmiAdaptor.maintenanceStart(1);
    }
    Component.onDestruction: {
        hmiAdaptor.maintenanceStop(1);
    }
    Image {
        anchors.fill: parent
        source: "qrc:/images/images/bg.png"
    }
    Rectangle {
        id: back
        width: parent.width * 0.3
        height: parent.height
        color: "#052a40"
//        opacity: 0.5
    }

    FolderListModel {
        id: dirModel
//        nameFilters: toolChange.fileFilter
        folder: toolChange.initFolder
        showDirsFirst: false // true
        showDotAndDotDot: false //true
    }
    FolderListModel {
        id: fileModel
//        nameFilters: toolChange.fileFilter
        folder: toolChange.initFolder2
        showDirsFirst: false // true
        showDotAndDotDot: false //true
    }

    Connections {
        target: toolChange
        onCurrentFileChanged: {
            listView.model = null
            listView.model = dirModel
        }
        onCurrentDirChanged: {
            listView.model = null
            listView.model = dirModel
        }
    }

    ListView {
        id: listView
        width: back.width * 0.8
        height: back.height
        anchors.top: back.top
        anchors.left: back.left
        anchors.topMargin: 20
        anchors.leftMargin: 20
        anchors.bottom: row.top
        clip: true
        model: dirModel
        delegate: Component {
            Item {
                width: listView.width
                height: index == currentDir ? (dirName.height + 10 + fileNameColumn.height) : dirName.height + 10
                Rectangle {
                    id: rect1
                    radius: 100
                    width: 30
                    height: 30
                    color: "white"
                    opacity: 0.5
                    Text {
                        anchors.centerIn: parent
                        font.family: "arial"
                        color: "black"
                        text: index + 1
                        font.pointSize: 14
                    }
                    Component.onCompleted: {
                        if (index == currentDir)
                            rect1.opacity = 1
                    }

                }
                Line {
                    id: line
                    width: 2
                    height: parent.height - 30
                    lineColor: "white"
                    anchors.top: rect1.bottom
                    anchors.horizontalCenter: rect1.horizontalCenter
                    Component.onCompleted: {
                        if (index == (dirModel.count - 1))
                            line.visible = false
                    }
                }

                Text {
                    id: dirName
                    text: fileName //qsTr("dir1")
                    color: "white"
                    anchors.left: rect1.right
                    anchors.leftMargin: 20
                    font.pointSize: 16
                    anchors.top: parent.top
                    font.family: "arial"
                    Component.onCompleted: {
                        if (currentDir == index) {
                            dirName.color = "blue"
                            fileNameRepeater.model.folder = "file:///" + filePath
                        }
                        else {
                            dirName.color = "white"
                            fileNameRepeater.model = null
                        }
                    }
                }
                Column {
                    id: fileNameColumn
                    visible: true
                    width: listView.width
                    height: 30 * fileModel.count
                    anchors.top: dirName.bottom
                    anchors.topMargin: 10
                    anchors.left: dirName.left
                    anchors.leftMargin: 30
                    Repeater {
                        id: fileNameRepeater
                        model: fileModel
                        delegate: Text {
                            id: myFileName
                            width: listView.width
                            height: 30
                            text: fileName
                            color: "white"
                            font.pointSize: 14
                            font.family: "arial"
                            verticalAlignment: Qt.AlignVCenter
                            opacity: 0.8
                            Component.onCompleted: {
                                if (currentFile == index) {
                                    myFileName.color = "blue"
                                    imageViewer.source = "file:///" + filePath
                                }
                                else {
                                    myFileName.color = "white"
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    Row {
        id: row
        anchors.bottom: back.bottom
        anchors.bottomMargin: 20
        anchors.horizontalCenter: back.horizontalCenter
        spacing: 5
        CButton {
            width: 200
            text: qsTr("BACK")
            onPressed: {
                if ((currentFile == 0 || currentFile == -1) && currentDir > 0){
                    currentDir--
                }
            }
            onReleased: {
                if (currentFile > 0)
                    currentFile--
                else if ((currentFile == 0 || currentFile == -1) && currentDir >= 0){
                    if (fileCount > 0)
                        currentFile = fileCount - 1

                }
            }
        }

        CButton {
            width: 200
            text: qsTr("NEXT STEP")
            onClicked: {
                if (dirCount > 0 && fileCount > 0 && currentFile < fileCount - 1)
                    currentFile++
                else if (dirCount > 0 && currentDir < (dirCount - 1) && fileCount > 0 && currentFile == (fileCount - 1))
                {
                    currentDir ++
                    currentFile = 0
                }
                else {
                    currentDir = 0
                    currentFile = 0
                }

            }
        }
    }

    Item {
        anchors.left: back.right
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        Image {
            id: imageViewer
            width: 500
            height: 500
            anchors.centerIn: parent
            //source: "file:///c:/ToolChangeImage/group2/wiredemo.jpg"
        }
    }

}
