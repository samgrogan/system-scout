#pragma once

#include <memory>
#include <vector>
#include <iostream>

#include <Windows.h>
#include <SetupAPI.h>

#include "Error.h"
#include "Device.h"
#include "SetupDriver.h"

namespace WinScoutNativeCore
{
	class DeviceInformationSet
	{
	private:
		// Filters applied to this set
		std::wstring _filter;
		ULONG _flags = 0UL;

		// Gets the size of the device id list
		ULONG GetDeviceIDListSize() const;

	public:
		// Constructor
		// Creates a DeviceInformationSet that includes all devices
		DeviceInformationSet();

		// Create a filtered set of devices
		DeviceInformationSet(PCWSTR Filter, ULONG Flags);

		// Builds a list of device information in the set
		std::vector<std::shared_ptr<Device>> EnumerateDevices() const;

		// Destructor
		virtual ~DeviceInformationSet();
	};
}
