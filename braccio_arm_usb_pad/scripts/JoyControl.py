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
msgQ.data= [1.57,1.57,1.57,1.57,1.57,0.01]

#rospy.spin()

while not rospy.is_shutdown():
        global msgQ
        msgQ.data[0] += info[0] * 0.005
        if msgQ.data[0] < 0:
            msgQ.data[0] = 0
        if msgQ.data[0] > 3.14:
            msgQ.data[0] = 3.14       
        
        msgQ.data[1] += info[1] * 0.005
        if msgQ.data[1] < 0.2618:
            msgQ.data[1] = 0.2618
        if msgQ.data[1] > 2.8798:
            msgQ.data[1] = 2.8798
            
        msgQ.data[2] += info[2] * 0.005
        if msgQ.data[2] < 0:
            msgQ.data[2] = 0
        if msgQ.data[2] > 3.1416:
            msgQ.data[2] = 3.1416

        msgQ.data[3] += info[3] * 0.005
        if msgQ.data[3] < 0:
            msgQ.data[3] = 0
        if msgQ.data[3] > 3.1416:
            msgQ.data[3] = 3.1416

        msgQ.data[4] += info[4] * 0.005
        if msgQ.data[4] < 0:
            msgQ.data[4] = 0
        if msgQ.data[4] > 3.1416:
            msgQ.data[4] = 3.1416

        msgQ.data[5] += info[5] * 0.001
        if msgQ.data[5] < 0.02:
            msgQ.data[5] = 0.02
        if msgQ.data[5] > 0.07:
            msgQ.data[5] = 0.07

	pub.publish(msgQ);
	rate.sleep();

