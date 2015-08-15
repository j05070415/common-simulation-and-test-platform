import QtQuick 2.0
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.2

ScrollView {
    id: root

    signal itemClicked(string name)

    function addItem(objName, pic, btnText)
    {
        var str = 'import QtQuick 2.2; HomePageContentItem {
                           objectName: "' + objName + '_button";
                           srcPicture:"' + pic + '";name:"' + btnText +'"
                           onClicked: {root.itemClicked(objectName.split("_")[0])}}'
        Qt.createQmlObject(str, layout, "log.txt")
    }

    function clear()
    {
        console.log(layout.children.cout)
        for (var i=layout.children.count - 1; i>=0; --i)
        {
            delete layout.children[i]
        }
    }

    GridLayout {
        id: layout
        anchors.fill: parent
        flow: GridLayout.LeftToRight
        columns: 4
        columnSpacing: 10
    }
}

