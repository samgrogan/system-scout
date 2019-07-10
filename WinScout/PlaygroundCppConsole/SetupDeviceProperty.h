#pragma once

#include <Windows.h>
#include <SetupAPI.h>


namespace Playground {
	class SetupDeviceProperty
	{
	private:
		HDEVINFO _device_info_set;

		// Structure that hold the unique identity of this device instance
		SP_DEVINFO_DATA _device_info_data{};

		// The key to identify this property
		DEVPROPKEY _property_key;

	public:
		SetupDeviceProperty(HDEVINFO DeviceInfoSet, SP_DEVINFO_DATA& DeviceInfoData, DEVPROPKEY& PropertyKey);
		virtual ~SetupDeviceProperty();
	};
}
