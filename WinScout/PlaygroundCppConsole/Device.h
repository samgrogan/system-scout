#pragma once

#include <Windows.h>
#include <SetupAPI.h>

#include "Error.h"

namespace playground {

	class Device
	{
	private:
		SP_DEVINFO_DATA _device_info_data{};

	public:
		// Constructor. Create a new object based on the given struct
		Device(SP_DEVINFO_DATA DeviceInfoData);

		// The class GUID that is part of this structure
		REFGUID GetClassGuid() const;

		// Desctructor
		virtual ~Device();
	};

}