#include "UM_DeviceDriver.h"

using namespace WinScout::Interop::Unmanaged;

// Constructor

// Create a new driver based on the image base name
DeviceDriver::DeviceDriver(LPVOID ImageBase) {
	_image_base = ImageBase;
}


// Create a new driver class based on the structure data
DeviceDriver::DeviceDriver(const std::wstring& DeviceId, SP_DRVINFO_DATA& DriverInfoData)
{
	_device_id = DeviceId;
	_drvinfo_data = DriverInfoData;
}


// Gets ID of the device this driver is attached to
const std::wstring DeviceDriver::GetDeviceId() const
{
	return _device_id;
}


// Gets the description of the driver/device
const std::wstring DeviceDriver::GetDescription() const
{
	return _drvinfo_data.Description;
}


// Get the provider
const std::wstring DeviceDriver::GetProviderName() const
{
	return _drvinfo_data.ProviderName;
}


// Gets the file name of the driver
const std::wstring DeviceDriver::GetFileName() const
{
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
