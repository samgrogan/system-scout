#pragma once

#include <memory>
#include <vector>
#include <string>

#include <Windows.h>
#include <psapi.h>

#include "UM_DeviceDriver.h"
#include "Extensions.h"

namespace WinScout::Interop::Unmanaged {

	class DeviceDriverEnumerator
	{
	private:
	public:
		// Constructor
		DeviceDriverEnumerator();

		// Enumerate the list of drivers installed on the system
		std::vector<std::shared_ptr<DeviceDriver>> EnumerateDrivers() const;

		// Destructor
		~DeviceDriverEnumerator();
	};

}
