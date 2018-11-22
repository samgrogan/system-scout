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
		MsiApiWrapper();

		List<InstalledProduct ^> ^EnumInstalledProducts();
	};

}
