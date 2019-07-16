#include "DeviceInstanceProperty.h"

using namespace WinScoutNativeCore;

DeviceInstanceProperty::DeviceInstanceProperty(DEVINST DevInst, DEVPROPKEY& PropertyKey) : DevicePropertyBase(PropertyKey)
{
	_device_instance = DevInst;
	GetPropertyValue();
}


// Gets th device instance the this property belongs to
DEVINST DeviceInstanceProperty::GetDevInst() const {
	return _device_instance;
}


// Try to read the value of the property
void DeviceInstanceProperty::GetPropertyValue() {
	// Get the size of the buffer needed to read 
	ULONG buffer_size = 0UL;
	CONFIGRET result = CM_Get_DevNode_Property(_device_instance, &_property_key, &_property_type, nullptr, &buffer_size, 0);

	if (buffer_size > 0) {
		// Try to allocate the memory to hold the property
		BYTE* buffer = static_cast<BYTE*>(HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, buffer_size));
		if (buffer != nullptr) {
			// Read the value of the property
			result = CM_Get_DevNode_Property(_device_instance, &_property_key, &_property_type, buffer, &buffer_size, 0);

			if (result == CR_SUCCESS) {
				// Parse the value
				ParsePropertyValue(buffer_size, buffer);
			}
			else {
				Error error;
				std::wcout << L"DeviceInstanceProperty::GetPropertyValue: " << error.GetErrorMessage() << std::endl;
			}

			// Free the memory
			HeapFree(GetProcessHeap(), 0, buffer);
			buffer = nullptr;
		}
		else {
			Error error;
			std::wcout << L"DeviceInstanceProperty::GetPropertyValue: " << error.GetErrorMessage() << std::endl;
		}
	}
}


bool DeviceInstanceProperty::operator ==(const DeviceInstanceProperty& compare) const
{
	if ((GetDevInst() == compare.GetDevInst()) && (this->GetKey() == compare.GetKey()))
		return true;
	else
		return false;
}


DeviceInstanceProperty::~DeviceInstanceProperty() = default;


// Output operator
std::wostream& operator<<(std::wostream& wos, DeviceInstanceProperty& property) {
	property.WriteToStream(wos);
	return wos;
}