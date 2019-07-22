#pragma once


#include "../Unmanaged/UM_DeviceEnumerator.h"
#include <vcclr.h>

#include "Device.h"


using System::Collections::Generic::List;

namespace WinScout::Interop::Managed {

	public ref class DeviceEnumerator {
	public:
		// Constructors
		DeviceEnumerator();

		// Return the list of compatible devices
		List<Device^>^ EnumerateDevices();
		List<Device^>^ EnumerateDevices(String^ filters, ULONG flags);
	};

}
