import QtQuick 2.2
import QtQuick.Layouts 1.1
import QtGraphicalEffects 1.0
import QtQuick.Window 2.2
import QtQuick.Layouts 1.1
import "SysComponent"
import "SysComponent/max_restore_funcion.js" as MaxRestore
import "CanProject"


Window {
    id : window

    visible: true
    color: "#00000000"
    flags: Qt.Window
           | Qt.FramelessWindowHint
           | Qt.CustomizeWindowHint
           | Qt.WindowTitleHint
           | Qt.WindowSystemMenuHint
           | Qt.WindowMinimizeButtonHint
           | Qt.WindowMaximizeButtonHint
           | Qt.WindowCloseButtonHint
    modality: Qt.NonModal
    property int margin: 50
    width: 800 + 2*margin
    height: 500 + 2*margin

    property bool started: false
    onWindowStateChanged: {
        if (!started)
        {
            console.log("started")
            started = true
            MaxRestore.max_function()
        }
    }

    RectangularGlow {
        x: 0
        y: 0
        anchors.fill: mainLayout
        glowRadius: 20
        spread: 0.1
        cornerRadius: 20
        color: "#FF000000"
    }

    ColumnLayout {
        id: mainLayout
        anchors.margins: 0
        x: parent.x + margin
        y: parent.y + margin
        width: parent.width - 2*margin
        height: parent.height - 2*margin
        spacing: 0

        TopTitle {
            id: topTitle
            Layout.fillWidth: true
            anchors.top: parent.top
            onHeaderClicked:
            {
                //tabWidget.setCurrent(index)
            }
        }

//        TabWidget
//        {
//            id: tabWidget
//            color: "#FFFFFF"

//            anchors.margins: 0
//            Layout.fillWidth: true
//            Layout.fillHeight: true
//        }
        CanProject {
            id: canProject
            anchors.top: topTitle.bottom
            anchors.margins: 0
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
    }
}
