#!/usr/bin/env python

import rospy
from std_msgs.msg import String
from geometry_msgs.msg import Twist
from drive_action_host.msg import *
from std_srvs.srv import Empty

def lin_drive_cb(req):
    global lin_vel
    print("tere lin")
    #rospy.loginfo('Linear Drive Callback')
    lin_vel=((req.move_fwd) - (req.move_bkwd))
    #rospy.loginfo(lin_vel) 

def ang_drive_cb(req):
    global ang_vel
    print("tere ang")
    #rospy.loginfo('Angular Drive Callback')
    ang_vel=((req.rotate_ccw) - (req.rotate_cw))
    #rospy.loginfo(ang_vel) 
		
def stop_drive_cb(req):
    global ang_vel, lin_vel
    #rospy.loginfo('Stop Drive Callback: ')
    lin_vel=0
    ang_vel=0
    #rospy.loginfo(ang_vel)
    #rospy.loginfo(lin_vel) 

def drive():
    global ang_vel, lin_vel
    print("tere tere")

    # Configure node and publisher
    rospy.init_node('drive_host', anonymous=False)
    vel_pub = rospy.Publisher('/cmd_vel', Twist, queue_size=10)
    #pub = rospy.Publisher('chatter', String, queue_size=10)
    rate = rospy.Rate(10) # 10hz

    # Get parameters
    k_lin = rospy.get_param('gain/linear', 0.1)
    k_ang = rospy.get_param('gain/angular', 0.1)

    # initialize velocity message
    vel_msg=Twist()
    vel_msg.linear.x = 0
    vel_msg.linear.y = 0
    vel_msg.linear.z = 0
    vel_msg.angular.x = 0
    vel_msg.angular.y = 0
    vel_msg.angular.z = 0


    # Start services
    stop_sub = rospy.Service('stop_drive', Empty, stop_drive_cb)
    lin_sub = rospy.Subscriber('lin_drive', LinDrive, lin_drive_cb)
    ang_sub = rospy.Subscriber('ang_drive', AngDrive , ang_drive_cb)

    while not rospy.is_shutdown():
        vel_msg.linear.x = k_lin*lin_vel
        vel_msg.angular.z = k_ang*ang_vel
        #hello_str = "hello world %s" % rospy.get_time()
        #rospy.loginfo(hello_str)
        vel_pub.publish(vel_msg)
        rate.sleep()

if __name__ == '__main__':
    try:
        global ang_vel, lin_vel
        lin_vel=0
        ang_vel=0        
        drive()
    except rospy.ROSInterruptException:
        pass
