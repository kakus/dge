/**
 * CmdManaager managing drawing/resizing/moving commands in application.
 * Every command has to defined undo and exec functions.
 * Every pushed command is immediately executing by call "exec" function.
 * To see how properly add and define commands see example_tool.js.
 * @class CmdManager
 * @constructor
 */
function CmdManager()
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
            if( index >= 0 )
            {
                stack[index].undo();
                --index;
            }

        },

        redo: function()
        {
            if( index < stack.length-1 )
            {
                ++index;
                stack[index].exec();
                cmd.exec();
            }
        }
    }
};
