const MongoClient = require('mongodb').MongoClient;
const assert = require('assert');

const updateDocument = function(db, callback) {
  // Get the documents collection
  const collection = db.collection('Players');
  // Update document where a is 2, set b equal to 1
  collection.updateOne({ 'name' : 'Abigale' }
    , { $set: { 'email' : 'abigale@gmail.com' } }, function(err, result) {
    assert.equal(err, null);
    assert.equal(1, result.result.n);
    console.log("Updated the document with the field name equal to Abigale");
    callback(result);
  });
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

  updateDocument(db, function() {
    client.close();
  });
});

