#include "UM_DeviceDriverEnumerator.h"

using namespace WinScout::Interop::Unmanaged;

// Constructor
DeviceDriverEnumerator::DeviceDriverEnumerator() = default;

// Enumerate the list of drivers installed on the system
std::vector<std::shared_ptr<DeviceDriver>> DeviceDriverEnumerator::EnumerateDrivers() const
{
	std::vector<std::shared_ptr<DeviceDriver>> drivers;

	// How much memory is needed to hold the list
	DWORD list_size = 0;
	EnumDeviceDrivers(nullptr, 0, &list_size);

	if (list_size > 0) {
		DWORD driver_count = list_size / sizeof(LPVOID);

		// Allocate the memory to hold the list of drivers
		LPVOID* driver_list = static_cast<LPVOID*>(HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, list_size));

		if (driver_list != nullptr) {
			// Read the list of device driver pointers
			if (EnumDeviceDrivers(driver_list, list_size, &list_size))
			{
				for (DWORD driver_index = 0; driver_index < driver_count; driver_index++)
				{
					std::shared_ptr<DeviceDriver> driver = std::make_shared<DeviceDriver>(DeviceDriver(driver_list[driver_index]));
					drivers.push_back(driver);
				}
			}

			// Free the memory
			HeapFree(GetProcessHeap(), 0, driver_list);
			driver_list = nullptr;
		}
	}

	return drivers;
}

// Destructor
DeviceDriverEnumerator::~DeviceDriverEnumerator() = default;