#!/usr/bin/env python
# Software License Agreement (BSD License)
#
# Copyright (c) 2008, Willow Garage, Inc.
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
#
#  * Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
#  * Redistributions in binary form must reproduce the above
#    copyright notice, this list of conditions and the following
#    disclaimer in the documentation and/or other materials provided
#    with the distribution.
#  * Neither the name of Willow Garage, Inc. nor the names of its
#    contributors may be used to endorse or promote products derived
#    from this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
# "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
# LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
# FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
# COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
# INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
# BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
# LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
# CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
# LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
# ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
# POSSIBILITY OF SUCH DAMAGE.
#
# Revision $Id$

## Listener that listens to std_msgs/Strings published 
## to the 'D_M_direction' topic
## to the 'D_M_rotation' topic

from breezycreate2 import Robot
from breezycreate2 import _Create2
import time
import rospy
from std_msgs.msg import String

direction_data = ""
rotation_data = ""

def callback_direction(data):	
	global direction_data
	direction_data = data.data
	rospy.loginfo(rospy.get_caller_id() + 'Move %s', direction_data)
	
def callback_rotation(data):
	global rotation_data
	rotation_data = data.data
   	rospy.loginfo(rospy.get_caller_id() + 'Rotation %s', rotation_data)

def listener():
	# In ROS, nodes are uniquely named. If two nodes with the same
	# name are launched, the previous one is kicked off. The
	# anonymous=True flag means that rospy will choose a unique
	# name for our 'listener' node so that multiple listeners can
	# run simultaneously.
	rospy.init_node('listener', anonymous=True)

	rospy.Subscriber('D_M_direction', String, callback_direction)
	rospy.Subscriber('D_M_rotation', String, callback_rotation)

    # spin() simply keeps python from exiting until this node is stopped

if __name__ == '__main__':

	listener()

	bot = Robot()					#Open Serial Connection
	robot = _Create2()
	
	while(1):
	
		# Direction	    
		if direction_data == "forward":
			print "Moving Forward"			
#			bot.setForwardSpeed(50)
			robot.drive(50,0)			#Move forward

			if rotation_data == "right":
				print "Moving Right"
				robot.drive(50,-100)	#Moving forward + right
				time.sleep(1)
				rotation_data = ""

			elif rotation_data == "left":
				print "Moving Left"	
				robot.drive(50,100)	#Move forward + left
				time.sleep(1)
				rotation_data = ""
	 
		elif direction_data == "backward":
			print "Moving Backward"
			robot.drive(-50,0)		#Move backward

			if rotation_data == "right":
				print "Moving Right"
				robot.drive(-50,-100)	#Move backward + right
				time.sleep(1)
				rotation_data = ""

			elif rotation_data == "left":
				print "Moving Left"
				robot.drive(-50,100)	#Move backward +left
				time.sleep(1)
				rotation_data = ""

		elif direction_data == "stop":
			print "Moving Stop"
			robot.drive(0,0)		#Stop movement
			direction_data = ""
			
		time.sleep(1)
	
 	bot.close()
	robot.destroy()					#Close serial connection
	
