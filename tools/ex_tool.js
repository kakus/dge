var temp, startX, startY;

var icon = "ex_tool.gif";

function mouseButtonPress(x,y)
{
    print("mouseButtonPress1\t" + "x: " + x.toString() + "\ty: "+y.toString());
    var fix = new FixtureDef;
    var body  = new BodyDef;

    startX = x;
    startY = y;

    fix.setAsBox(0, 0);
    fix.density = 1;

    body.dynamic = true;
    body.createFixture(fix);

    body.x = x;
    body.y = y;

    temp = body;

    world.addBody(body);

    print("created\n");
}

function mouseButtonRelease(x,y)
{
    print("mouseButtonRelease1\t" + "x: " + x.toString() + "\ty: "+y.toString());
}

function mouseMove(x,y)
{
    print("mouseButtonMove1\t" + "x: " + x + "\ty: "+y);

    world.removeBody(temp);

    var fix = new FixtureDef;
    var body  = new BodyDef;

    fix.setAsBox( (Math.abs(startX-x))/2, (Math.abs(startY-y))/2);
    fix.density = 1;

    body.dynamic = true;
    body.createFixture(fix);

    body.x = x > startX ? (x-startX)/2 + startX : (startX-x)/2 + startX;
    body.y = y > startY ? (y-startY)/2 + startY : (startY-y)/2 + startY;

    temp = body;

    world.addBody(body);
}
