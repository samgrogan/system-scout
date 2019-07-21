#pragma once

#include <memory>
#include <vector>
#include <iostream>

#include <Windows.h>
#include <cfgmgr32.h>

#include "UM_Error.h"
#include "UM_DeviceEnumerator.h"

namespace WinScout::Interop::Unmanaged {
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