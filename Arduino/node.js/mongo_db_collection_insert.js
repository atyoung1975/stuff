var MongoClient = require('mongodb').MongoClient;
var url = "mongodb://10.231.248.251:27017/";

MongoClient.connect(url, function(err, db) {
	  if (err) throw err;
	  var dbo = db.db("mydb");
	  var myobj = { name: "shithouse", address: "Park Lane 38" };
	  dbo.collection("customers").insertOne(myobj, function(err, res) {
		      if (err) throw err;
		      console.log("1 document inserted");
		      db.close();
		    });
});
