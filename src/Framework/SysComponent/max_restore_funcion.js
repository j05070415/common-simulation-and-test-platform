function max_function()
{
    window.showMaximized()
    homePage.x = 0
    homePage.y = 0
    homePage.width = window.width
    homePage.height = window.height
}

function restore_function()
{
    window.showNormal()
    homePage.x = homePage.x + margin
    homePage.y = homePage.y + margin
    homePage.width = window.width - 2*margin
    homePage.height = window.height - 2*margin
}
