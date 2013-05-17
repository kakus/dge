var temp, startX, startY;

var icon = "ex_tool.gif";

function mouseButtonPress(x,y)
{
    print("mouseButtonPress1\t" + "x: " + x.toString() + "\ty: "+y.toString());
    var fix = new FixtureDef;

    startX = x;
    startY = y;

    fix.setAsBox(0, 0);
    fix.density = 1;

    temp = world.createBody(fix);
    temp.dynamic = true;

    temp.x = x;
    temp.y = y;

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

    fix.setAsBox( (Math.abs(startX-x))/2, (Math.abs(startY-y))/2);
    fix.density = 1;

    body = world.createBody(fix);
    body.dynamic = true;

    body.x = x > startX ? (x-startX)/2 + startX : (startX-x)/2 + startX;
    body.y = y > startY ? (y-startY)/2 + startY : (startY-y)/2 + startY;

    temp = body;
}
