var express = require('express');
var app = express();
var fs = require('fs');
var qs = require('querystring');
//var user = require('/NodeProject/oracle_conn');


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
        console.log("/User ID=%s, User Pass=%s", post.userID, post.userPass);
        login(post.userID, post.userPass, response);
        //response.writeHead(200, {"Content-Type":"application/json"});
        //response.end(JSON.stringify(post));
    });
});


app.get('/form', function(request, response){
    response.writeHead(200, {"Content-Type": "text/html"});
    fs.createReadStream("./login_form.html").pipe(response);
});

app.listen(3000, function(){
    console.log('Example app listening on port 3000!');
});

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
        });
        });
}
