cmake_minimum_required(VERSION 2.8.3)
project(text_to_umrf)

## Compile as C++11, supported in ROS Kinetic and newer
add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  temoto_action_engine
)


catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES text_to_umrf
#  CATKIN_DEPENDS roscpp rospy std_msgs temoto_action_engine
#  DEPENDS system_lib
)

include_directories(
# include
  ${catkin_INCLUDE_DIRS}
)

# Parser node
add_executable(text_to_umrf
  src/text_to_umrf.cpp
)

add_dependencies(text_to_umrf
  ${catkin_EXPORTED_TARGETS}
  ${${PROJECT_NAME}_EXPORTED_TARGETS}
)
target_link_libraries(text_to_umrf
  ${catkin_LIBRARIES}
)  

