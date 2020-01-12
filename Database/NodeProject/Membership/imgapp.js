var express=require('express');
var app=express();
var fs = require('fs');

app.get('/', function(req, res){
    res.writeHead(200,{'Content-Type':'text/html'});
    fs.createReadStream('image.html').pipe(res);
});

app.get('/img', function(req, res){
    let img = req.query.pic;
    if(!img) return;
    fs.readFile(img, function(error, data){
        res.writeHead(200, {'Content-Type':'text/html'});
        res.end(data);
    });
});

var server = app.listen(3000,function(){
    console.log('Server is running on port 3000');
});