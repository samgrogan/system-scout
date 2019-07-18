#include "DeviceDriver.h"

using namespace WinScoutNativeCore;

// Constructor
// Create a new driver class based on the structure data
DeviceDriver::DeviceDriver(const SP_DRVINFO_DATA& DriverInfoData)
{
	_drvinfo_data = DriverInfoData;
}

// Gets the description of the driver/device
std::wstring DeviceDriver::GetDescription()
{
	return _drvinfo_data.Description;
}

// Gets the name of the manufacturer
std::wstring DeviceDriver::GetMfgName()
{
	return _drvinfo_data.MfgName;
}

// Get the provider
std::wstring DeviceDriver::GetProviderName()
{
	return _drvinfo_data.ProviderName;
}


DeviceDriver::~DeviceDriver() = default;
