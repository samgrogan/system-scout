#include "DeviceInformationSet.h"

using namespace playground;

// Constructor
DeviceInformationSet::DeviceInformationSet()
{
	// Initialize with a list of all devices
	_device_info_set = SetupDiGetClassDevs(NULL, NULL, NULL, DIGCF_ALLCLASSES);
}

// Returns a list of devices in the device set
std::vector<std::unique_ptr<Device>> DeviceInformationSet::EnumerateDevices() {
	// Create a vector to hold the interfaces
	std::vector<std::unique_ptr<Device>> devices;
	DWORD member_index = 0;
	SP_DEVINFO_DATA devinfo_data;
	devinfo_data.cbSize = sizeof(SP_DEVINFO_DATA);

	// Call get function to get the interfaces until there are no more interfaces
	while (SetupDiEnumDeviceInfo(_device_info_set, member_index++, &devinfo_data) != false) {
		std::unique_ptr<Device> device = std::make_unique<Device>(Device(devinfo_data));
		devices.push_back(device);
	}
	// Why did the loop end?
	Error last_error;

	return devices;
}

// Destructor
DeviceInformationSet::~DeviceInformationSet()
{
	// Clean up the handle to the device set
	if (_device_info_set != NULL) {
		if (!SetupDiDestroyDeviceInfoList(_device_info_set)) {
			Error error;
		}
		_device_info_set = NULL;
	}
}
