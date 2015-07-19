import QtQuick 2.2
import QtQuick.Layouts 1.1
import "max_restore_funcion.js" as MaxRestore

Rectangle {
    id: root
    height: 110
    signal headerClicked(int index)

    Image {
        id: skinpic
        anchors.fill: parent
        x: 0
        y: 0
        fillMode: Image.TileHorizontally
        source: "Image/background_mainwnd.jpg"

        Text {
            id: title
            anchors.top: parent.top
            anchors.left: parent.left
            width: 125
            height: 12
            color: "#ffffff"
            text: qsTr("仿真测试平台")
            anchors.leftMargin: 3
            anchors.topMargin: 3
            font.pointSize: 9
            font.family: "微软雅黑"
            font.pixelSize: 12
        }

        MouseArea {
            property variant previousPosition
            anchors.topMargin: 0
            anchors.bottom: parent.bottom
            anchors.right: parent.right
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.bottomMargin: 0
            onPressed: {
                previousPosition = Qt.point(mouseX, mouseY)
            }
            onPositionChanged: {
                if (pressedButtons == Qt.LeftButton && !sysbtngrp.maxed) {
                    var dx = mouseX - previousPosition.x
                    var dy = mouseY - previousPosition.y
                    window.x = window.x + dx
                    window.y = window.y + dy
                }
            }
            onDoubleClicked: {
                sysbtngrp.doubleClicked()
            }
        }

        Image
        {
            id: logo
            anchors.rightMargin: 3
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 3
            anchors.right: parent.right
            source: "Image/logo.png"
        }

        Row
        {
            id: toolbar
            spacing: 0
            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.bottom: parent.bottom
            property int current: 0
            onCurrentChanged:setCurrentToolBtn()

            function setCurrentToolBtn()
            {
                for(var i = 0; i < toolbar.children.length; i++)
                {
                    if (toolbar.current == i)
                    {
                        toolbar.children[i].state = 'checked'
                        root.headerClicked(i)
                    }
                    else
                    {
                        toolbar.children[i].state = 'leave'
                    }
                }
            }

            ToolBtn
            {
                index:0
                state:"checked"
                picSrc: "Image/ico_Examine.png"
                btnText:"Can数据视图"
                onClicked:toolbar.current=0
            }
//            ToolBtn
//            {
//                index:1
//                picSrc: "Image/ico_dsmain.png"
//                btnText:"木马查杀"
//                onClicked:toolbar.current=1
//            }
//            ToolBtn
//            {
//                index:2
//                picSrc: "Image/ico_SysRepair.png"
//                btnText:"系统修复"
//                onClicked:toolbar.current=2
//            }
//            ToolBtn
//            {
//                index:3
//                picSrc: "Image/ico_TraceCleaner.png"
//                btnText:"电脑清理"
//                onClicked:toolbar.current=3
//            }
//            ToolBtn
//            {
//                index:4
//                picSrc: "Image/ico_SpeedupOpt.png"
//                btnText:"优化加速"
//                onClicked:toolbar.current=4
//            }
//            ToolBtn
//            {
//                index:5
//                picSrc: "Image/ico_expert.png"
//                btnText:"电脑专家"
//                onClicked:toolbar.current=5
//            }
//            ToolBtn
//            {
//                index:6
//                picSrc: "Image/ico_diannaomenzhen.png"
//                btnText:"电脑门诊"
//                onClicked:toolbar.current=6
//            }
//            ToolBtn
//            {
//                index:7
//                picSrc: "Image/ico_softmgr.png"
//                btnText:"软件管家"
//                onClicked:toolbar.current=7
//            }
        }

        SysBtnGroup
        {
            id: sysbtngrp
            layoutDirection: Qt.LeftToRight
            anchors.top: parent.top
            anchors.right: parent.right

            onMin: window.showMinimized()
            onClose: window.close()
            onMax: {
                console.log("max");
                MaxRestore.max_function()
            }
            onRestore: {
                console.log("restore");
                MaxRestore.restore_function()
            }
        }
    }
}
