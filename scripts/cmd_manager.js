function CmdManager()
{
    var stack = [],
            index = 0;

    var hasUndo = function(){
        return index >= 0;
    }

    var hasRedo = function(){
        return index < stack.length - 1;
    }

    return {

        pushCmd: function(command)
        {
            stack.push(command);
            stack.splice(index + 1, stack.length - index - 2);
            index = stack.length - 1;
            command.exec();

        },

        undo: function()
        {
            if(hasUndo()){
                stack[index].undo();
                --index;
            }

        },

        redo: function()
        {
            if(hasRedo())
            {
                stack[index+1].exec();
                ++index;
                cmd.exec();
            }
        }
    }

};
