var temp;
var startX;
var startY;

function mouseButtonPress(x,y){
    print("mouseButtonPress1\t" + "x: " + x.toString() + "\ty: "+y.toString());
    var fix = new FixtureDef;
    var body  = new BodyDef;

    startX = x;
    startY = y;

    fix.setAsBox(1, 1);
    fix.density = 1;

    body.dynamic = true;
    body.createFixture(fix);

    body.x = x;
    body.y = y;

    temp = body;

    world.addBody(body);

    print("created\n");
}

function mouseButtonRelease(x,y){
    print("mouseButtonRelease1\t" + "x: " + x.toString() + "\ty: "+y.toString());

}

function mouseMove(x,y){
    print("mouseButtonMove1\t" + "x: " + x.toString() + "\ty: "+y.toString());

    world.removeBody(temp);

    var fix = new FixtureDef;
    var body  = new BodyDef;

    fix.setAsBox( Math.abs(startX-x), Math.abs(startY-y) );
    fix.density = 1;

    body.dynamic = true;
    body.createFixture(fix);

    body.x = startX;
    body.y = startY;

    temp = body;

    world.addBody(body);

}
