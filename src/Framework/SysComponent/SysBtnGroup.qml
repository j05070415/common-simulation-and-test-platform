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
    z: 1
    //初始最大化
    property bool maxed: true
    onMaxedChanged: {
        if (maxed)
        {
            maxbtn.picPressed = "Image/restore_pressed.png"
            maxbtn.picHover = "Image/restore_hover.png"
            maxbtn.picNormal = "Image/restore_normal.png"
            maxbtn.picCurrent = "Image/restore_normal.png"
            console.log("state max")
        }
        else
        {
            maxbtn.picPressed = "Image/max_pressed.png"
            maxbtn.picHover = "Image/max_hover.png"
            maxbtn.picNormal = "Image/max_normal.png"
            maxbtn.picCurrent = "Image/max_normal.png"
            console.log("state restore")
        }
    }

    function doubleClicked()
    {
        console.log("doubleClicked")
        maxbtn.clicked()
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
        id: maxbtn
        x: 652
        y: 1
        picPressed: "Image/restore_pressed.png"
        picHover: "Image/restore_hover.png"
        picNormal: "Image/restore_normal.png"
        picCurrent: "Image/restore_normal.png"

        onClicked:
        {
            if (maxed) {
                maxbtn.picPressed = "Image/max_pressed.png"
                maxbtn.picHover = "Image/max_hover.png"
                maxbtn.picNormal = "Image/max_normal.png"
                maxbtn.picCurrent = "Image/max_normal.png"
                console.log("restore btn clicked")
                sysbtngroup.restore()
            }
            else {
                maxbtn.picPressed = "Image/restore_pressed.png"
                maxbtn.picHover = "Image/restore_hover.png"
                maxbtn.picNormal = "Image/restore_normal.png"
                maxbtn.picCurrent = "Image/restore_normal.png"
                console.log("max btn clicked")
                sysbtngroup.max()
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
