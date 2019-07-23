#include "Device.h"
#include <xlocmon>

using namespace WinScout::Interop;
using namespace Managed;


// Create a managed device class from an unmanaged device class
Device::Device(std::shared_ptr<Unmanaged::Device> UMDevice)
{
	if (UMDevice == nullptr)
	{
		throw ("Can't create a managed Device from a nullptr");
	}

	// Try to populate the properties of the device
	PopulateProperties(UMDevice);
}

// Properties
String^ Device::DeviceId::get() { return _deviceId; }
String^ Device::Name::get() { return _name; }
String^ Device::Description::get() { return _description; }
List<String^>^ Device::HardwareIds::get() { return _hardwareIds; }


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


// Populate the properties for this device
void Device::PopulateProperties(std::shared_ptr<Unmanaged::Device> UMDevice)
{
	PopulateDeviceId(UMDevice);

	// Get the list of properties from the umdevice
	std::unordered_map<DEVPROPKEY, std::shared_ptr<Unmanaged::DeviceInstanceProperty>> device_properties = UMDevice->EnumerateProperties();

	// Populate based on the unmanaged properties
	PopulateName(device_properties[DEVPKEY_NAME]);
	PopulateDescription(device_properties[DEVPKEY_Device_DeviceDesc]);
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
void Device::PopulateHardwareIds(std::shared_ptr<Unmanaged::DeviceInstanceProperty> UMProperty) {
	_hardwareIds = gcnew List<String^>();

	if (UMProperty != nullptr) {
		std::vector<std::wstring> _items = UMProperty->GetStringListValue();

		for (auto& value : _values)
		{
			const std::wstring _value = UMDevice->GetDeviceID();
			const wchar_t* value = _value.c_str();
			if (value != nullptr)
			{
				_deviceId = gcnew String(value);
			}
		}
	}
}