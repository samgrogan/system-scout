#pragma once

#include <Windows.h>
#include <SetupAPI.h>

#include "Error.h"

namespace Playground {
	class SetupDeviceProperty
	{
	private:
		HDEVINFO _device_info_set;

		// Structure that hold the unique identity of this device instance
		SP_DEVINFO_DATA _device_info_data{};

		// The key to identify this property
		DEVPROPKEY _property_key;

		// The buffer to hold be value of the property
		BYTE* _buffer = nullptr;

	public:
		// Default constructor
		SetupDeviceProperty(HDEVINFO DeviceInfoSet, SP_DEVINFO_DATA& DeviceInfoData, DEVPROPKEY& PropertyKey);

		// Does this property have a value?
		bool HasValue();

		// Get the value as a string
		std::wstring GetValue();

		// Destructor
		virtual ~SetupDeviceProperty();
	};
}
