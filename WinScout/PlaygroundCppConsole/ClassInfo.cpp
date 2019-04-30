#include "ClassInfo.h"

using namespace playground;

/**
 * \brief 
 * \param ClassGuid 
 */

ClassInfo::ClassInfo(REFGUID ClassGuid)
{
	_class_info_guid = ClassGuid;
	std::fill(std::begin(_description), std::end(_description), 0);

	PopulateDescription();
}

// Populate the description of this class info
BOOL ClassInfo::PopulateDescription()
{
	if (SetupDiGetClassDescription(&this->_class_info_guid, this->_description, LINE_LEN, NULL))
	{
		return true;
	}

	Error last_error;
	return false;
}

// Gets the description of this class
LPWSTR ClassInfo::GetDescription()
{
	return _description;
}

// Gets the guid associated with this class
REFGUID ClassInfo::GetClassGuid() const
{
	return _class_info_guid;
}


ClassInfo::~ClassInfo()
= default;
