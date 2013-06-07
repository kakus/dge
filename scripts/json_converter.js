var json_converter = (function(){

    var shape_code_map = {
        "circle"    : 0,
        "edge"      : 1,
        "polygon"   : 2,
        "chain"     : 3
    }

    function stringify(world)
    {
        var obj = world.getBodies(),
                fileContent = "";

        for( var x in obj)
        {
            obj[x].shape = [];
            obj[x].data = [];

            for( var y in obj[x].fixtureList)
            {
                obj[x].shape.push(obj[x].fixtureList[y].getShapeType());
                obj[x].data.push(obj[x].fixtureList[y].getShapeData());
            }

            fileContent += JSON.stringify(obj[x]) + "\n";
        }

        return fileContent;
    }

    function parse(fileContent, world)
    {
        var lines = fileContent.split("\n"),
                size = lines.length - 1,
                obj = null,
                body = null,
                newBody = null,
                fix = null;

        for( var i = 0; i < size; ++i )
        {
            obj = JSON.parse(lines[i]);

            body = prepareBody(obj);
            fix = prepareFixture(obj);

            newBody = world.createBody(body);
            newBody.createFixture(fix);
        }
    }

    function prepareFixture(obj)
    {
        var fix = new FixtureDef;

        for(var x in obj.fixtureList )
        {
            switch(obj["shape"][x])
            {

            case shape_code_map["circle"]:  fix.setAsCircle(obj["data"][x][2]); break;

            case shape_code_map["edge"]: print("unsupported edge type"); break;

            case shape_code_map["polygon"]: fix.setAsPolygon(obj["data"][x]);   break;

            case shape_code_map["chain"]: print("unsupported chain type"); break;

            default : break;

            }
        }

        return fix;
    };

    function prepareBody(obj)
    {
        var body = new BodyDef;

        for ( var prop in obj )
        {
            if(body.hasOwnProperty(prop))
            {
                if( prop instanceof Array )
                    for( var x in obj[prop])
                        body[prop][x] = obj[prop][x];
                else
                    body[prop] = obj[prop];
            }
        }

        return body;
    };

    return {
        stringify : stringify,
        parse : parse
    };

})();
