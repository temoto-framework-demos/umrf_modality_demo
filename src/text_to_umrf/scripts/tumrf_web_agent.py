#!/usr/bin/env python
import rospy
import json
import requests
from std_msgs.msg import String
#TOD import custom temotoumrf ros message type

def callback(data):
    nl_chatter = data.data
    r = requests.post('http://ec2-3-94-111-251.compute-1.amazonaws.com', data=nl_chatter)
    print(r.status_code, r.reason)
    json_tumrf_str = r.text #.encode("utf-8")
    json_tumrf = json.loads(json_tumrf_str)
    
    wake_word = json_tumrf.get('wakeword')
    del json_tumrf['wakeword']


def listener():
    rospy.init_node('listener')
    rospy.Subscriber("chatter", String, callback)
    rospy.spin()

if __name__ == '__main__':
    listener()

