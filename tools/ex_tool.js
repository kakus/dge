(function(tool) {

// kiedy nie bylo samowykonującej się funkcji to zmienna box przeslaniala mi
// moja funkcje box, wiec chyba dobra praktyka bylo by branie narzedzi w
// te samo... funkcje :)
var box, startX, startY;

tool.icon = "ex_tool.gif";

tool.mouseButtonPress = function (x,y)
{
    print("mouseButtonPress1\t" + "x: " + x.toString() + "\ty: "+y.toString());
    var fix = new FixtureDef;

    startX = x;
    startY = y;

    fix.setAsBox(0, 0);
    fix.density = 1;

    box = world.createBody();
    box.dynamic = true;

    box.x = x;
    box.y = y;

    box.createFixture(fix);

    print("created\n");
}

tool.mouseButtonRelease = function(x,y)
{
    print("mouseButtonRelease1\t" + "x: " + x.toString() + "\ty: "+y.toString());
}

tool.mouseMove = function(x,y)
{
    print("mouseButtonMove1\t" + "x: " + x + "\ty: "+y);


    var fix = box.fixtureList[0];

    fix.setAsBox( (Math.abs(startX-x))/2, (Math.abs(startY-y))/2);
    fix.density = 1;


    box.x = x > startX ? (x-startX)/2 + startX : (startX-x)/2 + startX;
    box.y = y > startY ? (y-startY)/2 + startY : (startY-y)/2 + startY;
}

})(this);
