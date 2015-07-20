import QtQuick 2.0
import QtQuick.Controls 1.2

Rectangle {
    id: root
    width: 100
    height: 62
    color: "grey"
    property alias text: label.text
    property alias textColor: label.color
    property alias pixsize: label.font.pixelSize
    property alias alignment: label.horizontalAlignment
    Text {
        anchors.fill: parent
        id: label
        color: "white"
        font.pixelSize: 15
        font.family: "微软雅黑"
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        elide: Text.ElideRight
    }

    MouseArea {
        anchors.fill: parent
        hoverEnabled: true

        onEntered: {
            console.log("entered")
            root.color = "darkBlue"
        }
        onExited: root.color = "grey"
        onPressedChanged: {
            console.log("pressed changed")
        }

        onPressed: {
            console.log("pressed")
            root.color = "red"
        }
        onReleased: {
            root.color = "blue"
        }
    }
}

