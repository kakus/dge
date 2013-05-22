(function(){

    function Class(){
        this.sth = 1;
        this.sth2 = 'a';
        var sth3 = 2;
        var sth4 = 'b';
        this.sth5 = function(){
            return 1;
        }
        var sth6 = function(){
            return 2;
        }
        this.sth7 = [5,6,7];
    }

    var object = new Class;

    var text = JSON.stringify(object);
    print(text);

    var obj = JSON.parse(text);
    for(var x in obj)
        print(obj[x]);

    print(typeof world == object);

    //console.write(text);
})();
