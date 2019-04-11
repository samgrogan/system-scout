#pragma once

#include <Windows.h>
#include <SetupAPI.h>

#include "Error.h"

namespace playground {

	class Device
	{
	private:
		SP_DEVINFO_DATA _device_info_data;

	public:
		Device(SP_DEVINFO_DATA DeviceInfoData);
		virtual ~Device();
	};

}