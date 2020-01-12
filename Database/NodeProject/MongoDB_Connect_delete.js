const MongoClient = require('mongodb').MongoClient;
const assert = require('assert');

const removeDocument = function(db, callback) {
  // Get the documents collection
  const collection = db.collection('Players');
  // Delete document where a is 3
  collection.deleteOne({ 'name' : 'Smith' }, function(err, result) {
    assert.equal(err, null);
    assert.equal(1, result.result.n);
    console.log("Removed the document with the field name equal to Smith");
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

  removeDocument(db, function() {
    client.close();
  });
});

