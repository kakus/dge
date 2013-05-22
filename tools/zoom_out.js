(function()
{
    var tool = {};

    tool.icon = "zoom-out";
    tool.checkable = false;
    tool.positionOnToolbar = 22;

    tool.buttonClicked = function()
    {
        world.stage.zoomOut();
    }
    return tool;

})();
