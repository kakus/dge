(function()
{
    var tool = {};

    tool.icon = "zoom-in";
    tool.checkable = false;
    tool.positionOnToolbar = 21;

    tool.buttonClicked = function()
    {
        world.stage.zoomIn();
    }

    return tool;

})();
