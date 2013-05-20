(function()
{
    var tool = {},
    body = null,
            startX = 0,
            startY = 0;

    tool.icon = "undo.jpg";
    tool.checkable = false;

    tool.buttonClicked = function()
    {
        cmdManager.undo();
    }

    return tool;

})();
