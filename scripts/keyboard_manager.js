function KeyboardManager()
{
    var key_function_map = {};

    function removeWhitespaces(string)
    {
        return string.replace(/\s/g, "");
    }

    return{

        keyPress: function(code, modifier)
        {
            var modifierString = modifier_map[modifier];
            var keyString = key_map[code];

            if(keyString !== undefined)
            {
                if(modifierString !== undefined)
                    key_function_map[modifierString+"+"+keyString]();
                else
                    key_function_map[keyString]();
            }
        },

        register: function(key, func){
            var newKey = removeWhitespaces(key);
            key_function_map[newKey] = func;
        }
    };
};


