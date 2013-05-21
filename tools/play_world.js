(function()
{
    var tool = {};

    tool.icon = "play_world.png"
    tool.checkable = false;

    tool.buttonClicked = function()
    {
        world.run();
    }

    return tool;

})();
