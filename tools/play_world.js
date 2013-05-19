(function()
{
    var tool = {};

    tool.icon = "play_world.jpg"
    tool.checkable = false;

    tool.buttonClicked = function()
    {
        world.run();
    }

    return tool;

})();
