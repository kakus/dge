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
