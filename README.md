# icra_2020_ws – Operator Workspace
Demo materials for ICRA 2020 paper. 

## Setup
***operator-ws*** branch contains packages necessary from the operator side

``` bash
git clone -b <platform-branch> https://github.com/temoto-telerobotics-demos/icra_2020_ws
git submodule update --init --recursive
cd icra_2020_ws
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

Launch TeMoto:
```
roslaunch operator_temoto_ws temoto.launch
```

Invoke the natural language processing pipeline (speech_to_text→text_to_umrf_parser) via TeMoto Action:
```
rosrun temoto_action_engine parser_node ./icra_2020_ws/src/operator_temoto_ws/operator_temoto_ws/config/default_umrfs umrf_list.txt Operator
```
The parser node does nothing more than just reading in a UMRF JSON file and publishing it as UMRF Graph message with "Operator" as a wake word.

<br></br>

Now "Operator" system should be actively parsing speech to UMRF Graph messages, targeted to "Jack".
