#pragma once

#include <memory>
#include <vector>

#include <Windows.h>
#include <SetupAPI.h>

#include "Error.h"

namespace playground {

class ClassInfo
{
	private:
		GUID _class_info_guid{};
		wchar_t _description[LINE_LEN]{};

		// Populate the description of this class info
		BOOL PopulateDescription();

	public:
		// Constructor
		// Initialize the object for the given guid
		ClassInfo(REFGUID ClassGuid);

		// Gets the description of this class
		LPWSTR GetDescription();

		// Gets the guid associated with this class
		REFGUID GetClassGuid() const;

		virtual ~ClassInfo();
	};

}
