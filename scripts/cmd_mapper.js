(function(global){

    var map = [];

    global.getCmdManager= function()
    {
        for(var x in map){
            if( map[x].id == world.id)
                return map[x].cmdManager;
        }

        var newObject = {
            id: world.id,
            cmdManager: new CmdManager   };

        map.push(newObject);

        return newObject.cmdManager;

    }

})(this);
