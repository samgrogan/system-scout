#include "SetupDeviceInformationSet.h"

using namespace Playground;

// Constructor
// Return all devices
SetupDeviceInformationSet::SetupDeviceInformationSet()
{
	// Initialize with a list of all devices
	_device_info_set = SetupDiGetClassDevs(nullptr, nullptr, nullptr, DIGCF_ALLCLASSES);
}


// Returns a list of devices in the device set
std::vector<std::shared_ptr<SetupDevice>> SetupDeviceInformationSet::EnumerateDevices() const
{
	// Create a vector to hold the devices
	std::vector<std::shared_ptr<SetupDevice>> devices;
	DWORD member_index = 0;
	SP_DEVINFO_DATA devinfo_data;
	devinfo_data.cbSize = sizeof(SP_DEVINFO_DATA);

	// Call get function to get the devices until there are no more devices
	while (SetupDiEnumDeviceInfo(_device_info_set, member_index++, &devinfo_data))
	{
		std::shared_ptr<SetupDevice> device = std::make_shared<SetupDevice>(SetupDevice(_device_info_set, devinfo_data));
		devices.push_back(device);
	}
	// Why did the loop end?
	const Error last_error;
	if (last_error.GetErrorCode() != ERROR_NO_MORE_ITEMS)
	{
		std::wcout << L"SetupDeviceInformationSet::EnumerateDevices() - " << last_error.GetErrorMessage();
	}

	return devices;
}

std::vector<std::shared_ptr<SetupDevice>> SetupDeviceInformationSet::CM_EnumerateDevices() {
	// Create a vector to hold the devices
	std::vector<std::shared_ptr<SetupDevice>> devices;

	// Get the size of the list of devices
	_device_id_list_size = GetDeviceIDListSize();

	std::wcout << L"Device ID list size: " << _device_id_list_size << std::endl;

	// Try to allocate the memory to hold the list of device ids
	_device_id_list = static_cast<PWSTR>(HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, _device_id_list_size * sizeof(WCHAR)));

	if (_device_id_list != nullptr) {

		// Read the list of device ids
		CONFIGRET result = CM_Get_Device_ID_List(NULL, _device_id_list, _device_id_list_size, CM_GETIDLIST_FILTER_NONE);
		if (result == CR_SUCCESS) {
			PWSTR current_device = nullptr;
			UINT count = 0;
			for (current_device = _device_id_list; *current_device; current_device += wcslen(current_device) + 1)
			{
				std::wcout << current_device << std::endl;
				count++;
			}
			std::wcout << L"Found " << count << " devices." << std::endl;
		}
		else {
			Error error;
			std::wcout << L"SetupDeviceInformationSet::CM_EnumerateDevices(): " << error.GetErrorMessage() << std::endl;
		}

		// Free the memory
		HeapFree(GetProcessHeap(), 0, _device_id_list);
		_device_id_list = nullptr;
	}
	else {
		Error error;
		std::wcout << L"SetupDeviceInformationSet::CM_EnumerateDevices(): " << error.GetErrorMessage() << std::endl;
	}

	return devices;
}


// Gets the underlying handle
HDEVINFO SetupDeviceInformationSet::GetHandle() const
{
	return _device_info_set;
}


ULONG SetupDeviceInformationSet::GetDeviceIDListSize() {
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
SetupDeviceInformationSet::~SetupDeviceInformationSet()
{
	// Clean up the handle to the device set
	if (_device_info_set != nullptr)
	{
		if (!SetupDiDestroyDeviceInfoList(_device_info_set))
		{
			Error error;
		}
		_device_info_set = nullptr;
	}
}
