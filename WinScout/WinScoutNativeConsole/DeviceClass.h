#pragma once

#include <memory>
#include <vector>
#include <unordered_map>

#include <Windows.h>
#include <cfgmgr32.h>

#include "Error.h"
#include "DeviceClassProperty.h"

namespace WinScoutNativeCore
{
	class DeviceClass
	{
	private:
		GUID _class_info_guid{};
		//wchar_t _description[LINE_LEN]{};

		//// Populate the description of this class info
		//BOOL PopulateDescription();

	public:
		// Constructor
		// Initialize the object for the given guid
		DeviceClass(REFGUID ClassGuid);

		// Get the list of properties for this device
		std::unordered_map<DEVPROPKEY, std::shared_ptr<DeviceClassProperty>> EnumerateProperties();

		//// Gets the description of this class
		//LPWSTR GetDescription();

		// Gets the guid associated with this class
		REFGUID GetClassGuid() const;

		virtual ~DeviceClass();
	};
}
