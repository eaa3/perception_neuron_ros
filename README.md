# PerceptionNeuronROS (Windows Server)

This server reads data from PerceptionNeuron tracking system and publishes it to ROS.

It is a reorganised version of: https://github.com/smhaller/perception-neuron-ros
Using the [Neuron Data Reader SDK version b15](https://neuronmocap.com/software/neuron-data-reader-sdk).

## Building

Open windows cmd and run the following commands:

```
git clone https://github.com/eaa3/perception_neuron_ros_win_server.git
mkdir build
```

### Configure and generate

Run cmake-gui from cmd. Then, configure and generate a visual studio x86 solution

```
cmake-gui ..
```

# Running instructions ([adapted from here](https://github.com/smhaller/perception-neuron-ros))

This repository contains two ROS Modules: 
- a Windows ROS Serial Module, which sends the Perception Neuron BVH Data to a ROS Serial Server 
- a ROS BVH tf broadcaster package.

Usage 
=====
On your windows machine:

- Connect your Perception Neuron to Axis Neuron and publish the BVH data.
- Adapt IP addresses for ROS Serial Server and Axis Neuron in windows/config.txt 
- Start perception_neuron_ros.exe 


On your ROS machine:

- start roscore and ros serial server
- start perception_neuron_tf_broadcaster









