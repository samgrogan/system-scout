// PlaygroundCppConsole.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include "SetupDeviceInformationSet.h"
#include "SetupClassInfoList.h"
#include "SetupDeviceProperty.h"
#include "Extensions.h"

using namespace Playground;

int main()
{
	std::cout << "Starting Playground" << std::endl;

	// Print out the list of devices
	const SetupDeviceInformationSet dis;
	std::vector<std::shared_ptr<SetupDevice>> devices = dis.EnumerateDevices();
	std::cout << "*Found " << devices.size() << " devices*" << std::endl;

	for (auto& device : devices)
	{
		std::wcout << L"\t" << device->GetClassGuid() << L"\t" << device->GetDeviceId() << std::endl;

		// Get a list of properties for this device
		std::vector<std::shared_ptr<SetupDeviceProperty>> properties = device->EnumerateProperties();
		std::wcout << L"\t\t" << properties.size() << L" properties" << std::endl;
		for (auto& property : properties)
		{
			if (property->HasValue()) {
				std::wcout << L"\t\t" << property->GetValue() << std::endl;
			}
		}

		// Get the list of drivers for this device
		std::vector<std::shared_ptr<SetupDriver>> drivers = device->EnumerateDrivers();
		for (auto& driver : drivers)
		{
			std::wcout << L"\t\t" << driver->GetDescription() << L"\t" << driver->GetMfgName() << L"\t" << driver->GetProviderName() << std::endl;
		}
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
