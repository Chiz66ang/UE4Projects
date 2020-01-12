var express=require('express');
var app=express();
var fs = require('fs'); //npm install fs --save
var qs =  require('querystring');
var expressSession = require('express-session');

app.use(expressSession({
    secret:'my key',
    resave: true,
    saveUninitialized:true
}));

app.get('/',function(req,res){
    res.writeHead(200,{'Content-Type':'text/html'});
    fs.createReadStream('index.html').pipe(res);
});

app.get('/login',function(req,res){
    res.writeHead(200,{'Content-Type':'text/html'});
    fs.createReadStream('login.html').pipe(res);
});

app.get('/main', function(req,res){
    if(!req.session.userid){
        res.redirect('/login');
        return;
    }
    res.writeHead(200, {'Content-Type': 'text/html'});
    fs.createReadStream('main.html').pipe(res);
})

app.post('/login',function(req,res){
    let param = '';
    req.on('data', function(data){
        //res.send('Data On');
        param += data;
        if(param.length > 1e6) req.connection.destroy();
    });
    req.on('end', function(){
        //res.send('Data End');
        let post = qs.parse(param);
        console.log('id=%s, pass=%s', post.id, post.pass);
        if(post.id=='Ward' && post.pass=='123456'){
            //검증된 사람이라면 그 id를 세션에 추가한다.
            req.session.userid = {id: post.id};
            res.redirect('/main');
        }
    });
});

var server=app.listen(3000,function(){
    console.log('Server is running on port 3000');
});