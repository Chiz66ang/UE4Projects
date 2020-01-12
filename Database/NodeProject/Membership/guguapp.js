var express=require('express');
var app=express();
var fs = require('fs'); //npm install fs --save
var qs =  require('querystring');
var util = require('util');

var server=app.listen(3000,function(){
    console.log('Server listening on port 3000');
})

app.get('/', function(req,res){
    res.writeHead(200,{'Content-Type':'text/html'});
    fs.createReadStream('gugu.html').pipe(res);
});

app.get('/result', function(req,res){
    let num = req.query.num;
    res.writeHead(200, {'Content-Type':'application/json'});
    let arr = [];
    for(let i =1; i<=9; i++){
        //9줄의 내용을 배열에 저장한다.
        let line = util.format('%d * %d = %d', num,i,num*i);
        arr.push(line);
        //res.write(num + '*' + i +'=' + (num*i) + '<br>');
    }
    let obj = {};
    obj.gugu = arr;
    res.end(JSON.stringify(obj));
});
