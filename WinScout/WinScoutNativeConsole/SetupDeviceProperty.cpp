#include "SetupDeviceProperty.h"

using namespace WinScoutNativeCore;


SetupDeviceProperty::SetupDeviceProperty(HDEVINFO DeviceInfoSet, SP_DEVINFO_DATA& DeviceInfoData, DEVPROPKEY& PropertyKey)
{
	_device_info_set = DeviceInfoSet;
	_device_info_data = DeviceInfoData;
	_property_key = PropertyKey;

	// Try to read the value of the property

	// Get the size of the required buffer
	SP_DEVINFO_DATA devinfo_data = _device_info_data;

	// Get the size and type of this property
	SetupDiGetDeviceProperty(_device_info_set, &devinfo_data, &_property_key, &_property_type, nullptr, 0, &_buffer_size, 0);
}


// Get the GUID of this property
REFGUID SetupDeviceProperty::GetGuid() const {
	return _property_key.fmtid;
}


// Gets the Id of this property
DEVPROPID SetupDeviceProperty::GetId() const {
	return _property_key.pid;
}


// Get the type of the property value
DEVPROPTYPE SetupDeviceProperty::GetType() const {
	return (_property_type & DEVPROP_MASK_TYPE);
}


// Does this property have a value?
bool SetupDeviceProperty::HasValue() const {
	return (_buffer_size > 0);
}

// Does this property have a value of the given type?
bool SetupDeviceProperty::HasValue(DEVPROPTYPE Type) const {
	return (HasValue() && (GetType() == Type));
}


// Get the value as a string
std::wstring SetupDeviceProperty::GetStringValue() const {
	if (HasValue(DEVPROP_TYPE_STRING)) {

		// Allocate the buffer to hold the data
		if (_buffer_size > 0) {
			BYTE* _buffer = new BYTE[_buffer_size];

			SP_DEVINFO_DATA devinfo_data = _device_info_data;
			DEVPROPTYPE property_type = _property_type;
			DWORD buffer_size = _buffer_size;


			if (SetupDiGetDeviceProperty(_device_info_set, &devinfo_data, &_property_key, &property_type, _buffer, _buffer_size, &buffer_size, 0)) {
				std::wstring value = std::wstring(reinterpret_cast<const WCHAR*>(_buffer));
				delete[] _buffer;
				return value;
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
	return std::wstring(L"\0");
}


bool SetupDeviceProperty::operator ==(const SetupDeviceProperty& compare)
{
	if ((this->GetGuid() == compare.GetGuid()) && (this->GetId() == compare.GetId()))
		return true;
	else
		return false;
}


SetupDeviceProperty::~SetupDeviceProperty() = default;