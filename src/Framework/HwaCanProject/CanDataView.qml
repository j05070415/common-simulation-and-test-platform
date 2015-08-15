import QtQuick 2.2
import QtQml 2.2
import QtQuick.Controls 1.3

Rectangle {
    id: root
    signal action(string json, var parameter)
    signal itemChanged(string item, string parameter)
    function onChangeValue(name, parameter)
    {
        if (name == tableView.objectName)
        {
            tableView.append(parameter)
        }
    }

    CanTableView {
        id: tableView
        anchors.fill: parent
        state: "active"
        objectName: "table1"

        MouseArea {
            anchors.fill: parent
            onClicked: {
                console.log('can table view clicked!')
                root.action('{"action":0,"objectName":"' + tableView.objectName + '"}', '')
            }
        }
    }
}

