#pragma once

#include <memory>
#include <vector>
#include <string>
#include <iostream>

#include <Windows.h>
#include <cfgmgr32.h>

#include "UM_DeviceInterface.h"

namespace WinScout::Interop::Unmanaged
{
	class DeviceInterfaceEnumerator
	{
	public:
		// Constructor
		DeviceInterfaceEnumerator();

		// Get the list of interfaces for this enumerator
		std::vector<std::shared_ptr<DeviceInterface>> EnumerateInterfaces() const;

		// Destructoor
		~DeviceInterfaceEnumerator();
	};

}