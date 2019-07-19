#include "DeviceDriverEnumerator.h"

using namespace WinScoutNativeCore;

// Constructor
DeviceDriverEnumerator::DeviceDriverEnumerator() = default;

// Enumerate the list of drivers installed on the system
std::vector<std::shared_ptr<DeviceDriver>> DeviceDriverEnumerator::EnumerateDrivers() const {
	std::vector<std::shared_ptr<DeviceDriver>> drivers;

	// How much memory is needed to hold the list
	DWORD list_size = 0;
	EnumDeviceDrivers(nullptr, 0, &list_size);

	std::wcout << list_size << L"drivers found." << std::endl;

	return drivers;
}

// Destructor
DeviceDriverEnumerator::~DeviceDriverEnumerator() = default;