#pragma once

#include <string>
#include <iostream>

#include <Windows.h>
#include <SetupAPI.h>

namespace WinScoutNativeCore
{
	class DeviceDriver
	{
	private:
		SP_DRVINFO_DATA _drvinfo_data {};

	public:
		// Constructor
		// Create a new driver class based on the structure data
		DeviceDriver(const SP_DRVINFO_DATA& DriverInfoData);

		// Gets the description of the driver/device
		std::wstring GetDescription();

		// Gets the name of the manufacturer
		std::wstring GetMfgName();

		// Get the provider
		std::wstring GetProviderName();

		// Destructor
		~DeviceDriver();
	};
}
