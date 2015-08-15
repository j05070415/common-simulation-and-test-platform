import QtQuick 2.2
import QtQuick.Layouts 1.1
import "max_restore_funcion.js" as MaxRestore

Rectangle {
    id: root
    height: 110

    function show(maxed) {
        sysbtngrp.maxed = maxed
    }

    Rectangle {
        id: backGround
        anchors.fill: parent
        color: "grey"
    }

//    Image
//    {
//        id: logo
//        anchors.bottom: parent.bottom
//        anchors.right: parent.right
//        Layout.fillWidth: true
//        source: "Image/logo.png"
//    }

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
        anchors.margins: 0
        anchors.fill: parent
        onPressed: {
            console.log('header pressed')
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

