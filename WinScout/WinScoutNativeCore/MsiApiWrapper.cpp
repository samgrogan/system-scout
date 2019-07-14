#include "stdafx.h"
#include "MsiApiWrapper.h"

using namespace System;
using namespace System::Collections;
using namespace System::Collections::Generic;
using namespace WinScoutNativeWrapper;

// Default constructor
MsiApiWrapper::MsiApiWrapper() {}

// Returns information about the installed products in the given context
List<MsiInstalledProduct ^>^ MsiApiWrapper::EnumInstalledProducts(MsiInstalledProductContext context) {
	// Id of the special "everyone" user
	// https://docs.microsoft.com/en-us/windows/desktop/api/msi/nf-msi-msienumproductsexw
	const wchar_t* szAllUsersSid = L"s-1-1-0";

	// Based on the requested context, pass the correct flags to the enum function
	switch (context) {
		case MsiInstalledProductContext::AllUsers:
			return this->EnumInstalledProducts(szAllUsersSid, MSIINSTALLCONTEXT_ALL);
		case MsiInstalledProductContext::PerMachine:
			return this->EnumInstalledProducts(nullptr, MSIINSTALLCONTEXT_MACHINE);
		case MsiInstalledProductContext::CurrentUser:
		default:
			return this->EnumInstalledProducts(nullptr, MSIINSTALLCONTEXT_ALL);
	}
}

List<MsiInstalledProduct ^>^ MsiApiWrapper::EnumInstalledProducts(const wchar_t* szUserSid, const DWORD dwContext) {

	// List of installed products to return
	List<MsiInstalledProduct ^>^ installedProducts = gcnew List<MsiInstalledProduct ^>();

	// Values to
	UINT result;

	DWORD dwIndex = 0;
	wchar_t szInstalledProductCode[39];
	MSIINSTALLCONTEXT dwInstalledContext;

	wchar_t szSid[128] = {0};
	DWORD cchSid;

	do {
		memset(szInstalledProductCode, 0, sizeof(szInstalledProductCode));
		cchSid = sizeof(szSid) / sizeof(szSid[0]);

		result = MsiEnumProductsEx(
			nullptr,
			szUserSid,
			dwContext,
			dwIndex,
			szInstalledProductCode,
			&dwInstalledContext,
			szSid,
			&cchSid
		);

		if (result == ERROR_SUCCESS) {
			// Read the properties of the product based on the GUID
			MsiInstalledProduct^ installedProduct = this->GetInstalledProductFromProductCode(szInstalledProductCode, (cchSid == 0 ? nullptr : szSid), dwInstalledContext);

			// Add to the list of products to return
			if (installedProduct != nullptr) {
				installedProducts->Add(installedProduct);
			}
			dwIndex++;
		}
		else {
			switch (result) {
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
	while (result == ERROR_SUCCESS);

	return installedProducts;
}

// Returns the properties of a given product guid
MsiInstalledProduct^ MsiApiWrapper::GetInstalledProductFromProductCode(wchar_t* szProductCode, wchar_t* szUserSid, MSIINSTALLCONTEXT dwInstalledContext) {
	System::String^ defaultValue = gcnew System::String(INSTALLED_PRODUCT_UNKNOWN_PROPERTY);

	// Make sure the product is installed
	// Product State
	System::String^ productState = this->GetInstalledProductPropertyWithDefault(szProductCode, szUserSid, dwInstalledContext, INSTALLPROPERTY_PRODUCTSTATE, defaultValue);
	if (productState != "5") {
		return nullptr;
	}

	// Create a new object to hold the properties
	MsiInstalledProduct^ installedProduct = gcnew MsiInstalledProduct();

	// Try to get the properties of the product

	// Product Code
	installedProduct->ProductCode = gcnew System::String(szProductCode);

	// Product Name
	installedProduct->ProductName = this->GetInstalledProductPropertyWithDefault(szProductCode, szUserSid, dwInstalledContext, INSTALLPROPERTY_INSTALLEDPRODUCTNAME, defaultValue);

	// Version
	installedProduct->ProductVersion = this->GetInstalledProductPropertyWithDefault(szProductCode, szUserSid, dwInstalledContext, INSTALLPROPERTY_VERSIONSTRING, defaultValue);

	// Install Date
	System::String^ installDateString = this->GetInstalledProductPropertyWithDefault(szProductCode, szUserSid, dwInstalledContext, INSTALLPROPERTY_INSTALLDATE, defaultValue);
	DateTime installDate;
	System::DateTime::TryParseExact(installDateString, "yyyyMMdd", gcnew Globalization::CultureInfo("en-US"), Globalization::DateTimeStyles::None, installDate);
	installedProduct->InstallDate = installDate;

	// Location
	installedProduct->InstallLocation = this->GetInstalledProductPropertyWithDefault(szProductCode, szUserSid, dwInstalledContext, INSTALLPROPERTY_INSTALLLOCATION, defaultValue);

	// Source
	installedProduct->InstallSource = this->GetInstalledProductPropertyWithDefault(szProductCode, szUserSid, dwInstalledContext, INSTALLPROPERTY_INSTALLSOURCE, defaultValue);

	// Local Package
	installedProduct->LocalPackage = this->GetInstalledProductPropertyWithDefault(szProductCode, szUserSid, dwInstalledContext, INSTALLPROPERTY_LOCALPACKAGE, defaultValue);

	// Package Name
	installedProduct->PackageName = this->GetInstalledProductPropertyWithDefault(szProductCode, szUserSid, dwInstalledContext, INSTALLPROPERTY_PRODUCTNAME, defaultValue);

	// Package Code
	installedProduct->PackageCode = this->GetInstalledProductPropertyWithDefault(szProductCode, szUserSid, dwInstalledContext, INSTALLPROPERTY_PACKAGECODE, defaultValue);

	// Language
	installedProduct->Language = this->GetInstalledProductPropertyWithDefault(szProductCode, szUserSid, dwInstalledContext, INSTALLPROPERTY_INSTALLEDLANGUAGE, defaultValue);


	// Publisher
	installedProduct->Publisher = this->GetInstalledProductPropertyWithDefault(szProductCode, szUserSid, dwInstalledContext, INSTALLPROPERTY_PUBLISHER, defaultValue);

	return installedProduct;
}

// Returns the requested of a given product guid or the default value if it can't be read
System::String^ MsiApiWrapper::GetInstalledProductPropertyWithDefault(wchar_t* szProductCode, wchar_t* szUserSid, MSIINSTALLCONTEXT dwInstalledContext, wchar_t* szProperty, System::String^ defaultValue) {
	try {
		return this->GetInstalledProductProperty(szProductCode, szUserSid, dwInstalledContext, szProperty);
	}
	catch (Exception^) {
		return defaultValue;
	}
}

// Returns the given property of a product guid as string
System::String^ MsiApiWrapper::GetInstalledProductProperty(wchar_t* szProductCode, wchar_t* szUserSid, MSIINSTALLCONTEXT dwInstalledContext, wchar_t* szProperty) {

	DWORD value_length = 1024; // TODO: Retreive correct length
	wchar_t value[1024] = {0};

	const UINT result = MsiGetProductInfoEx(
		szProductCode,
		szUserSid,
		dwInstalledContext,
		szProperty,
		value,
		&value_length
	);

	if (result == ERROR_SUCCESS) {
		return gcnew System::String(value);
	}
	switch (result) {
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
