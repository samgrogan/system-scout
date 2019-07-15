#pragma once

#include <Windows.h>
#include <cfgmgr32.h>
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

		// The device instance for the device this property applies to
		DEVINST _device_instance = 0UL;

		// The size of the buffer
		DWORD _buffer_size = 0;

		// The type of the property
		DEVPROPTYPE _property_type = 0UL;


	public:
		// Default constructor
		DeviceProperty(DEVINST DevInst, DEVPROPKEY& PropertyKey);

		// Gets the type of this property
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
