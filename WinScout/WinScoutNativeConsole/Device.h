#pragma once

#include <vector>
#include <string>
#include <unordered_map>

#include <Windows.h>
#include <SetupAPI.h>
#include <cfgmgr32.h>

#include "SetupDriver.h"
#include "SetupDeviceProperty.h"
#include "Error.h"
#include "Extensions.h"

namespace WinScoutNativeCore
{
	class Device
	{
	private:
		// Device id of this device
		std::wstring _device_id;

	public:
		// Constructor. Create a new object based on the given struct
		Device(PWSTR device_id);

		// Returns the device id of this device
		const std::wstring GetDeviceId() const;

		// Get the list of drivers that are associated with this device
		std::vector<std::shared_ptr<SetupDriver>> EnumerateDrivers() const;

		// Get the list of properties for this device
		std::unordered_map<DEVPROPKEY, std::shared_ptr<SetupDeviceProperty>> EnumerateProperties() const;

		// Destructor
		virtual ~Device();
	};
}
