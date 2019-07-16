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
	if (_property_key == DEVPKEY_NAME) { return L"Name"; }
	if (_property_key == DEVPKEY_Device_DeviceDesc) { return L"Description"; }
	if (_property_key == DEVPKEY_Device_HardwareIds) { return L"Hardware Ids"; }
	if (_property_key == DEVPKEY_Device_CompatibleIds) { return L"Compatible Ids"; }
	if (_property_key == DEVPKEY_Device_Service) { return L"Service"; }
	if (_property_key == DEVPKEY_Device_Class) { return L"Class"; }
	if (_property_key == DEVPKEY_Device_ClassGuid) { return L"Class Guid"; }
	if (_property_key == DEVPKEY_Device_Driver) { return L"Driver"; }
	if (_property_key == DEVPKEY_Device_ConfigFlags) { return L"Config Flags"; }
	if (_property_key == DEVPKEY_Device_Manufacturer) { return L"Manufacturer"; }
	if (_property_key == DEVPKEY_Device_FriendlyName) { return L"Friendly Name"; }
	if (_property_key == DEVPKEY_Device_LocationInfo) { return L"Location Info"; }
	if (_property_key == DEVPKEY_Device_PDOName) { return L"PDO Name"; }
	if (_property_key == DEVPKEY_Device_Capabilities) { return L"Capabilities"; }
	if (_property_key == DEVPKEY_Device_UINumber) { return L"UI Number"; }
	if (_property_key == DEVPKEY_Device_UpperFilters) { return L"Upper Filters"; }
	if (_property_key == DEVPKEY_Device_LowerFilters) { return L"Lower Filters"; }
	if (_property_key == DEVPKEY_Device_BusTypeGuid) { return L"Bus Type Guid"; }
	if (_property_key == DEVPKEY_Device_LegacyBusType) { return L"Legacy Bus Type"; }
	if (_property_key == DEVPKEY_Device_BusNumber) { return L"Bus Number"; }
	if (_property_key == DEVPKEY_Device_EnumeratorName) { return L"Enumerator Number"; }
	if (_property_key == DEVPKEY_Device_Security) { return L"Security"; }
	if (_property_key == DEVPKEY_Device_SecuritySDS) { return L"Security SDS"; }
	if (_property_key == DEVPKEY_Device_DevType) { return L"Type"; }
	if (_property_key == DEVPKEY_Device_Exclusive) { return L"Exclusive"; }
	if (_property_key == DEVPKEY_Device_Characteristics) { return L"Characteristics"; }
	if (_property_key == DEVPKEY_Device_Address) { return L"Address"; }
	if (_property_key == DEVPKEY_Device_UINumberDescFormat) { return L"UI Number Description Format"; }
	if (_property_key == DEVPKEY_Device_PowerData) { return L"Power Data"; }
	if (_property_key == DEVPKEY_Device_RemovalPolicy) { return L"Removal Policy"; }
	if (_property_key == DEVPKEY_Device_RemovalPolicyDefault) { return L"Removal Policy Default"; }
	if (_property_key == DEVPKEY_Device_RemovalPolicyOverride) { return L"Removal Policy Override"; }
	if (_property_key == DEVPKEY_Device_InstallState) { return L"Install State"; }
	if (_property_key == DEVPKEY_Device_LocationPaths) { return L"Location Paths"; }
	if (_property_key == DEVPKEY_Device_BaseContainerId) { return L"Base Container Id"; }


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