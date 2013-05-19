(function(global) {

var body, startX, startY;

global.icon = "rectangle.jpg";
global.checkable = true;

global.mouseButtonPress = function (x,y)
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

global.mouseButtonRelease = function(x,y)
{

}

global.mouseMove = function(x,y)
{
    var fix = body.fixtureList[0];

    fix.setAsBox( (Math.abs(startX-x))/2, (Math.abs(startY-y))/2);
    fix.density = 1;

    body.x = x > startX ? (x-startX)/2 + startX : (startX-x)/2 + x;
    body.y = y > startY ? (y-startY)/2 + startY : (startY-y)/2 + y;
}

})(this);
