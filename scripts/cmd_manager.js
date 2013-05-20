var cmdManager = (function()
{
    var stack = [],
        index = 0;

    function Command(undoObj, undoFunc, undoParams, redoObj, redoFunc, redoParams)
    {
        this.undo = {
            obj : undoObj,
            func: undoFunc,
            params: undoParams
        };

        this.redo = {
            obj: redoObj,
            func: redoFunc,
            params: redoParams
        };

        return this;
    }

    function execute(command)
    {
        if(command !== undefined)
            command.func.apply( command.obj, command.params);
    }

    return {

        pushCmd: function(undoObj, undoFunc, undoParams, redoObj, redoFunc, redoParams)
        {
            stack.push(new Command(undoObj, undoFunc, undoParams, redoObj, redoFunc, redoParams));
            stack.splice(index + 1, stack.length - index - 2);
            index = stack.length - 1;
            print(stack);

        },

        undo: function()
        {
            var cmd;
            if(index >= 0){
            cmd = stack[index];
                  --index;
                execute(cmd.undo);
            }

        },

        redo: function()
        {
            var cmd;

            if(index < stack.length - 1)
            {
                cmd = stack[index+1];
                 ++index;
                execute(cmd.redo);

            }

        }
    }

})();
