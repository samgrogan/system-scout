#include "Extensions.h"

// Based on https://stackoverflow.com/questions/1672677/print-a-guid-variable

#define GUID_FORMAT "%08lX-%04hX-%04hX-%02hhX%02hhX-%02hhX%02hhX%02hhX%02hhX%02hhX%02hhX"
#define GUID_ARG(guid) guid.Data1, guid.Data2, guid.Data3, guid.Data4[0], guid.Data4[1], guid.Data4[2], guid.Data4[3], guid.Data4[4], guid.Data4[5], guid.Data4[6], guid.Data4[7]

std::wostream& operator<<(std::wostream& wos, REFGUID guid)
{
	wchar_t szGUID[64] = {0};
	if (StringFromGUID2(guid, szGUID, 64))
	{
		wos << szGUID;
	}

	return wos;
}