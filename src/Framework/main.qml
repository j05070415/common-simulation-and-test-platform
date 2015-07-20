import QtQuick 2.2
import QtQuick.Layouts 1.1
import QtQuick.Window 2.2
import QtQuick.Layouts 1.1
import QtGraphicalEffects 1.0
import "SysComponent"
import "CanProject"
import "SysComponent/max_restore_funcion.js" as MaxRestore


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
        anchors.fill: homePage
        glowRadius: 20
        spread: 0.1
        cornerRadius: 20
        color: "#FF000000"
    }

    HomePage {
        id: homePage
        anchors.margins: 0
        x: parent.x + margin
        y: parent.y + margin
        width: parent.width - 2*margin
        height: parent.height - 2*margin
    }
}
