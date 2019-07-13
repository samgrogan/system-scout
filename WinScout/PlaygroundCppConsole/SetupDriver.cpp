#include "SetupDriver.h"

using namespace Playground;

// Constructor
// Create a new driver class based on the structure data
SetupDriver::SetupDriver(const SP_DRVINFO_DATA& DriverInfoData)
{
	_drvinfo_data = DriverInfoData;
}

// Gets the description of the driver/device
std::wstring SetupDriver::GetDescription()
{
	return _drvinfo_data.Description;
}

// Gets the name of the manufacturer
std::wstring SetupDriver::GetMfgName()
{
	return _drvinfo_data.MfgName;
}

// Get the provider
std::wstring SetupDriver::GetProviderName()
{
	return _drvinfo_data.ProviderName;
}


SetupDriver::~SetupDriver() = default;
