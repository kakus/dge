// Tool for selecting bodies
// @date   21.05.2013
// @author Kamil Misiowiec
(function()
{

    var tool = {}
    , selectedBodies = []
    , selectedRect = []
    , startX = 0
    , startY = 0
    , moveX = 0
    , moveY = 0
    , SELECTION_MODE = false
    , posBeforeDrag = []
    ;

    tool.keyboardManager = new KeyboardManager;
    tool.checkable = true;
    tool.icon = "select.png";
    tool.positionOnToolbar = 8;

    tool.mouseButtonPress = function (x,y)
    {
        var body = world.bodyAt(x, y);

        startX = moveX = x;
        startY = moveY = y;

        if (!body)
        {
            SELECTION_MODE = true;

            for (var i in selectedBodies)
                selectedBodies[i].isSelected = false;

            selectedBodies = [];
            selectedRect = [];
        }

        if (selectedBodies.length !== 0 )
        {
            var newSelection = true;

            for (var i in selectedBodies)
                if (body == selectedBodies[i])
                    newSelection = false;

            if (newSelection)
            {
                for (var i in selectedBodies)
                    selectedBodies[i].isSelected = false;

                selectedBodies = [];
            }
            // we are clicked on selected body, which means we can move it now
            else
            {
                posBeforeDrag = []
                for (var i in selectedBodies)
                    posBeforeDrag.push({
                                          id: selectedBodies[i].id,
                                          x: selectedBodies[i].x,
                                          y: selectedBodies[i].y
                                      });
                return;
            }
        }

        selectedBodies = [ body ];
        body.isSelected = true;
        posBeforeDrag = [ {
            id: body.id,
            x: body.x,
            y: body.y
        } ];
    }

    tool.mouseButtonRelease = function(x,y)
    {
        if (SELECTION_MODE)
        {
            world.stage.clearSelection();
            SELECTION_MODE = false;
            var bodies = world.bodiesAt(
                        selectedRect[0],
                        selectedRect[1],
                        selectedRect[2],
                        selectedRect[3]
                        );
            for (var i in bodies)
                bodies[i].isSelected = true;

            selectedBodies = bodies;
        }
        else
        {
            if (selectedBodies.length === 0)
                return;

            getCmdManager().pushCmd( (function(selectedBodies, posBeforeDrag) {
                var bodiesPos = []
                  , bodiesOldPos = [];

                for (var i in selectedBodies)
                {
                    bodiesPos.push({
                        id: selectedBodies[i].id,
                        x: selectedBodies[i].x,
                        y: selectedBodies[i].y
                    });
                }

                for (var i in posBeforeDrag)
                {
                    bodiesOldPos.push({
                        id: posBeforeDrag[i].id,
                        x: posBeforeDrag[i].x,
                        y: posBeforeDrag[i].y
                    });
                }

                return {
                    exec: function() {
                        for (var i in bodiesPos)
                        {
                            var body = world.getBodyById(bodiesPos[i].id);
                            body.x = bodiesPos[i].x;
                            body.y = bodiesPos[i].y;
                        }
                    },

                    undo: function() {
                        for (var i in bodiesOldPos)
                        {
                            var body = world.getBodyById(bodiesOldPos[i].id);
                            body.x = bodiesOldPos[i].x;
                            body.y = bodiesOldPos[i].y;
                        }
                    }
                };
            })(selectedBodies, posBeforeDrag) );
        }
    }

    tool.mouseMove = function(x,y)
    {
        if (SELECTION_MODE)
        {
            var sx, sy, ex, ey;
            if (x > startX) {
                sx = startX; ex = x;
            } else {
                sx = x; ex = startX;
            }

            if (y > startY) {
                sy = startY; ey = y;
            } else {
                sy = y; ey = startY;
            }

            world.stage.setSelection(sx, sy, ex - sx, ey - sy);
            selectedRect = [sx, sy, ex - sx, ey - sy];
        }
        else
        {
            var dx = x - moveX
            , dy = y - moveY
            ;

            for (var i in selectedBodies)
            {
                selectedBodies[i].x += dx;
                selectedBodies[i].y += dy;
            }

        }

        moveX = x;
        moveY = y;
    }

    tool.keyboardManager.register("Delete", function()
    {
        if(selectedBodies !== null)
        {
            getCmdManager().pushCmd( (function(selectedBodies) {

                var ids = [];
                var bodies = [];

                for (var i in selectedBodies)
                {
                    ids.push(selectedBodies[i].id);
                    bodies.push(new BodyDef(selectedBodies[i]));
                }


                return {
                    exec: function() {
                        for (var i in ids)
                            world.removeBody(world.getBodyById(ids[i]));
                    },

                    undo: function()
                    {
                        for (var i in bodies)
                            world.createBody(bodies[i]);
                    }
                };
            })(selectedBodies) );
        }
    });

    return tool;

})();
