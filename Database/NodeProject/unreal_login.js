var express = require('express');
var app = express();
var fs = require('fs');
var qs = require('querystring');
//var user = require('/NodeProject/oracle_conn');u7

app.get('/app/:id/:pass', function(req, res){
    var id = ''
    id = req.params.id;
    var pass = ''
    pass = req.params.pass;
    login (id, pass, res);
    //var jsonObj = {};
   // jsonObj.result = 'Login OK';
    //res.end(JSON.stringify(jsonObj));
})

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
                jsonObj.result = "Login Succeeded";
            }
            else {
                console.log("검색 실패")
                jsonObj.result = "Login Failed";
            }
           }
           res.end(JSON.stringify(jsonObj));
        }
        );
        }
        );
}
