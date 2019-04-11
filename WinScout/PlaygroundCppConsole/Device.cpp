#include "Device.h"

using namespace playground;

Device::Device(SP_DEVINFO_DATA DeviceInfoData)
{
	_device_info_data = DeviceInfoData;
}

Device::~Device()
{
}

