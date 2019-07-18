#pragma once

#include <memory>
#include <vector>
#include <iostream>

#include <Windows.h>
#include <cfgmgr32.h>

#include "Error.h"
#include "Device.h"
#include "DeviceDriver.h"

namespace WinScoutNativeCore
{
	class DeviceEnumerator
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
		DeviceEnumerator();

		// Create a filtered set of devices
		DeviceEnumerator(PCWSTR Filter, ULONG Flags);

		// Returns a list of devices for this enumerator
		std::vector<std::shared_ptr<Device>> EnumerateDevices() const;

		// Gets the filter applied to this enumerator
		std::wstring GetFilter() const;

		// Destructor
		virtual ~DeviceEnumerator();
	};
}
