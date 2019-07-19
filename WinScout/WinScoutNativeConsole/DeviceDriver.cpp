#include "DeviceDriver.h"

using namespace WinScoutNativeCore;

// Constructor

// Create a new driver based on the image base name
DeviceDriver::DeviceDriver(LPVOID ImageBase) {
	_image_base = ImageBase;
}


// Create a new driver class based on the structure data
DeviceDriver::DeviceDriver(const SP_DRVINFO_DATA& DriverInfoData)
{
	_drvinfo_data = DriverInfoData;
}


// Gets the description of the driver/device
std::wstring DeviceDriver::GetDescription()
{
	return _drvinfo_data.Description;
}


// Gets the name of the manufacturer
std::wstring DeviceDriver::GetMfgName()
{
	return _drvinfo_data.MfgName;
}


// Get the provider
std::wstring DeviceDriver::GetProviderName()
{
	return _drvinfo_data.ProviderName;
}


// Gets the file name of the driver
std::wstring DeviceDriver::GetFileName() {
	std::wstring filename{};
	
	// Gets the size of the file name
	wchar_t filename_buffer[MAX_PATH];

	DWORD filename_length = GetDeviceDriverFileName(_image_base, filename_buffer, MAX_PATH);
	if (filename_length > 0) {
		filename = std::wstring(filename_buffer);
	}

	return filename;
}


DeviceDriver::~DeviceDriver() = default;
