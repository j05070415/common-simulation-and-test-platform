import QtQuick 2.2
import QtGraphicalEffects 1.0
import QtQuick.Layouts 1.1
import QtQuick.Window 2.2
import "../SysComponent"
import "../SysComponent/max_restore_funcion.js" as MaxRestore

Rectangle {
    id: root
    objectName: "HwaCanProject"
    anchors.fill: parent

    Component.onCompleted: {
        print('HomePage:' + Window.Maximized)
        topTitle.show(window.visibility == Window.Maximized)
    }

    ColumnLayout {
        id: mainLayout
        anchors.margins: 0
        anchors.fill: parent

        TopTitle {
            id: topTitle
            Layout.fillWidth: true
            anchors.top: parent.top
            onHeaderClicked:
            {
                console.log('title index:'+index)
                if (index == 0)
                {
                    homepage.show(window.visibility == Window.Maximized)
                    homepage.opacity = 1
                    canproject.x = 200
                }
            }
        }

        RowLayout {
            ColumnLayout {
                HwaTreeView {
                    id: treeview
                    Layout.fillHeight: true
                }

                HwaTreeNodePropertyEditor {
                    id: propeditor
                    Layout.fillHeight: true
                }
            }

            CanDataView {
                id: canView
                objectName: "HwaCanDataView"
                Layout.fillHeight: true
                Layout.fillWidth: true
            }
        }
    }
}


