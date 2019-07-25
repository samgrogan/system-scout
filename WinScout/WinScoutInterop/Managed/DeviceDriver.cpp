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
Nullable<DateTime> DeviceDriver::ReleaseDate::get() { return _releaseDate; }
String^ DeviceDriver::InfFile::get() { return _infFile; }


// Populate the properties for this device
void DeviceDriver::PopulateProperties(std::shared_ptr<Unmanaged::DeviceDriver> UMDriver)
{
	PopulateHardwareIds(UMDriver);
	PopulateDescription(UMDriver);
	PopulateManufacturer(UMDriver);
	PopulateVersion(UMDriver);
	PopulateInfFile(UMDriver);
}


void DeviceDriver::PopulateHardwareIds(std::shared_ptr<Unmanaged::DeviceDriver> UMDriver)
{
	_hardwareIds = gcnew List<String^>();

	const wchar_t* device_id = UMDriver->GetDeviceId().c_str();
	if (device_id != nullptr) {
		_hardwareIds->Add(gcnew String(device_id));
	}
}


void DeviceDriver::PopulateDescription(std::shared_ptr<Unmanaged::DeviceDriver> UMDriver)
{
	const wchar_t* description = UMDriver->GetDescription().c_str();
	if (description != nullptr) {
		_description = gcnew String(description);
	}
}


void DeviceDriver::PopulateManufacturer(std::shared_ptr<Unmanaged::DeviceDriver> UMDriver)
{
	const wchar_t* manufacturer = UMDriver->GetProviderName().c_str();
	if (manufacturer != nullptr) {
		_manufacturer = gcnew String(manufacturer);
	}
}


void DeviceDriver::PopulateVersion(std::shared_ptr<Unmanaged::DeviceDriver> UMDriver)
{

}


void DeviceDriver::PopulateReleaseDate(std::shared_ptr<Unmanaged::DeviceDriver> UMDriver)
{

}


void DeviceDriver::PopulateInfFile(std::shared_ptr<Unmanaged::DeviceDriver> UMDriver)
{

}
