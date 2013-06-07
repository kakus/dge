var io = (function(){
    return {

        saveFile : function()
        {
            var fileContent;

            if(world !== undefined)
            {
                fileContent = json_converter.stringify( world );
                saveFile(fileContent);
            }
        },

        /**
          * @method loadFile
          * Open file with JSON content in new tab
          */
        loadFile : function()
        {
            var fileContent = openFile();

            if(fileContent !== undefined)
                json_converter.parse(fileContent, newWorld());
        }
    };

})();
