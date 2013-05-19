(function(tool) {

var body = null
, offsetx = 0
, offsety = 0
;


tool.mouseButtonPress = function (x,y)
{
    body = world.bodyAt(x, y);
    offsetx = x - body.x;
    offsety = y - body.y;
    body.isSelected = true;
}

tool.mouseButtonRelease = function(x,y)
{
    body.isSelected = false;
    body = null;
}

tool.mouseMove = function(x,y)
{
    if (body)
    {
        body.x = x - offsetx; body.y = y - offsety;
    }
}

})(this);
