import QtQuick 2.2
import QtQuick.Layouts 1.1
import QtQuick.Dialogs 1.2
import QtQuick.Controls 1.2

Rectangle {
    id: rectangle2
    width: 110
    height: 62

    SplitView {
        id: splitView1
        orientation: Qt.Vertical
        anchors.fill: parent

        RowLayout {
            id: columnLayout1
            width: 100
            height: 100


            Item {
                id: item1
                width: 200
                height: 200
                Layout.fillWidth: true
            }
            ToolButton {
                id: toolButton1
                text: "adfs"
            }
        }
    }
}

