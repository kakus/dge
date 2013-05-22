(function()
{
    var tool = {},
        body = null,
        startX = 0,
        startY = 0;

    tool.icon = "box.png";
    tool.checkable = true;
    tool.positionOnToolbar = 4;

    tool.mouseButtonPress = function (x,y)
    {
        var fix = new FixtureDef;

        fix.setAsBox(0, 0);
        fix.density = 1;

        body = world.createBody();
        body.dynamic = true;
        body.x = x;
        body.y = y;
        body.createFixture(fix);

        startX = x;
        startY = y;

    }

    tool.mouseMove = function(x,y)
    {
        var fix = body.fixtureList[0];

        fix.setAsBox( (Math.abs(startX-x))/2, (Math.abs(startY-y))/2);
        fix.density = 1;

        body.x = x > startX ? (x-startX)/2 + startX : (startX-x)/2 + x;
        body.y = y > startY ? (y-startY)/2 + startY : (startY-y)/2 + y;
    }

    tool.mouseButtonRelease = function(x, y)
    {
        cmdManager.pushCmd(
                        (function(){
                            var currentBody = null;
                            var bodyTemplate = new BodyDef(body);

                            return{
                                exec: function()
                                {
                                   currentBody = world.createBody(bodyTemplate);
                                },

                                undo: function()
                                {
                                    world.removeBody(currentBody);
                                }
                            }
        })());

        world.removeBody(body);
    }

    return tool;

})();
