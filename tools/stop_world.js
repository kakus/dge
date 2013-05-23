(function()
{
    var tool = {};

    tool.icon = "stop_world.png"
    tool.checkable = false;
    tool.positionOnToolbar = 16;

    tool.buttonClicked = function()
    {
        world.stop();
    }

    return tool;

})();
