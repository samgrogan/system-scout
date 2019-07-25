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
		std::wstring _device_id;

	public:
		// Create a new driver based on the image base name
		DeviceDriver(LPVOID ImageBase);

		// Create a new driver class based on the structure data
		DeviceDriver(const std::wstring& DeviceId, SP_DRVINFO_DATA& DriverInfoData);

		// Gets the ID of the device this driver is associated with
		const std::wstring GetDeviceId() const;

		// Gets the description of the driver
		const std::wstring GetDescription() const;

		// Get the maker/provider of the driver
		const std::wstring GetProviderName() const;

		// Gets the file name of the driver
		const std::wstring GetFileName() const;

		// Destructor
		~DeviceDriver();
	};
}
