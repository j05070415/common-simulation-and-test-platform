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
                btnText:"数据视图"
                onClicked:toolbar.current=0
            }
        }
    }
}
