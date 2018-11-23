#include "stdafx.h"
#include "MsiApiWrapper.h"

using namespace System;
using namespace System::Collections;
using namespace System::Collections::Generic;
using namespace WinScoutNativeWrapper;

// Default constructor
MsiApiWrapper::MsiApiWrapper() {}

// Returns a list of installed products, and their properties
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
			InstalledProduct^ installedProduct = gcnew InstalledProduct();
			installedProduct->ProductCode = gcnew System::String(szInstalledProductCode);

			// Try to get the product name
			try {
				installedProduct->ProductName = GetInstalledProductProperty(
					szInstalledProductCode, (cchSid == 0 ? nullptr : szSid), dwInstalledContext,
					INSTALLPROPERTY_INSTALLEDPRODUCTNAME);
			}
			catch (Exception^ ex) {
				installedProduct->ProductName = gcnew System::String(INSTALLED_PRODUCT_UNKNOWN_PROPERTY);
			}

			installedProducts->Add(installedProduct);
			dwIndex++;
		}
		else {
			switch (ret) {
				case ERROR_ACCESS_DENIED:
					throw gcnew Exception("MsiEnumProductsEx returned ERROR_ACCESS_DENIED");
				case ERROR_BAD_CONFIGURATION:
					throw gcnew Exception("MsiEnumProductsEx returned ERROR_BAD_CONFIGURATION");
				case ERROR_INVALID_PARAMETER:
					throw gcnew Exception("MsiEnumProductsEx returned ERROR_INVALID_PARAMETER");
				case ERROR_NO_MORE_ITEMS:
					// This is the expected completion of the loop
					break;
				case ERROR_MORE_DATA:
					throw gcnew Exception("MsiEnumProductsEx returned ERROR_MORE_DATA");
				case ERROR_UNKNOWN_PRODUCT:
					throw gcnew Exception("MsiEnumProductsEx returned ERROR_UNKNOWN_PRODUCT");
				case ERROR_FUNCTION_FAILED:
					throw gcnew Exception("MsiEnumProductsEx returned ERROR_FUNCTION_FAILED");
				default:
					throw gcnew Exception("Unknown return value from MsiEnumProductsEx");
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
	switch (ret) {
		case ERROR_ACCESS_DENIED:
			throw gcnew Exception("MsiGetProductInfoEx returned ERROR_ACCESS_DENIED");
		case ERROR_BAD_CONFIGURATION:
			throw gcnew Exception("MsiGetProductInfoEx returned ERROR_BAD_CONFIGURATION");
		case ERROR_INVALID_PARAMETER:
			throw gcnew Exception("MsiGetProductInfoEx returned ERROR_INVALID_PARAMETER");
		case ERROR_MORE_DATA:
			throw gcnew Exception("MsiGetProductInfoEx returned ERROR_MORE_DATA");
		case ERROR_UNKNOWN_PRODUCT:
			throw gcnew Exception("MsiGetProductInfoEx returned ERROR_UNKNOWN_PRODUCT");
		case ERROR_UNKNOWN_PROPERTY:
			throw gcnew Exception("MsiGetProductInfoEx returned ERROR_UNKNOWN_PROPERTY");
		case ERROR_FUNCTION_FAILED:
			throw gcnew Exception("MsiGetProductInfoEx returned ERROR_FUNCTION_FAILED");
		default:
			throw gcnew Exception("Unknown return value from MsiGetProductInfoEx");
	}
}
