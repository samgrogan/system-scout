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
		case DEVPROP_TYPE_SBYTE: std::wcout << L"\t\t\tUnhandled property type: DEVPROP_TYPE_SBYTE" << std::endl; break;
		case DEVPROP_TYPE_BYTE: std::wcout << L"\t\t\tUnhandled property type: DEVPROP_TYPE_BYTE" << std::endl; break;
		case DEVPROP_TYPE_INT16: std::wcout << L"\t\t\tUnhandled property type: DEVPROP_TYPE_INT16" << std::endl; break;
		case DEVPROP_TYPE_UINT16: std::wcout << L"\t\t\tUnhandled property type: DEVPROP_TYPE_UINT16" << std::endl; break;
		case DEVPROP_TYPE_INT32: std::wcout << L"\t\t\tUnhandled property type: DEVPROP_TYPE_INT32" << std::endl; break;
		case DEVPROP_TYPE_UINT32: std::wcout << L"\t\t\tUnhandled property type: DEVPROP_TYPE_UINT32" << std::endl; break;
		case DEVPROP_TYPE_INT64: std::wcout << L"\t\t\tUnhandled property type: DEVPROP_TYPE_INT64" << std::endl; break;
		case DEVPROP_TYPE_UINT64: std::wcout << L"\t\t\tUnhandled property type: DEVPROP_TYPE_UINT64" << std::endl; break;
		case DEVPROP_TYPE_FLOAT: std::wcout << L"\t\t\tUnhandled property type: DEVPROP_TYPE_FLOAT" << std::endl; break;
		case DEVPROP_TYPE_DOUBLE: std::wcout << L"\t\t\tUnhandled property type: DEVPROP_TYPE_DOUBLE" << std::endl; break;
		case DEVPROP_TYPE_DECIMAL: std::wcout << L"\t\t\tUnhandled property type: DEVPROP_TYPE_DECIMAL" << std::endl; break;
		case DEVPROP_TYPE_GUID:
		{
			_value_guid = *(reinterpret_cast<GUID*>(Buffer));			
		}
		break;
		case DEVPROP_TYPE_CURRENCY: std::wcout << L"\t\t\tUnhandled property type: DEVPROP_TYPE_CURRENCY" << std::endl; break;
		case DEVPROP_TYPE_DATE: std::wcout << L"\t\t\tUnhandled property type: DEVPROP_TYPE_DATE" << std::endl; break;
		case DEVPROP_TYPE_FILETIME: std::wcout << L"\t\t\tUnhandled property type: DEVPROP_TYPE_FILETIME" << std::endl; break;
		case DEVPROP_TYPE_BOOLEAN: std::wcout << L"\t\t\tUnhandled property type: DEVPROP_TYPE_BOOLEAN" << std::endl; break;
		case DEVPROP_TYPE_STRING:
		{
			_value_string = std::wstring(reinterpret_cast<const WCHAR*>(Buffer));
		}
		break;
		case DEVPROP_TYPE_STRING_LIST: std::wcout << L"\t\t\tUnhandled property type: DEVPROP_TYPE_STRING_LIST" << std::endl; break;
		case DEVPROP_TYPE_SECURITY_DESCRIPTOR: std::wcout << L"\t\t\tUnhandled property type: DEVPROP_TYPE_SECURITY_DESCRIPTOR" << std::endl; break;
		case DEVPROP_TYPE_SECURITY_DESCRIPTOR_STRING: std::wcout << L"\t\t\tUnhandled property type: DEVPROP_TYPE_SECURITY_DESCRIPTOR_STRING" << std::endl; break;
		case DEVPROP_TYPE_DEVPROPKEY: std::wcout << L"\t\t\tUnhandled property type: DEVPROP_TYPE_DEVPROPKEY" << std::endl; break;
		case DEVPROP_TYPE_DEVPROPTYPE: std::wcout << L"\t\t\tUnhandled property type: DEVPROP_TYPE_DEVPROPTYPE" << std::endl; break;
		case DEVPROP_TYPE_BINARY: std::wcout << L"\t\t\tUnhandled property type: DEVPROP_TYPE_BINARY" << std::endl; break;
		case DEVPROP_TYPE_ERROR: std::wcout << L"\t\t\tUnhandled property type: DEVPROP_TYPE_ERROR" << std::endl; break;
		case DEVPROP_TYPE_NTSTATUS: std::wcout << L"\t\t\tUnhandled property type: DEVPROP_TYPE_NTSTATUS" << std::endl; break;
		case DEVPROP_TYPE_STRING_INDIRECT: std::wcout << L"\t\t\tUnhandled property type: DEVPROP_TYPE_STRING_INDIRECT" << std::endl; break;
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
	if (_property_key == DEVPKEY_NAME) { return L"Name"; }
	if (_property_key == DEVPKEY_Device_DeviceDesc) { return L"Device Description"; }
	if (_property_key == DEVPKEY_Device_HardwareIds) { return L"Hardware Ids"; }
	if (_property_key == DEVPKEY_Device_CompatibleIds) { return L"Compatible Ids"; }
	if (_property_key == DEVPKEY_Device_Service) { return L"Service"; }
	if (_property_key == DEVPKEY_Device_Class) { return L"Class"; }


	return L"Unknown";
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
	case DEVPROP_TYPE_STRING: wos << _value_string; break;
	case DEVPROP_TYPE_GUID: wos << _value_guid; break;
	default: wos << L"Unknown"; break;
	}

	return wos;
}


// Destructor
DevicePropertyBase::~DevicePropertyBase() = default;