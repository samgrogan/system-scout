#pragma once

#include <memory>
#include <vector>
#include <iostream>

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