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
    ;

    tool.icon = "input-mouse";
    tool.checkable = true;

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
            else
                return;
        }

        selectedBodies = [ body ];
        body.isSelected = true;
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

    return tool;

})();
