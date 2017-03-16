cmake_minimum_required(VERSION 3.0)
project( PerceptionNeuronROS )


SET(INCLUDE_DIRS include ros_lib ms_includes)

SET(ROS_SRC ros_lib/WindowsSocket.cpp ros_lib/time.cpp ros_lib/duration.cpp)

SET(PERCEPTION_NEURON_ROS_SRC src/PerceptionNeuronROSserial.cpp src/stdafx.cpp)

FIND_LIBRARY(NEURON_DATA_READER_LIBRARY NeuronDataReader HINTS ${CMAKE_CURRENT_SOURCE_DIR}/lib/x86)

message("Found NEURON_DATA_READER_LIBRARY: ${NEURON_DATA_READER_LIBRARY}")

include_directories( ${INCLUDE_DIRS} )

add_executable( perception_neuron_ros ${PERCEPTION_NEURON_ROS_SRC} ${ROS_SRC})

target_link_libraries( perception_neuron_ros ${NEURON_DATA_READER_LIBRARY} )