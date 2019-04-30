#include "ClassInfo.h"

using namespace playground;

ClassInfo::ClassInfo(REFGUID ClassGuid)
{
	this->_class_info_guid = ClassGuid;
	this->PopulateDescription();
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
LPWSTR ClassInfo::GetDescription() {
	return this->_description;
}

ClassInfo::~ClassInfo()
{
}
