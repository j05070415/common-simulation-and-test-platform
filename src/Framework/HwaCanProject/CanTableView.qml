import QtQuick 2.2
import QtQuick.Controls 1.3
import "../SysComponent"

Rectangle {
    id: root
    color: "white"
    state: "hide"

    function append(data)
    {
        tableView.appendRow(data)
    }

    TableView {
        id: tableView
        anchors.fill: parent
        horizontalScrollBarPolicy: 0
        headerVisible: true
        model: ListModel { id: listModel; }
        property var roles: []
        property int cursor: 0
        signal itemChanged(string name, var params)

        rowDelegate: Rectangle {
            height: 20
            color: styleData.selected ?　"#4040FF" : (styleData.alternate ? "#D3D3D3":"white")
        }

        headerDelegate: HeaderDelegate{}

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
                tableView.appendRow('A'+i, data[i*column + i])
                roles[i] = 'A'+i
            }
        }

        function appendColumn(title, role, width)
        {
            var str = 'import QtQuick 2.2;import QtQuick.Controls 1.2; TableViewColumn {title: "'
                    + title + '";role:"' + role + '";width:' + width + '}'
            var newObject = Qt.createQmlObject(str, tableView, "dynamicSnippet1");

            tableView.addColumn(newObject)
            roles.push(role)
        }

        function appendRow(values)
        {
            var index = listModel.count
            for (var i=0; i<tableView.roles.length; ++i)
            {
                var str = '{"' + tableView.roles[i] + '":"' + values[i] + '"}'
                listModel.set(index, eval(str));
            }
        }

        Component.onCompleted: {
            appendColumn('Identity', 'Identity', 150)
            appendColumn('RTR', 'RTR', 150)
            appendColumn('IDE', 'IDE', 150)
            appendColumn('r0', 'r0', 150)
            appendColumn('DLC', 'DLC', 150)
            appendColumn('CRC序列', 'CRC', 150)
        }
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
