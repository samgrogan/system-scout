#include "DeviceInformationSet.h"

using namespace playground;

// Constructor
DeviceInformationSet::DeviceInformationSet() {
	// Initialize with a list of all devices
	_device_info_set = SetupDiGetClassDevs(nullptr, nullptr, nullptr, DIGCF_ALLCLASSES);
}

// Returns a list of devices in the device set
std::vector<std::shared_ptr<Device>> DeviceInformationSet::EnumerateDevices() const
{
	// Create a vector to hold the devices
	std::vector<std::shared_ptr<Device>> devices;
	DWORD member_index = 0;
	SP_DEVINFO_DATA devinfo_data;
	devinfo_data.cbSize = sizeof(SP_DEVINFO_DATA);

	// Call get function to get the interfaces until there are no more interfaces
	while (SetupDiEnumDeviceInfo(_device_info_set, member_index++, &devinfo_data)) {
		std::shared_ptr<Device> device = std::make_shared<Device>(Device(devinfo_data));
		devices.push_back(device);
	}
	// Why did the loop end?
	const Error last_error;
	if (last_error.GetErrorCode() != ERROR_NO_MORE_ITEMS)
	{
		std::wcout << last_error.GetErrorMessage();
	}

	return devices;
}

// Destructor
DeviceInformationSet::~DeviceInformationSet() {
	// Clean up the handle to the device set
	if (_device_info_set != nullptr) {
		if (!SetupDiDestroyDeviceInfoList(_device_info_set)) {
			Error error;
		}
		_device_info_set = nullptr;
	}
}
