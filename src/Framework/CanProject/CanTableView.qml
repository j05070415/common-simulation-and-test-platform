import QtQuick 2.2
import QtQuick.Controls 1.3

Rectangle {
    id: root
    width: parent.width
    height: parent.height
    color: "white"
    state: "hide"
    property alias row: tableView.rowCount
    property alias col: tableView.columnCount

    TableView {
        id: tableView
        horizontalScrollBarPolicy: 0
        objectName: "TableView"
        headerVisible: true

        function updateView(string data)
        {
            var d = data
            count = d.size()
            root.row = count / columnCount
        }
    }

    states:
    [
        State
        {
            name:"active"
            PropertyChanges
            {
                target: widget
                x:parent.x
            }

        },
        State
        {
            name:"hide"
            PropertyChanges
            {
                target: widget
                x:parent.x - width
            }
        }

    ]

    transitions:
    [
        Transition
        {
            PropertyAnimation
            {
                property:"x"
                duration: 500
                easing.type: Easing.OutBounce
                easing.amplitude: 0.1
            }
        }
    ]
}
