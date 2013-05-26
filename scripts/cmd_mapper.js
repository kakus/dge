/**
 * Return CmdManager for current scene ( every scene has its own CmdManager )
 * @method getCmdManager
 */

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
