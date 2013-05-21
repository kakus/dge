(function()
{
    var tool = {},
    body = null,
            startX = 0,
            startY = 0;

    tool.icon = "redo.png";
    tool.checkable = false;
     tool.positionOnToolbar = 1;

    tool.buttonClicked = function()
    {
        cmdManager.redo();
    }

    return tool;

})();
