#pragma once

#include <string>
#include <iostream>

#include <Windows.h>
#include <SetupAPI.h>
#include <psapi.h>


namespace WinScout::Interop::Unmanaged
{
	class DeviceDriver
	{
	private:
		SP_DRVINFO_DATA _drvinfo_data {};
		LPVOID _image_base = nullptr;

	public:
		// Create a new driver based on the image base name
		DeviceDriver(LPVOID ImageBase);

		// Create a new driver class based on the structure data
		DeviceDriver(const SP_DRVINFO_DATA& DriverInfoData);

		// Gets the description of the driver/device
		std::wstring GetDescription();

		// Gets the name of the manufacturer
		std::wstring GetMfgName();

		// Get the provider
		std::wstring GetProviderName();

		// Gets the file name of the driver
		std::wstring GetFileName();

		// Destructor
		~DeviceDriver();
	};
}
