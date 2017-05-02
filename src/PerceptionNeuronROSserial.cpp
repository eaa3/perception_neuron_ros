// PerceptionNeuronROSserial.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ros.h"
#include <Windows.h>
#include <geometry_msgs\Pose.h>
#include <std_msgs\Float64MultiArray.h>
#include <std_msgs\MultiArrayLayout.h>
#include <std_msgs\MultiArrayDimension.h>
#include <std_msgs\Int32MultiArray.h>
#include <std_msgs\String.h>
#include <string>
#include <stdlib.h>
#include <sstream>
#include <stdexcept>
#include <iostream>
#include <fstream>
#include <vector>
#include <typeinfo>
#include "WindowsSocket.h"
#include <stdio.h>
#include "NeuronDataReader.h"
#include "SocketCommand.h"


SOCKET_REF sockTCPREF = NULL;
FrameDataReceived _DataReceived;
CalculationDataReceived _CmdDataReceived;
BvhDataHeader     _bvhHeader;
SocketStatusChanged    _SocketStatusChanged;


float * _valuesBuffer=NULL;
int _frameCount = 0;
int bufferLength = 0;
bool bCallbacks = false;

// Max Array Length for ROS Data = 255  should be for UINT8 (-> data_msg.data_length )
// But not working maybe they used somewhere signed int8
// -> therefore the max array length = 127.

// we split Axis Neuron Data in 3 Parts -> therefore
int MAX_DATA_LENGTH = 120;


struct MyCallbacks {

	static void __stdcall bvhDataReceived(void * customObject, SOCKET_REF sockRef, BvhDataHeader* header, float * data)
	{
		BvhDataHeader * ptr = header;
		if (ptr->DataCount != bufferLength || _valuesBuffer == NULL) {
			_valuesBuffer = new float[ptr->DataCount];
			bufferLength = ptr->DataCount;
		}
		memcpy((char *)_valuesBuffer, (char*)data, (int)ptr->DataCount*sizeof(float));
		_frameCount++;

	}
	static void __stdcall calculationDataReceived(void* customedObj, SOCKET_REF sockRef, CalcDataHeader* header, float* data) {
		printf("Data received!! \n");
	}

	static void __stdcall socketStatusChanged(void * customObject, SOCKET_REF sockRef, SocketStatus status, char * message) {
		printf("Socket status changed\n");

	}


	virtual void registerNeuronCallbacks() {
		bool bBVH = false;
		bool bCmd = false;
		bool bSSt = false;


		BRRegisterFrameDataCallback(this, bvhDataReceived);

		BRRegisterCalculationDataCallback(this, calculationDataReceived);

		BRRegisterSocketStatusCallback(this, socketStatusChanged);

		printf("Register Neuron Callbacks");
	}


};

MyCallbacks cbks;





void prepareDataMsg(std_msgs::Float64MultiArray & data_msg) {
	data_msg.layout.dim = (std_msgs::MultiArrayDimension *) malloc(sizeof(std_msgs::MultiArrayDimension) * 2);
	data_msg.layout.dim[0].label = "PerceptionNeuronData";
	data_msg.layout.dim[0].size = MAX_DATA_LENGTH;
	// adapted ros_lib/ros/node_handle.h buffer limitations to 1024 (max would be 2048)
	// that we can use MAX_DATA_LENGTH for data_msg.data_length.
	data_msg.data_length = MAX_DATA_LENGTH;
	data_msg.layout.data_offset = 0;
	data_msg.data = (double *)malloc(sizeof(float) * 1048);
}

