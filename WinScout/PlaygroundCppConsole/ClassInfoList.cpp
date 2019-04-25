#include "ClassInfoList.h"

using namespace playground;

ClassInfoList::ClassInfoList()
{
}

// Returns a list of device interfaces in the set
std::vector<std::shared_ptr<ClassInfo>> ClassInfoList::EnumerateClasses() {
	// Create a vector to hold the interfaces
	std::vector<std::shared_ptr<ClassInfo>> classes;

	return classes;
}

ClassInfoList::~ClassInfoList()
{
}
