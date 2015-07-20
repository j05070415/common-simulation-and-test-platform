﻿import QtQuick 2.2
import QtQml 2.2
import QtQuick.Controls 1.3

Rectangle {
    id: root
    objectName: "CanDataView"

    CanTableView {
        id: tableView
        anchors.fill: parent
        state: "active"
        objectName: "CanTableView"
    }
}

