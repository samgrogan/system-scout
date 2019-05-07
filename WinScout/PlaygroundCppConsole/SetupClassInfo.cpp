#include "SetupClassInfo.h"

using namespace playground;

/**
 * \brief 
 * \param ClassGuid 
 */

SetupClassInfo::SetupClassInfo(REFGUID ClassGuid)
{
	_class_info_guid = ClassGuid;
	std::fill(std::begin(_description), std::end(_description), 0);

	PopulateDescription();
}

// Populate the description of this class info
BOOL SetupClassInfo::PopulateDescription()
{
	if (SetupDiGetClassDescription(&_class_info_guid, _description, LINE_LEN, nullptr))
	{
		return true;
	}

	Error last_error;
	return false;
}

// Gets the description of this class
LPWSTR SetupClassInfo::GetDescription()
{
	return _description;
}

// Gets the guid associated with this class
REFGUID SetupClassInfo::GetClassGuid() const
{
	return _class_info_guid;
}


SetupClassInfo::~SetupClassInfo()
= default;
