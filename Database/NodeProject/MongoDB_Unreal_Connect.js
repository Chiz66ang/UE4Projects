var express = require('express');
var app = express();
var fs = require('fs');
var qs = require('querystring');
const MongoClient = require('mongodb').MongoClient;
const assert = require('assert');

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
        console.log("User ID=%s, Team=%s, Date=%s, Score=%s", post.ID, post.team, post.Date, post.score);
        login(post.ID, post.team, post.Date, post.score, response);

    });
});

app.listen(3000, function(){
    console.log('Example app listening on port 3000!');
});

function login (ID, Team, Date, Score, res) {
const url = 'mongodb://localhost:27017';
 
// Database Name
const dbName = 'MyDB';
 
// Use connect method to connect to the server
MongoClient.connect(url, function(err, client) {
  assert.equal(null, err);
  console.log("Connected successfully to server");
 
  const db = client.db(dbName);

  insertDocuments(db, function(){
    client.close();
  })
});

const insertDocuments = function(db, callback) {
    //Get the documents collection
    const collection = db.collection('Players');
    var jsonObj = {};
    //insert some documents
    collection.insertMany([
      {'ID':ID, 'team':Team,'Date':Date,'score':Score}
    ], function(err, result){
      assert.equal(err, null);
      assert.equal(1, result.result.n);
      assert.equal(1, result.ops.length);
      jsonObj.result = "Insert Succeeded!";
      res.end(JSON.stringify(jsonObj));
      console.log("Inserted 1 documents into the collection");
      callback(result);
    })
    
  }
}
