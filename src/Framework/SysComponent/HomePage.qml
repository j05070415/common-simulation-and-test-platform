import QtQuick 2.0
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1
import "max_restore_funcion.js" as MaxRestore

Rectangle {
    id: root

    Rectangle {
        id: columnLay
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        anchors.top: parent.top
        width: root.width/7
        color: "grey"

        Image
        {
            id: logo
            source: "Image/logo.png"
        }

        Rectangle
        {
            id: spacer
            y: logo.y + logo.height + 10
            anchors.left: parent.left
            anchors.right: parent.right
            height: 1
            color:"#BBBBBB"
        }

        RectLabel {
            id: newProject
            anchors.top: spacer.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            pixsize: 14
            text: "新建"
        }

        RectLabel {
            id: openProject
            anchors.top: newProject.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            pixsize: 14
            text: "打开"
        }

        RectLabel {
            id: saveProject
            anchors.top: openProject.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            pixsize: 14
            text: "保存"
        }

        RectLabel {
            id: closeProject
            anchors.top: saveProject.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            pixsize: 14
            text: "关闭"
        }
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

    MouseArea {
        id: mouseArea
        property variant previousPosition
        anchors.topMargin: 0
        anchors.fill: parent
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
}

