/*!
 * Display all object properties in formated manner
 */
var list = function(obj, intend)
{
    intend = intend || '';
    var str = '{\n';

    for (var i in obj)
    {
        if (!obj.hasOwnProperty(i))
            continue;

        str += intend +'  ' + i + ': ';
        if (obj[i] instanceof Object)
        {
            if ( /[^(]*\([^)]*\)/i.test(i) )
                str += 'slot or signal\n';
            else
                str += list(obj[i], intend + '  ');
        }
        else
            str += obj[i] + '\n';
    }

    return str += intend + '}\n';
};


// Create a copy of all properties and fixtures of a body
// So you can store bodies without creating them in the world
// Example:
//      var b = box();
//      var g = new GhostBody(b);
//      world.removeBody(b);        # body disapears of screen
//      g.reincarnate();            # now we can easly recreate that body
function GhostBody(body)
{
    var m_ghost = {
        fixtureList: []
    };

    // clone all properties
    for (var prop in body)
    {
        if (body.hasOwnProperty(prop))
        {
            if (typeof body[prop] === 'number' || typeof body[prop] === 'boolean' )
                m_ghost[prop] = body[prop];
        }
    }

    // clone fixtures
    for (var fix in body.fixtureList)
        m_ghost.fixtureList.push(new FixtureDef(body.fixtureList[fix]));

    // display properties of body
    this.show = function()
    {
        return list(m_ghost);
    };

    // recreate this body and add to the world !
    this.reincarnate = function()
    {
        var body = world.createBody();
        for (var i in m_ghost.fixtureList)
            body.createFixture(m_ghost.fixtureList[i]);

        for (var prop in m_ghost)
            if (typeof body[prop] === 'number' || typeof body[prop] === 'boolean' )
                body[prop] = m_ghost[prop];

        return body;
    };
};
