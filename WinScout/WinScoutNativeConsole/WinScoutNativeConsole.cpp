// PlaygroundCppConsole.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "WinScoutNativeConsole.h"

using namespace WinScoutNativeCore;

int main()
{
	std::vector<std::shared_ptr<DeviceEnumerator>> enumerators = GetEnumerators();
	std::vector<std::shared_ptr<DeviceClass>> classes = GetClasses(false);
	std::vector<std::shared_ptr<Device>> devices = GetDevices(false, true);
	std::vector<std::shared_ptr<DeviceDriver>> drivers = GetDrivers();

	return 0;
}

// Gets and displays the list of enumerators
std::vector<std::shared_ptr<DeviceEnumerator>> WinScoutNativeCore::GetEnumerators() {
	const DeviceEnumeratorEnumerator dee;
	std::vector<std::shared_ptr<DeviceEnumerator>> enumerators = dee.EnumerateEnumerators();

	std::wcout << enumerators.size() << L" enumerators found" << std::endl;

	for (auto& enumerator : enumerators)
	{
		std::wcout << L"\t" << enumerator->GetFilter() << std::endl;
	}

	return enumerators;
}

// Get and display the list of classes
std::vector<std::shared_ptr<DeviceClass>> WinScoutNativeCore::GetClasses(bool ShowProperties) {
	const DeviceClassEnumerator dce;
	std::vector<std::shared_ptr<DeviceClass>> classes = dce.EnumerateClasses();

	std::cout << classes.size() << " classes found" << std::endl;

	// Print out the list of classes
	for (auto& class_info : classes)
	{
		std::wcout << L"\t" << class_info->GetClassGuid() << std::endl;

		std::unordered_map<DEVPROPKEY, std::shared_ptr<DeviceClassProperty>> class_properties = class_info->EnumerateProperties();
		std::wcout << L"\t\t" << class_properties.size() << L" properties" << std::endl;

		if (ShowProperties) {
			for (auto i : class_properties)
			{
				auto property = i.second;
				std::wcout << L"\t\t" << property->GetDescription() << L"\t" << *property << std::endl;
			}
		}
	}

	return classes;
}

// Gets and display the list of devices
std::vector<std::shared_ptr<Device>> WinScoutNativeCore::GetDevices(bool ShowProperties, bool ShowDrivers) {
	DeviceEnumerator de;
	std::vector<std::shared_ptr<Device>> devices = de.EnumerateDevices();

	std::wcout << devices.size() << L" devices found" << std::endl;

	for (auto& device : devices)
	{
		std::wcout << L"\t" << device->GetDeviceID() << std::endl;

		// Get a list of interfaces for this device
		std::vector<std::shared_ptr<DeviceInterface>> device_interfaces = device->EnumerateInterfaces();
		std::wcout << L"\t\t" << device_interfaces.size() << L" interfaces" << std::endl;

		// Get a list of properties for this device
		std::unordered_map<DEVPROPKEY, std::shared_ptr<DeviceInstanceProperty>> device_properties = device->EnumerateProperties();
		std::wcout << L"\t\t" << device_properties.size() << L" properties" << std::endl;

		if (ShowProperties) {
			for (auto i : device_properties)
			{
				auto property = i.second;
				std::wcout << L"\t\t" << property->GetDescription() << L"\t" << *property << std::endl;
			}
		}

		// Get the list of drivers for this device
		std::vector<std::shared_ptr<DeviceDriver>> drivers = device->EnumerateDrivers();
		std::wcout << L"\t\t" << drivers.size() << L" drivers" << std::endl;

		if (ShowDrivers) {
			for (auto& driver : drivers)
			{
				std::wcout << L"\t\t" << driver->GetDescription() << L"\t" << driver->GetMfgName() << L"\t" << driver->GetProviderName() << std::endl;
			}
		}
	}

	return devices;
}

// Gets the list of interfaces
std::vector<std::shared_ptr<DeviceInterface>> WinScoutNativeCore::GetInterfaces(bool ShowProperties) {
	const DeviceInterfaceEnumerator die;

	std::vector<std::shared_ptr<DeviceInterface>> interfaces = die.EnumerateInterfaces();
	std::wcout << L"\t\t" << interfaces.size() << L" interfaces" << std::endl;

	// Print out the list of interfaces
	for (auto& interface_info : interfaces) {

	}

	return interfaces;
}

// Get and display a list of drivers
std::vector<std::shared_ptr<DeviceDriver>> WinScoutNativeCore::GetDrivers() {
	const DeviceDriverEnumerator dde;
	
	std::vector<std::shared_ptr<DeviceDriver>> drivers = dde.EnumerateDrivers();
	std::wcout << drivers.size() << L" drivers found" << std::endl;

	// Print out the list of drivers
	for (auto& driver_info : drivers) {

	}

	return drivers;
}
