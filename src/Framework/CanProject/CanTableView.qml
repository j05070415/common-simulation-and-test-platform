import QtQuick 2.2
import QtQuick.Controls 1.3

Rectangle {
    id: root
    width: parent.width
    height: parent.height
    color: "white"
    state: "hide"

    TableView {
        id: tableView
        anchors.fill: parent
        horizontalScrollBarPolicy: 0
        objectName: "TableView"
        headerVisible: true
//        itemDelegate: itemDelegate
//        headerDelegate: headerDelegate
        property int cursor: 0
        signal itemChanged(string name, var params)

        //item,row,column,count,header
        function updateView(infor, data)
        {
            console.log(infor)
            var jsonObj = eval(infor)
            var row = Number(jsonObj.row)
            var column = Number(jsonObj.column)
            var count = (jsonObj.count)
            tableView.cursor += row
            var header = jsonObj.header.split(",")
            for (var i=0; i<header.size; ++i)
            {
                tableView.addColumn(Qt.createComponent('import QtQuick 2.0; Text { text:"Item"}'))
                console.log(i)
            }
        }

//        TableViewColumn {
//            id: authorColumn
//            delegate: listDelegate
//            title: "Author"
//            role: "author"
//            movable: false
//            resizable: false
//            width: tableView.viewport.width / 3
//        }

//        Component {
//            id:columnComponent
//            Text {
//                    text: name;
//                    font.pixelSize: 24
//                }
//        }

//        ListModel {
//            id: listDelegate
//            ListElement { name:"Author" }
//            ListElement { name:"name" }
//        }


//        Component {
//            id: headerDelegate
//            Text {
//                anchors.fill: parent
//                text: styleData.value
//                //effectiveHorizontalAlignment: Text.AlignHCenter
//            }
//        }
//        Component {
//            id: itemDelegate
//            Text {
//                anchors.fill: parent
//                color: styleData.textColor
//                elide: styleData.elideMode
//                text: sytleData.value
//            }
//        }
     }

    states:
    [
        State
        {
            name:"active"
            PropertyChanges
            {
                target: root
                x:parent.x
            }

        },
        State
        {
            name:"hide"
            PropertyChanges
            {
                target: root
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
