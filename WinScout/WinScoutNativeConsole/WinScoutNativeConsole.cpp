// PlaygroundCppConsole.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <unordered_map>

#include "DeviceEnumeratorEnumerator.h"
#include "DeviceEnumerator.h"
#include "DeviceClassEnumerator.h"
#include "DeviceInstanceProperty.h"
#include "Extensions.h"

using namespace WinScoutNativeCore;

int main()
{
	// Print out the list of enumerators
	DeviceEnumeratorEnumerator dee;

	std::vector<std::shared_ptr<DeviceEnumerator>> enumerators = dee.EnumerateEnumerators();
	std::wcout << enumerators.size() << L" enumerators" << std::endl;

	for (auto& enumerator : enumerators)
	{
		std::wcout << L"\t" << enumerator->GetFilter() << std::endl;
	}


	// Print out the list of devices
	DeviceEnumerator de;

	std::vector<std::shared_ptr<Device>> devices = de.EnumerateDevices();
	std::wcout << devices.size() << L" devices" << std::endl;

	for (auto& device : devices)
	{
		std::wcout << L"\t" << device->GetDeviceID() << std::endl;

		// Get a list of properties for this device
		std::unordered_map<DEVPROPKEY, std::shared_ptr<DeviceInstanceProperty>> properties = device->EnumerateProperties();
		std::wcout << L"\t\t" << properties.size() << L" properties" << std::endl;

		for (auto i : properties)
		{
			auto property = i.second;

			std::wcout << L"\t\t" << property->GetDescription() << L"\t" << *property << std::endl;
		}

		// Get the list of drivers for this device
		std::vector<std::shared_ptr<Driver>> drivers = device->EnumerateDrivers();
		std::wcout << L"\t\t" << drivers.size() << L" drivers" << std::endl;

		for (auto& driver : drivers)
		{
			std::wcout << L"\t\t" << driver->GetDescription() << L"\t" << driver->GetMfgName() << L"\t" << driver->GetProviderName() << std::endl;
		}
	}

	// Print out the list of classes
	const DeviceClassEnumerator dce;
	std::vector<std::shared_ptr<DeviceClass>> classes = dce.EnumerateClasses();
	std::cout << "Found " << classes.size() << " classes" << std::endl;

	for (auto& class_info : classes)
	{
		std::wcout << L"\t" << class_info->GetClassGuid() << std::endl;

		std::unordered_map<DEVPROPKEY, std::shared_ptr<DeviceClassProperty>> class_properties = class_info->EnumerateProperties();
		std::wcout << L"\t\t" << class_properties.size() << L" properties" << std::endl;

	}

	return 0;
}
