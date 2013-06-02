(function()
{
    var tool = {},
    body = null,
            startX = 0,
            startY = 0;

    tool.icon = "save.png";
    tool.checkable = false;
    tool.positionOnToolbar = -1;
    tool.shortcut = "Ctrl+S";

    tool.buttonClicked = function()
    {
        io.saveFile();
    }

    return tool;

})();
