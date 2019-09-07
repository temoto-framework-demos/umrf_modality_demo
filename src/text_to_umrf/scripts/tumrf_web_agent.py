#!/usr/bin/env python
import rospy
import json
import requests
from std_msgs.msg import String
from temoto_action_engine.msg import UmrfJsonGraph
#TOD import custom temotoumrf ros message type

tumrf_pub = rospy.Publisher('named_umrf_graph_topic', UmrfJsonGraph, queue_size=10)

def callback(data):
    nl_chatter = data.data
    r = requests.post('http://ec2-3-94-111-251.compute-1.amazonaws.com', data=nl_chatter)
    print(r.status_code, r.reason)
    json_tumrf_str = r.text #.encode("utf-8")
    json_tumrf = json.loads(json_tumrf_str)
    json_tumrf['name'] = 'Nameless'
    json_tumrf['suffix'] = '0'
    
    wake_word = json_tumrf.get('wakeword').encode('ascii', 'ignore')
    del json_tumrf['wakeword']

    graph_msg = UmrfJsonGraph()
    graph_msg.graph_name = 'Web Agent Graph'
    graph_msg.targets.append(wake_word)
    graph_msg.umrf_json_strings.append(json.dumps(json_tumrf))
    tumrf_pub.publish(graph_msg)

def listener():
    rospy.init_node('tumrf_web_handler')
    rospy.Subscriber("chatter_data_topic", String, callback)
    rospy.spin()

if __name__ == '__main__':
    listener()

