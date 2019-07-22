#pragma once


#include "../Unmanaged/UM_Device.h"

using namespace System;

namespace WinScout::Interop::Managed {

	public ref class Device
	{
	private:
		// The ID of this device
		String^ _deviceId;

	public:
		// Properties
		property String^ DeviceId {
			String^ get();
		}

		// Create a managed device class from an unmanaged device class
		Device(std::shared_ptr<WinScout::Interop::Unmanaged::Device> UMDevice);
	};

}

