import QtQuick 2.7
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.0
import QtQuick.Window 2.2

MouseArea {
    id: button

    implicitWidth: labelItemLoader.implicitWidth + implicitHorizontalPadding
    implicitHeight: labelItemLoader.implicitHeight + implicitVerticalPadding
    opacity: enabled ? (button.pressed ? 0.2 : 1) : 0.5

    /*! 设置默认垂直方向内容区域与边界的距离。如果设置了高度，则此不起作用 */
    property int implicitVerticalPadding: 20

    /*! 设置默认水平方向内容区域与边界的距离。如果设置了宽度，则此不起作用 */
    property int implicitHorizontalPadding: 30

    /*! 设置是否显示背景 */
    property bool backgroundEnabled: true

    /*! 设置图标 */
    property url iconSource: ""

    /*! 数值<0, 向左偏移, 反之向右偏移*/
    property int labelHorizontalOffset: 0

    /*! labelItem偏移量, 数值<0 向上偏移, 反之向下偏移 */
    property int labelVerticalOffset: 0

    /*! 设置文本字体大小 */
    property int pixelSize: 20

    property int pointSize: 20

    /*! 设置图片和文本间距 */
    property int spacing: (button.iconSource != "" && button.text != "") ? 10 : 0   //控制文字与元素间距

    /*! 设置文本内容 */
    property string text: ""

    /*! 设置字体颜色 */
    property string textColor: "white"

    /*!
        \qmlproperty item CButton::backgroundItem
        backgroundComponent加载完成之后对应的Item元素
    */
    property alias backgroundItem: backgroundLoader.item

    /*! 用于定制按钮的背景样式*/
    property Component backgroundComponent: Item {
        Image {
            anchors.fill: parent
            source: "qrc:/images/images/icon-bg.png"
        }
//        Rectangle {
//            anchors.centerIn: parent
//            anchors.fill: parent
//            radius: 3
//            color: "#0079c1"
//            Rectangle{
//                anchors.fill: parent
//                anchors.margins: 1
//                radius: 3
//                anchors.centerIn: parent
//                color: "#0079c1"
//            }
//        }
    }

    /*!
        \qmlproperty item CButton::labelItem
        labelComponent加载完成之后对应的Item元素
    */
    property alias labelItem:labelItemLoader.item

    /*! 用于定制按钮的内容标示*/
    property Component labelComponent: Row {
        spacing:button.spacing
        Image {
            id: icon
            source: button.iconSource
            anchors.verticalCenter: parent.verticalCenter
        }

        Text {
            id: text
            anchors.verticalCenter: parent.verticalCenter
            font.pixelSize: button.pixelSize
            color: button.textColor
            text: qsTr(button.text)
            font.family: "arial"

        }
    }

    Loader {
        id: backgroundLoader
        anchors.fill: parent
        sourceComponent: backgroundComponent
        active: button.backgroundEnabled
        z:-1
    }

    Loader {
        id: labelItemLoader
        sourceComponent: labelComponent
        anchors.centerIn: parent
        anchors.horizontalCenterOffset: button.labelHorizontalOffset
        anchors.verticalCenterOffset: button.labelVerticalOffset
    }
}
