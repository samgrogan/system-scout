#include "SetupDeviceProperty.h"

using namespace Playground;


SetupDeviceProperty::SetupDeviceProperty(HDEVINFO DeviceInfoSet, SP_DEVINFO_DATA& DeviceInfoData, DEVPROPKEY& PropertyKey)
{
	_device_info_set = DeviceInfoSet;
	_device_info_data = DeviceInfoData;
	_property_key = PropertyKey;

	// Try to read the value of the property

	// Get the size of the required buffer
	SP_DEVINFO_DATA devinfo_data = _device_info_data;
	DEVPROPTYPE devproptype(0);
	DWORD required_size(0);

	SetupDiGetDeviceProperty(_device_info_set, &devinfo_data, &_property_key, &devproptype, nullptr, 0, &required_size, 0);

}

SetupDeviceProperty::~SetupDeviceProperty() = default;