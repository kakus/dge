var save = function()
{
    saveFile(json_converter.stringify(world));
}

var load = function()
{
    json_converter.parse(openFile(), world);
}
