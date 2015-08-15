import QtQuick 2.2
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1
import QtQuick.Window 2.2
import QtQuick.Layouts 1.1
import QtGraphicalEffects 1.0
import "SysComponent"
import "HwaCanProject"
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
    Component.onCompleted: {
        if (!started)
        {
            console.log("started")
            MaxRestore.max_function()
        }
    }

    RectangularGlow {
        anchors.fill: mainrect
        glowRadius: 20
        spread: 0.1
        cornerRadius: 20
        color: "#FF000000"
    }

    Rectangle {
        id: mainrect
        anchors.margins: 0
        x: parent.x + margin
        y: parent.y + margin
        width: parent.width - 2*margin
        height: parent.height - 2*margin
        color: "grey"
        clip: true
        property var curProject: 0
        property var prevProject: 0

        function loadProject(name)
        {
            var com = Qt.createComponent(name + '/' +name + '.qml', Component.PreferSynchronous, window)
            if (com.status == Component.Ready)
            {
                console.log('ready')
                mainrect.prevProject = mainrect.curProject
                mainrect.curProject = com.createObject(canproject)
                canproject.x = 0
                //homepage.x = -1.0*width
                homepage.opacity = 0
                homepage.action('{"objectName":"content","action":1,"projectName":"'+ name +'"}', '')
            }
            else
                console.log('component:'+com.errorString())
        }

        HomePage {
            id: homepage
            width: parent.width
            height: parent.height
            //visible: x !== -1.0*width
            Behavior on opacity {
                PropertyAnimation {
                    id: homepageAna
                    easing.type: Easing.Linear
                    duration: 1000
                }
            }
        }

        Rectangle {
            id: canproject
            width: parent.width
            height: parent.height
            x: 200
            color: "grey"
            visible: x < 200
            Behavior on x {
                PropertyAnimation {
                    id: projectAna
                    easing.type: Easing.InExpo
                    duration: 1000
                }
            }
        }

//        Rectangle {
//            id: mask
//            visible: projectAna.running
//            z: 1
//            MouseArea {
//                anchors.fill: parent
//            }
//        }
    }
}
