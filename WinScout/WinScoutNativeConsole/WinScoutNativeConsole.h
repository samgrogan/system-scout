#pragma once

#include <iostream>
#include <vector>
#include <unordered_map>

#include "DeviceEnumeratorEnumerator.h"
#include "DeviceClassEnumerator.h"
#include "DeviceInterfaceEnumerator.h"
#include "Extensions.h"

int main();

namespace WinScoutNativeCore {

	// Gets and displays the list of enumerators
	std::vector<std::shared_ptr<DeviceEnumerator>> GetEnumerators();

	// Get and display the list of classes
	std::vector<std::shared_ptr<DeviceClass>> GetClasses(bool ShowProperties);

	// Get and dispaly a list of devices (and drivers)
	std::vector<std::shared_ptr<Device>> GetDevices(bool ShowProperties, bool ShowDrivers);

	// Gets and display a list of interfaces
	std::vector<std::shared_ptr<DeviceInterface>> GetInterfaces(bool ShowProperties);

	// Get and display a list of drivers
	std::vector<std::shared_ptr<DeviceDriver>> 
}
