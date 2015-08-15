
function max_function()
{
    window.showMaximized()
    mainrect.x = 0
    mainrect.y = 0
    mainrect.width = window.width
    mainrect.height = window.height
}

function restore_function()
{
    window.showNormal()
    mainrect.x = mainrect.x + margin
    mainrect.y = mainrect.y + margin
    mainrect.width = window.width - 2*margin
    mainrect.height = window.height - 2*margin
}
