(function()
{
    var tool = {},
    body = null,
            startX = 0,
            startY = 0;

    tool.icon = "static_circle.png";
    tool.checkable = true;
    tool.positionOnToolbar = 3;

    tool.mouseButtonPress = function (x,y)
    {
        var fix = new FixtureDef;

        fix.setAsCircle(0);
        fix.density = 1;

        body = world.createBody();
        body.static = true;
        body.x = x;
        body.y = y;
        body.createFixture(fix);

        startX = x;
        startY = y;
    }

    tool.mouseButtonRelease = function(x, y)
    {
        getCmdManager().pushCmd(
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
