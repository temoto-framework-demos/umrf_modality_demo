# jackal_temoto_ws
TeMoto workspace for Clearpath Jackal robot. Contains ICRA 2020 demo code.

## Setup
1. First, install TeMoto: https://temoto-telerobotics.github.io/tutorials/installing_temoto.html
2. *git clone https://github.com/temoto-telerobotics/jackal_temoto_ws*
3. catkin build
4. source your workspace


## Usage
``` bash
roslaunch jackal_temoto_ws temoto.launch
```

**temoto.launch** contains the following parameters:
* ***temoto_namespace*** - Namespace for all ros topics and nodes launched from this file. Also, it's the default wake word (currently "**Jack**") 
* ***additional_wake_words*** - Any other wake words that the action_engine_node should respond to. Default is "everybody"
* ***action_packages_path*** - Path to a .yaml file which shows where action packages can be found
* ***default_umrf_path*** - Path to a umrf.json file which should be run automatically when the action engine is loaded up 

The action engine is expecting instructions on a global [umrf graph msg](https://github.com/temoto-telerobotics/temoto_action_engine/blob/master/msg/UmrfJsonGraph.msg) topic.

## Developer tools
You can use *parser_node* from *temoto_action_engine* package to invoke [umrf graph](https://github.com/temoto-telerobotics/temoto_action_engine/blob/master/msg/UmrfJsonGraph.msg) messages.
``` bash
rosrun temoto_action_engine parser_node <PATH_TO_UMRF_FOLDER> <UMRF_LIST_FILE> <TARGET_NAME>
```
For example:
``` bash
rosrun temoto_action_engine parser_node ~/<CATKIN_WS>/src/jackal_temoto_ws/jackal_temoto_ws/config/default_umrfs umrf_list.txt Jack
```

The "umrf list" allows to execute multiple umrfs in parallel and organize them as a graph.
