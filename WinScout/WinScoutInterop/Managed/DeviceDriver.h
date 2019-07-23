#pragma once

#include "../Unmanaged/UM_DeviceDriver.h"

namespace WinScout::Interop::Managed {
	public ref class DeviceDriver
	{
	private:
	public:
		DeviceDriver(std::shared_ptr<Unmanaged::DeviceDriver> UMDriver);
	};
}
