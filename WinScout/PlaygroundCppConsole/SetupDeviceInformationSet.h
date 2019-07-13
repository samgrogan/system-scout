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

		// Gets the size of the device id list
		ULONG _device_id_list_size = 0UL;
		ULONG GetDeviceIDListSize();

		// Hold the list of device ids
		PWSTR _device_id_list = nullptr;

	public:
		// Constructor
		// Creates a DeviceInformationSet that includes all devices
		SetupDeviceInformationSet();

		// Builds a list of device information in the set
		std::vector<std::shared_ptr<SetupDevice>> EnumerateDevices() const;

		std::vector<std::shared_ptr<SetupDevice>> CM_EnumerateDevices();

		// Gets the underlying handle
		HDEVINFO GetHandle() const;

		// Destructor
		virtual ~SetupDeviceInformationSet();
	};
}
