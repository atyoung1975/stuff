var MongoClient = require('mongodb').MongoClient;
var url = "mongodb://10.231.248.251:27017/";

MongoClient.connect(url, function(err, db) {
	  if (err) throw err;
	  var dbo = db.db("mySensorData");
	  dbo.createCollection("telemerty", function(err, res) {
		      if (err) throw err;
		      console.log("Collection created!");
		      db.close();
		    });
});
