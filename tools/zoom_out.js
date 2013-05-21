(function()
{
    var tool = {};

    tool.icon = "zoom-out";
    tool.checkable = false;

    tool.mouseButtonPress = function (x,y)
    {
    }

    tool.mouseMove = function(x,y)
    {
    }

    tool.mouseButtonRelease = function(x,y)
    {
    }

    tool.buttonClicked = function()
    {
        world.stage.zoomOut();
    }
    return tool;

})();
