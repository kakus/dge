(function()
{
    var tool = {},
    body = null,
            startX = 0,
            startY = 0;

    tool.icon = "redo.png";
    tool.checkable = false;
    tool.positionOnToolbar = 1;
    tool.shortcut = "Ctrl+Shift+Z";

    tool.buttonClicked = function()
    {
        getCmdManager().redo();
    }

    return tool;

})();
