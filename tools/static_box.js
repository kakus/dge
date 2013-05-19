(function(tool) {

var box, startX, startY;

tool.icon = "static_rectangle.jpg";

tool.mouseButtonPress = function (x,y)
{
    var fix = new FixtureDef;

    startX = x;
    startY = y;

    fix.setAsBox(0, 0);
    fix.density = 1;

    box = world.createBody();
    box.static = true;
    box.x = x;
    box.y = y;
    box.createFixture(fix);
}

tool.mouseButtonRelease = function(x,y)
{

}

tool.mouseMove = function(x,y)
{
    var fix = box.fixtureList[0];

    fix.setAsBox( ( Math.abs(startX-x) )/2, ( Math.abs(startY-y) )/2);
    fix.density = 1;

    box.x = x > startX ? (x-startX)/2 + startX : (startX-x)/2 + x;
    box.y = y > startY ? (y-startY)/2 + startY : (startY-y)/2 + y;
}

})(this);
