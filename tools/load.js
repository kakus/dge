(function()
{
    var tool = {},
    body = null,
            startX = 0,
            startY = 0;

    tool.icon = "load2.png";
    tool.checkable = false;
    tool.positionOnToolbar = -2;
    tool.shortcut = "Ctrl+O";

    tool.buttonClicked = function()
    {
        io.loadFile();
    }

    return tool;

})();
