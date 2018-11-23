#pragma once
#include <windows.h>
#include <msi.h>

using namespace System;
using namespace System::Collections;
using namespace System::Collections::Generic;

namespace WinScoutNativeWrapper {

	ref class InstalledProduct {
	public:
		property System::String ^ProductCode;
		property System::String ^ProductName;
	};

	ref class MsiApiWrapper {
	public:
		// Default constructor
		MsiApiWrapper();

		// Returns information about the installed products in the given context
		List<InstalledProduct ^>^ EnumInstalledProducts();

	private:
		System::String^ GetInstalledProductProperty(wchar_t* szProductCode, wchar_t* szUserSid, MSIINSTALLCONTEXT dwInstalledContext, wchar_t* szProperty);
	};

}
