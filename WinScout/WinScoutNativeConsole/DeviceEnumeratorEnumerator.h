#pragma once

#include <memory>
#include <vector>
#include <iostream>

#include <Windows.h>
#include <cfgmgr32.h>

#include "Error.h"
#include "DeviceEnumerator.h"

namespace WinScoutNativeCore {
	class DeviceEnumeratorEnumerator
	{
	public:
		// Constructor
		DeviceEnumeratorEnumerator();

		// Returns a list of device enumerators
		std::vector<std::shared_ptr<DeviceEnumerator>> EnumerateEnumerators() const;

		// Destructor
		virtual ~DeviceEnumeratorEnumerator();
	};
}