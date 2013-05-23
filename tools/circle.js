(function()
{
    var tool = {},
        body = null,
        body_template = null,
        start_x = 0,
        start_y = 0;

    tool.keyboardManager = new KeyboardManager;

    tool.icon = "circle.png";
    tool.checkable = true;
    tool.positionOnToolbar = 2;

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

        start_x = x;
        start_y = y;
    }

    tool.mouseButtonRelease = function(x, y)
    {
        body_template = new BodyDef(body);
        world.removeBody(body);

        getCmdManager().pushCmd(
                    (function(body){

                        var body_template = body;
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
                    })(body_template));
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
