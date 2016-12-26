/*******************************************************************
Copyright:http://www.sinux.com.cn
Date:2016/12/26
Author:zhangjiyong&lilongfei
Description: progressbar component
The function interface:
*******************************************************************/
import QtQuick 2.3

Item {
   id:cprogressBar

   objectName: "CProgressBar_SyberOS2.0"

   implicitHeight: 10
   implicitWidth: 460

   /*! 表示当前值进度值 */
   property real value: 0.0

   /*! 表示进度区间的最小值 */
   property real minimum:0

   /*! 表示进度区间的最大值 */
   property real maximum:1.0

   /*! 背景颜色 */
   property color backgroundColor: "#9fa1a4"

   /*! 前景颜色 */
   property color progressColor: "#60bb46"

   /*!
       \qmlproperty Component CProgressBar::backgroundComponent
       进度条背景组件，可通过自定义来代替默认样式
   */
   property alias backgroundComponent:backgroundLoader.sourceComponent

   /*!
       \qmlproperty object CProgressBar::backgroundItem
       backgroundComponent加载完成之后的Item元素
   */
   property alias backgroundItem:backgroundLoader.item

   /*!
       \qmlproperty Component CProgressBar::progressComponent
       进度值组件，可通过自定义来代替默认样式
   */
   property alias progressComponent: progressLoader.sourceComponent

   /*!
       \qmlproperty object CProgressBar::progressItem
       progressComponent加载完成之后的Item元素
   */
   property alias progressItem: progressLoader.item

   Loader{
       id:backgroundLoader
       anchors.left: parent.left
       anchors.right: parent.right
       height: parent.height
       sourceComponent: Rectangle{
           radius: height/2
           color: backgroundColor
       }
   }

   Loader{
       id: progressLoader
       height: parent.height
       width: value > minimum ? (value < maximum ? (value-minimum)/(maximum-minimum)*cprogressBar.width : cprogressBar.width) : 0
       sourceComponent: Rectangle{
           radius: height/2
           color: progressColor
       }
   }
}
