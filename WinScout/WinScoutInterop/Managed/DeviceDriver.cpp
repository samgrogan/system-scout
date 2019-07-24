#include "DeviceDriver.h"

using namespace WinScout::Interop;
using namespace Managed;

DeviceDriver::DeviceDriver(std::shared_ptr<Unmanaged::DeviceDriver> UMDriver)
{
	if (UMDriver == nullptr)
	{
		throw gcnew System::Exception("Can't create a managed Driver from a nullptr");
	}

	// Try to populate the properties of the device
	PopulateProperties(UMDriver);
}


// Properties
List<String^>^ DeviceDriver::HardwareIds::get() { return _hardwareIds; }
String^ DeviceDriver::Description::get() { return _description; }
String^ DeviceDriver::Manufacturer::get() { return _manufacturer; }
String^ DeviceDriver::Version::get() { return _version; }
DateTime DeviceDriver::ReleaseDate::get() { return _releaseDate; }
String^ DeviceDriver::InfFile::get() { return _infFile; }


// Populate the properties for this device
void DeviceDriver::PopulateProperties(std::shared_ptr<Unmanaged::DeviceDriver> UMDriver)
{
	_description = gcnew String(UMDriver->GetDescription().c_str());
}
