#pragma once

#include <memory>
#include <vector>
#include <iostream>

#include <Windows.h>
#include <SetupAPI.h>

#include "Error.h"
#include "SetupDevice.h"
#include "SetupDriver.h"

namespace Playground
{
	class SetupDeviceInformationSet
	{
	private:
		HDEVINFO _device_info_set;

	public:
		// Constructor
		// Creates a DeviceInformationSet that includes all devices
		SetupDeviceInformationSet();

		// Constructor
		// Creates a DeviceInformationSet for the given class
		SetupDeviceInformationSet(REFGUID ClassGuid);

		// Builds a list of device information in the set
		std::vector<std::shared_ptr<SetupDevice>> EnumerateDevices() const;

		// Gets the underlying handle
		HDEVINFO GetHandle() const;

		// Destructor
		virtual ~SetupDeviceInformationSet();
	};
}
