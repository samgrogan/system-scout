#include "DeviceClassProperty.h"

using namespace WinScoutNativeCore;

DeviceClassProperty::DeviceClassProperty(REFGUID ClassGUID, DEVPROPKEY& PropertyKey) : DevicePropertyBase(PropertyKey)
{
	_class_guid = ClassGUID;
	GetPropertyValue();
}

// Try to read the value of the property
void DeviceClassProperty::GetPropertyValue() {
	// Get the size of the buffer needed to read 
	ULONG buffer_size = 0UL;
	CONFIGRET result = CM_Get_Class_Property(&_class_guid, &_property_key, &_property_type, nullptr, &buffer_size, 0);

	if (buffer_size > 0) {
		// Try to allocate the memory to hold the property
		BYTE* buffer = static_cast<BYTE*>(HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, buffer_size));
		if (buffer != nullptr) {
			// Read the value of the property
			result = CM_Get_Class_Property(&_class_guid, &_property_key, &_property_type, buffer, &buffer_size, 0);

			if (result == CR_SUCCESS) {
				// Parse the value
				ParsePropertyValue(buffer_size, buffer);
			}
			else {
				Error error;
				std::wcout << L"DeviceClassProperty::GetPropertyValue(): " << error.GetErrorMessage() << std::endl;
			}

			// Free the memory
			HeapFree(GetProcessHeap(), 0, buffer);
			buffer = nullptr;
		}
		else {
			Error error;
			std::wcout << L"DeviceClassProperty::GetPropertyValue(): " << error.GetErrorMessage() << std::endl;
		}
	}
}

// Get the GUID of this property
REFGUID DeviceClassProperty::GetGuid() const {
	return _class_guid;
}

// Comparison operator
bool DeviceClassProperty::operator ==(const DeviceClassProperty& compare) {
	if ((this->GetGuid() == compare.GetGuid()) && (this->GetKey() == compare.GetKey()))
		return true;
	else
		return false;
}

DeviceClassProperty::~DeviceClassProperty() = default;

// Output operator
std::wostream& operator<<(std::wostream& wos, DeviceClassProperty& property) {
	property.WriteToStream(wos);
	return wos;
}