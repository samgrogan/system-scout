#include "UM_DeviceInterfaceEnumerator.h"

using namespace WinScout::Interop::Unmanaged;

// Constructor
DeviceInterfaceEnumerator::DeviceInterfaceEnumerator() = default;

// Get the list of interfaces for this enumerator
std::vector<std::shared_ptr<DeviceInterface>> DeviceInterfaceEnumerator::EnumerateInterfaces() const {
	std::vector<std::shared_ptr<DeviceInterface>> interfaces;

	//ULONG list_size = 0UL;
	//CONFIGRET result = CM_Get_Device_Interface_List_Size(&list_size, nullptr, 0, CM_GET_DEVICE_INTERFACE_LIST_ALL_DEVICES);

	//std::wcout << L"Found " << list_size << L" interfaces." << std::endl;


	return interfaces;
}

// Destructoor
DeviceInterfaceEnumerator::~DeviceInterfaceEnumerator() {

}