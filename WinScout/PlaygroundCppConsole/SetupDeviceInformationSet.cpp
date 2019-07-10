#include "SetupDeviceInformationSet.h"

using namespace playground;

// Constructor
// Return all devices
SetupDeviceInformationSet::SetupDeviceInformationSet()
{
	// Initialize with a list of all devices
	_device_info_set = SetupDiGetClassDevs(nullptr, nullptr, nullptr, DIGCF_ALLCLASSES);
}

// Constructor
SetupDeviceInformationSet::SetupDeviceInformationSet(REFGUID ClassGuid)
{
	// Initialize with a list of devices in the class
	_device_info_set = SetupDiGetClassDevs(&ClassGuid, nullptr, nullptr, DIGCF_ALLCLASSES);
}

// Returns a list of devices in the device set
std::vector<std::shared_ptr<SetupDevice>> SetupDeviceInformationSet::EnumerateDevices() const
{
	// Create a vector to hold the devices
	std::vector<std::shared_ptr<SetupDevice>> devices;
	DWORD member_index = 0;
	SP_DEVINFO_DATA devinfo_data;
	devinfo_data.cbSize = sizeof(SP_DEVINFO_DATA);

	// Call get function to get the devices until there are no more devices
	while (SetupDiEnumDeviceInfo(_device_info_set, member_index++, &devinfo_data))
	{
		std::shared_ptr<SetupDevice> device = std::make_shared<SetupDevice>(SetupDevice(_device_info_set, devinfo_data));
		devices.push_back(device);
	}
	// Why did the loop end?
	const Error last_error;
	if (last_error.GetErrorCode() != ERROR_NO_MORE_ITEMS)
	{
		std::wcout << L"SetupDeviceInformationSet::EnumerateDevices() - " << last_error.GetErrorMessage();
	}

	return devices;
}

// Gets the underlying handle
HDEVINFO SetupDeviceInformationSet::GetHandle() const
{
	return _device_info_set;
}

// Destructor
SetupDeviceInformationSet::~SetupDeviceInformationSet()
{
	// Clean up the handle to the device set
	if (_device_info_set != nullptr)
	{
		if (!SetupDiDestroyDeviceInfoList(_device_info_set))
		{
			Error error;
		}
		_device_info_set = nullptr;
	}
}
