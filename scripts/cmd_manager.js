var CMD_MANAGER = (function(){
    function execute (command){
        if(command !== undefined){
            command.func.apply ( command.obj, command.param);
        }
    }

    function addCommand(func, object, params){
        command = {
            func: func,
            obj: object,
            param: params
        }
    }

})();
