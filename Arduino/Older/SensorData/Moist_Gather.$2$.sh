#!/bin/sh
rm /tmp/data
/home/pi/Arduino/SensorData/Moist_Gather.exp
grep [1-9] /tmp/data >> /home/pi/Arduino/SensorData/results.csv
