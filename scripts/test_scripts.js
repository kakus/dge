var createSampleWorld = function()
{
    var f = new FixtureDef,
        f2 = new FixtureDef,
        b  = new BodyDef,
        ground = new BodyDef;

    f.setAsBox(25, 25);
    f2.setAsBox(200, 25);

    b.dynamic = true;
    b.createFixture(f);

    ground.createFixture(f2);
    ground.y = 100;

    world.addBody(ground);
    world.addBody(b);
}
