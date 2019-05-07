#include "SetupDevice.h"

using namespace playground;

SetupDevice::SetupDevice(HDEVINFO DeviceInfoSet, const SP_DEVINFO_DATA& DeviceInfoData)
{
	_device_info_set = DeviceInfoSet;
	_device_info_data = DeviceInfoData;
}

// The class GUID that is part of the underlying structure
REFGUID SetupDevice::GetClassGuid() const
{
	return _device_info_data.ClassGuid;
}

// The device instance that is part of the underlying structure
DWORD SetupDevice::GetDevInst() const
{
	return _device_info_data.DevInst;
}

// Builds a list of driver information in the set
std::vector<std::shared_ptr<SetupDriver>> SetupDevice::EnumerateDrivers() const
{
	// Create a vector to hold the drivers
	std::vector<std::shared_ptr<SetupDriver>> drivers;
	DWORD member_index = 0;
	
	SP_DEVINFO_DATA devinfo_data;
	devinfo_data.cbSize = sizeof(SP_DEVINFO_DATA);

	SP_DRVINFO_DATA drvinfo_data;
	drvinfo_data.cbSize = sizeof(SP_DRVINFO_DATA);

	// Iterate through the available drivers
	while (SetupDiEnumDriverInfo(_device_info_set, &devinfo_data, SPDIT_COMPATDRIVER, member_index++, &drvinfo_data))
	{
		std::shared_ptr<SetupDriver> driver = std::make_shared<SetupDriver>(SetupDriver(drvinfo_data));
		drivers.push_back(driver);

	}
	// Why did the loop end?
	const Error last_error;
	if (last_error.GetErrorCode() != ERROR_NO_MORE_ITEMS)
	{
		std::wcout << last_error.GetErrorMessage();
	}

	return drivers;
}


SetupDevice::~SetupDevice() = default;
