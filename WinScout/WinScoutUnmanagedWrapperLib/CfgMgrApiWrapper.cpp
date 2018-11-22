#include "stdafx.h"
#include "CfgMgrApiWrapper.h"


CfgMgrApi::ChgMgrApiWrapper::ChgMgrApiWrapper()
{
}

//CONFIGRET cr = CR_SUCCESS;
//PWSTR DeviceList = nullptr;
//ULONG DeviceListLength = 0;
//PWSTR CurrentDevice;
//DEVINST Devinst;
//WCHAR DeviceDesc[2048];
//WCHAR hardware_id[256];
//DEVPROPTYPE PropertyType;
//const DEVPROPKEY  DEVPKEY_Device_HardwareIds;
//ULONG PropertySize;
//DWORD Index = 0;
//
//cr = CM_Get_Device_ID_List_Size(&DeviceListLength,
//	NULL,
//	CM_GETIDLIST_FILTER_PRESENT);
//
//if (cr != CR_SUCCESS)
//{
//	goto Exit;
//}
//
//DeviceList = (PWSTR)HeapAlloc(GetProcessHeap(),
//	HEAP_ZERO_MEMORY,
//	DeviceListLength * sizeof(WCHAR));
//
//if (DeviceList == NULL) {
//	goto Exit;
//}
//
//cr = CM_Get_Device_ID_List(NULL,
//	DeviceList,
//	DeviceListLength,
//	CM_GETIDLIST_FILTER_PRESENT);
//
//if (cr != CR_SUCCESS)
//{
//	goto Exit;
//}
//
//for (CurrentDevice = DeviceList;
//	*CurrentDevice;
//	CurrentDevice += wcslen(CurrentDevice) + 1)
//{
//
//	// If the list of devices also includes non-present devices,
//	// CM_LOCATE_DEVNODE_PHANTOM should be used in place of
//	// CM_LOCATE_DEVNODE_NORMAL.
//	cr = CM_Locate_DevNode(&Devinst,
//		CurrentDevice,
//		CM_LOCATE_DEVNODE_NORMAL);
//
//	if (cr != CR_SUCCESS)
//	{
//		goto Exit;
//	}
//
//	// Query a property on the device.  For example, the device description.
//	PropertySize = sizeof(DeviceDesc);
//	cr = CM_Get_DevNode_Property(Devinst,
//		&DEVPKEY_Device_HardwareIds,
//		&PropertyType,
//		(PBYTE)hardware_id,
//		&PropertySize,
//		0);
//
//	if (cr != CR_SUCCESS)
//	{
//		Index++;
//		continue;
//	}
//
//	if (PropertyType != DEVPROP_TYPE_STRING)
//	{
//		Index++;
//		continue;
//	}
//
//	Index++;
//}
//
//Exit:
//
//if (DeviceList != NULL)
//{
//	HeapFree(GetProcessHeap(),
//		0,
//		DeviceList);
//}