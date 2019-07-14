#include "SetupDeviceInformationSet.h"

using namespace Playground;

// Constructors

// Creates a DeviceInformationSet that includes all devices
SetupDeviceInformationSet::SetupDeviceInformationSet() {
	_flags = CM_GETIDLIST_FILTER_NONE;
}

// Create a filtered set of devices
SetupDeviceInformationSet::SetupDeviceInformationSet(PCWSTR Filter, ULONG Flags) {
	if (Filter != nullptr) {
		_filter = std::wstring(Filter);
	}
	_flags = Flags;
}


std::vector<std::shared_ptr<SetupDevice>> SetupDeviceInformationSet::EnumerateDevices() const
{
	// Create a vector to hold the devices
	std::vector<std::shared_ptr<SetupDevice>> devices;

	// Get the size of the list of devices
	ULONG device_id_list_size = GetDeviceIDListSize();

	// Try to allocate the memory to hold the list of device ids
	PWSTR device_id_list = static_cast<PWSTR>(HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, device_id_list_size * sizeof(WCHAR)));

	if (device_id_list != nullptr) {

		// Read the list of device ids
		CONFIGRET result = CM_Get_Device_ID_List(_filter.c_str(), device_id_list, device_id_list_size, _flags);
		if (result == CR_SUCCESS) {
			PWSTR current_device = nullptr;
			for (current_device = device_id_list; *current_device; current_device += wcslen(current_device) + 1)
			{
				std::shared_ptr<SetupDevice> setup_device = std::make_shared<SetupDevice>(SetupDevice(current_device));
				devices.push_back(setup_device);
			}
		}
		else {
			Error error;
			std::wcout << L"SetupDeviceInformationSet::CM_EnumerateDevices(): " << error.GetErrorMessage() << std::endl;
		}

		// Free the memory
		HeapFree(GetProcessHeap(), 0, device_id_list);
		device_id_list = nullptr;
	}
	else {
		Error error;
		std::wcout << L"SetupDeviceInformationSet::CM_EnumerateDevices(): " << error.GetErrorMessage() << std::endl;
	}

	return devices;
}


ULONG SetupDeviceInformationSet::GetDeviceIDListSize() const {
	ULONG device_id_list_size = 0UL;

	CONFIGRET result = CM_Get_Device_ID_List_Size(&device_id_list_size, nullptr, 0UL);

	if (result == CR_SUCCESS) {
		return device_id_list_size;
	}
	else {
		Error error;
		std::wcout << L"SetupDeviceInformationSet::GetDeviceIDListSize(): " << error.GetErrorMessage() << std::endl;
	}

	return 0UL;
}


// Destructor
SetupDeviceInformationSet::~SetupDeviceInformationSet() = default;