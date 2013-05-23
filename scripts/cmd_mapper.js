(function(global)
{
    var cmd_map = {};

    global.getCmdManager= function()
    {
        if( cmd_map[world.id] === undefined)
            cmd_map[world.id] = new CmdManager;

        return cmd_map[world.id];
    }

})(this);
