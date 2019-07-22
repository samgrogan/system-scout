#include "Device.h"

using namespace WinScout::Interop::Managed;

// Create a managed device class from an unmanaged device class
Device::Device(std::shared_ptr<WinScout::Interop::Unmanaged::Device> UMDevice) {


}

String^ Device::DeviceId::get() {
	return _deviceId;
}