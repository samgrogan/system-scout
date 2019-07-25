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
		Nullable<DateTime> _releaseDate;

		// The path to the INF file for this driver
		String^ _infFile;

		// Populate the properties for this device
		inline void PopulateProperties(std::shared_ptr<Unmanaged::DeviceDriver> UMDriver);
		inline void PopulateHardwareIds(std::shared_ptr<Unmanaged::DeviceDriver> UMDriver);
		inline void PopulateDescription(std::shared_ptr<Unmanaged::DeviceDriver> UMDriver);
		inline void PopulateManufacturer(std::shared_ptr<Unmanaged::DeviceDriver> UMDriver);
		inline void PopulateVersion(std::shared_ptr<Unmanaged::DeviceDriver> UMDriver);
		inline void PopulateReleaseDate(std::shared_ptr<Unmanaged::DeviceDriver> UMDriver);
		inline void PopulateInfFile(std::shared_ptr<Unmanaged::DeviceDriver> UMDriver);

	public:
		// Properties
		property List<String^>^ HardwareIds { List<String^>^ get(); }
		property String^ Description { String^ get(); }
		property String^ Manufacturer { String^ get(); }
		property String^ Version { String^ get(); }
		property Nullable<DateTime> ReleaseDate { Nullable<DateTime> get(); }
		property String^ InfFile { String^ get(); }


		// Constructor
		// Create a managed driver class from an unmanaged device class
		DeviceDriver(std::shared_ptr<Unmanaged::DeviceDriver> UMDriver);
	};
}
