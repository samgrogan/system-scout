#include "SetupDeviceProperty.h"

using namespace Playground;


SetupDeviceProperty::SetupDeviceProperty(HDEVINFO DeviceInfoSet, SP_DEVINFO_DATA& DeviceInfoData, DEVPROPKEY& PropertyKey)
{
	_device_info_set = DeviceInfoSet;
	_device_info_data = DeviceInfoData;
	_property_key = PropertyKey;

	// Try to read the value of the property

	// Get the size of the required buffer
	SP_DEVINFO_DATA devinfo_data = _device_info_data;
	DEVPROPTYPE devproptype(0);
	DWORD required_size(0);

	SetupDiGetDeviceProperty(_device_info_set, &devinfo_data, &_property_key, &devproptype, nullptr, 0, &required_size, 0);

	// Allocate the buffer to hold the data
	if (required_size > 0) {
		_buffer = new BYTE[required_size];

		if (SetupDiGetDeviceProperty(_device_info_set, &devinfo_data, &_property_key, &devproptype, _buffer, required_size, &required_size, 0)) {

		}
		else {
			Error last_error;
			std::wcout << L"SetupDeviceProperty(): " << last_error.GetErrorMessage() << std::endl;
		}
	}
	else {
		Error last_error;
		std::wcout << L"SetupDeviceProperty(): " << last_error.GetErrorMessage() << std::endl;
	}
}

// Does this property have a value?
bool SetupDeviceProperty::HasValue() {
	return (_buffer != nullptr);
}


// Get the value as a string
std::wstring SetupDeviceProperty::GetValue() {
	if (HasValue()) {
		return std::wstring(reinterpret_cast<wchar_t*>(_buffer));
	}
	return std::wstring(L"\0");
}


SetupDeviceProperty::~SetupDeviceProperty() {
	//if (_buffer != nullptr) {
	//	delete[] _buffer;
	//	_buffer = nullptr;
	//}
}