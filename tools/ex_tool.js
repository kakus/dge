var temp;
var startX;
var startY;

function mouseButtonPress(x,y){
    print("mouseButtonPress1\t" + "x: " + x.toString() + "\ty: "+y.toString());
    var fix = new FixtureDef;

    startX = x;
    startY = y;

    fix.setAsBox(1, 1);
    fix.density = 1;

    temp = world.createBody(fix);
    temp.dynamic = true;

    temp.x = x;
    temp.y = y;

    print("created\n");
}

function mouseButtonRelease(x,y){
    print("mouseButtonRelease1\t" + "x: " + x.toString() + "\ty: "+y.toString());

}

function mouseMove(x,y){
    print("mouseButtonMove1\t" + "x: " + x.toString() + "\ty: "+y.toString());

    world.removeBody(temp);

    var fix = new FixtureDef;

    fix.setAsBox( Math.abs(startX-x), Math.abs(startY-y) );
    fix.density = 1;

    temp = world.createBody(fix);
    temp.dynamic = true;
    temp.x = startX;
    temp.y = startY;
}
