#include "stdafx.h"
#include "MsiApiWrapper.h"

using namespace System;
using namespace System::Collections;
using namespace System::Collections::Generic;
using namespace WinScoutNativeWrapper;

MsiApiWrapper::MsiApiWrapper() {
}

List<InstalledProduct ^>^ MsiApiWrapper::EnumInstalledProducts() {
	// List of installed products to return
	List<InstalledProduct ^>^ installedProducts = gcnew List<InstalledProduct ^>();

	UINT ret;
	DWORD dwIndex = 0;
	const DWORD dwContext = MSIINSTALLCONTEXT_ALL;
	wchar_t szInstalledProductCode[39] = {0};
	wchar_t szSid[128] = {0};
	const wchar_t* szUserSid = L"s-1-1-0";
	DWORD cchSid;
	MSIINSTALLCONTEXT dwInstalledContext;

	do {
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

		if (ret == ERROR_SUCCESS) {
			Console::WriteLine("Enumerated Product " + dwIndex);

			InstalledProduct^ installedProduct = gcnew InstalledProduct();
			installedProduct->ProductCode = gcnew System::String(szInstalledProductCode);
			installedProduct->ProductName = GetInstalledProductProperty(
				szInstalledProductCode, (cchSid == 0 ? NULL : szSid), dwInstalledContext,
				INSTALLPROPERTY_INSTALLEDPRODUCTNAME);

			Console::WriteLine(installedProduct->ProductCode + L"|" + installedProduct->ProductName);

			dwIndex++;
		}
		else {
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
	}
	while (ret == ERROR_SUCCESS);

	return installedProducts;
}

// Returns the given property as string
System::String^ MsiApiWrapper::GetInstalledProductProperty(wchar_t* szProductCode, wchar_t* szUserSid,
                                                           MSIINSTALLCONTEXT dwInstalledContext, wchar_t* szProperty) {
	DWORD value_length = 1024;
	wchar_t value[1024] = {0};

	UINT ret = MsiGetProductInfoEx(
		szProductCode,
		szUserSid,
		dwInstalledContext,
		szProperty,
		value,
		&value_length
	);

	if (ret == ERROR_SUCCESS) {
		return gcnew System::String(value);
	}
	else {
		switch (ret) {
		case ERROR_ACCESS_DENIED:
			Console::WriteLine("MsiGetProductInfoEx returned ERROR_ACCESS_DENIED");
			break;
		case ERROR_BAD_CONFIGURATION:
			Console::WriteLine("MsiGetProductInfoEx returned ERROR_BAD_CONFIGURATION");
			break;
		case ERROR_INVALID_PARAMETER:
			Console::WriteLine("MsiGetProductInfoEx returned ERROR_INVALID_PARAMETER");
			break;
		case ERROR_MORE_DATA:
			Console::WriteLine("MsiGetProductInfoEx returned ERROR_MORE_DATA");
			break;
		case ERROR_SUCCESS:
			Console::WriteLine("MsiGetProductInfoEx returned ERROR_SUCCESS");
			break;
		case ERROR_UNKNOWN_PRODUCT:
			Console::WriteLine("MsiGetProductInfoEx returned ERROR_UNKNOWN_PRODUCT");
			break;
		case ERROR_UNKNOWN_PROPERTY:
			Console::WriteLine("MsiGetProductInfoEx returned ERROR_UNKNOWN_PROPERTY");
			break;
		case ERROR_FUNCTION_FAILED:
			Console::WriteLine("MsiGetProductInfoEx returned ERROR_FUNCTION_FAILED");
			break;
		default:
			Console::WriteLine("Unknown return value from MsiGetProductInfoEx");
			break;
		}
	}

	return nullptr;
}
