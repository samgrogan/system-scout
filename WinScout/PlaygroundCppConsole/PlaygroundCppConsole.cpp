// PlaygroundCppConsole.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "DeviceInformationSet.h"
#include "ClassInfoList.h"

using namespace playground;

int main()
{
    std::cout << "Starting Playground" << std::endl; 

	DeviceInformationSet dis;
	std::vector<std::shared_ptr<Device>> devices = dis.EnumerateDevices();
	std::cout << "Found " << devices.size() << " devices" << std::endl;
	
	ClassInfoList cil;
	std::vector<std::shared_ptr<ClassInfo>> classes = cil.EnumerateClasses();
	std::cout << "Found " << classes.size() << " classes" << std::endl;

	std::cout << "Ending Playground" << std::endl;
}
