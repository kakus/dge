(function()
{
    var tool = {};

    tool.icon = "zoom-original";
    tool.checkable = false;
    tool.positionOnToolbar = 23;

    tool.buttonClicked = function()
    {
        world.stage.resetZoom();
    }

    return tool;

})();
