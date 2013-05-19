(function(global) {

var box, startX, startY;

global.icon = "rectangle.jpg";

global.mouseButtonPress = function (x,y)
{
    var fix = new FixtureDef;

    fix.setAsBox(0, 0);
    fix.density = 1;

    box = world.createBody();
    box.dynamic = true;
    box.x = x;
    box.y = y;
    box.createFixture(fix);

    startX = x;
    startY = y;

}

global.mouseButtonRelease = function(x,y)
{

}

global.mouseMove = function(x,y)
{
    var fix = box.fixtureList[0];

    fix.setAsBox( (Math.abs(startX-x))/2, (Math.abs(startY-y))/2);
    fix.density = 1;

    box.x = x > startX ? (x-startX)/2 + startX : (startX-x)/2 + x;
    box.y = y > startY ? (y-startY)/2 + startY : (startY-y)/2 + y;
}

})(this);
