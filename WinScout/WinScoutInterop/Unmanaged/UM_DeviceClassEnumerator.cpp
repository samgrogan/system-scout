#include "UM_DeviceClassEnumerator.h"

using namespace WinScout::Interop::Unmanaged;

DeviceClassEnumerator::DeviceClassEnumerator()
= default;

// Returns a list of device interfaces in the set
std::vector<std::shared_ptr<DeviceClass>> DeviceClassEnumerator::EnumerateClasses() const
{
	// Create a vector to hold the interfaces
	std::vector<std::shared_ptr<DeviceClass>> classes;

	// Loop through and get the list of GUIDs
	ULONG index = 0;
	GUID class_guid;
	while (CM_Enumerate_Classes(index, &class_guid, 0) != CR_NO_SUCH_VALUE) {
		std::shared_ptr<DeviceClass> class_info = std::make_shared<DeviceClass>(DeviceClass(class_guid));
		classes.push_back(class_info);

		index++;
	}

	return classes;
}

DeviceClassEnumerator::~DeviceClassEnumerator()
= default;
