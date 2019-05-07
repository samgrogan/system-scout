#include "SetupDriver.h"

using namespace playground;

// Constructor
// Create a new driver class based on the structure data
SetupDriver::SetupDriver(const SP_DRVINFO_DATA& DriverInfoData)
{
	_drvinfo_data = DriverInfoData;
}

SetupDriver::~SetupDriver()
= default;
