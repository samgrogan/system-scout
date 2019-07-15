#include "DeviceProperty.h"

using namespace WinScoutNativeCore;


DeviceProperty::DeviceProperty(DEVINST DevInst, DEVPROPKEY& PropertyKey)
{
	_device_instance = DevInst;
	_property_key = PropertyKey;
}



// Get the type of the property value
DEVPROPTYPE DeviceProperty::GetType() const {
	return (_property_type & DEVPROP_MASK_TYPE);
}

// Does this property have a value?
bool DeviceProperty::HasValue() const {
	return (_buffer_size > 0);
}

// Does this property have a value of the given type?
bool DeviceProperty::HasValue(DEVPROPTYPE Type) const {
	return (HasValue() && (GetType() == Type));
}


// Get the value as a string
std::wstring DeviceProperty::GetStringValue() const {
	//if (HasValue(DEVPROP_TYPE_STRING)) {

	//	// Allocate the buffer to hold the data
	//	if (_buffer_size > 0) {
	//		BYTE* _buffer = new BYTE[_buffer_size];

	//		SP_DEVINFO_DATA devinfo_data = _device_info_data;
	//		DEVPROPTYPE property_type = _property_type;
	//		DWORD buffer_size = _buffer_size;


	//		if (SetupDiGetDeviceProperty(_device_info_set, &devinfo_data, &_property_key, &property_type, _buffer, _buffer_size, &buffer_size, 0)) {
	//			std::wstring value = std::wstring(reinterpret_cast<const WCHAR*>(_buffer));
	//			delete[] _buffer;
	//			return value;
	//		}
	//		else {
	//			Error last_error;
	//			std::wcout << L"SetupDeviceProperty(): " << last_error.GetErrorMessage() << std::endl;
	//		}
	//	}
	//	else {
	//		Error last_error;
	//		std::wcout << L"SetupDeviceProperty(): " << last_error.GetErrorMessage() << std::endl;
	//	}

	//}
	return std::wstring(L"\0");
}


bool DeviceProperty::operator ==(const DeviceProperty& compare)
{
	//if ((this->GetGuid() == compare.GetGuid()) && (this->GetId() == compare.GetId()))
	//	return true;
	//else
		return false;
}


DeviceProperty::~DeviceProperty() = default;