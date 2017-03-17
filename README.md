# PerceptionNeuronROS (Windows Server)

This server reads data from PerceptionNeuron tracking system and publishes it to ROS.

It is a reorganised version of: https://github.com/smhaller/perception-neuron-ros
Using the (Neuron Data Reader SDK version b15)[https://neuronmocap.com/software/neuron-data-reader-sdk].

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






