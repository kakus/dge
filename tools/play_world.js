(function()
{
    var tool = {};

    tool.icon = "play_world.png"
    tool.checkable = true;
    tool.positionOnToolbar = 15;

    tool.buttonClicked = function()
    {
        world.run();
    }

    return tool;

})();
