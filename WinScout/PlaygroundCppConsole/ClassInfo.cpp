#include "ClassInfo.h"

using namespace playground;

ClassInfo::ClassInfo(GUID ClassGuid)
{
	this->_class_info_guid = ClassGuid;
	this->GetDescription();
}

// Populate the description of this class info
BOOL ClassInfo::GetDescription()
{
	if (SetupDiGetClassDescription(&this->_class_info_guid, this->_description, LINE_LEN, NULL))
	{
		return true;
	}

	Error last_error;
	return false;
}


ClassInfo::~ClassInfo()
{
}
