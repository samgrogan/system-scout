#include "DeviceEnumerator.h"

using namespace WinScout::Interop::Managed;

// Constructors
DeviceEnumerator::DeviceEnumerator() {

}

// Return the list of compatible devices
List<Device^>^ DeviceEnumerator::EnumerateDevices() {
	List<Device^>^ devices = gcnew List<Device^>();

	return devices;
}