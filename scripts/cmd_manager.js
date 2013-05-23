var cmdManager = (function()
{
    var stack = [],
            index = 0;

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
            if(index >= 0){
                stack[index].undo();
                --index;
            }

        },

        redo: function()
        {
            if(index < stack.length - 1)
            {
                stack[index+1].exec();
                ++index;
                cmd.exec();
            }
        }
    }

})();
