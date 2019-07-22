#include "Device.h"

using namespace WinScout::Interop::Managed;

// Create a managed device class from an unmanaged device class
Device::Device(std::shared_ptr<WinScout::Interop::Unmanaged::Device> UMDevice) {
	if (UMDevice == nullptr)
	{
		throw ("Can't create a managed Device from a nullptr");
	}

	// Get the list of properties from the umdevice
	std::unordered_map<DEVPROPKEY, std::shared_ptr<Unmanaged::DeviceInstanceProperty>> device_properties = UMDevice->EnumerateProperties();

	// Find the standard properties
	_deviceId = gcnew String(UMDevice->GetDeviceID().c_str());
}

String^ Device::DeviceId::get() {
	return _deviceId;
}