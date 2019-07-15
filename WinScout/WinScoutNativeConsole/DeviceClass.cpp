#include "DeviceClass.h"

using namespace WinScoutNativeCore;

/**
 * \brief 
 * \param ClassGuid 
 */

DeviceClass::DeviceClass(REFGUID ClassGuid)
{
	_class_info_guid = ClassGuid;

	//PopulateDescription();
}

// Get the list of properties for this device
std::unordered_map<DEVPROPKEY, std::shared_ptr<DeviceClassProperty>> DeviceClass::EnumerateProperties() {
	std::unordered_map<DEVPROPKEY, std::shared_ptr<DeviceClassProperty>> properties;

	// How many property keys are there?
	ULONG property_key_count = 0;
	const GUID class_info_guid = _class_info_guid;

	CM_Get_Class_Property_Keys(&class_info_guid, nullptr, &property_key_count, 0);

	if (property_key_count > 0) {
		// Try to allocate the memory to hold the list of device ids
		DEVPROPKEY* property_keys = static_cast<DEVPROPKEY*>(HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, property_key_count * sizeof(DEVPROPKEY)));

		if (property_keys != nullptr) {
			// Read the list of keys
			CONFIGRET result = CM_Get_Class_Property_Keys(&class_info_guid, property_keys, &property_key_count, 0);
			if (result == CR_SUCCESS) {
				for (ULONG index = 0; index < property_key_count; index++) {
					DEVPROPKEY property_key = property_keys[index];
					std::shared_ptr<DeviceClassProperty> property = std::make_shared<DeviceClassProperty>(DeviceClassProperty(class_info_guid, property_key));

					properties[property_key] = property;
				}
			}
			else {
				const Error last_error;
				std::wcout << L"DeviceClass::EnumerateProperties(): " << last_error.GetErrorMessage();
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


//// Populate the description of this class info
//BOOL DeviceClass::PopulateDescription()
//{
//	if (SetupDiGetClassDescription(&_class_info_guid, _description, LINE_LEN, nullptr))
//	{
//		return true;
//	}
//
//	Error last_error;
//	std::wcout << L"SetupClassInfo::PopulateDescription(): " << last_error.GetErrorMessage();
//
//	return false;
//}
//
//// Gets the description of this class
//LPWSTR DeviceClass::GetDescription()
//{
//	return _description;
//}

// Gets the guid associated with this class
REFGUID DeviceClass::GetClassGuid() const
{
	return _class_info_guid;
}


DeviceClass::~DeviceClass()
= default;
