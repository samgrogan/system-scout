#include "SetupDriver.h"

using namespace playground;

// Constructor
// Create a new driver class based on the structure data
SetupDriver::SetupDriver(const SP_DRVINFO_DATA& DriverInfoData)
{
	_drvinfo_data = DriverInfoData;
}

// Gets the description of the driver/device
wchar_t* SetupDriver::GetDescription()
{
	return _drvinfo_data.Description;
}

// Gets the name of the manufacturer
wchar_t* SetupDriver::GetMfgName()
{
	return _drvinfo_data.MfgName;
}

// Get the provider
wchar_t* SetupDriver::GetProviderName()
{
	return _drvinfo_data.ProviderName;
}


SetupDriver::~SetupDriver()
= default;
