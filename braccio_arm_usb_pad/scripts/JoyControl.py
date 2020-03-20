#!/usr/bin/env python

import rospy
import copy
from std_msgs.msg import Float64MultiArray
from sensor_msgs.msg import Joy


pub = rospy.Publisher('/braccio_arm/joint_angles', Float64MultiArray, queue_size=10)

info = [0.0,0.0,0.0,0.0,0.0,0.0]

def callback(joy):
        global info
        #print("axes = ", joy.axes)
        info = joy.axes
        #print ("info =", info)
        
        

rospy.init_node('JoyControl')


rospy.Subscriber("/joy", Joy, callback, queue_size=10)
rate = rospy.Rate(100)

msgQ = Float64MultiArray()
msgQ.data= [1.57,1.57,1.57,1.57,1.57,1.57]

#rospy.spin()

while not rospy.is_shutdown():
        global msgQ
        msgQ.data[0] += info[0] * 0.001
        msgQ.data[1] += info[1] * 0.001
        msgQ.data[2] += info[2] * 0.001
        msgQ.data[3] += info[3] * 0.001
        msgQ.data[4] += info[4] * 0.001
        msgQ.data[5] += info[5] * 0.01
	pub.publish(msgQ);
	rate.sleep();

