#include "stdafx.h"
#include "Windows.h"
#include "Msi.h"

using namespace System;
using namespace System::Collections;
using namespace System::Collections::Generic;

ref class InstalledProduct {
public:
	property System::String ^ProductCode;
};

int main(array<System::String ^> ^args)
{
	//if (args->Length == 0)
	//{
	//	Console::WriteLine("No arguments given.");
	//	return -1;
	//}

	//if (args[0] == "software")
	{
		List<InstalledProduct ^> ^installedProducts = gcnew List<InstalledProduct ^>();

		UINT ret;
		DWORD dwIndex = 0;
		const DWORD dwContext = MSIINSTALLCONTEXT_ALL;
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
				nullptr,
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
				Console::WriteLine("Enumerated Product " + dwIndex);

				InstalledProduct ^installedProduct = gcnew InstalledProduct();
				installedProduct->ProductCode = gcnew System::String(szInstalledProductCode);

				//wchar_t* name = MsiGetProductInfoEx(
				//	szInstalledProductCode,
				//	cchSid == 0 ? NULL : szSid,
				//	dwInstalledContext,
				//	INSTALLPROPERTY_INSTALLEDPRODUCTNAME
				//);

				//wchar_t* version = MsiGetProductInfoEx(
				//	szInstalledProductCode,
				//	cchSid == 0 ? NULL : szSid,
				//	dwInstalledContext,
				//	INSTALLPROPERTY_VERSIONSTRING
				//);

				Console::WriteLine(installedProduct->ProductCode);

				dwIndex++;
			} else {
				switch (ret) {
					case ERROR_ACCESS_DENIED:
						Console::WriteLine("MsiEnumProductsEx returned ERROR_ACCESS_DENIED");
						break;
					case ERROR_BAD_CONFIGURATION:
						Console::WriteLine("MsiEnumProductsEx returned ERROR_BAD_CONFIGURATION");
						break;
					case ERROR_INVALID_PARAMETER:
						Console::WriteLine("MsiEnumProductsEx returned ERROR_INVALID_PARAMETER");
						break;
					case ERROR_NO_MORE_ITEMS:
						Console::WriteLine("MsiEnumProductsEx returned ERROR_NO_MORE_ITEMS");
						break;
					case ERROR_MORE_DATA:
						Console::WriteLine("MsiEnumProductsEx returned ERROR_MORE_DATA");
						break;
					case ERROR_UNKNOWN_PRODUCT:
						Console::WriteLine("MsiEnumProductsEx returned ERROR_UNKNOWN_PRODUCT");
						break;
					case ERROR_FUNCTION_FAILED:
						Console::WriteLine("MsiEnumProductsEx returned ERROR_FUNCTION_FAILED");
						break;
					default:
						Console::WriteLine("Unknown return value from MsiEnumProductsEx");
						break;
				}
			}

		} while (ret == ERROR_SUCCESS);
	}


	return 0;
}
