import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import QtQuick.Window 2.2
import QtQuick.Controls 1.1
import QtQuick.Dialogs 1.2
//import QtWebView 1.1
import QtWebEngine 1.3

Item {
    id: userManual
    Rectangle {
        id: leftArea
        anchors.top: parent.top
        anchors.left: parent.left
        width: Screen.width*0.3
        height: parent.height
        color: "#052a40"
        Text {
            id: search
            anchors.top: parent.top
            anchors.topMargin: 15
            anchors.left: parent.left
            anchors.leftMargin: 5
            font.pixelSize: 18
            font.family: "arial"
            color: "white"
            text: qsTr("Search")
        }
        MyLineEdit {
            id: searchValue
            anchors.top: search.bottom
            anchors.topMargin: 5
            anchors.left: search.left
            width: parent.width - 70
            height: 48

            inputWidth: parent.width - 70
            inputHeight: 48
            inputColor: "#8295a0"
            borderColor: "#375566"
        }
        CButton {
            width: 48
            height: 55
            anchors.top: searchValue.top
            anchors.left: searchValue.right
            anchors.leftMargin: 10
            onClicked: {
                searchValue.inputFocus = false

            }
        }

        Row {
            id: row
            spacing: 10
            anchors.top: searchValue.bottom
            anchors.topMargin: 5
            anchors.left: searchValue.left
            height: 60
            width: parent.width
            CButton {
                width: (parent.width - 20) / 2
                height: 60
                text: qsTr("Previous")
                onClicked: {
                    searchValue.inputFocus = false
                    var str = "window.find('" + searchValue .inputText + "', false, true);"
                    webVieW.runJavaScript(str, function(result) { console.log(result); });
                }
            }
            CButton {
                width: (parent.width - 20) / 2
                height: 60
                text: qsTr("Next")
                onClicked: {
                    searchValue.inputFocus = false
                    var str = "window.find('" + searchValue .inputText + "', false, false);"
                    webVieW.runJavaScript(str, function(result) { console.log(result); });
                }
            }
        }

        WebEngineView {
//        WebView {

            id: web1
            anchors.top: row.bottom
            anchors.left: leftArea.left
            anchors.right: leftArea.right
            anchors.bottom: parent.bottom
            url: hmiAdaptor.getUserManualPath()
//            url: ("file:///d:\\mytest.html");
    //        url: ("https://www.baidu.com/")
        }
    }


    WebEngineView {
//    WebView {
        id: webVieW;
        anchors.top: parent.top
        anchors.left: leftArea.right
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        url: hmiAdaptor.getUserManualPath()
//        url: ("file:///c:\\mytest.html");
//        url: ("https://www.baidu.com/")

    }
}
