#include "Driver.h"

using namespace WinScoutNativeCore;

// Constructor
// Create a new driver class based on the structure data
Driver::Driver(const SP_DRVINFO_DATA& DriverInfoData)
{
	_drvinfo_data = DriverInfoData;
}

// Gets the description of the driver/device
std::wstring Driver::GetDescription()
{
	return _drvinfo_data.Description;
}

// Gets the name of the manufacturer
std::wstring Driver::GetMfgName()
{
	return _drvinfo_data.MfgName;
}

// Get the provider
std::wstring Driver::GetProviderName()
{
	return _drvinfo_data.ProviderName;
}


Driver::~Driver() = default;
