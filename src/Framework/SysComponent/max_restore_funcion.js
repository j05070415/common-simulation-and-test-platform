function max_function()
{
    window.showMaximized()
    mainLayout.x = 0
    mainLayout.y = 0
    mainLayout.width = window.width
    mainLayout.height = window.height
}

function restore_function()
{
    window.showNormal()
    mainLayout.x = mainLayout.x + margin
    mainLayout.y = mainLayout.y + margin
    mainLayout.width = window.width - 2*margin
    mainLayout.height = window.height - 2*margin
}
