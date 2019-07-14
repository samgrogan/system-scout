#pragma once

#include <memory>
#include <vector>
#include <iostream>

#include <Windows.h>
#include <SetupAPI.h>
#include <cfgmgr32.h>

#include "Error.h"
#include "DeviceClass.h"

namespace WinScoutNativeCore
{
	class DeviceClassList
	{
	private:

	public:
		// Constructor
		// Creates a ClassInfoList that includes all classes
		DeviceClassList();

		// Returns a list of device interfaces in the set
		std::vector<std::shared_ptr<DeviceClass>> EnumerateClasses() const;

		virtual ~DeviceClassList();
	};
}
