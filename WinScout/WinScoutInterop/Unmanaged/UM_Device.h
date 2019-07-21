#pragma once

#include <vector>
#include <string>
#include <unordered_map>

#include <Windows.h>
#include <cfgmgr32.h>

#include "UM_DeviceDriver.h"
#include "UM_DeviceInterface.h"
#include "UM_DeviceClass.h"
#include "UM_DeviceInstanceProperty.h"
#include "UM_Error.h"
#include "Extensions.h"

namespace WinScout::Interop::Unmanaged
{
	class Device
	{
	private:
		// Device id of this device
		std::wstring _device_id;

		// The device instance for this device
		DEVINST _device_instance = 0UL;

		// Try to get the device instance of this device, based on the id
		DEVINST GetDeviceInstance(const std::wstring& DeviceID);

	public:
		// Constructor. Create a new object based on the given struct
		Device(PWSTR DeviceId);

		// Returns the device id of this device
		const std::wstring GetDeviceID() const;

		// Get the list of properties for this device
		std::unordered_map<DEVPROPKEY, std::shared_ptr<DeviceInstanceProperty>> EnumerateProperties() const;

		// Get the list of interfaces for this device
		std::vector<std::shared_ptr<DeviceInterface>> EnumerateInterfaces() const;

		// Get the list of drivers that are associated with this device
		std::vector<std::shared_ptr<DeviceDriver>> EnumerateDrivers() const;

		// Destructor
		virtual ~Device();
	};
}
