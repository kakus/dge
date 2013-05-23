(function()
{
    var tool = {},
        body = 0,
        start_x = 0,
        start_y = 0;

    tool.keyboardManager = new KeyboardManager;

    tool.icon = "static_box.png";
    tool.checkable = true;
    tool.positionOnToolbar = 5;

    tool.mouseButtonPress = function (x,y)
    {
        var fix = new FixtureDef;

        start_x = x;
        start_y = y;

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

        fix.setAsBox( ( Math.abs(start_x-x) )/2, ( Math.abs(start_y-y) )/2);
        fix.density = 1;

        body.x = x > start_x ? (x-start_x)/2 + start_x : (start_x-x)/2 + x;
        body.y = y > start_y ? (y-start_y)/2 + start_y : (start_y-y)/2 + y;
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

    return tool;

})();
