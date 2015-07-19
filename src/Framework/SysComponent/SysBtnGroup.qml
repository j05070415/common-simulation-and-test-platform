import QtQuick 2.2

Row
{
    id: sysbtngroup
    spacing: 0

    signal skin
    signal feedback
    signal menu
    signal min
    signal close
    signal max
    signal restore
    layoutDirection: Qt.LeftToRight
    //初始最大化
    property bool maxed: true
    z: 1

    function doubleClicked()
    {
        console.log("doubleClicked")
        max.clicked()
    }

    SysBtn
    {
        id:skin
        picHover: "Image/skin_hover.png"
        picNormal: "Image/skin_normal.png"
        picPressed: "Image/skin_pressed.png"
        onClicked:
        {
            console.log("skin btn clicked")
            sysbtngroup.skin()
        }
    }

    SysBtn
    {
        id:menu
        picHover: "Image/menu_hover.png"
        picNormal: "Image/menu_normal.png"
        picPressed: "Image/menu_pressed.png"
        onClicked:
        {
            console.log("menu btn clicked")
            sysbtngroup.menu()
        }
    }

    SysBtn
    {
        id:min
        picHover: "Image/min_hover.png"
        picNormal: "Image/min_normal.png"
        picPressed: "Image/min_pressed.png"
        onClicked:
        {
            console.log("min btn clicked")
            sysbtngroup.min()
        }
    }

    SysBtn {
        id: max
        x: 652
        y: 1
        picPressed: "Image/max_pressed.png"
        picHover: "Image/max_hover.png"
        picNormal: "Image/max_normal.png"
        picCurrent: "Image/max_normal.png"

        onClicked:
        {
            if (maxed)
            {
                picPressed: "Image/restore_pressed.png"
                picHover: "Image/restore_hover.png"
                picNormal: "Image/restore_normal.png"
                picCurrent: "Image/restore_normal.png"
                sysbtngroup.restore()
                console.log("restore btn clicked")
            }
            else
            {
                picPressed: "Image/max_pressed.png"
                picHover: "Image/max_hover.png"
                picNormal: "Image/max_normal.png"
                picCurrent: "Image/max_normal.png"
                sysbtngroup.max()
                console.log("max btn clicked")
            }

            maxed = !maxed
        }
    }

    SysBtn
    {
        id:close
        width: 27
        picCurrent: "Image/close_normal.png"
        picHover: "Image/close_hover.png"
        picNormal: "Image/close_normal.png"
        picPressed: "Image/close_pressed.png"
        onClicked:
        {
            console.log("close btn clicked")
            sysbtngroup.close()
        }
    }




}
