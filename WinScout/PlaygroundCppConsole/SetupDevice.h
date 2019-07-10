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
		// Handle of the device set that contains this device
		HDEVINFO _device_info_set;

		// Structure that hold the unique identity of this device instance
		SP_DEVINFO_DATA _device_info_data {};


	public:
		// Constructor. Create a new object based on the given struct
		SetupDevice(HDEVINFO DeviceInfoSet, const SP_DEVINFO_DATA& DeviceInfoData);

		// The class GUID that is part of the underlying structure
		REFGUID GetClassGuid() const;

		// The device instance that is part of the underlying structure
		DWORD GetDevInst() const;

		// Get the list of drivers that are associated with this device
		std::vector<std::shared_ptr<SetupDriver>> EnumerateDrivers() const;

		// Get the list of properties for this device
		std::vector<std::shared_ptr<DEVPROPKEY>> EnumeratePropertyKeys() const;

		// Destructor
		virtual ~SetupDevice();
	};
}