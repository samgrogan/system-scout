#include "DevicePropertyBase.h"

using namespace WinScoutNativeCore;

// Constructor
DevicePropertyBase::DevicePropertyBase(DEVPROPKEY& PropertyKey) {
	_property_key = PropertyKey;
}

// Parse the property value and convert to the underlying type
void DevicePropertyBase::ParsePropertyValue(ULONG PropertyBufferSize, PBYTE Buffer) {
	if (Buffer != nullptr && PropertyBufferSize > 0) {
		// What type of property is this?
		DEVPROPTYPE base_type = GetType();

		switch (base_type) {
		case DEVPROP_TYPE_STRING:
		{
			_value_string = std::wstring(reinterpret_cast<const WCHAR*>(Buffer));
		}
		break;
		default:
			std::wcout << L"\t\t\tUnhandled property type: " << base_type << std::endl;
		}
	}
}

// Gets the key of this property
DEVPROPKEY DevicePropertyBase::GetKey() const {
	return _property_key;
}


// Get the type of the property value
DEVPROPTYPE DevicePropertyBase::GetType() const {
	return (_property_type & DEVPROP_MASK_TYPE);
}

// Get the string value of this property
std::wstring DevicePropertyBase::GetStringValue() const {
	return _value_string;
}

// Destructor
DevicePropertyBase::~DevicePropertyBase() = default;