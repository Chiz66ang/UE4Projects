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

app.post('/login', function(req,res){
    let param = '';
    req.on('data', function(data){
        param += data;
        if(param.length > 1e6) req.connection.destroy();
    });

    req.on('end', function(){
        let post = qs.parse(param);
        console.log('ID = %s, Pass = %s' , post.ID, post.Pass);
        Login(post.ID, post.Pass, res);
        });
})

app.get('/register',function(req,res){
    res.writeHead(200,{'Content-Type':'text/html'});
    fs.createReadStream('register.html').pipe(res);
});

app.post('/emailrepcheck',function(req,res){
    let param = '';
    res.writeHead(200, {'Content-Type':'application/json'});
    req.on('data', function(data){
        param += data;
        if(param.length > 1e6) req.connection.destroy();
    });

    req.on('end', function(){
        let post = qs.parse(param);
        console.log('Entered Email = %s', post.email);
        EmailCheck(post.email, res);
        });
});

app.post('/idrepcheck', function(req,res){
    let param = '';
    res.writeHead(200, {'Content-Type':'application/json'});
    req.on('data', function(data){
        param += data;
        if(param.length > 1e6) req.connection.destroy();
    });

    req.on('end', function(){
        let post = qs.parse(param);
        console.log('Entered id = %s', post.id);
        IDCheck(post.id, res);
        });
})

app.post('/regnewuser', function(req,res){
    let param = '';
    req.on('data', function(data){
        param += data;
        if(param.length > 1e6) req.connection.destroy();
    });

    req.on('end', function(){
        let post = qs.parse(param);
        console.log('Email = %s, ID = %s, Pass = %s' , post.email, post.id, post.pass);
        NewMemberReg(post.id, post.email, post.pass, res);
        });
})

var server=app.listen(3000,function(){
    console.log('Server is running on port 3000');
});

function Login(id, pass, res){
    const oracledb = require('oracledb');
    oracledb.getConnection(
        {
           user		:'hr',
           password	:'hr',
           connectString:'localhost/XEPDB1'
        },

        function(err, connection){
            if(err){
                console.error(err.message);
                return;
            }
        
        connection.execute(

            'SELECT PLAYERID FROM UNREAL_PLAYERS WHERE PLAYERID=:dv AND PASS=:e',
            [id, pass],
            {
                maxRows:1
            },
        function(err, result){
            var jsonObj = {};
            if(err){
            console.error(err.message);
            connection.close();
            jsonObj.result = 'Search Failed';
            return;
           }
           else{
            console.log(result.rows);
            connection.close();
            if(result.rows.length>0) {
                console.log('Player Found')
                jsonObj.result = 'Login Success';
            }
            else {
                console.log('Unidentified Player')
                jsonObj.result = 'Login Fail';
                }
           }
           res.end(JSON.stringify(jsonObj));
        });
    });
}

//Oracle 데이터베이스 접속. 이메일 중복체크 (이미 회원인지)
function EmailCheck(email, res){
    const oracledb = require('oracledb');
    oracledb.getConnection(
        {
           user		:'hr',
           password	:'hr',
           connectString:'localhost/XEPDB1'
        },

        function(err, connection){
            if(err){
                console.error(err.message);
                return;
            }
        
        connection.execute(

            'SELECT EMAIL FROM UNREAL_PLAYERS WHERE EMAIL=:d',
            [email],
            {
                maxRows:1
            },
        function(err, result){
            var jsonObj = {};
            if(err){
            console.error(err.message);
            connection.close();
            jsonObj.result = 'Search Failed';
            return;
           }
           else{
            console.log(result.rows);
            connection.close();
            if(result.rows.length>0) {
                console.log('Duplicate Email Found')
                jsonObj.result = 'You are already registered';
            }
            else {
                console.log('New Player. Moving to Registeration')
                jsonObj.result = 'New User';
                }
           }
           res.end(JSON.stringify(jsonObj));
        });
    });
}

function IDCheck(id, res){
    const oracledb = require('oracledb');
    oracledb.getConnection(
        {
           user		:'hr',
           password	:'hr',
           connectString:'localhost/XEPDB1'
        },

        function(err, connection){
            if(err){
                console.error(err.message);
                return;
            }
        
        connection.execute(

            'SELECT PLAYERID FROM UNREAL_PLAYERS WHERE PLAYERID=:dv',
            [id],
            {
                maxRows:1
            },
        function(err, result){
            var jsonObj = {};
            if(err){
            console.error(err.message);
            connection.close();
            jsonObj.result = 'Search Failed';
            return;
           }
           else{
            console.log(result.rows);
            connection.close();
            if(result.rows.length>0) {
                console.log('Duplicate ID Found')
                jsonObj.result = 'Invalid ID';
            }
            else {
                console.log('Valid ID')
                jsonObj.result = 'Valid ID';
                }
           }
           res.end(JSON.stringify(jsonObj));
        });
    });
}

function NewMemberReg(id, email, pass, res){
    const oracledb = require('oracledb');
    oracledb.getConnection(
        {
           user		:'hr',
           password	:'hr',
           connectString:'localhost/XEPDB1'
        },

        function(err, connection){
            if(err){
                console.log('error');
                console.error(err.message);
                return;
            }
        
            connection.execute(
            
            'INSERT INTO UNREAL_PLAYERS (playerid, email, pass, regdate) VALUES(:id, :email, :pass, SYSDATE)',
            [id, email, pass],
           
            function(err, result){
            var jsonObj = {};
            if(err){
                console.log('error2');
                console.error(err.message);
                connection.close();
                jsonObj.result = 'Insert Failed';
                return;
            }
            else{
                if(result.rowsAffected >0){
                    
                    connection.commit();
                    console.log('Register Complete');
                    connection.close();
                }
                //connection.close();
                //jsonObj.result = 'Register Complete';
                //res.end(JSON.stringify(jsonObj));
            }
        });
    });
}