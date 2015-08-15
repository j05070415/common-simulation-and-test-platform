import QtQuick 2.0
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1

Rectangle {
    id: root
    objectName: "homepage"
    signal action(string json, var paramter)
    function onCommand(json, parameter)
    {
        var obj = eval(json)
        //objectName is target
        if (obj.action == 5)
            newProject.onCommand(json, parameter)
        else if (obj.action == 3)
        {
            console.log('close project')
            if (!mainrect.prevProject)
            {
                mainrect.project.destroy()
            }
        }
    }

    function show(maxed) {
        homeHeader.show(maxed)
    }

    HomePageHeader {
        id: homeHeader
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right

        Rectangle
        {
            id: logoSpacer
            x: left.width
            anchors.top: parent.top
            height: root.height
            width: 1
            color:"#BBBBBB"
        }
    }

    Rectangle {
        id: left
        anchors.left: homeHeader.left
        anchors.bottom: parent.bottom
        anchors.top: homeHeader.bottom
        width: root.width/7
        color: "grey"

        Rectangle
        {
            id: spacer
            anchors.top: parent.top
            anchors.left: parent.left
            width: parent.width
            height: 1
            color:"#BBBBBB"
        }

        RectLabel {
            id: newProject
            objectName: "actionNewProject"
            anchors.top: spacer.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            pixsize: 14
            text: "新    建"

            function clearContent()
            {
                //newContent.clear()
            }

            function onCommand(command, params)
            {
                //{projectName, icon, desc}
                var json = eval(command)
                newContent.addItem(json.projectName, json.picture, json.text)
            }

            onClicked: {
                newProject.clearContent()
                root.action('{"action":5,"objectName":"actionNewProject"}', '')
            }
        }

        Rectangle
        {
            id: spacer1
            anchors.top: newProject.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            height: 1
            color: spacer.color
        }

        RectLabel {
            id: openProject
            objectName: "actionOpenProject"
            anchors.top: spacer1.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            pixsize: 14
            text: "打    开"
        }

        Rectangle
        {
            id: spacer2
            anchors.top: openProject.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            height: 1
            color: spacer.color
        }

        RectLabel {
            id: saveProject
            objectName: "actionSaveProject"
            anchors.top: spacer2.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            pixsize: 14
            text: "保    存"
        }

        Rectangle
        {
            id: spacer3
            anchors.top: saveProject.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            height: 1
            color: spacer.color
        }

        RectLabel {
            id: closeProject
            objectName: "actionCloseProject"
            anchors.top: spacer3.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            pixsize: 14
            text: "关    闭"
        }

        HomePageContent {
            id: newContent
            objectName: "content"
            x: left.width
            y: spacer.y
            width:  root.width - left.width + 1
            height: root.height - homeHeader.height + 1

            onItemClicked: {
                console.log('load projectName:'+name)
                mainrect.loadProject(name)
            }
        }
    }
}

