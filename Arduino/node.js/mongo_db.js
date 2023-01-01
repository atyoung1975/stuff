var MongoClient = require('mongodb').MongoClient;
var url = "mongodb://10.231.248.251:27017/mySensorData";

MongoClient.connect(url, function(err, db) {
	  if (err) throw err;
	  console.log("Database created!");
	  db.close();
});
