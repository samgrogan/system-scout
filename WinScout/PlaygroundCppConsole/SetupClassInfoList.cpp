#include "SetupClassInfoList.h"

using namespace playground;

SetupClassInfoList::SetupClassInfoList()
= default;

// Returns a list of device interfaces in the set
std::vector<std::shared_ptr<SetupClassInfo>> SetupClassInfoList::EnumerateClasses() const
{
	// Create a vector to hold the interfaces
	std::vector<std::shared_ptr<SetupClassInfo>> classes;

	// Determine how much space we need to store the list of class guids
	DWORD required_size = 0;
	SetupDiBuildClassInfoList(0, nullptr, 0, &required_size);
	// If there are any GUIDs, allocate space to hold them
	if (required_size > 0)
	{
		GUID* class_guid_list = new GUID[required_size];

		if (SetupDiBuildClassInfoList(0, class_guid_list, required_size, &required_size))
		{
			for (DWORD index = 0; index < required_size; index++)
			{
				std::shared_ptr<SetupClassInfo> class_info = std::make_shared<SetupClassInfo>(SetupClassInfo(class_guid_list[index]));
				classes.push_back(class_info);
			}
		}
		else
		{
			Error last_error;
		}

		// Clean up
		delete[] class_guid_list;
	}

	return classes;
}

SetupClassInfoList::~SetupClassInfoList()
= default;
