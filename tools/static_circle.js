(function()
{
    var tool = {},
        body = null,
        start_x = 0,
        start_y = 0;

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

        start_x = x;
        start_y = y;
    }

    tool.mouseButtonRelease = function(x, y)
    {
        getCmdManager().pushCmd(
                        (function(body){

                            var body_template = new BodyDef(body);
                            var id = body.id;

                            return{
                                exec: function()
                                {
                                   world.createBody(body_template);
                                },

                                undo: function()
                                {
                                    world.removeBody( world.getBodyById(id) );
                                }
                            }
        })(body));

        world.removeBody(body);

    }

    tool.mouseMove = function(x,y)
    {
        var fix = body.fixtureList[0];
        var size = ( Math.abs(start_x-x)) > (Math.abs(start_y-y)) ? (Math.abs(start_y-y))/2 : (Math.abs(start_x-x))/2;

        fix.setAsCircle(size);
        fix.density = 1;

        body.x = x > start_x ? start_x + size : start_x - size;
        body.y = y > start_y ? start_y + size : start_y - size;
    }

    return tool;

})();
