(function(global) {

    var body, startX, startY;

    global.icon = "circle.jpg";
    global.checkable = true;

    global.mouseButtonPress = function (x,y)
    {
        var fix = new FixtureDef;

        fix.setAsCircle(0,0);
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

        var size = ( Math.abs(startX-x)) > (Math.abs(startY-y)) ? (Math.abs(startY-y))/2 : (Math.abs(startX-x))/2;

        fix.setAsCircle(size);
        fix.density = 1;

        body.x = x > startX ? startX + size : startX - size;
        body.y = y > startY ? startY + size : startY - size;

    }

})(this);
