#pragma once

#include <Windows.h>
#include <SetupAPI.h>
#include <string>

namespace Playground
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
		std::wstring GetDescription();

		// Gets the name of the manufacturer
		std::wstring GetMfgName();

		// Get the provider
		std::wstring GetProviderName();

		// Destructor
		virtual ~SetupDriver();
	};
}