int main(int argc, _TCHAR * argv[])
{

	// first set some default values if no config file found
	std::string ipAxisNeuron = "192.168.1.5";
	std::string ipROS = "192.168.1.4";
	int portAxisNeuron = 7001;
	bool verbose = true;

	// read config file
	std::ifstream fin("config.txt", std::ios::in);
	std::string line;
	std::istringstream iss;
	if (fin.is_open())
	{
		printf("Reading values from config.txt\n");
		while (fin.good())
		{
			std::getline(fin, line);
			iss.str(line.substr(line.find("=") + 1));
			if (line.find("ipAxisNeuron") != std::string::npos) {
				printf("IP Axis Neuron %s \n", iss.str().c_str());
				iss >> ipAxisNeuron;

			}
			else if (line.find("portAxisNeuron") != std::string::npos) {
				printf("Port Axis Neuron %s \n", iss.str().c_str());
				iss >> portAxisNeuron;
			}
			else if (line.find("ipROS") != std::string::npos) {
				printf("IP ROS Serial Server %s \n", iss.str().c_str());
				iss >> ipROS;
			}
			iss.clear();
		}
		fin.close();
	}
	else
	{
		printf("Unable to open config.txt file.. using DEFAULT values. \n" );
		printf("ROS Master (Serial Windwos): 192.168.1.4, Axis Neuron 192.168.1.5. \n");
		printf("The config file will be read if use the commandline \n");
		printf( "  cd to PerceptionNeuronROSSerial path, start PerceptionNeuronROSserial.exe .. \n");
	}

	// ROS Handle
	ros::NodeHandle nh;
	char *ros_master = new char[ipROS.length() + 1];
	strcpy(ros_master, ipROS.c_str());

	printf("\nConnecting to ROS Master (ROS Serial Server) at %s \n", ros_master);
	 nh.initNode(ros_master);
	// Neuron Connection
	void * neuronptr = NULL;
	if (BRGetSocketStatus(neuronptr) == SocketStatus::CS_Running) {
		BRCloseSocket(neuronptr);
	}


	printf("Okay, we after the if SocketStatus::CS_Running\n");

	char *nIP = new char[ipAxisNeuron.length() + 1];
	strcpy(nIP, ipAxisNeuron.c_str());

	printf("Okay, calluing BRConnectTo IP: %s port %d\n",nIP,portAxisNeuron);


	neuronptr = BRConnectTo(nIP, portAxisNeuron);
	if (neuronptr == NULL) {
		printf("Axis Neuron Connection refused! \n ");
		printf("Trying again... \n");
			//return 0;
	}
	else {
		printf("Connected to Axis Neuron at %s \n", nIP);
	}



	cbks.registerNeuronCallbacks();

	printf("\n \nAdvertising Axis Neuron Data to ROS Serial Server\n");

	// Prepare the data msg arrays for the ros publisher


	std_msgs::Float64MultiArray data_msg_1, data_msg_2, data_msg_3;
	prepareDataMsg(data_msg_1);
	prepareDataMsg(data_msg_2);
	prepareDataMsg(data_msg_3);


	ros::Publisher data_pub_1("/perception_neuron/data_1", &data_msg_1);
	ros::Publisher data_pub_2("/perception_neuron/data_2", &data_msg_2);
	ros::Publisher data_pub_3("/perception_neuron/data_3", &data_msg_3);


	nh.advertise(data_pub_1);
	nh.advertise(data_pub_2);
	nh.advertise(data_pub_3);


	while (1)
	{

		if (verbose) {
			printf("Current Data Frame %i \n", _frameCount);
		}

		 // check that it have already received values from Axis Neuron
		if (_valuesBuffer != NULL && _valuesBuffer[114]) {

			for (int i = 0; i < MAX_DATA_LENGTH; i++) {
				data_msg_1.data[i] = _valuesBuffer[i];
				data_msg_2.data[i] = _valuesBuffer[i + MAX_DATA_LENGTH];
				data_msg_3.data[i] = _valuesBuffer[i + 2*MAX_DATA_LENGTH];
			}
			// Publish part one of the array
			data_pub_1.publish(&data_msg_1);
			data_pub_2.publish(&data_msg_2);
			data_pub_3.publish(&data_msg_3);

		}

		nh.spinOnce();
		Sleep(50);
	}
	BRCloseSocket(neuronptr);
	printf("All done!\n");
	return 0;
}
