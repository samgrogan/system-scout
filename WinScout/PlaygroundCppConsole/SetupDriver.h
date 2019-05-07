#pragma once

#include <Windows.h>
#include <SetupAPI.h>

namespace playground
{
	class SetupDriver
	{
	private:
		SP_DRVINFO_DATA _drvinfo_data {};

	public:
		// Constructor
		// Create a new driver class based on the structure data
		SetupDriver(const SP_DRVINFO_DATA& DriverInfoData);

		// Gets the description of the driver/device
		wchar_t* GetDescription();

		// Gets the name of the manufacturer
		wchar_t* GetMfgName();

		// Get the provider
		wchar_t* GetProviderName();

		// Destructor
		virtual ~SetupDriver();
	};
}
