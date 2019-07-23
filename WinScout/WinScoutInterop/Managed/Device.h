#pragma once


#include "../Unmanaged/UM_Device.h"

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

		// Model of the device
		String^ _model;

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
		void PopulateModel(std::shared_ptr<Unmanaged::DeviceInstanceProperty> UMProperty);


	public:
		// Properties
		property String^ DeviceId { String^ get(); }
		property String^ Name { String^ get(); }
		property String^ Description { String^ get(); }
		property List<String^>^ HardwareIds { List<String^>^ get(); }
		property List<String^>^ CompatibleIds { List<String^>^ get(); }
		property String^ Manufacturer { String^ get(); }
		property String^ Model { String^ get(); }

		// Constructor
		// Create a managed device class from an unmanaged device class
		Device(std::shared_ptr<Unmanaged::Device> UMDevice);
	};

}

