#include "DeviceInformationSet.h"

// Constructor
DeviceInformationSet::DeviceInformationSet()
{
	DeviceInfoSet = SetupDiGetClassDevs(NULL, NULL, NULL, DIGCF_ALLCLASSES);
}

// Destructor
DeviceInformationSet::~DeviceInformationSet()
{
}
