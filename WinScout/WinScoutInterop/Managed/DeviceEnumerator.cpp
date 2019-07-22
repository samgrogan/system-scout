#include "DeviceEnumerator.h"

using namespace WinScout::Interop::Managed;

// Constructors
DeviceEnumerator::DeviceEnumerator()
{

}


// Return the list of compatible devices
List<Device^>^ DeviceEnumerator::EnumerateDevices()
{
	return EnumerateDevices(nullptr, 0UL);
}


List<Device^>^ DeviceEnumerator::EnumerateDevices(String^ filters, ULONG flags) {
	List<Device^>^ devices = gcnew List<Device^>();

	// Create the unmanged enumerator
	pin_ptr<const wchar_t> um_filters = PtrToStringChars(filters);
	WinScout::Interop::Unmanaged::DeviceEnumerator em_enumerator(um_filters, flags);

	// Get the list of devices and create managed copies
	std::vector<std::shared_ptr<WinScout::Interop::Unmanaged::Device>> um_devices = em_enumerator.EnumerateDevices();

	for (auto& um_device : um_devices)
	{
		// Convert the unmanaged class to a managed class
		Device^ device = gcnew Device(um_device);
		devices->Add(device);
	}

	return devices;
}