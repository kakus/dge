(function()
{
    var tool = {},
        body = null,
        startX = 0,
        startY = 0;

    tool.icon = "circle.jpg";
    tool.checkable = true;

    tool.mouseButtonPress = function (x,y)
    {
        var fix = new FixtureDef;

        fix.setAsCircle(0);
        fix.density = 1;

        body = world.createBody();
        body.dynamic = true;
        body.x = x;
        body.y = y;
        body.createFixture(fix);

        startX = x;
        startY = y;
    }

    tool.mouseButtonRelease = function(x, y)
    {
        cmdManager.pushCmd(world, world.removeBody , [body] , undefined , print, ["here should be redo"]);
    }

    tool.mouseMove = function(x,y)
    {
        var fix = body.fixtureList[0];
        var size = ( Math.abs(startX-x)) > (Math.abs(startY-y)) ? (Math.abs(startY-y))/2 : (Math.abs(startX-x))/2;

        fix.setAsCircle(size);
        fix.density = 1;

        body.x = x > startX ? startX + size : startX - size;
        body.y = y > startY ? startY + size : startY - size;
    }

    return tool;

})();
