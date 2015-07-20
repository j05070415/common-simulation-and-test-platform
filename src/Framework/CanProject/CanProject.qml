import QtQuick 2.2
import QtGraphicalEffects 1.0
import QtQuick.Layouts 1.1
import "../SysComponent"
import "../SysComponent/max_restore_funcion.js" as MaxRestore

Rectangle {




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

//        CanProject {
//            id: canProject
//            anchors.top: topTitle.bottom
//            anchors.margins: 0
//            Layout.fillHeight: true
//            Layout.fillWidth: true
//        }
    }
}


