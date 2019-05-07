// PlaygroundCppConsole.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include "SetupDeviceInformationSet.h"
#include "SetupClassInfoList.h"
#include "Extensions.h"

using namespace playground;

int main()
{
	std::cout << "Starting Playground" << std::endl;

	// Print out the list of devices
	const SetupDeviceInformationSet dis;
	std::vector<std::shared_ptr<SetupDevice>> devices = dis.EnumerateDevices();
	std::cout << "*Found " << devices.size() << " devices*" << std::endl;

	for (auto& device : devices)
	{
		std::wcout << L"\t" << device->GetClassGuid() << std::endl;
	}

	// Print out the list of classes
	const SetupClassInfoList cil;
	std::vector<std::shared_ptr<SetupClassInfo>> classes = cil.EnumerateClasses();
	std::cout << "Found " << classes.size() << " classes" << std::endl;

	for (auto& class_info : classes)
	{
		std::wcout << L"\t" << class_info->GetClassGuid() << L"\t" << class_info->GetDescription() << std::endl;
	}

	std::cout << "Ending Playground" << std::endl;
}
