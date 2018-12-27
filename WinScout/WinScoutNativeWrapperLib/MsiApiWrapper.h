#pragma once
#include <windows.h>
#include <msi.h>

using namespace System;
using namespace System::Collections;
using namespace System::Collections::Generic;

#define INSTALLED_PRODUCT_UNKNOWN_PROPERTY	L"Unknown"

namespace WinScoutNativeWrapper {

	public enum MsiInstalledProductState {
		Unknown = 0,
		Advertised = 1,
		Installed = 5
	};

	public ref class MsiInstalledProduct {
	public:
		// Is the product installed, or just advertised?
		property MsiInstalledProductState ProductState;

		// The unique identifier for this product
		property System::String ^ProductCode;

		// The name of the product
		property System::String ^ProductName;

		// The version of the product
		property System::String ^ProductVersion;

		// The date the product was installer or updated or repaired
		property System::DateTime InstallDate;

		// Where is this program installed?
		property System::String ^InstallLocation;

		// Where was the program installed from?
		property System::String ^InstallSource;

		// The local package containing the installer
		property System::String ^LocalPackage;

		// The name of the publisher
		property System::String ^Publisher;
	};

	// Error codes returned by the MSI API wrapper


	public ref class MsiApiWrapper {
	public:
		// Default constructor
		MsiApiWrapper();

		// Returns information about the installed products in the given context
		List<MsiInstalledProduct ^>^ EnumInstalledProducts();

		// Returns the properties of a given product guid
		MsiInstalledProduct^ GetInstalledProductFromProductCode(System::String^ productCode);

	private:
		// Returns the properties of a given product guid
		MsiInstalledProduct^ GetInstalledProductFromProductCode(wchar_t* szProductCode);

		// Try to get the given property for the given product
		System::String^ GetInstalledProductProperty(wchar_t* szProductCode, wchar_t* szUserSid, MSIINSTALLCONTEXT dwInstalledContext, wchar_t* szProperty);
		System::String^ GetInstalledProductPropertyWithDefault(wchar_t* szProductCode, wchar_t* szUserSid, MSIINSTALLCONTEXT dwInstalledContext, wchar_t* szProperty, System::String^ defaultValue);
	};

}
