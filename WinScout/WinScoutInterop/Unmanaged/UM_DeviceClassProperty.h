#pragma once

#include "UM_DevicePropertyBase.h"

namespace WinScout::Interop::Unmanaged {

	class DeviceClassProperty : public DevicePropertyBase
	{
	private:
		// The GUID of the class this property applies to
		GUID _class_guid{};

		// Try to read the value of the property
		virtual void GetPropertyValue();

	public:
		DeviceClassProperty(REFGUID ClassGUID, DEVPROPKEY& PropertyKey);

		// Get the GUID of this property
		REFGUID GetGuid() const;

		// Comparison operator
		bool operator ==(const DeviceClassProperty& compare);

		~DeviceClassProperty();
	};

}

// Output operator
std::wostream& operator<<(std::wostream& wos, WinScout::Interop::Unmanaged::DeviceClassProperty& property);
