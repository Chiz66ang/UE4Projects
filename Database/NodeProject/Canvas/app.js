var express=require('express');
var app= express();
var fs = require('fs');
var qs = require('querystring');

app.get('/', function(req, res){
    res.writeHead(200,{"Content-Type" : "text/html"});
    fs.createReadStream("canvas_drawing.html").pipe(res);
});

var server= app.listen(3000,function(){
    console.log('Server listening on port 3000');
})