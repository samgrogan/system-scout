#include "DeviceEnumeratorEnumerator.h"

using namespace WinScoutNativeCore;

DeviceEnumeratorEnumerator::DeviceEnumeratorEnumerator() = default;

// Returns a list of device enumerators
std::vector<std::shared_ptr<DeviceEnumerator>> DeviceEnumeratorEnumerator::EnumerateEnumerators() const {
	std::vector<std::shared_ptr<DeviceEnumerator>> enumerators;




	return enumerators;
}

DeviceEnumeratorEnumerator::~DeviceEnumeratorEnumerator() = default;
