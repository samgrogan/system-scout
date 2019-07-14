#include "DeviceClass.h"

using namespace WinScoutNativeCore;

/**
 * \brief 
 * \param ClassGuid 
 */

DeviceClass::DeviceClass(REFGUID ClassGuid)
{
	_class_info_guid = ClassGuid;
	std::fill(std::begin(_description), std::end(_description), 0);

	PopulateDescription();
}

// Populate the description of this class info
BOOL DeviceClass::PopulateDescription()
{
	if (SetupDiGetClassDescription(&_class_info_guid, _description, LINE_LEN, nullptr))
	{
		return true;
	}

	Error last_error;
	std::wcout << L"SetupClassInfo::PopulateDescription(): " << last_error.GetErrorMessage();

	return false;
}

// Gets the description of this class
LPWSTR DeviceClass::GetDescription()
{
	return _description;
}

// Gets the guid associated with this class
REFGUID DeviceClass::GetClassGuid() const
{
	return _class_info_guid;
}


DeviceClass::~DeviceClass()
= default;
