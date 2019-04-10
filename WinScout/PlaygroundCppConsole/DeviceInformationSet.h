#pragma once

#include <Windows.h>
#include <SetupAPI.h>
#include "Error.h"

namespace playground {
	class DeviceInformationSet
	{
	private:
		HDEVINFO DeviceInfoSet;

	public:
		// Constructor
		// Creates a DeviceInformationSet that includes all devices
		DeviceInformationSet();


		// Desctructor
		virtual ~DeviceInformationSet();
	};

}