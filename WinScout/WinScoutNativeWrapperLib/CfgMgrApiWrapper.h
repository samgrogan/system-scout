#pragma once
#include <windows.h>
#include <cfgmgr32.h>

namespace WinScoutNativeWrapper {

	public enum class CfgMgrReturnValue : int {
		Success = CR_SUCCESS,
		Default = CR_DEFAULT,
		OutOfMemory = CR_OUT_OF_MEMORY,
		InvalidPointer = CR_INVALID_POINTER,
		InvalidFlag = CR_INVALID_FLAG,
		InvalidDevOrInstanceNode = CR_INVALID_DEVNODE,
		InvalidResDes = CR_INVALID_RES_DES,
		InvalidLogicalConfiguration = CR_INVALID_LOG_CONF,
		InvalidArbitrator = CR_INVALID_ARBITRATOR,
		InvalidNodeList = CR_INVALID_NODELIST,
		DevOrInstanceNodeHasReqs = CR_DEVNODE_HAS_REQS,
		InvalidResourceID = CR_INVALID_RESOURCEID,
		DlvxdNotFound = CR_DLVXD_NOT_FOUND,
		NoSuchDevNodeOrInstance = CR_NO_SUCH_DEVNODE,
		NoMoreLogConf = CR_NO_MORE_LOG_CONF,
		NoMoreResDes = CR_NO_MORE_RES_DES,
		AlreadySuchDevNodeOrInstance = CR_ALREADY_SUCH_DEVNODE,
		InvalidRangeList = CR_INVALID_RANGE_LIST,
		InvalidRange = CR_INVALID_RANGE,
		Failure = CR_FAILURE,
		NoSuchLogicalDev = CR_NO_SUCH_LOGICAL_DEV,
		CreateBlocked = CR_CREATE_BLOCKED,
		NotSystemVm = CR_NOT_SYSTEM_VM,
		RemoveVetoed = CR_REMOVE_VETOED,
		ApmVetoed = CR_APM_VETOED,
		InvalidLoadType = CR_INVALID_LOAD_TYPE,
		BufferSmall = CR_BUFFER_SMALL,
		NoArbitrator = CR_NO_ARBITRATOR,
		NoRegistryHandle = CR_NO_REGISTRY_HANDLE,
		RegistryError = CR_REGISTRY_ERROR,
		InvalidDeviceID = CR_INVALID_DEVICE_ID,
		InvalidData = CR_INVALID_DATA,
		InvalidApi = CR_INVALID_API,
		DevLoaderNotReday = CR_DEVLOADER_NOT_READY,
		NeedRestart = CR_NEED_RESTART,
		NoMoreHwProfiles = CR_NO_MORE_HW_PROFILES,
		DeviceNotThere = CR_DEVICE_NOT_THERE,
		NoSuchValue = CR_NO_SUCH_VALUE,
		WrongType = CR_WRONG_TYPE,
		InvalidPriority = CR_INVALID_PRIORITY,
		NotDisableable = CR_NOT_DISABLEABLE,
		FreeResources = CR_FREE_RESOURCES,
		QueryVetoed = CR_QUERY_VETOED,
		CantShareIrg = CR_CANT_SHARE_IRQ,
		NoDependent = CR_NO_DEPENDENT,
		SameResources = CR_SAME_RESOURCES,
		NoSuchRegistryKey = CR_NO_SUCH_REGISTRY_KEY,
		InvalidMachineName = CR_INVALID_MACHINENAME,
		RemoteCommFailure = CR_REMOTE_COMM_FAILURE,
		MachineUnavailable = CR_MACHINE_UNAVAILABLE,
		NoCmServices = CR_NO_CM_SERVICES,
		AccessDenied = CR_ACCESS_DENIED,
		CallNotImplemented = CR_CALL_NOT_IMPLEMENTED,
		InvalidProperty = CR_INVALID_PROPERTY,
		DeviceInterfaceActive = CR_DEVICE_INTERFACE_ACTIVE,
		NoSuchDeviceInterface = CR_NO_SUCH_DEVICE_INTERFACE,
		InvalidReferenceString = CR_INVALID_REFERENCE_STRING,
		InvalidConflictList = CR_INVALID_CONFLICT_LIST,
		InvalidIndex = CR_INVALID_INDEX,
		InvalidStructureSize = CR_INVALID_STRUCTURE_SIZE
	};

	ref class CfgMgrApiWrapper {
	public:
		CfgMgrApiWrapper();
		int GetDeviceIDListSize();
	};

}
