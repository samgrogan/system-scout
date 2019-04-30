#include "Device.h"

using namespace playground;

Device::Device(SP_DEVINFO_DATA DeviceInfoData) {
	_device_info_data = DeviceInfoData;
}

// The class GUID that is part of this structure
REFGUID Device::GetClassGuid() {
	return (this->_device_info_data.ClassGuid);
}

Device::~Device() {
}

