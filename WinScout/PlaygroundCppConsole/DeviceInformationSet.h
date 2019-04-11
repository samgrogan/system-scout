#pragma once

#include <memory>
#include <vector>
#include <iostream>

#include <Windows.h>
#include <SetupAPI.h>

#include "Error.h"
#include "Device.h"

namespace playground {
	class DeviceInformationSet
	{
	private:
		HDEVINFO _device_info_set;

	public:
		// Constructor
		// Creates a DeviceInformationSet that includes all devices
		DeviceInformationSet();

		// Returns a list of device interfaces in the set
		std::vector<std::unique_ptr<Device>> EnumerateDevices();

		// Desctructor
		virtual ~DeviceInformationSet();
	};

}