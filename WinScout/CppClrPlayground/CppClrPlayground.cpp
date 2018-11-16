#include "stdafx.h"
#include "Windows.h";
#include "Msi.h";

using namespace System;

int main(array<System::String ^> ^args)
{
	if (args->Length == 0)
	{
		Console::WriteLine("No arguments given.");
		return -1;
	}

	if (args[0] == "software")
	{
		UINT ret;
		DWORD dwIndex = 0;
		DWORD dwContext = MSIINSTALLCONTEXT_ALL;
		wchar_t szInstalledProductCode[39] = { 0 };
		wchar_t szSid[128] = { 0 };
		const wchar_t* szUserSid = L"s-1-1-0";
		DWORD cchSid;
		MSIINSTALLCONTEXT dwInstalledContext;

		do
		{
			memset(szInstalledProductCode, 0, sizeof(szInstalledProductCode));
			cchSid = sizeof(szSid) / sizeof(szSid[0]);

			ret = MsiEnumProductsEx(
				NULL,
				szUserSid,
				dwContext,
				dwIndex,
				szInstalledProductCode,
				&dwInstalledContext,
				szSid,
				&cchSid
			);

			if (ret == ERROR_SUCCESS)
			{
				char* name = MsiGetProductInfoEx(
					szInstalledProductCode,
					cchSid == 0 ? NULL : szSid,
					dwInstalledContext,
					INSTALLPROPERTY_INSTALLEDPRODUCTNAME
				);

				char* version = MsiGetProductInfoEx(
					szInstalledProductCode,
					cchSid == 0 ? NULL : szSid,
					dwInstalledContext,
					INSTALLPROPERTY_VERSIONSTRING
				);

				cout << name << endl;
				cout << "  - " << version << endl;

				dwIndex++;
			}

		} while (ret == ERROR_SUCCESS);
	}


	return 0;
}
