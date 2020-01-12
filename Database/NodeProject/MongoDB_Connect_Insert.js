const MongoClient = require('mongodb').MongoClient;
const assert = require('assert');

const insertDocuments = function(db, callback) {
  //Get the documents collection
  const collection = db.collection('Players');
  //insert some documents
  collection.insertMany([
    {'name':'Clint', 'team':'TeamB','email':'cwood@gmail.com','score':52},
    {'name':'Khan', 'team':'TeamA','email':'khan@gmail.com','score':32}
  ], function(err, result){
    assert.equal(err, null);
    assert.equal(2, result.result.n);
    assert.equal(2, result.ops.length);
    console.log("Inserted 2 documents into the collection");
    callback(result);
  })
}

// Connection URL
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

