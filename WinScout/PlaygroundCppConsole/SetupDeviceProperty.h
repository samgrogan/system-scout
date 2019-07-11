#pragma once

#include <Windows.h>
#include <SetupAPI.h>
#include <Devpropdef.h>

#include "Error.h"

namespace Playground {
	class SetupDeviceProperty
	{
	private:
		HDEVINFO _device_info_set;

		// Structure that hold the unique identity of this device instance
		SP_DEVINFO_DATA _device_info_data{};

		// The key to identify this property
		DEVPROPKEY _property_key {};

		// The buffer to hold be value of the property
		BYTE* _buffer = nullptr;

		// The type of the property
		DEVPROPTYPE _property_type = 0UL;


	public:
		// Default constructor
		SetupDeviceProperty(HDEVINFO DeviceInfoSet, SP_DEVINFO_DATA& DeviceInfoData, DEVPROPKEY& PropertyKey);

		// Get the GUID of this property
		REFGUID GetGuid();

		// Gets the Id of this property
		DEVPROPID GetId();

		// Get the type of the property value
		DEVPROPTYPE GetType();

		// Does this property have a value?
		bool HasValue();

		// Does this property have a value of the given type?
		bool HasValue(DEVPROPTYPE Type);

		// Get the value as a string
		std::wstring GetStringValue();

		// Destructor
		virtual ~SetupDeviceProperty();
	};
}
