import QtQuick 2.2
import QtQuick.Controls 1.4
import Hwa.TreeModel 1.0 as TreeModel

TreeView {
    id: root
    headerVisible: true
    model: TreeModel.HwaTreeModel {
        id: model1
    }

    itemDelegate: Item {
        property int iconwight: 20
        Image {
            id: image
            height: parent.height
            width: iconwight
        }

        Text {
            id: text
            x: iconwight
            width: parent.width - iconwight
            height: parent.height
            font.pointSize: 9
        }

        Connections {
            target: styleData

            onValueChanged: {
                if (styleData.value.length != 0)
                {
                    var data = JSON.parse(styleData.value)
                    if("icon" in data)
                    {
                        image.source = data["icon"]
                    }
                    if ("text" in data)
                    {
                        text.text = data["text"]
                    }
                }
            }
        }
    }

    rowDelegate: Rectangle {
        height: 20
        color: styleData.selected ?　"#4040FF" : (styleData.alternate ? "#D3D3D3":"white")
    }

    headerDelegate: HeaderDelegate{}

    Component.onCompleted: {
        model.insertRows(0, 10);
        for (var i=0; i<10; ++i)
        {
            model.setData(model.index(i, 0), "file:///F:/VS/QmlTreeView/1.ico", Qt.DecorationRole);
            model.setData(model.index(i, 0), "A");
            model.setData(model.index(i, 1), 'E'+i);
        }

        var index = model.index(0, 0);
        model.insertRows(0, 1, index)
        model.setData(model.index(0, 0, index), "DD")
    }

    TableViewColumn {
        title: "名称"
        role: "column1"
        width: root.width/2
    }
    TableViewColumn {
        title: "状态"
        role: "column2"
        width: root.width/2
    }
}
