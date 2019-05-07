#pragma once

#include <Windows.h>
#include <SetupAPI.h>

namespace playground
{
	class SetupDriver
	{
	private:
		SP_DRVINFO_DATA _drvinfo_data;

	public:
		// Constructor
		// Create a new driver class based on the structure data
		SetupDriver(const SP_DRVINFO_DATA& DriverInfoData);

		// Destructor
		virtual ~SetupDriver();
	};
}
