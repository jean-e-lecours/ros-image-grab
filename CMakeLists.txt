cmake_minimum_required(VERSION 3.0.2)
project(image_grab)

## Find catkin and any catkin packages
find_package(catkin REQUIRED COMPONENTS 
    roscpp 
    rospy 
    std_msgs
    sensor_msgs
    message_generation
)

add_service_files(
  FILES
  imgfr.srv
)

generate_messages(
  DEPENDENCIES
  std_msgs
  sensor_msgs
)

## Declare a catkin package
catkin_package(
  CATKIN_DEPENDS rospy
)

## Build talker and listener
include_directories( 
  ${catkin_INCLUDE_DIRS})



add_executable(image_freeze src/image_freeze.cpp)

target_link_libraries(image_freeze ${catkin_LIBRARIES})