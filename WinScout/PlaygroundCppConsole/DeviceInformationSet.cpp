#include "DeviceInformationSet.h"

using namespace playground;

// Constructor
DeviceInformationSet::DeviceInformationSet()
{
	// Initialize with a list of all devices
	DeviceInfoSet = SetupDiGetClassDevs(NULL, NULL, NULL, DIGCF_ALLCLASSES);
}

// Destructor
DeviceInformationSet::~DeviceInformationSet()
{
	// Clean up the handle to the device set
	if (DeviceInfoSet != NULL) {
		if (!SetupDiDestroyDeviceInfoList(DeviceInfoSet)) {
			Error error;
		}
		DeviceInfoSet = NULL;
	}
}
