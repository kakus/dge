var createSampleWorld = function()
{
    var boxfix = new FixtureDef
      , groundFix = new FixtureDef
      , box;

    boxfix.setAsBox(20, 20);
    boxfix.density = 1;

    groundFix.setAsBox(100, 10);

    box = world.createBody(boxfix);
    box.y -= 100;
    box.dynamic = true;

    box = world.createBody(boxfix);
    box.y -= 150;
    box.x = 30
    box.dynamic = true;

    world.createBody(groundFix);
}

var box = function(width, height)
{
    var f = new FixtureDef;

    width = width || 10;

    if (height === null || height === undefined)
        f.setAsBox(width, width);
    else
        f.setAsBox(width, height);

    f.density = 1;

    return world.createBody(f);
}

var cir = function(size)
{
    var f = new FixtureDef;

    size = size || 30;

    f.setAsCircle(size);
    f.density = 1;

    return world.createBody(f);
}
