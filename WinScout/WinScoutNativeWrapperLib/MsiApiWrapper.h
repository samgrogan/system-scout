#pragma once
#include <windows.h>
#include <msi.h>

using namespace System;
using namespace System::Collections;
using namespace System::Collections::Generic;

#define INSTALLED_PRODUCT_UNKNOWN_PROPERTY	L"Unknown"

namespace WinScoutNativeWrapper {

	public ref class MsiInstalledProduct {
	public:
		property System::String ^ProductCode;
		property System::String ^ProductName;
	};

	public ref class MsiApiWrapper {
	public:
		// Default constructor
		MsiApiWrapper();

		// Returns information about the installed products in the given context
		List<MsiInstalledProduct ^>^ EnumInstalledProducts();
		List<MsiInstalledProduct ^>^ EnumInstalledProducts();


		// Returns the properties of a given product guid
		MsiInstalledProduct^ GetInstalledProductFromProductCode(wchar_t* szProductCode);
		MsiInstalledProduct^ GetInstalledProductFromProductCode(System::String^ productCode);

	private:
		// Try to get the given property for the given product
		System::String^ GetInstalledProductProperty(wchar_t* szProductCode, wchar_t* szUserSid, MSIINSTALLCONTEXT dwInstalledContext, wchar_t* szProperty);
		System::String^ GetInstalledProductPropertyWithDefault(wchar_t* szProductCode, wchar_t* szUserSid, MSIINSTALLCONTEXT dwInstalledContext, wchar_t* szProperty, System::String defaultValue);
	};

}
