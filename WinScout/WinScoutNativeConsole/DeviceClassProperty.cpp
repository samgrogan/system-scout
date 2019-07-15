#include "DeviceClassProperty.h"

using namespace WinScoutNativeCore;

DeviceClassProperty::DeviceClassProperty(REFGUID ClassGUID, DEVPROPKEY& PropertyKey)
{
	_class_guid = ClassGUID;
	_property_key = PropertyKey;
}

// Get the GUID of this property
REFGUID DeviceClassProperty::GetGuid() const {
	return _class_guid;
}

// Gets the key of this property
DEVPROPKEY DeviceClassProperty::GetKey() const {
	return _property_key;
}

// Comparison operator
bool DeviceClassProperty::operator ==(const DeviceClassProperty& compare) {
	if ((this->GetGuid() == compare.GetGuid()) && (this->GetKey() == compare.GetKey()))
		return true;
	else
		return false;
}

DeviceClassProperty::~DeviceClassProperty() = default;