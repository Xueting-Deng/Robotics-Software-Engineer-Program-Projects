#!/bin/sh
xterm -e "roslaunch my_robot world.launch" &
sleep 5
xterm -e "roslaunch my_robot amcl.launch" &
sleep 5
xterm -e "rosrun pick_objects pick_objects"
