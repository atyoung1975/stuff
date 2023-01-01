/*
This program reads and parses all lines from csv files countries2.csv into an array (countriesArray) of arrays; each nested array represents a country.
The initial file read is synchronous. The country records are kept in memory.
*/
 
var fs = require('fs');
var parse = require('csv-parse');
var MongoClient = require('mongodb').MongoClient;
var url = "mongodb://10.231.248.251:27017/";

 
var inputFile='/home/pi/Arduino/SensorData/results.csv.1';
console.log("Processing Data File");

var parser = parse({delimiter: ','}, function (err, data) {
    // when all countries are available,then process them
    // note: array element at index 0 contains the row of headers that we should skip

	MongoClient.connect(url, function(err, db) {
		          if (err) throw err;
	        	  var dbo = db.db("mydb");
    			  data.forEach(function(line) {
      			  var country = { "Time" : line[0]
                    		, "Tent" : line[1].substring(0,2)
                    		, "Sensor" : line[1].substring(2)
                    		, "Data" : line[2]
                    		};
			  dbo.collection("customers").insertOne(country, function(err, res) {
			                      if (err) throw err;
			                      console.log("1 document inserted");
			                    });
     console.log(JSON.stringify(country));

    			});    

			                      db.close();
});
}); 
// read the inputFile, feed the contents to the parser
fs.createReadStream(inputFile).pipe(parser);
