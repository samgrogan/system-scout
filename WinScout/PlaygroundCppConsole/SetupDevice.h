#pragma once

#include <vector>

#include <Windows.h>
#include <SetupAPI.h>

#include "SetupDriver.h"
#include "Error.h"

namespace playground
{
	class SetupDevice
	{
	private:
		HDEVINFO _device_info_set;
		SP_DEVINFO_DATA _device_info_data {};

	public:
		// Constructor. Create a new object based on the given struct
		SetupDevice(HDEVINFO DeviceInfoSet, const SP_DEVINFO_DATA& DeviceInfoData);

		// The class GUID that is part of the underlying structure
		REFGUID GetClassGuid() const;

		// The device instance that is part of the underlying structure
		DWORD GetDevInst() const;

		std::vector<std::shared_ptr<SetupDriver>> EnumerateDrivers() const;

		// Destructor
		virtual ~SetupDevice();
	};
}
