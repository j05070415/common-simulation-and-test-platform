import QtQuick 2.2
import QtQuick.Controls 1.3

Rectangle {
    id: root
    objectName: "CanDataView"

    //item,row,count,header
    function update(infor, data){
        var jsonObj = eval(infor)
        var itemName = jsonObj.item
        var childItem = root.findChild(itemName)
        chidItem.setData(data)
    }

    CanTableView {
        id: tableView
        anchors.fill: parent
        state: "active"
        CanTableView {
            anchors.fill: parent
        }
    }
}

