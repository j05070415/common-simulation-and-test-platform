import QtQuick 2.0
import QtQuick.Controls 1.2

Rectangle {
    id: root
    width: 100
    height: 62
    color: "#323232"
    property alias text: label.text
    property alias textColor: label.color
    property alias pixsize: label.font.pixelSize
    property alias alignment: label.horizontalAlignment

    signal clicked()

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
        enabled: true

        onClicked: root.clicked()
        onEntered: {
            root.color = "blue"
        }
        onExited: root.color = "#323232"

        onPressed: {
            root.color = "darkBlue"
        }
        onReleased: {
            root.color = "blue"
        }
    }
}

