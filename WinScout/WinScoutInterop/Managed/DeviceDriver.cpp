#include "DeviceDriver.h"

using namespace WinScout::Interop;
using namespace Managed;

DeviceDriver::DeviceDriver(std::shared_ptr<Unmanaged::DeviceDriver> UMDriver)
{
	if (UMDriver == nullptr)
	{
		throw gcnew System::Exception("Can't create a managed Driver from a nullptr");
	}
}


// Properties
List<String^>^ DeviceDriver::HardwareIds::get() { return _hardwareIds; }
String^ DeviceDriver::Description::get() { return _description; }
String^ DeviceDriver::Manufacturer::get() { return _manufacturer; }
String^ DeviceDriver::Version::get() { return _version; }
DateTime DeviceDriver::ReleaseDate::get() { return _releaseDate; }
String^ DeviceDriver::InfFile::get() { return _infFile; }