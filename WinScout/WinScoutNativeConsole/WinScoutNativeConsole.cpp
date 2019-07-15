// PlaygroundCppConsole.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <unordered_map>

#include "DeviceEnumeratorEnumerator.h"
#include "DeviceEnumerator.h"
#include "DeviceClassEnumerator.h"
#include "DeviceProperty.h"
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
		std::wcout << L"\t" << device->GetDeviceId() << std::endl;

		// Get a list of properties for this device
		std::unordered_map<DEVPROPKEY, std::shared_ptr<DeviceProperty>> properties = device->EnumerateProperties();
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
