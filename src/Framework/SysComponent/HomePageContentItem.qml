import QtQuick 2.0
import QtQuick.Layouts 1.1

Rectangle {
    id: root
    width: 200
    height: 240
    border.color: "grey"
    border.width: 2
    color: "grey"
    opacity: 0.5
    property int margin: 15

    property alias srcPicture: icon.source
    property alias name: text.text

    signal clicked()

    Image
    {
        id: icon
        x: root.margin
        y: root.margin
        height: 200 - 2*margin
        width: root.width - 2*margin
        sourceSize.width: root.width - 2*margin
        sourceSize.height: icon.height - 2*margin
    }

    Text {
        id: text
        anchors.top: icon.bottom
        width: parent.width
        height: 40
        elide: Text.ElideMiddle
        font.bold: true
        font.pixelSize: 16
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        text: '默认'
    }

    MouseArea {
        anchors.fill: parent
        hoverEnabled: true
        onEntered: {
            parent.color = "#C8C8FF"
        }
        onExited: {
            parent.color = "grey"
        }

        onPressed: {
            parent.color = "#8C8CFF"
        }

        onReleased: {
            parent.color = "#C8C8FF"
        }

        onClicked: {
            root.clicked();
        }
    }
}

