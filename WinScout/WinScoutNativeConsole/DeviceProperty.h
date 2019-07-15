#pragma once

#include <Windows.h>
#include <SetupAPI.h>
#include <Devpropdef.h>
#include <Devpkey.h>

#include "Error.h"
#include "Extensions.h"

namespace WinScoutNativeCore {
	class DeviceProperty
	{
	private:
		HDEVINFO _device_info_set;

		// Structure that hold the unique identity of this device instance
		SP_DEVINFO_DATA _device_info_data{};

		// The key to identify this property
		DEVPROPKEY _property_key {};

		// The size of the buffer
		DWORD _buffer_size = 0;

		// The type of the property
		DEVPROPTYPE _property_type = 0UL;


	public:
		// Default constructor
		DeviceProperty(HDEVINFO DeviceInfoSet, SP_DEVINFO_DATA& DeviceInfoData, DEVPROPKEY& PropertyKey);

		// Get the GUID of this property
		REFGUID GetGuid() const;

		// Gets the Id of this property
		DEVPROPID GetId() const;

		// Get the type of the property value
		DEVPROPTYPE GetType() const;

		// Does this property have a value?
		bool HasValue() const;

		// Does this property have a value of the given type?
		bool HasValue(DEVPROPTYPE Type) const;

		// Get the value as a string
		std::wstring GetStringValue() const;

		// Comparison operator
		bool operator ==(const DeviceProperty& compare);

		// Destructor
		virtual ~DeviceProperty();
	};
}
