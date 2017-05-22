import QtQuick 2.0
import QtQuick.Controls 1.0
import QtQuick.Layouts 1.0
import QtQuick.Window 2.2
import QtQuick.Controls 1.1
import QtQuick.Dialogs 1.2
import QtWebView 1.1

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
            text: qsTr("Search℃")
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
        }

        Row {
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
            }
            CButton {
                width: (parent.width - 20) / 2
                height: 60
                text: qsTr("Next")
                onClicked: {
//                    webVieW.runJavaScript("document.title", function(result) { console.log(result); });
                    webVieW.runJavaScript("document.head.value", function(result) { console.log(result); });

                }
            }
        }
    }

    function findIt() {
         if (document.getElementById("searchstr").value != "")
             findInPage(document.getElementById("searchstr").value);
    }


    function findInPage(str) {
    var txt, i, found;

    if (str == "")
         return false;

    if (DOM)
    {
         win.find(str, false, true);
         return true;
    }

    if (NS4) {
         if (!win.find(str))
             while(win.find(str, false, true))
                 n++;
         else
             n++;

         if (n == 0)
             alert("未找到指定内容.");
    }

    if (IE4) {
         txt = win.document.body.createTextRange();

         for (i = 0; i <= n && (found = txt.findText(str)) != false; i++) {
             txt.moveStart("character", 1);
             txt.moveEnd("textedit");
         }

    if (found) {
         txt.moveStart("character", -1);
         txt.findText(str);
         txt.select();
         txt.scrollIntoView();
         n++;
    }
    else {
         if (n > 0) {
             n = 0;
             findInPage(str);
         }
         else
             alert("未找到指定内容.");
         }
    }

    return false;
    }

    WebView {
        id: webVieW;
        anchors.top: parent.top
        anchors.left: leftArea.right
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        url: hmiAdaptor.getUserManualPath()
//        url: ("file:///d:\\Special Double Hit Mode functionality for Delphi Ground Terminal Welder II.html");
//        url: ("https://www.baidu.com/")
    }
}
