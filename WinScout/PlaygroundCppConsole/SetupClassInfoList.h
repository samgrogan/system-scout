#pragma once

#include <memory>
#include <vector>
#include <iostream>

#include <Windows.h>
#include <SetupAPI.h>

#include "Error.h"
#include "SetupClassInfo.h"

namespace Playground
{
	class SetupClassInfoList
	{
	private:

	public:
		// Constructor
		// Creates a ClassInfoList that includes all classes
		SetupClassInfoList();

		// Returns a list of device interfaces in the set
		std::vector<std::shared_ptr<SetupClassInfo>> EnumerateClasses() const;

		virtual ~SetupClassInfoList();
	};
}
