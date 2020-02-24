# iros_2020_ws – Jackal Workspace
Demo materials for iros 2020 paper.

## Setup

``` bash
git clone -b jackal-ws https://github.com/temoto-telerobotics-demos/iros_2020_ws
git submodule update --init --recursive
cd iros_2020_ws
```

If you want the latest versions of the submodules, then (after that the state of this workspace may not be the same as it was for the demo)
``` bash
git submodule foreach git pull origin master
```

Initialize the catkin workspace
``` bash
catkin build
```

## Usage
Jackal related hardware divers are expected to be running when the system starts up.

Launch TeMoto:
```
roslaunch jackal_temoto_ws temoto.launch
```

Invoke the human tracking pipeline (camera→gesture_recognizer→gesture_to_umrf_parser) via TeMoto Action:
```
rosrun temoto_action_engine parser_node <iros_2020_ws>/src/jackal_temoto_ws/jackal_temoto_ws/config/default_umrfs/ umrf_list_gesture_parser.txt Jack
```
The parser node does nothing more than just read in a UMRF JSON file and publishes it as UMRF Graph message with "Jack" as a wake word.

<br></br>

Now "Jack" should be listening to UMRF Graph messages and interpret body gestures as movement commands.
