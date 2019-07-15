#include "Device.h"

using namespace WinScoutNativeCore;

Device::Device(PWSTR DeviceId)
{
	if (DeviceId == nullptr || wcslen(DeviceId) == 0) {
		throw "Device ID cannot be null or blank.";
	}

	_device_id = std::wstring(DeviceId);

	// Try to locate this device instance
	_device_instance = GetDeviceInstance(_device_id);
}

// Try to get the device instance of this device, based on the id
DEVINST Device::GetDeviceInstance(const std::wstring& DeviceID) {
	DEVINST device_instance = 0UL;

	CONFIGRET result = CM_Locate_DevNode(&device_instance, const_cast<DEVINSTID_W>(DeviceID.c_str()), CM_LOCATE_DEVNODE_PHANTOM);
	if (result == CR_SUCCESS) {

	}
	else {
		const Error last_error;
		std::wcout << L"Device::GetDeviceInstance: " << last_error.GetErrorMessage();
	}

	return device_instance;
}


// Returns the device id of this device
const std::wstring Device::GetDeviceID() const {
	return _device_id;
}


// Get the list of properties for this device
std::unordered_map<DEVPROPKEY, std::shared_ptr<DeviceProperty>> Device::EnumerateProperties() const
{
	// A list of keys for the available properties of this device
	std::unordered_map<DEVPROPKEY, std::shared_ptr<DeviceProperty>> properties;

	// How many property keys are there?
	ULONG property_key_count = 0;

	CM_Get_DevNode_Property_Keys(_device_instance, nullptr, &property_key_count, 0);

	if (property_key_count > 0) {

		// Try to allocate the memory to hold the list of device ids
		DEVPROPKEY* property_keys = static_cast<DEVPROPKEY*>(HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, property_key_count * sizeof(DEVPROPKEY)));

		if (property_keys != nullptr) {
			// Read the list of keys
			CONFIGRET result = CM_Get_DevNode_Property_Keys(_device_instance, property_keys, &property_key_count, 0);
			if (result == CR_SUCCESS) {
				for (ULONG index = 0; index < property_key_count; index++) {
					DEVPROPKEY property_key = property_keys[index];
					std::shared_ptr<DeviceProperty> property = std::make_shared<DeviceProperty>(DeviceProperty(_device_instance, property_key));

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


	//// How many property keys are there
	//DWORD key_count = 0;
	//SP_DEVINFO_DATA devinfo_data = _device_info_data;

	//SetupDiGetDevicePropertyKeys(_device_info_set, &devinfo_data, nullptr, 0, &key_count, 0);
	//const Error last_error;
	//if (last_error.GetErrorCode() == ERROR_INSUFFICIENT_BUFFER && key_count > 0)
	//{
	//	// Allocate the array to hold the keys
	//	DEVPROPKEY* property_keys = new DEVPROPKEY[static_cast<size_t>(key_count)+ static_cast<size_t>(1)];

	//	// Get the list of keys
	//	if (SetupDiGetDevicePropertyKeys(_device_info_set, &devinfo_data, property_keys, key_count, &key_count, 0)) {

	//		for (size_t index = 0; index < static_cast<size_t>(key_count); index++)
	//		{
	//			// Read the property keys and store them in a vector
	//			DEVPROPKEY property_key = property_keys[index];
	//			std::shared_ptr<SetupDeviceProperty> property = std::make_shared<SetupDeviceProperty>(SetupDeviceProperty(_device_info_set, devinfo_data, property_key));

	//			properties[property_key] = property;
	//		}
	//	}
	//	else {
	//		// Unexpected error
	//		std::wcout << L"SetupDevice::InitPropertyKeys(): " << last_error.GetErrorMessage();
	//	}

	//	// Clean up
	//	if (property_keys != nullptr) {
	//		delete[] property_keys;
	//		property_keys = nullptr;
	//	}
	//}
	//else {
	//	// Unexpected error
	//	std::wcout << L"SetupDevice::InitPropertyKeys(): " << last_error.GetErrorMessage();
	//}

	return properties;
}



// Builds a list of driver information in the set
std::vector<std::shared_ptr<Driver>> Device::EnumerateDrivers() const
{
	// Create a vector to hold the drivers
	std::vector<std::shared_ptr<Driver>> drivers;
	//DWORD member_index = 0;

	//SP_DEVINFO_DATA devinfo_data = _device_info_data;

	//SP_DRVINFO_DATA drvinfo_data;
	//drvinfo_data.cbSize = sizeof(SP_DRVINFO_DATA);

	//// Iterate through the available drivers
	//while (SetupDiEnumDriverInfo(_device_info_set, &devinfo_data, SPDIT_COMPATDRIVER, member_index++, &drvinfo_data))
	//{
	//	std::shared_ptr<SetupDriver> driver = std::make_shared<SetupDriver>(SetupDriver(drvinfo_data));
	//	drivers.push_back(driver);
	//}
	//// Why did the loop end?
	//const Error last_error;
	//if (last_error.GetErrorCode() != ERROR_NO_MORE_ITEMS)
	//{
	//	std::wcout << L"SetupDevice::EnumerateDrivers(): " << last_error.GetErrorMessage();
	//}

	return drivers;
}


// Destructor
Device::~Device() = default;