import QtQuick 2.2
import QtQuick.Controls 1.4
import "."
import "control_creator.js" as ControlCreator

TableView {
    id: root
    headerVisible: true
    property var columRoles: new Array
    property int cursor: 0
    property var createdItems: new Array
    property var propjson: new Array
    signal itemChanged(string id, var value)
    model: ListModel { id: listModel; }

    Component.onCompleted: {
        root.appendColumn("名称", "name", 100)
        root.appendColumn("值", "value", 100)

        propjson = eval('[{"id":"age","type":"label","name":"年龄","value":"123"}, \
                               {"id":"sex","type":"textEdit","name":"性别","value":"男"}, \
                               {"id":"rate","type":"enum","name":"速率","value":["1","2M","3M"]}, \
                               {"id":"length","type":"int","name":"长度","value":11}, \
                               {"id":"decimal","type":"double","name":"小数","value":9999999.14}]')
        for (var i=0; i<propjson.length; ++i)
        {
            var obj = new Object
            obj["name"] = String(propjson[i].name)
            obj["value"] = String(propjson[i].value)
            listModel.append(obj)
        }
    }

    function onNewPropertyMap(json) {
        var newPropjson = eval(json)
        for (var i=0; i<newPropjson.length; ++i)
        {
            var propLine = newPropjson[i]
            var has = false
            var j=0
            for (; j<root.propjson.length; ++j)
            {
                if (propLine.id == root.propjson[j].id)
                {
                    has = true
                    break;
                }
            }

            if (has && j != i)
            {
                listModel.move(j, i, 1)
                var temp = root.propjson.splice(j, 1)
                root.propjson.splice(i, 0, temp)
            }
            else if (!has)
            {
                listModel.insert(i, eval('{"name":"unknow","value":"unknow"}'))

                root.propjson.splice(i, 0, new Object)
            }
        }

        var newLength = newPropjson.length
        var dist = listModel.count-newLength
        if (dist > 0)
        {
            listModel.remove(newPropjson.length, dist)
            for (var i=0; i<dist; ++i)
            {
                var index = root.findItemIndex(root.propjson[newLength+i].id)
                print('remove '+root.propjson[newLength+i].id)
                if (index >= 0) root.createdItems.splice(index, index)
            }
        }
        root.propjson = newPropjson
    }

    function appendColumn(title, role, width)
    {
        var str = 'import QtQuick 2.2;import QtQuick.Controls 1.4; TableViewColumn {title: "'
                + title + '";role:"' + role + '";width:' + width + '}'
        var newObject = Qt.createQmlObject(str, root, "dynamicSnippet1");

        root.addColumn(newObject)
        columRoles.push(role)
    }

    function findItem(id)
    {
        for (var i=0; i<root.createdItems.length; ++i)
        {
            if (root.createdItems[i].itemName == id) return root.createdItems[i]
        }
    }

    function findItemIndex(id)
    {
        for (var i=0; i<root.createdItems.length; ++i)
        {
            if (root.createdItems[i].itemName == id) return i
        }

        return -1
    }

    itemDelegate: Item {
        id: container
        Component.onCompleted: {
            ControlCreator.createItem(styleData.row, styleData.column, container)
        }

        Connections {
            target: styleData
            onValueChanged: {
                if (styleData.column == 1)
                {
                    var item = root.findItem(root.propjson[styleData.row].id)
                    if (item != null)
                        item.setValue(styleData.value)
                }
            }
        }
    }

    rowDelegate: Rectangle {
        height: 20
        color: styleData.selected ?　"#4040FF" : (styleData.alternate ? "#D3D3D3":"white")
    }

    headerDelegate: HeaderDelegate{}

    onItemChanged: {
        print('on item changed')
        var str = '[{"id":"age","type":"label","name":"年龄","value":"1234"}, \
                               {"id":"rate","type":"enum","name":"速率","value":["1","2M","3M"]}, \
                               {"id":"length","type":"int","name":"长度","value":11}, \
                               {"id":"sex","type":"textEdit","name":"性别","value":"男"}, \
                               {"id":"time","type":"int","name":"时间","value":11}, \
                               {"id":"iconsize","type":"int","name":"图标","value":14}, \
                               {"id":"decimal","type":"double","name":"小数","value":9999999.14}]'

        root.onNewPropertyMap(str)
        listModel.set(1, eval('{"name":"adsfasdf","value":"1211"}'))
    }
}
