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

		// The device instance for the device this property applies to
		DEVINST _device_instance = 0UL;

		// The property key this instance contains
		DEVPROPKEY _property_key{};

		// The type of the property
		DEVPROPTYPE _property_type = 0UL;


	public:
		// Default constructor
		DeviceProperty(DEVINST DevInst, DEVPROPKEY& PropertyKey);

		// Gets th device instance the this property belongs to
		DEVINST GetDevInst() const;

		// Gets the property key of this property
		const DEVPROPKEY& GetPropertyKey() const;

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
