#pragma once

#include <memory>
#include <vector>
#include <iostream>

#include <Windows.h>
#include <SetupAPI.h>

#include "Error.h"
#include "ClassInfo.h"

namespace playground {
	class ClassInfoList
	{
	private:

	public:
		// Constructor
		// Creates a ClassInfoList that includes all classes
		ClassInfoList();

		// Returns a list of device interfaces in the set
		std::vector<std::shared_ptr<ClassInfo>> EnumerateClasses() const;

		virtual ~ClassInfoList();
	};
}
