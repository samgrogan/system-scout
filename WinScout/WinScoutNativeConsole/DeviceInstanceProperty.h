#pragma once

#include "DevicePropertyBase.h"

namespace WinScoutNativeCore {
	class DeviceInstanceProperty : public DevicePropertyBase
	{
	private:

		// The device instance for the device this property applies to
		DEVINST _device_instance = 0UL;

		// Try to read the value of the property
		virtual void GetPropertyValue();

	public:
		// Default constructor
		DeviceInstanceProperty(DEVINST DevInst, DEVPROPKEY& PropertyKey);

		// Gets th device instance the this property belongs to
		DEVINST GetDevInst() const;

		// Comparison operator
		bool operator ==(const DeviceInstanceProperty& compare) const;

		// Destructor
		virtual ~DeviceInstanceProperty();
	};
}

// Output operator
std::wostream& operator<<(std::wostream& wos, WinScoutNativeCore::DeviceInstanceProperty& property);
