#!/usr/bin/expect -f
exp_internal 1
# device
set modem /dev/ttyACM0
set systemTime [clock seconds]
set outcome "[clock format $systemTime -format %m-%d-%Y] "
append outcome "[clock format $systemTime -format %H:%M:%S],"
puts $outcome
# keep it open
exec sh -c "sleep 3 < $modem" &

# serial port parameters
exec stty -F $modem 9600 raw -clocal -echo -istrip -hup

# connect
send_user "connecting to $modem, exit with ~.\n"
spawn -open [open $modem w+]
set output [open "data" "w"]
sleep 2
send "1\r"
expect "#"
append outcome $expect_out(buffer)
puts $output $outcome
close $output 
