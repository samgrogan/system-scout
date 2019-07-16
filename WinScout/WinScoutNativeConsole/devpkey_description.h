#pragma once

#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>

#include <Windows.h>
#include <cfgmgr32.h>
#include <initguid.h>
#include <Devpropdef.h>

#include "Extensions.h"

namespace WinScoutNativeCore {

	static std::unordered_map<DEVPROPKEY, std::wstring> _devpkey_map({
		{DEVPKEY_NAME, L"Name" },
		{DEVPKEY_Device_DeviceDesc, L"Description" },
		{DEVPKEY_Device_HardwareIds, L"Hardware Ids" },
		{DEVPKEY_Device_CompatibleIds, L"Compatible Ids" },
		{DEVPKEY_Device_Service, L"Service" },
		{DEVPKEY_Device_Class, L"Class" },
		{DEVPKEY_Device_ClassGuid, L"Class Guid" },
		{DEVPKEY_Device_Driver, L"Driver" },
		{DEVPKEY_Device_ConfigFlags, L"Config Flags" },
		{DEVPKEY_Device_Manufacturer, L"Manufacturer" },
		{DEVPKEY_Device_FriendlyName, L"Friendly Name" },
		{DEVPKEY_Device_LocationInfo, L"Location Info" },
		{DEVPKEY_Device_PDOName, L"PDO Name" },
		{DEVPKEY_Device_Capabilities, L"Capabilities" },
		{DEVPKEY_Device_UINumber, L"UI Number" },
		{DEVPKEY_Device_UpperFilters, L"Upper Filters" },
		{DEVPKEY_Device_LowerFilters, L"Lower Filters" },
		{DEVPKEY_Device_BusTypeGuid, L"Bus Type Guid" },
		{DEVPKEY_Device_LegacyBusType, L"Legacy Bus Type" },
		{DEVPKEY_Device_BusNumber, L"Bus Number" },
		{DEVPKEY_Device_EnumeratorName, L"Enumerator Number" },
		{DEVPKEY_Device_Security, L"Security" },
		{DEVPKEY_Device_SecuritySDS, L"Security SDS" },
		{DEVPKEY_Device_DevType, L"Type" },
		{DEVPKEY_Device_Exclusive, L"Exclusive" },
		{DEVPKEY_Device_Characteristics, L"Characteristics" },
		{DEVPKEY_Device_Address, L"Address" },
		{DEVPKEY_Device_UINumberDescFormat, L"UI Number Description Format" },
		{DEVPKEY_Device_PowerData, L"Power Data" },
		{DEVPKEY_Device_RemovalPolicy, L"Removal Policy" },
		{DEVPKEY_Device_RemovalPolicyDefault, L"Removal Policy Default" },
		{DEVPKEY_Device_RemovalPolicyOverride, L"Removal Policy Override" },
		{DEVPKEY_Device_InstallState, L"Install State" },
		{DEVPKEY_Device_LocationPaths, L"Location Paths" },
		{DEVPKEY_Device_BaseContainerId, L"Base Container Id" }
	});

}
