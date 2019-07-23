#pragma once

#include "../Unmanaged/UM_DeviceDriver.h"

using namespace System;
using namespace Collections::Generic;

namespace WinScout::Interop::Managed {
	public ref class DeviceDriver
	{
	private:
		// List of the hardware ids associated with this driver
		List<String^>^ _hardwareIds;

		// Description of the driver
		String^ _description;

		// Manufacturer of the driver
		String^ _manufacturer;

		// Version of the driver
		String^ _version;

		// The release date of the driver
		DateTime _releaseDate;

		// The path to the INF file for this driver
		String^ _infFile;

	public:
		// Properties
		property List<String^>^ HardwareIds { List<String^>^ get(); }
		property String^ Description { String^ get(); }
		property String^ Manufacturer { String^ get(); }
		property String^ Version { String^ get(); }
		property DateTime ReleaseDate { DateTime get(); }
		property String^ InfFile { String^ get(); }

		// Constructor
		// Create a managed driver class from an unmanaged device class
		DeviceDriver(std::shared_ptr<Unmanaged::DeviceDriver> UMDriver);
	};
}
