#include "stdafx.h"
#include "MsiApiWrapper.h"

using namespace System;
using namespace System::Collections;
using namespace System::Collections::Generic;
using namespace WinScoutNativeWrapper;

WinScoutNativeWrapper::MsiApiWrapper::MsiApiWrapper()
{
}

List<InstalledProduct ^> ^WinScoutNativeWrapper::MsiApiWrapper::EnumInstalledProducts() {
	return nullptr;
}
