#include "Device.h"
#include <xlocmon>

using namespace WinScout::Interop;
using namespace Managed;


// Create a managed device class from an unmanaged device class
Device::Device(std::shared_ptr<Unmanaged::Device> UMDevice)
{
	if (UMDevice == nullptr)
	{
		throw gcnew System::Exception("Can't create a managed Device from a nullptr");
	}

	// Try to populate the properties of the device
	PopulateProperties(UMDevice);

	// Read the list of drivers
	EnumerateDrivers(UMDevice);
}


// Properties
String^ Device::DeviceId::get() { return _deviceId; }
String^ Device::Name::get() { return _name; }
String^ Device::Description::get() { return _description; }
List<String^>^ Device::HardwareIds::get() { return _hardwareIds; }
List<String^>^ Device::CompatibleIds::get() { return _compatibleIds; }
String^ Device::Manufacturer::get() { return _manufacturer; }
String^ Device::ClassGuid::get() { return _classGuid; }
UINT32 Device::Type::get() { return _type; }
List<DeviceDriver^>^ Device::Drivers::get() { return _drivers; }


// Gets the value of a property as a string
String^ Device::GetPropertyStringValue(std::shared_ptr<Unmanaged::DeviceInstanceProperty> UMProperty)
{
	String^ result = nullptr;

	if (UMProperty != nullptr)
	{
		const std::wstring _value = UMProperty->GetStringValue();
		const wchar_t* value = _value.c_str();
		if (value != nullptr)
		{
			result = gcnew String(value);
		}
	}

	return result;
}


// Gets the value of a property as a string
List<String^>^ Device::GetPropertyStringListValue(std::shared_ptr<Unmanaged::DeviceInstanceProperty> UMProperty)
{
	List<String^>^ result = gcnew List<String^>();

	if (UMProperty != nullptr) {
		std::vector<std::wstring> _items = UMProperty->GetStringListValue();

		for (auto& _item : _items)
		{
			const wchar_t* value = _item.c_str();
			if (value != nullptr)
			{
				String^ _value = gcnew String(value);
				result->Add(_value);
			}
		}
	}

	return result;
}


// Populate the properties for this device
void Device::PopulateProperties(std::shared_ptr<Unmanaged::Device> UMDevice)
{
	PopulateDeviceId(UMDevice);

	// Get the list of properties from the umdevice
	std::unordered_map<DEVPROPKEY, std::shared_ptr<Unmanaged::DeviceInstanceProperty>> device_properties = UMDevice->GetProperties();

	// Populate based on the unmanaged properties
	PopulateName(device_properties[DEVPKEY_NAME]);
	PopulateDescription(device_properties[DEVPKEY_Device_DeviceDesc]);
	PopulateHardwareIds(device_properties[DEVPKEY_Device_HardwareIds]);
	PopulateCompatibleIds(device_properties[DEVPKEY_Device_CompatibleIds]);
	PopulateManufacturer(device_properties[DEVPKEY_Device_Manufacturer]);
	PopulateClassGuid(device_properties[DEVPKEY_Device_ClassGuid]);
	PopulateType(device_properties[DEVPKEY_Device_DevType]);

	// Get the list of drivers from the umdevice
	std::vector<std::shared_ptr<Unmanaged::DeviceDriver>> device_drivers = UMDevice->GetDrivers();
}


// Populate the device ID
void Device::PopulateDeviceId(std::shared_ptr<Unmanaged::Device> UMDevice)
{
	const std::wstring _value = UMDevice->GetDeviceID();
	const wchar_t* value = _value.c_str();
	if (value != nullptr)
	{
		_deviceId = gcnew String(value);
	}
}


// Populate the device name
void Device::PopulateName(std::shared_ptr<Unmanaged::DeviceInstanceProperty> UMProperty)
{
	_name = GetPropertyStringValue(UMProperty);
}


// Populate the device description
void Device::PopulateDescription(std::shared_ptr<Unmanaged::DeviceInstanceProperty> UMProperty)
{
	_description = GetPropertyStringValue(UMProperty);
}


// Populate the hardware ids
void Device::PopulateHardwareIds(std::shared_ptr<Unmanaged::DeviceInstanceProperty> UMProperty)
{
	_hardwareIds = GetPropertyStringListValue(UMProperty);
}


// Populate the compatible ids
void Device::PopulateCompatibleIds(std::shared_ptr<Unmanaged::DeviceInstanceProperty> UMProperty)
{
	_compatibleIds = GetPropertyStringListValue(UMProperty);
}


// Populate the device manufacturer
void Device::PopulateManufacturer(std::shared_ptr<Unmanaged::DeviceInstanceProperty> UMProperty)
{
	_manufacturer = GetPropertyStringValue(UMProperty);
}


// Class GUID for this device
void Device::PopulateClassGuid(std::shared_ptr<Unmanaged::DeviceInstanceProperty> UMProperty)
{
	if (UMProperty != nullptr) {
		if (UMProperty->GetType() != DEVPROP_TYPE_GUID)
		{
			throw gcnew Exception("Class GUID is not of GUID type.");
		}

		REFGUID guid = UMProperty->GetGuidValue();
		const std::wstring _value = std::to_wstring(guid);
		const wchar_t* value = _value.c_str();
		if (value != nullptr)
		{
			_classGuid = gcnew String(value);
		}
	}
}


// Class GUID for this device
void Device::PopulateType(std::shared_ptr<Unmanaged::DeviceInstanceProperty> UMProperty)
{
	if (UMProperty != nullptr) {
		if (UMProperty->GetType() != DEVPROP_TYPE_UINT32)
		{
			throw gcnew Exception("Device Type is not of UINT32 type.");
		}

		_type = UMProperty->GetUInt32Value();
	}
}


// Enumerate the list of drivers compatible with this device
void Device::EnumerateDrivers(std::shared_ptr<Unmanaged::Device> UMDevice)
{
	_drivers = gcnew List<DeviceDriver^>();

	// Get the list of unmanaged drivers for this device
	std::vector<std::shared_ptr<Unmanaged::DeviceDriver>> umdrivers = UMDevice->GetDrivers();

	// Create managed wrappers for each driver
	for (auto& umdriver : umdrivers)
	{
		DeviceDriver^ driver = gcnew DeviceDriver(umdriver);
		_drivers->Add(driver);
	}
}
