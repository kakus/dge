(function()
{
    var tool = {},
        body = 0,
        startX = 0,
        startY = 0;

    tool.icon = "static_rectangle.jpg";
    tool.checkable = true;

    tool.mouseButtonPress = function (x,y)
    {
        var fix = new FixtureDef;

        startX = x;
        startY = y;

        fix.setAsBox(0, 0);
        fix.density = 1;

        body = world.createBody();
        body.static = true;
        body.x = x;
        body.y = y;
        body.createFixture(fix);

    }

    tool.mouseMove = function(x,y)
    {
        var fix = body.fixtureList[0];

        fix.setAsBox( ( Math.abs(startX-x) )/2, ( Math.abs(startY-y) )/2);
        fix.density = 1;

        body.x = x > startX ? (x-startX)/2 + startX : (startX-x)/2 + x;
        body.y = y > startY ? (y-startY)/2 + startY : (startY-y)/2 + y;
    }

    tool.mouseButtonRelease = function(x,y)
    {
        cmdManager.pushCmd(world, world.removeBody , [body] , undefined , print, ["here should be redo"]);
    }

    return tool;

})();
