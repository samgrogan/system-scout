#include "DeviceClassProperty.h"

using namespace WinScoutNativeCore;

DeviceClassProperty::DeviceClassProperty(REFGUID ClassGUID, DEVPROPKEY& PropertyKey) : DevicePropertyBase(PropertyKey)
{
	_class_guid = ClassGUID;
	GetPropertyValue();
}

// Try to read the value of the property
void DeviceClassProperty::GetPropertyValue() {

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