cmake_minimum_required(VERSION 3.2)
project(echoserver)

find_package(catkin REQUIRED COMPONENTS roscpp rospy std_msgs genmsg)

add_executable(talker src/talker.cpp)
target_link_libraries(talker ${catkin_LIBRARIES})

add_executable(echosrv src/echosrv.cpp)
target_link_libraries(echosrv ${catkin_LIBRARIES})
