#include "UM_Device.h"

using namespace WinScout::Interop::Unmanaged;

Device::Device(PWSTR DeviceId)
{
	if (DeviceId == nullptr || wcslen(DeviceId) == 0) {
		throw "Device ID cannot be null or blank.";
	}

	_device_id = std::wstring(DeviceId);

	// Try to locate this device instance
	_device_instance = GetDeviceInstance(_device_id);

	// Read the properties of the device
	_properties = EnumerateProperties();

	// Get the list of drivers for this device
	_drivers = EnumerateDrivers();
}


// Try to get the device instance of this device, based on the id
DEVINST Device::GetDeviceInstance(const std::wstring& DeviceID) {
	DEVINST device_instance = 0UL;

	const CONFIGRET result = CM_Locate_DevNode(&device_instance, const_cast<DEVINSTID_W>(DeviceID.c_str()), CM_LOCATE_DEVNODE_PHANTOM);
	if (result == CR_SUCCESS) {

	}
	else {
		const Error last_error;
		std::wcout << L"Device::GetDeviceInstance(): " << last_error.GetErrorMessage();
	}

	return device_instance;
}


// Get the list of properties for this device
std::unordered_map<DEVPROPKEY, std::shared_ptr<DeviceInstanceProperty>> Device::EnumerateProperties() const
{
	// A list of keys for the available properties of this device
	std::unordered_map<DEVPROPKEY, std::shared_ptr<DeviceInstanceProperty>> properties;

	// How many property keys are there?
	ULONG property_key_count = 0;

	CM_Get_DevNode_Property_Keys(_device_instance, nullptr, &property_key_count, 0);

	if (property_key_count > 0) {

		// Try to allocate the memory to hold the list of device ids
		DEVPROPKEY* property_keys = static_cast<DEVPROPKEY*>(HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, property_key_count * sizeof(DEVPROPKEY)));

		if (property_keys != nullptr) {
			// Read the list of keys
			const CONFIGRET result = CM_Get_DevNode_Property_Keys(_device_instance, property_keys, &property_key_count, 0);
			if (result == CR_SUCCESS) {
				for (ULONG index = 0; index < property_key_count; index++) {
					DEVPROPKEY property_key = property_keys[index];
					const std::shared_ptr<DeviceInstanceProperty> property = std::make_shared<DeviceInstanceProperty>(DeviceInstanceProperty(_device_instance, property_key));

					properties[property_key] = property;
				}
			}
			else {
				const Error last_error;
				std::wcout << L"Device::EnumerateProperties(): " << last_error.GetErrorMessage();
			}

			// Free the memory
			HeapFree(GetProcessHeap(), 0, property_keys);
			property_keys = nullptr;
		}
	}

	return properties;
}


// Builds a list of driver information in the set
std::vector<std::shared_ptr<DeviceDriver>> Device::EnumerateDrivers() const
{
	// Create a vector to hold the drivers
	std::vector<std::shared_ptr<DeviceDriver>> drivers;

	// Create the device info for this device
	SP_DEVINFO_DATA devinfo_data{};
	devinfo_data.cbSize = sizeof(SP_DEVINFO_DATA);
	devinfo_data.DevInst = _device_instance;

	// Set the guid, if available
	if (_properties.count(DEVPKEY_Device_ClassGuid) > 0)
	{
		std::shared_ptr<DeviceInstanceProperty> class_guid_property = _properties.at(DEVPKEY_Device_ClassGuid);
		devinfo_data.ClassGuid = class_guid_property->GetGuidValue();
	}

	SP_DRVINFO_DATA drvinfo_data{};
	drvinfo_data.cbSize = sizeof(SP_DRVINFO_DATA);

	// Create a device info list and add this device to it
	HDEVINFO device_info_set = SetupDiCreateDeviceInfoList(nullptr, nullptr);
	if (SetupDiOpenDeviceInfo(device_info_set, _device_id.c_str(), nullptr, 0, &devinfo_data))
	{
		// Build the list of drivers for this device
		if (SetupDiBuildDriverInfoList(device_info_set, &devinfo_data, SPDIT_COMPATDRIVER))
		{
			// Iterate through the available drivers
			DWORD member_index = 0;
			while (SetupDiEnumDriverInfo(device_info_set, &devinfo_data, SPDIT_COMPATDRIVER, member_index++, &drvinfo_data))
			{
				// Create a new driver object to wrap the returned data
				std::shared_ptr<DeviceDriver> driver = std::make_shared<DeviceDriver>(DeviceDriver(_device_id, drvinfo_data));
				drivers.push_back(driver);
			}
		}
	}

	// Why did the loop end?
	const Error last_error;
	if (last_error.GetErrorCode() != ERROR_NO_MORE_ITEMS)
	{
		std::wcout << L"Device::EnumerateDrivers(): " << last_error.GetErrorMessage();
	}

	// Free the device list handle
	SetupDiDestroyDeviceInfoList(device_info_set);

	return drivers;
}


// Returns the device id of this device
std::wstring Device::GetDeviceID() const
{
	return _device_id;
}


// Get the list of properties for this device
std::unordered_map<DEVPROPKEY, std::shared_ptr<DeviceInstanceProperty>> Device::GetProperties() const
{
	return _properties;
}


// Get the list of drivers for this device
std::vector<std::shared_ptr<DeviceDriver>> Device::GetDrivers() const
{
	return _drivers;
}


//// Get the list of interfaces for this device
//std::vector<std::shared_ptr<DeviceInterface>> Device::EnumerateInterfaces() const {
//	std::vector<std::shared_ptr<DeviceInterface>> interfaces;
//
//	ULONG list_size = 0UL;
//	GUID class_guid{}; // TODO: Set to class guid
//	DEVINSTID_W device_id = const_cast<DEVINSTID_W>(_device_id.c_str());
//	if (device_id != nullptr) {
//		CONFIGRET result = CM_Get_Device_Interface_List_Size(&list_size, &class_guid, device_id, CM_GET_DEVICE_INTERFACE_LIST_ALL_DEVICES);
//
//		if (list_size > 0) {
//			std::wcout << list_size << L" device interfaces found." << std::endl;
//		}
//	}
//
//	return interfaces;
//}


// Destructor
Device::~Device() = default;