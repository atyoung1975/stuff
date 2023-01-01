#!/bin/sh
rm /tmp/data
./Moist_Gather.exp
grep [1-9] /tmp/data >> /home/pi/Arduino/SensorData/results.csv
