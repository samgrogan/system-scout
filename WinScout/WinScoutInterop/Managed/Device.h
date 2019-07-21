#pragma once


#include "../Unmanaged/UM_Device.h"

using namespace System;

namespace WinScout::Interop::Managed {

	public ref class Device
	{
	private:
		String^ _DeviceId;

	public:
		// Create a managed device class from an unmanaged device class
		Device(std::shared_ptr<WinScout::Interop::Unmanaged::Device> UMDevice);

		property String^ DeviceId {
			String^ get();
		}

	};

}

