#!/bin/sh
xterm -e "roslaunch my_robot world.launch" &
sleep 10
xterm -e "roslaunch my_robot gmapping.launch" &
sleep 10
xterm -e "roslaunch my_robot teleop.launch"
