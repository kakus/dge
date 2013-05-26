(function()
{
    var tool = {},
        body = null,
            startX = 0,
            startY = 0;

    tool.icon = "undo.png";
    tool.checkable = false;
    tool.positionOnToolbar = 0;
    tool.shortcut = "Ctrl+Z";

    tool.buttonClicked = function()
    {
        getCmdManager().undo();
    }

    return tool;

})();
