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
		// Common DEVPKEY used to retrieve the display name for an object.
		{ DEVPKEY_NAME, L"Name" },

		// These DEVPKEYs correspond to the SetupAPI SPDRP_XXX device properties.
		{ DEVPKEY_Device_DeviceDesc, L"Description" },
		{ DEVPKEY_Device_HardwareIds, L"Hardware Ids" },
		{ DEVPKEY_Device_CompatibleIds, L"Compatible Ids" },
		{ DEVPKEY_Device_Service, L"Service" },
		{ DEVPKEY_Device_Class, L"Class" },
		{ DEVPKEY_Device_ClassGuid, L"Class Guid" },
		{ DEVPKEY_Device_Driver, L"Driver" },
		{ DEVPKEY_Device_ConfigFlags, L"Config Flags" },
		{ DEVPKEY_Device_Manufacturer, L"Manufacturer" },
		{ DEVPKEY_Device_FriendlyName, L"Friendly Name" },
		{ DEVPKEY_Device_LocationInfo, L"Location Info" },
		{ DEVPKEY_Device_PDOName, L"PDO Name" },
		{ DEVPKEY_Device_Capabilities, L"Capabilities" },
		{ DEVPKEY_Device_UINumber, L"UI Number" },
		{ DEVPKEY_Device_UpperFilters, L"Upper Filters" },
		{ DEVPKEY_Device_LowerFilters, L"Lower Filters" },
		{ DEVPKEY_Device_BusTypeGuid, L"Bus Type GUID" },
		{ DEVPKEY_Device_LegacyBusType, L"Legacy Bus Type" },
		{ DEVPKEY_Device_BusNumber, L"Bus Number" },
		{ DEVPKEY_Device_EnumeratorName, L"Enumerator Number" },
		{ DEVPKEY_Device_Security, L"Security" },
		{ DEVPKEY_Device_SecuritySDS, L"Security SDS" },
		{ DEVPKEY_Device_DevType, L"Device Type" },
		{ DEVPKEY_Device_Exclusive, L"Exclusive" },
		{ DEVPKEY_Device_Characteristics, L"Characteristics" },
		{ DEVPKEY_Device_Address, L"Address" },
		{ DEVPKEY_Device_UINumberDescFormat, L"UI Number Description Format" },
		{ DEVPKEY_Device_PowerData, L"Power Data" },
		{ DEVPKEY_Device_RemovalPolicy, L"Removal Policy" },
		{ DEVPKEY_Device_RemovalPolicyDefault, L"Removal Policy Default" },
		{ DEVPKEY_Device_RemovalPolicyOverride, L"Removal Policy Override" },
		{ DEVPKEY_Device_InstallState, L"Install State" },
		{ DEVPKEY_Device_LocationPaths, L"Location Paths" },
		{ DEVPKEY_Device_BaseContainerId, L"Base Container Id" },

		// Common DEVPKEY used to retrieve the device instance id associated with devices and device interfaces.
		{ DEVPKEY_Device_InstanceId, L"Instance Id" },

		// These DEVPKEYs correspond to a device's status and problem code.
		{ DEVPKEY_Device_DevNodeStatus, L"Status" },
		{ DEVPKEY_Device_ProblemCode, L"Problem Code" },

		// These DEVPKEYs correspond to a device's relations.
		{ DEVPKEY_Device_EjectionRelations, L"Ejection Relations" },
		{ DEVPKEY_Device_RemovalRelations, L"Removal Relations" },
		{ DEVPKEY_Device_PowerRelations, L"Power Relations" },
		{ DEVPKEY_Device_BusRelations, L"Bus Relations" },
		{ DEVPKEY_Device_Parent, L"Parent" },
		{ DEVPKEY_Device_Children, L"Children" },
		{ DEVPKEY_Device_Siblings, L"Siblings" },
		{ DEVPKEY_Device_TransportRelations, L"Transport Relations" },

		// This DEVPKEY corresponds to a the status code that resulted in a device to be in a problem state.
		{ DEVPKEY_Device_ProblemStatus, L"Problem Status" },

		// These DEVPKEYs are set for the corresponding types of root-enumerated devices.
		{ DEVPKEY_Device_Reported, L"Reported" },
		{ DEVPKEY_Device_Legacy, L"Legacy" },

		// Device Container Id
		{ DEVPKEY_Device_ContainerId, L"Container Id" },
		{ DEVPKEY_Device_InLocalMachineContainer, L"In Local Machine Container" },

		// This DEVPKEY correspond to a device's model.
		{ DEVPKEY_Device_Model, L"Model" },

		// Device Experience related Keys
		{ DEVPKEY_Device_ModelId, L"Model Id" },
		{ DEVPKEY_Device_FriendlyNameAttributes, L"Friendly Name Attributes" },
		{ DEVPKEY_Device_ManufacturerAttributes, L"Manufacturer Attributes" },
		{ DEVPKEY_Device_PresenceNotForDevice, L"Presence Not For Device" },
		{ DEVPKEY_Device_SignalStrength, L"Signal Strength" },
		{ DEVPKEY_Device_IsAssociateableByUserAction, L"Is Associateable By User Action" },
		{ DEVPKEY_Device_ShowInUninstallUI, L"Show In Uninstall UI" },

		// Other Device properties
		{ DEVPKEY_Device_Numa_Proximity_Domain, L"Numa Proximity Domain" },
		{ DEVPKEY_Device_DHP_Rebalance_Policy, L"DHP Rebalance Policy" },
		{ DEVPKEY_Device_Numa_Node, L"Numa Node" },
		{ DEVPKEY_Device_BusReportedDeviceDesc, L"Bus Reported Device Description" },
		{ DEVPKEY_Device_IsPresent, L"Is Present" },
		{ DEVPKEY_Device_HasProblem, L"Has Problem" },
		{ DEVPKEY_Device_ConfigurationId, L"Configuration Id" },
		{ DEVPKEY_Device_ReportedDeviceIdsHash, L"Reported Device Ids Hash" },
		{ DEVPKEY_Device_PhysicalDeviceLocation, L"Physical Device Location" },
		{ DEVPKEY_Device_BiosDeviceName, L"BIOS Device Name" },
		{ DEVPKEY_Device_DriverProblemDesc, L"Driver Problem Description" },
		{ DEVPKEY_Device_DebuggerSafe, L"Debugger Safe" },
		{ DEVPKEY_Device_PostInstallInProgress, L"Post Install In Progress" },
		{ DEVPKEY_Device_Stack, L"Stack" },
		{ DEVPKEY_Device_ExtendedConfigurationIds, L"Extended Configuration Ids" },
		{ DEVPKEY_Device_IsRebootRequired, L"Is Reboot Required" },
		{ DEVPKEY_Device_FirmwareDate, L"Firmware Date" },
		{ DEVPKEY_Device_FirmwareVersion, L"Firmware Version" },
		{ DEVPKEY_Device_FirmwareRevision, L"Firmware Revision" },
		{ DEVPKEY_Device_DependencyProviders, L"Dependency Providers" },
		{ DEVPKEY_Device_DependencyDependents, L"Dependency Dependents" },
		{ DEVPKEY_Device_SoftRestartSupported, L"Soft Restart Supported" },
		{ DEVPKEY_Device_ExtendedAddress, L"Extended Address" },
		{ DEVPKEY_Device_AssignedToGuest, L"Assigned To Guest" },
		{ DEVPKEY_Device_SessionId, L"Session Id" },

		// Device activity timestamp properties
		{ DEVPKEY_Device_InstallDate, L"Install Date" },
		{ DEVPKEY_Device_FirstInstallDate, L"First Install Date" },
		{ DEVPKEY_Device_LastArrivalDate, L"Last Arrival Date" },
		{ DEVPKEY_Device_LastRemovalDate, L"Last Removal Date" },

		// Device driver properties
		{ DEVPKEY_Device_DriverDate, L"Driver Date" },
		{ DEVPKEY_Device_DriverVersion, L"Driver Version" },
		{ DEVPKEY_Device_DriverDesc, L"Driver Description" },
		{ DEVPKEY_Device_DriverInfPath, L"Driver INF Path" },
		{ DEVPKEY_Device_DriverInfSection, L"Driver INF Section" },
		{ DEVPKEY_Device_DriverInfSectionExt, L"Driver INF Section Extended" },
		{ DEVPKEY_Device_MatchingDeviceId, L"Driver Matching Device Id" },
		{ DEVPKEY_Device_DriverProvider, L"Driver Provider" },
		{ DEVPKEY_Device_DriverPropPageProvider, L"Driver Property Page Provider" },
		{ DEVPKEY_Device_DriverCoInstallers, L"Driver Co-Installers" },
		{ DEVPKEY_Device_ResourcePickerTags, L"Resource Picker Tags" },
		{ DEVPKEY_Device_ResourcePickerExceptions, L"Resource Picker Exceptions" },
		{ DEVPKEY_Device_DriverRank, L"Driver Rank" },
		{ DEVPKEY_Device_DriverLogoLevel, L"Driver Logo Level" },

		// Device properties
		{ DEVPKEY_Device_NoConnectSound, L"No Connect Sound" },
		{ DEVPKEY_Device_GenericDriverInstalled, L"Generic Driver Installed" },
		{ DEVPKEY_Device_AdditionalSoftwareRequested, L"Additional Software Requested" },

		// Device safe-removal properties
		{ DEVPKEY_Device_SafeRemovalRequired, L"Safe Removal Required" },
		{ DEVPKEY_Device_SafeRemovalRequiredOverride, L"Safe Removal Required Override" },

		// Device properties
		{ DEVPKEY_DrvPkg_Model, L"Driver Package Model" },
		{ DEVPKEY_DrvPkg_VendorWebSite, L"Driver Package Vendor Website" },
		{ DEVPKEY_DrvPkg_DetailedDescription, L"Driver Package DetailedDescription" },
		{ DEVPKEY_DrvPkg_DocumentationLink, L"Driver Package Documentation Link" },
		{ DEVPKEY_DrvPkg_Icon, L"Driver Package Icon" },
		{ DEVPKEY_DrvPkg_BrandingIcon, L"Driver Package Branding Icon" },
			
		// These DEVPKEYs correspond to the SetupAPI SPCRP_XXX setup class properties.
		{ DEVPKEY_DeviceClass_UpperFilters, L"Upper Filters" },
		{ DEVPKEY_DeviceClass_LowerFilters, L"Lower Filters" },
		{ DEVPKEY_DeviceClass_Security, L"Security" },
		{ DEVPKEY_DeviceClass_SecuritySDS, L"Security SDS" },
		{ DEVPKEY_DeviceClass_DevType, L"Device Type" },
		{ DEVPKEY_DeviceClass_Exclusive, L"Exclusive" },
		{ DEVPKEY_DeviceClass_Characteristics, L"Characteristics" },

		// Device setup class properties
		{ DEVPKEY_DeviceClass_Name, L"Name" },
		{ DEVPKEY_DeviceClass_ClassName, L"Class Name" },
		{ DEVPKEY_DeviceClass_Icon, L"Icon" },
		{ DEVPKEY_DeviceClass_ClassInstaller, L"Class Installer" },
		{ DEVPKEY_DeviceClass_PropPageProvider, L"Property Page Provider" },
		{ DEVPKEY_DeviceClass_NoInstallClass, L"No Install Class" },
		{ DEVPKEY_DeviceClass_NoDisplayClass, L"No Display Class" },
		{ DEVPKEY_DeviceClass_SilentInstall, L"Silent Install" },
		{ DEVPKEY_DeviceClass_NoUseClass, L"No Use Class" },
		{ DEVPKEY_DeviceClass_DefaultService, L"Default Service" },
		{ DEVPKEY_DeviceClass_IconPath, L"Icon Path" },

		// Other Device setup class properties
		{ DEVPKEY_DeviceClass_DHPRebalanceOptOut, L"DHP Rebalance Opt Out" },
		{ DEVPKEY_DeviceClass_ClassCoInstallers, L"Class Co-Installers" },

		// Device interface properties
		{ DEVPKEY_DeviceInterface_FriendlyName, L"FriendlyName" },
		{ DEVPKEY_DeviceInterface_Enabled, L"Enabled" },
		{ DEVPKEY_DeviceInterface_ClassGuid, L"GUID" },
		{ DEVPKEY_DeviceInterface_ReferenceString, L"Reference String" },
		{ DEVPKEY_DeviceInterface_Restricted, L"Restricted" },
		{ DEVPKEY_DeviceInterface_UnrestrictedAppCapabilities, L"Unrestricted App Capabilities" },
		{ DEVPKEY_DeviceInterface_SchematicName, L"Schematic Name" },

		// Device interface class properties
		{ DEVPKEY_DeviceInterfaceClass_DefaultInterface, L"Default Interface" },
		{ DEVPKEY_DeviceInterfaceClass_Name, L"Name" },

		// Device Container Properties
		{ DEVPKEY_DeviceContainer_Address, L"Address" },
		{ DEVPKEY_DeviceContainer_DiscoveryMethod, L"Discovery Method" },
		{ DEVPKEY_DeviceContainer_IsEncrypted, L"Is Encrypted" },
		{ DEVPKEY_DeviceContainer_IsAuthenticated, L"Is Authenticated" },
		{ DEVPKEY_DeviceContainer_IsConnected, L"Is Connected" },
		{ DEVPKEY_DeviceContainer_IsPaired, L"Is Paired" },
		{ DEVPKEY_DeviceContainer_Icon, L"Icon" },
		{ DEVPKEY_DeviceContainer_Version, L"Version" },
		{ DEVPKEY_DeviceContainer_Last_Seen, L"Last_Seen" },
		{ DEVPKEY_DeviceContainer_Last_Connected, L"Last_Connected" },
		{ DEVPKEY_DeviceContainer_IsShowInDisconnectedState, L"Is Show In Disconnected State" },
		{ DEVPKEY_DeviceContainer_IsLocalMachine, L"Is Local Machine" },
		{ DEVPKEY_DeviceContainer_MetadataPath, L"MetadataPath" },
		{ DEVPKEY_DeviceContainer_IsMetadataSearchInProgress, L"Is Metadata Search In Progress" },
		{ DEVPKEY_DeviceContainer_MetadataChecksum, L"Metadata Checksum" },
		{ DEVPKEY_DeviceContainer_IsNotInterestingForDisplay, L"Is Not Interesting For Display" },
		{ DEVPKEY_DeviceContainer_LaunchDeviceStageOnDeviceConnect, L"Launch Device Stage On Device Connect" },
		{ DEVPKEY_DeviceContainer_LaunchDeviceStageFromExplorer, L"Launch Device Stage From Explorer" },
		{ DEVPKEY_DeviceContainer_BaselineExperienceId, L"Baseline Experience Id" },
		{ DEVPKEY_DeviceContainer_IsDeviceUniquelyIdentifiable, L"Is Device Uniquely Identifiable" },
		{ DEVPKEY_DeviceContainer_AssociationArray, L"Association Array" },
		{ DEVPKEY_DeviceContainer_DeviceDescription1, L"Device Description 1" },
		{ DEVPKEY_DeviceContainer_DeviceDescription2, L"Device Description 2" },
		{ DEVPKEY_DeviceContainer_HasProblem, L"Has Problem" },
		{ DEVPKEY_DeviceContainer_IsSharedDevice, L"Is Shared Device" },
		{ DEVPKEY_DeviceContainer_IsNetworkDevice, L"Is Network Device" },
		{ DEVPKEY_DeviceContainer_IsDefaultDevice, L"Is Default Device" },
		{ DEVPKEY_DeviceContainer_MetadataCabinet, L"Metadata Cabinet" },
		{ DEVPKEY_DeviceContainer_RequiresPairingElevation, L"Requires Pairing Elevation" },
		{ DEVPKEY_DeviceContainer_ExperienceId, L"Experience Id" },
		{ DEVPKEY_DeviceContainer_Category, L"Category" },
		{ DEVPKEY_DeviceContainer_Category_Desc_Singular, L"Description Singular" },
		{ DEVPKEY_DeviceContainer_Category_Desc_Plural, L"Description Plural" },
		{ DEVPKEY_DeviceContainer_Category_Icon, L"Category Icon" },
		{ DEVPKEY_DeviceContainer_CategoryGroup_Desc, L"Category Group Description" },
		{ DEVPKEY_DeviceContainer_CategoryGroup_Icon, L"Category Group Icon" },
		{ DEVPKEY_DeviceContainer_PrimaryCategory, L"Primary Category" },
		{ DEVPKEY_DeviceContainer_UnpairUninstall, L"Unpair Uninstall" },
		{ DEVPKEY_DeviceContainer_RequiresUninstallElevation, L"Requires Uninstall Elevation" },
		{ DEVPKEY_DeviceContainer_DeviceFunctionSubRank, L"Device Function Sub-Rank" },
		{ DEVPKEY_DeviceContainer_AlwaysShowDeviceAsConnected, L"Always Show Device As Connected" },
		{ DEVPKEY_DeviceContainer_ConfigFlags, L"Config Flags" },
		{ DEVPKEY_DeviceContainer_PrivilegedPackageFamilyNames, L"Privileged Package Family Names" },
		{ DEVPKEY_DeviceContainer_CustomPrivilegedPackageFamilyNames, L"Custom Privileged Package Family Names" },
		{ DEVPKEY_DeviceContainer_IsRebootRequired, L"IsRebootRequired" },
		{ DEVPKEY_DeviceContainer_FriendlyName, L"Friendly Name" },
		{ DEVPKEY_DeviceContainer_Manufacturer, L"Manufacturer" },
		{ DEVPKEY_DeviceContainer_ModelName, L"Model Name" },
		{ DEVPKEY_DeviceContainer_ModelNumber, L"Model Number" },
		{ DEVPKEY_DeviceContainer_InstallInProgress, L"Install In Progress" },

		// DevQuery properties
		{ DEVPKEY_DevQuery_ObjectType, L"Object Type" },

		});

}
