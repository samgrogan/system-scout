// PlaygroundCppConsole.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <unordered_map>

#include "DeviceInformationSet.h"
#include "DeviceClassList.h"
#include "SetupDeviceProperty.h"
#include "Extensions.h"

using namespace WinScoutNativeCore;

int main()
{
	std::cout << "Starting Playground" << std::endl;

	// Print out the list of devices
	DeviceInformationSet dis;

	std::vector<std::shared_ptr<Device>> devices = dis.EnumerateDevices();
	std::wcout << devices.size() << L" devices" << std::endl;

	for (auto& device : devices)
	{
		std::wcout << L"\t" << device->GetDeviceId() << std::endl;

		// Get a list of properties for this device
		std::unordered_map<DEVPROPKEY, std::shared_ptr<SetupDeviceProperty>> properties = device->EnumerateProperties();
		std::wcout << L"\t\t" << properties.size() << L" properties" << std::endl;

		for (auto i : properties)
		{
			auto property = i.second;

			std::wcout << L"\t\t" << property->GetGuid() << L"\t" << property->GetId();
			if (property->HasValue(DEVPROP_TYPE_STRING)) {
				std::wcout << L"\t" << property->GetStringValue();
			}
			std::wcout << std::endl;
		}

		// Get the list of drivers for this device
		std::vector<std::shared_ptr<SetupDriver>> drivers = device->EnumerateDrivers();
		std::wcout << L"\t\t" << drivers.size() << L" drivers" << std::endl;

		for (auto& driver : drivers)
		{
			std::wcout << L"\t\t" << driver->GetDescription() << L"\t" << driver->GetMfgName() << L"\t" << driver->GetProviderName() << std::endl;
		}
	}

	// Print out the list of classes
	const DeviceClassList cil;
	std::vector<std::shared_ptr<DeviceClass>> classes = cil.EnumerateClasses();
	std::cout << "Found " << classes.size() << " classes" << std::endl;

	for (auto& class_info : classes)
	{
		std::wcout << L"\t" << class_info->GetClassGuid() << L"\t" << class_info->GetDescription() << std::endl;
	}

	std::cout << "Ending Playground" << std::endl;
	return 0;
}
