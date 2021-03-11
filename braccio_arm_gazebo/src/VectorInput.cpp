//      test_button.cpp
//      Copyright (C) 2012 lengagne (lengagne@gmail.com)
//
//      This program is free software: you can redistribute it and/or modify
//      it under the terms of the GNU General Public License as published by
//      the Free Software Foundation, either version 3 of the License, or
//      (at your option) any later version.
//
//      This program is distributed in the hope that it will be useful,
//      but WITHOUT ANY WARRANTY; without even the implied warranty of
//      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//      GNU General Public License for more details.
//
//      You should have received a copy of the GNU General Public License
//      along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
//	from 2020:  Université Clermont Auvergne : Institut Pascal / axis : ISPR / theme MACCS

#include <ros/ros.h>
#include "std_msgs/Float64.h"
#include "std_msgs/Float64MultiArray.h"

std_msgs::Float64 msg_base, msg_elbow, msg_gripper, msg_shoulder, msg_wrist_pitch, msg_wrist_roll, msg_camera_rotate, msg_camera_depth, msg_camera_height, msg_camera_tilt;

void callback(const std_msgs::Float64MultiArray& msg)
{
    msg_base.data = msg.data[0];
    msg_shoulder.data = msg.data[1];
    msg_elbow.data = msg.data[2];
    msg_wrist_pitch.data = msg.data[3];
    msg_wrist_roll.data = msg.data[4];
    msg_gripper.data = msg.data[5];
}

void callback_camera(const std_msgs::Float64MultiArray& msg)
{
    msg_camera_rotate.data = msg.data[0];
    msg_camera_depth.data = msg.data[1];
    msg_camera_height.data = msg.data[2];
    msg_camera_tilt.data = msg.data[3];
}


int main(int argc, char *argv[])
{
    msg_base.data = 0; 
    msg_elbow.data = 0; 
    msg_gripper.data = 0.01; 
    msg_shoulder.data = 1.57; 
    msg_wrist_pitch.data = 0; 
    msg_wrist_roll.data = 0; 
    
    msg_camera_rotate.data = 0.0;
    msg_camera_depth.data = 0.6;
    msg_camera_height.data = 0.6;
    msg_camera_tilt.data = 0.5;
    
    ros::init(argc, argv, "braccio_arm_vector_input");

    ros::NodeHandle nh;

    ros::Publisher pub_base = nh.advertise<std_msgs::Float64>("/braccio_arm/base_joint_position_controller/command", 1000);
    ros::Publisher pub_elbow = nh.advertise<std_msgs::Float64>("/braccio_arm/elbow_joint_position_controller/command", 1000);
    ros::Publisher pub_gripper = nh.advertise<std_msgs::Float64>("/braccio_arm/gripper_joint_position_controller/command", 1000);
    ros::Publisher pub_sub_gripper = nh.advertise<std_msgs::Float64>("/braccio_arm/sub_gripper_joint_position_controller/command", 1000);
    ros::Publisher pub_shoulder = nh.advertise<std_msgs::Float64>("/braccio_arm/shoulder_joint_position_controller/command", 1000);
    ros::Publisher pub_wrist_pitch = nh.advertise<std_msgs::Float64>("/braccio_arm/wrist_pitch_joint_position_controller/command", 1000);
    ros::Publisher pub_wrist_roll = nh.advertise<std_msgs::Float64>("/braccio_arm/wrist_roll_joint_position_controller/command", 1000);
    
    ros::Publisher pub_camera_rotate = nh.advertise<std_msgs::Float64>("/braccio_arm/camera_rotate_controller/command", 1000);
    ros::Publisher pub_camera_height = nh.advertise<std_msgs::Float64>("/braccio_arm/camera_height_controller/command", 1000);
    ros::Publisher pub_camera_depth = nh.advertise<std_msgs::Float64>("/braccio_arm/camera_depth_controller/command", 1000);
    ros::Publisher pub_camera_tilt = nh.advertise<std_msgs::Float64>("/braccio_arm/camera_tilt_controller/command", 1000);
    
    ros::Subscriber sub = nh.subscribe("/braccio_arm/joint_angles", 10, callback);
    
    ros::Subscriber sub_camera = nh.subscribe("/braccio_arm/camera_joint_angles", 10, callback_camera);
    
    ros::Rate rate(100.0);
    while (nh.ok())
    {   
        pub_base.publish(msg_base);
        pub_elbow.publish(msg_elbow);
        pub_gripper.publish(msg_gripper);
        pub_sub_gripper.publish(msg_gripper);
        pub_shoulder.publish(msg_shoulder);
        pub_wrist_pitch.publish(msg_wrist_pitch);
        pub_wrist_roll.publish(msg_wrist_roll);
        
        pub_camera_rotate.publish(msg_camera_rotate);
        pub_camera_height.publish(msg_camera_height);
        pub_camera_depth.publish(msg_camera_depth);
        pub_camera_tilt.publish(msg_camera_tilt);
        
        ros::spinOnce();
        rate.sleep();
    }    
    
    return 0;
}
