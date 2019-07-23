#pragma once

#include "../Unmanaged/UM_Device.h"
#include "DeviceDriver.h"

using namespace System;
using namespace Collections::Generic;

namespace WinScout::Interop::Managed
{

	public ref class Device
	{
	private:
		// The ID of this device
		String^ _deviceId;

		// The name of the device
		String^ _name;

		// Description of the device
		String^ _description;

		// List of the hardware ids associated with this device
		List<String^>^ _hardwareIds;
		List<String^>^ _compatibleIds;

		// Manufacturer of the device
		String^ _manufacturer;

		// Class GUID for this device
		String^ _classGuid;

		// The device type
		UINT32 _type;

		// Gets the value of a property as a string
		static String^ GetPropertyStringValue(std::shared_ptr<Unmanaged::DeviceInstanceProperty> UMProperty);

		// Gets the value of a property as a string
		static List<String^>^ GetPropertyStringListValue(std::shared_ptr<Unmanaged::DeviceInstanceProperty> UMProperty);

		// Populate the properties for this device
		void PopulateProperties(std::shared_ptr<Unmanaged::Device> UMDevice);
		void PopulateDeviceId(std::shared_ptr<Unmanaged::Device> UMDevice);
		void PopulateName(std::shared_ptr<Unmanaged::DeviceInstanceProperty> UMProperty);
		void PopulateDescription(std::shared_ptr<Unmanaged::DeviceInstanceProperty> UMProperty);
		void PopulateHardwareIds(std::shared_ptr<Unmanaged::DeviceInstanceProperty> UMProperty);
		void PopulateCompatibleIds(std::shared_ptr<Unmanaged::DeviceInstanceProperty> UMProperty);
		void PopulateManufacturer(std::shared_ptr<Unmanaged::DeviceInstanceProperty> UMProperty);
		void PopulateClassGuid(std::shared_ptr<Unmanaged::DeviceInstanceProperty> UMProperty);
		void PopulateType(std::shared_ptr<Unmanaged::DeviceInstanceProperty> UMProperty);

		// The list of device drivers associated with this device
		List<DeviceDriver^>^ _drivers;

		// Populate the list of drivers
		void EnumerateDrivers(std::shared_ptr<Unmanaged::Device> UMDevice);

	public:
		// Properties
		property String^ DeviceId { String^ get(); }
		property String^ Name { String^ get(); }
		property String^ Description { String^ get(); }
		property List<String^>^ HardwareIds { List<String^>^ get(); }
		property List<String^>^ CompatibleIds { List<String^>^ get(); }
		property String^ Manufacturer { String^ get(); }
		property String^ ClassGuid { String^ get(); }
		property UINT32 Type { UINT32 get(); }
		property List<DeviceDriver^>^ Drivers { List<DeviceDriver^>^ get(); }

		// Constructor
		// Create a managed device class from an unmanaged device class
		Device(std::shared_ptr<Unmanaged::Device> UMDevice);

	};

}

