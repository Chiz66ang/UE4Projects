var express = require('express');
var app = express();
var fs = require('fs');
var qs = require('querystring');

//리슨 서버 오픈
app.listen(3000, function(){
    console.log('Example app listening on port 3000!');
});


//중복 계정 확인 처리 후 
app.post('/register_repcheck', function(request, response){
    var body = '';

    request.on('data', function(data){
        body += data;
        if(body.length > 1e6)
        request.connection.destroy();
    });

    request.on('end', function(){
        var post = qs.parse(body);
        console.log('register information: Email =%s', post.Email);
        registerEmailCheck(post.Email, response);
    })
});

//회원가입 처리
app.post('/register', function(request, response){
    var body = '';

    request.on('data', function(data){
        body += data;
        if(body.length > 1e6)
        request.connection.destroy();
    });

    request.on('end', function(){
        var post = qs.parse(body);
        console.log('register information: ID =%s, Pass =%s, regdate=%s', post.ID, post.Pass, post.Date);
        register(post.ID, post.Pass, post.Date, post.Email, response);
    })
});

//로그인 처리
app.post('/login', function(request, response){
    var body = '';

    request.on('data', function(data){
        body += data;
        if (body.length >1e6)
         // 1*10의 6승 (클라이언트에서 온 자료가 1M가 넘으면 받지 말아라)
        request.connection.destroy();
    });

    request.on('end', function() {
        var post = qs.parse(body);
        console.log('User ID=%s, User Pass=%s', post.ID, post.Pass);
        login(post.ID, post.Pass, response);
    });
});

function registerEmailCheck (Email, res) {
    //오라클 hr 계정 연결
    const oracledb = require('oracledb');
    oracledb.getConnection(
        {
           user		:'hr',
           password	:'hr',
           connectString:'192.168.0.4/XEPDB1'
        },

        function(err, connection){
        if(err){
           console.error(err.message);
           return;
        }
        
        connection.execute(

            'SELECT email FROM UNREAL_PLAYERS WHERE email =:email'
            [Email],
            {
                maxRows:1
            },
        function(err, result)
        {
            var jsonObj = {};
           if(err){
            console.error(err.message);
            connection.close();
            jsonObj.result = 'Search Failed';
            return;
           }

           else{
            console.log(result.rows); //2차원 배열이므로 원소는 result.rows
            connection.close();
            if(result.rows.length>0) {
                console.log('Duplicate Email Found')
                jsonObj.result = 'You are already registered';
            }
            else {
                console.log('New Player. Moving to Registeration')
                jsonObj.result = 'Success';
                register()
            }
           }
           res.end(JSON.stringify(jsonObj));
        });
    });
}

function register (ID, Pass, Date, Email, res) {
    //오라클 hr 계정 연결
    const oracledb = require('oracledb');
    oracledb.getConnection(
        {
           user		:'hr',
           password	:'hr',
           connectString:'192.168.0.4/XEPDB1'
        },

        function(err, connection){
        if(err){
           console.error(err.message);
           return;
        }
        
        connection.execute(

            'SELECT id FROM UNREAL_PLAYERS WHERE id =:id'
            [ID],
            {
                maxRows:1
            },
        function(err, result)
        {
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
                jsonObj.result = 'This ID is already in use!';
            }
            else {
                console.log('Register Player %s', ID)
                'INSERT INTO UNREAL_PLAYERS (playerid, pass, date'

                jsonObj.result = 'Success';
            }
           }
           res.end(JSON.stringify(jsonObj));
        });
    });
}

function login (empID, empName, res) {
    const oracledb = require('oracledb');
    oracledb.getConnection(
        {
           user		:"hr",
           password	:"hr",
           connectString:"192.168.0.4/XEPDB1"
        },
        function(err, connection){
        if(err){
           console.error(err.message);
           return;
        }
        
        connection.execute(
           'SELECT * FROM PLAYERS WHERE Pid=:bv AND Pass=:dv',
           [empID,empName],
           {
           maxRows:1
           },
        
        function(err, result)
        {
            var jsonObj = {};
           if(err){
            console.error(err.message);
            connection.close();
            jsonObj.result = "Login Failed!";
            return;
           }
           else{
            console.log(result.rows); //2차원 배열이므로 원소는 result.rows
            connection.close();
            if(result.rows.length>0) {
                console.log("검색 성공")
                jsonObj.result = "Login Succeeded!";
            }
            else {
                console.log("검색 실패")
                jsonObj.result = "Login Failed!";
            }
           }
           res.end(JSON.stringify(jsonObj));
        }
        );
        }
        );
}
