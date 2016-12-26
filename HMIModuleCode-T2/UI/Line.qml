/*******************************************************************
Copyright:http://www.sinux.com.cn
Date:2016/12/26
Author:zhangjiyong&lilongfei
Description: line component
The function interface:
*******************************************************************/
import QtQuick 2.0

Item {
    property alias lineColor: line.color
    Rectangle {
        id: line
        width: parent.width
        height: parent.height
        color: "white"
    }
}
