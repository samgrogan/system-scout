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
		case DEVPROP_TYPE_EMPTY: break;
		case DEVPROP_TYPE_NULL: break;
		case DEVPROP_TYPE_SBYTE: _value_sbyte = *(reinterpret_cast<INT8*>(Buffer)); break;
		case DEVPROP_TYPE_BYTE: _value_byte = *(reinterpret_cast<BYTE*>(Buffer)); break;
		case DEVPROP_TYPE_INT16: _value_int16 = *(reinterpret_cast<INT16*>(Buffer)); break;
		case DEVPROP_TYPE_UINT16: _value_uint16 = *(reinterpret_cast<UINT16*>(Buffer)); break;
		case DEVPROP_TYPE_INT32: _value_int32 = *(reinterpret_cast<INT32*>(Buffer)); break;
		case DEVPROP_TYPE_UINT32: _value_uint32 = *(reinterpret_cast<UINT32*>(Buffer)); break;
		case DEVPROP_TYPE_INT64: _value_int64 = *(reinterpret_cast<INT64*>(Buffer)); break;
		case DEVPROP_TYPE_UINT64: _value_uint64 = *(reinterpret_cast<UINT64*>(Buffer)); break;
		case DEVPROP_TYPE_FLOAT: _value_float = *(reinterpret_cast<FLOAT*>(Buffer)); break;
		case DEVPROP_TYPE_DOUBLE: _value_double = *(reinterpret_cast<DOUBLE*>(Buffer)); break;
		case DEVPROP_TYPE_DECIMAL: _value_decimal = *(reinterpret_cast<DECIMAL*>(Buffer)); break;
		case DEVPROP_TYPE_GUID: _value_guid = *(reinterpret_cast<GUID*>(Buffer)); break;
		case DEVPROP_TYPE_CURRENCY: _value_currency = *(reinterpret_cast<CURRENCY*>(Buffer)); break;
		case DEVPROP_TYPE_DATE: _value_date = *(reinterpret_cast<DATE*>(Buffer)); break;
		case DEVPROP_TYPE_FILETIME: _value_filetime = *(reinterpret_cast<FILETIME*>(Buffer)); break;
		case DEVPROP_TYPE_BOOLEAN: _value_boolean = *(reinterpret_cast<BOOLEAN*>(Buffer)); break;
		case DEVPROP_TYPE_STRING: _value_string = std::wstring(reinterpret_cast<const WCHAR*>(Buffer)); break;
		case DEVPROP_TYPE_STRING_LIST: std::wcout << L"\t\t\tUnhandled property type: DEVPROP_TYPE_STRING_LIST (" << PropertyBufferSize << ")" << std::endl; break;
		case DEVPROP_TYPE_SECURITY_DESCRIPTOR: _value_security_descriptor = *(reinterpret_cast<const SECURITY_DESCRIPTOR*>(Buffer)); break;
		case DEVPROP_TYPE_SECURITY_DESCRIPTOR_STRING: std::wcout << L"\t\t\tUnhandled property type: DEVPROP_TYPE_SECURITY_DESCRIPTOR_STRING (" << PropertyBufferSize << ")" << std::endl; break;
		case DEVPROP_TYPE_DEVPROPKEY: std::wcout << L"\t\t\tUnhandled property type: DEVPROP_TYPE_DEVPROPKEY (" << PropertyBufferSize << ")" << std::endl; break;
		case DEVPROP_TYPE_DEVPROPTYPE: std::wcout << L"\t\t\tUnhandled property type: DEVPROP_TYPE_DEVPROPTYPE (" << PropertyBufferSize << ")" << std::endl; break;
		case DEVPROP_TYPE_BINARY: std::wcout << L"\t\t\tUnhandled property type: DEVPROP_TYPE_BINARY (" << PropertyBufferSize << ")" << std::endl; break;
		case DEVPROP_TYPE_ERROR: _value_error = *(reinterpret_cast<UINT32*>(Buffer)); break;
		case DEVPROP_TYPE_NTSTATUS: _value_ntstatus = *(reinterpret_cast<NTSTATUS*>(Buffer)); break;
		case DEVPROP_TYPE_STRING_INDIRECT: std::wcout << L"\t\t\tUnhandled property type: DEVPROP_TYPE_STRING_INDIRECT (" << PropertyBufferSize << ")" << std::endl; break;
		default:
			std::wcout << L"\t\t\tUnhandled property type: " << base_type << std::endl;
			break;
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


// Gets the description of this property
std::wstring DevicePropertyBase::GetDescription() const {
	// Look up the key in the global table
	if (::_devpkey_map.count(_property_key) > 0) {
		return ::_devpkey_map[_property_key];
	}

	// If the description isn't found, return the guid and id
	return (std::to_wstring(_property_key));
}


// Get the string value of this property
std::wstring DevicePropertyBase::GetStringValue() const {
	return _value_string;
}


// Get the GUID value of this property
REFGUID DevicePropertyBase::GetGuidValue() const {
	return _value_guid;
}


// Output the value to the given stream
std::wostream& DevicePropertyBase::WriteToStream(std::wostream& wos) const {
	// What type of property is this?
	DEVPROPTYPE base_type = GetType();

	switch (base_type) {
	case DEVPROP_TYPE_EMPTY: break;
	case DEVPROP_TYPE_NULL: break;
	case DEVPROP_TYPE_SBYTE: wos << _value_sbyte; break;
	case DEVPROP_TYPE_BYTE: wos << _value_byte; break;
	case DEVPROP_TYPE_INT16: wos << _value_int16; break;
	case DEVPROP_TYPE_UINT16: wos << _value_uint16; break;
	case DEVPROP_TYPE_INT32: wos << _value_int32; break;
	case DEVPROP_TYPE_UINT32: wos << _value_uint32; break;
	case DEVPROP_TYPE_INT64: wos << _value_int64; break;
	case DEVPROP_TYPE_UINT64: wos << _value_uint64; break;
	case DEVPROP_TYPE_FLOAT: wos << _value_float; break;
	case DEVPROP_TYPE_DOUBLE: wos << _value_double; break;
	// case DEVPROP_TYPE_DECIMAL: wos << _value_decimal; break;
	case DEVPROP_TYPE_GUID: wos << _value_guid; break;
	// case DEVPROP_TYPE_CURRENCY: wos << _value_currency; break;
	case DEVPROP_TYPE_DATE: wos << _value_date; break;
	// case DEVPROP_TYPE_FILETIME: wos << _value_filetime; break;
	case DEVPROP_TYPE_BOOLEAN: wos << _value_boolean; break;
	case DEVPROP_TYPE_STRING: wos << _value_string; break;
	//case DEVPROP_TYPE_STRING_LIST: break;
	//case DEVPROP_TYPE_SECURITY_DESCRIPTOR: break;
	//case DEVPROP_TYPE_SECURITY_DESCRIPTOR_STRING: break;
	//case DEVPROP_TYPE_DEVPROPKEY: break;
	//case DEVPROP_TYPE_DEVPROPTYPE: break;
	//case DEVPROP_TYPE_BINARY: break;
	case DEVPROP_TYPE_ERROR: wos << _value_error; break;
	case DEVPROP_TYPE_NTSTATUS: wos << _value_ntstatus; break;
	//case DEVPROP_TYPE_STRING_INDIRECT: break;

	default: wos << L"Unknown"; break;
	}

	return wos;
}


// Destructor
DevicePropertyBase::~DevicePropertyBase() = default;