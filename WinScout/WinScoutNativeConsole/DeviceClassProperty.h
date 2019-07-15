#pragma once

#include <Windows.h>
#include <cfgmgr32.h>
#include <SetupAPI.h>
#include <Devpropdef.h>
#include <Devpkey.h>

#include "Error.h"
#include "Extensions.h"

namespace WinScoutNativeCore {

	class DeviceClassProperty
	{
	private:
		// The GUID of the class this property applies to
		GUID _class_guid{};

		// The key to identify this property
		DEVPROPKEY _property_key{};

	public:
		DeviceClassProperty(REFGUID ClassGUID, DEVPROPKEY& PropertyKey);

		// Get the GUID of this property
		REFGUID GetGuid() const;

		// Gets the key of this property
		DEVPROPKEY GetKey() const;

		// Comparison operator
		bool operator ==(const DeviceClassProperty& compare);

		~DeviceClassProperty();
	};

}