var createSampleWorld = function()
{
    var f = new FixtureDef,
        f2 = new FixtureDef,
        f3 = new FixtureDef,
        b  = new BodyDef,
        b2 = new BodyDef,
        ground = new BodyDef;

    f.setAsBox(25, 25);
    f.density = 1;
    f2.setAsBox(200, 25);
    f3.setAsBox(15, 15);
    f3.density = 1;

    b.dynamic = true;
    b.createFixture(f);
    b2.dynamic = true;
    b2.createFixture(f3);
    b2.x = 35;
    b2.y = -120;

    ground.createFixture(f2);
    ground.y = 100;

    world.addBody(ground);
    world.addBody(b);
    world.addBody(b2);
}

var box = function(size)
{
    var b = new BodyDef,
        f = new FixtureDef;

    size = size || 10;

    f.setAsBox(size, size);
    f.density = 1;

    b.createFixture(f);
    return b;
}
