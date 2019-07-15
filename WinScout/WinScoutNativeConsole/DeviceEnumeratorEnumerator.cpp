#include "DeviceEnumeratorEnumerator.h"

using namespace WinScoutNativeCore;

DeviceEnumeratorEnumerator::DeviceEnumeratorEnumerator() = default;

// Returns a list of device enumerators
std::vector<std::shared_ptr<DeviceEnumerator>> DeviceEnumeratorEnumerator::EnumerateEnumerators() const {
	std::vector<std::shared_ptr<DeviceEnumerator>> enumerators;

	ULONG index = 0;
	wchar_t buffer[MAX_DEVICE_ID_LEN];
	ULONG length = MAX_DEVICE_ID_LEN;
	while (CM_Enumerate_Enumerators(index, buffer, &length, 0) != CR_NO_SUCH_VALUE)
	{
		// Does the buffer contain anything?
		if (wcslen(buffer) > 0) {
			std::shared_ptr<DeviceEnumerator> enumerator = std::make_shared<DeviceEnumerator>(DeviceEnumerator(buffer, CM_GETIDLIST_FILTER_ENUMERATOR));
			enumerators.push_back(enumerator);
		}

		index++;
	}

	return enumerators;
}

DeviceEnumeratorEnumerator::~DeviceEnumeratorEnumerator() = default;
