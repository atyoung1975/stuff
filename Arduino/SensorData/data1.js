const fs = require('fs'); 
const csv = require('csv-parse');

fs.createReadStream("/home/pi/Arduino/SensorData/results.csv")
.pipe(csv())
.on('data', function(data){
	    try {
		            console.log("Name is: "+data.time);
		            console.log("Age is: "+data.sensor);

		            //perform the operation
		        }
		           catch(err) {
		                   //error handler
		                        }
		                        })
		                        .on('end',function(){
		                            //some final operation
		     });  
