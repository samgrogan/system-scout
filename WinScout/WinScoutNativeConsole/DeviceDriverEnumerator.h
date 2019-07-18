#pragma once

#include <memory>
#include <vector>
#include <string>

#include <Windows.h>
#include <psapi.h>

#include "DeviceDriver.h"
#include "Extensions.h"

namespace WinScoutNativeCore {

	class DeviceDriverEnumerator
	{
	private:
	public:
		// Constructor
		DeviceDriverEnumerator();

		// Enumerate the list of drivers installed on the system
		std::vector<std::shared_ptr<DeviceDriver>> EnumerateDrivers();

		// Destructor
		~DeviceDriverEnumerator();
	};

}
